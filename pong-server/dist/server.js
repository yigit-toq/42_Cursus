"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const ws_1 = require("ws");
const uuid_1 = require("uuid");
const Player_1 = require("./core/Player");
const GameRoom_1 = require("./core/GameRoom");
const MessageTypes_1 = require("./network/MessageTypes");
class PongServer {
    wss;
    players = new Map();
    gameRooms = new Map();
    waitingPlayers = [];
    port;
    constructor(port = 8080) {
        this.port = port;
        this.wss = new ws_1.WebSocketServer({ port });
        this.setupServer();
    }
    setupServer() {
        this.wss.on('connection', (socket) => {
            this.handleConnection(socket);
        });
        this.wss.on('error', (error) => {
            console.error('❌ WebSocket Server Error:', error);
        });
        console.log(`🚀 Pong Server running on ws://localhost:${this.port}`);
    }
    handleConnection(socket) {
        const playerId = (0, uuid_1.v4)();
        const player = new Player_1.Player(playerId, socket);
        this.players.set(playerId, player);
        console.log(`🔗 Player connected: ${playerId}`);
        const welcomeMessage = {
            type: MessageTypes_1.ServerMessageType.WELCOME,
            playerId: playerId,
            serverTime: Date.now()
        };
        player.send(welcomeMessage);
        socket.on('message', (data) => {
            this.handleMessage(player, data);
        });
        socket.on('close', () => {
            this.handleDisconnect(player);
        });
        socket.on('error', (error) => {
            console.error(`❌ Socket error for player ${playerId}:`, error);
        });
    }
    handleMessage(player, data) {
        try {
            const message = JSON.parse(data.toString());
            switch (message.type) {
                case MessageTypes_1.ClientMessageType.CONNECT:
                    if (message.playerName) {
                        player.name = message.playerName;
                        console.log(`👤 Player ${player.id} set name: ${player.name}`);
                    }
                    break;
                case MessageTypes_1.ClientMessageType.FIND_MATCH:
                    this.handleFindMatch(player);
                    break;
                case MessageTypes_1.ClientMessageType.INPUT:
                    this.handleInput(player, message.input.vertical);
                    break;
                case MessageTypes_1.ClientMessageType.PING:
                    player.lastPing = Date.now();
                    player.send({
                        type: MessageTypes_1.ServerMessageType.PONG,
                        timestamp: message.timestamp
                    });
                    break;
                default:
                    console.warn(`⚠️  Unknown message type from ${player.id}`);
            }
        }
        catch (error) {
            console.error(`❌ Error parsing message from ${player.id}:`, error);
            this.sendError(player, 'Invalid message format');
        }
    }
    handleFindMatch(player) {
        console.log(`🔍 Player ${player.name} is looking for a match...`);
        if (player.roomID) {
            console.warn(`⚠️  Player ${player.name} already in room ${player.roomID}`);
            return;
        }
        if (this.waitingPlayers.includes(player)) {
            console.warn(`⚠️  Player ${player.name} already waiting`);
            return;
        }
        if (this.waitingPlayers.length > 0) {
            const opponent = this.waitingPlayers.shift();
            this.createMatch(player, opponent);
        }
        else {
            this.waitingPlayers.push(player);
            console.log(`⏳ Player ${player.name} added to waiting list (${this.waitingPlayers.length} waiting)`);
        }
    }
    createMatch(player1, player2) {
        const roomID = (0, uuid_1.v4)();
        const room = new GameRoom_1.GameRoom(roomID);
        room.addPlayer(player1);
        room.addPlayer(player2);
        this.gameRooms.set(roomID, room);
        console.log(`🎮 Match created: ${player1.name} vs ${player2.name} (Room: ${roomID})`);
    }
    handleInput(player, vertical) {
        player.updateInput(vertical);
    }
    handleDisconnect(player) {
        console.log(`👋 Player disconnected: ${player.name} (${player.id})`);
        // Remove from waiting list
        const waitingIndex = this.waitingPlayers.indexOf(player);
        if (waitingIndex !== -1) {
            this.waitingPlayers.splice(waitingIndex, 1);
        }
        // Remove from room
        if (player.roomID) {
            const room = this.gameRooms.get(player.roomID);
            if (room) {
                room.removePlayer(player.id);
                // Delete room if empty
                if (room.isEmpty()) {
                    room.dispose();
                    this.gameRooms.delete(player.roomID);
                    console.log(`🗑️  Room ${player.roomID} deleted (empty)`);
                }
            }
        }
        this.players.delete(player.id);
    }
    sendError(player, message) {
        const errorMessage = {
            type: MessageTypes_1.ServerMessageType.ERROR,
            message
        };
        player.send(errorMessage);
    }
    getStats() {
        console.log('\n📊 Server Stats:');
        console.log(`   Players: ${this.players.size}`);
        console.log(`   Waiting: ${this.waitingPlayers.length}`);
        console.log(`   Rooms  : ${this.gameRooms.size}`);
        console.log('');
    }
}
const server = new PongServer(8080);
setInterval(() => {
    server.getStats();
}, 30000);
process.on('SIGINT', () => {
    console.log('\n👋 Shutting down server...');
    process.exit(0);
});
//# sourceMappingURL=server.js.map