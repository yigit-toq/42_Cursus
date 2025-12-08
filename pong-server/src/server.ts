import { WebSocketServer, WebSocket } from 'ws';

import { v4 as uuidv4 } from 'uuid';

import { Player }	from './core/Player';
import { GameRoom }	from './core/GameRoom';
import {
    ClientMessageType,
    ServerMessageType,
	type ErrorMessage,
    type ClientMessage,
    type WelcomeMessage
} from './network/MessageTypes';

class PongServer
{
	private wss				: WebSocketServer;
	private players			: Map<string, Player>	= new Map();
	private gameRooms		: Map<string, GameRoom>	= new Map();

	private waitingPlayers	: Player[] = [];
	private port			: number;

	constructor(port: number = 8080)
	{
		this.port	= port;

		this.wss	= new WebSocketServer({ port });

		this.setupServer();
	}

	private setupServer(): void
	{
		this.wss.on('connection', (socket: WebSocket) =>
		{
			this.handleConnection(socket);
		});

		this.wss.on('error', (error) =>
		{
			console.error('❌ WebSocket Server Error:', error);
		});

		console.log(`🚀 Pong Server running on ws://localhost:${this.port}`);
	}

	private handleConnection(socket: WebSocket): void
	{
		const playerId	= uuidv4();

		const player	= new Player(playerId, socket);

		this.players.set(playerId, player);

		console.log		(`🔗 Player connected: ${playerId}`);

		const welcomeMessage: WelcomeMessage =
		{
			type		: ServerMessageType.WELCOME,

			playerId	: playerId,
			serverTime	: Date.now()
		};
		player.send(welcomeMessage);

		socket.on('message', (data: Buffer) =>
		{
			this.handleMessage		(player, data);
		});

		socket.on('close', () =>
		{
			this.handleDisconnect	(player);
		});

		socket.on('error', (error) =>
		{
			console.error(`❌ Socket error for player ${playerId}:`, error);
		});
	}

	private handleMessage(player: Player, data: Buffer): void
	{
		try
		{
			const message: ClientMessage = JSON.parse(data.toString());

			switch (message.type)
			{
				case ClientMessageType.CONNECT:
					if (message.playerName)
					{
						player.name = message.playerName;

						console.log(`👤 Player ${player.id} set name: ${player.name}`);
					}
					break;

				case ClientMessageType.FIND_MATCH:
					this.handleFindMatch(player);
					break;

				case ClientMessageType.INPUT:
					this.handleInput	(player, message.input.vertical);
					break;

				case ClientMessageType.PING:
					player.lastPing = Date.now();

					player.send({
						type: ServerMessageType.PONG,
						timestamp: message.timestamp
					});
					break;

				default:
					console.warn(`⚠️  Unknown message type from ${player.id}`);
			}
		}
		catch (error)
		{
			console.error	(`❌ Error parsing message from ${player.id}:`, error);

			this.sendError	(player, 'Invalid message format');
		}
	}

	private handleFindMatch(player: Player): void
	{
		console.log(`🔍 Player ${player.name} is looking for a match...`);

		if (player.roomID)
		{
			console.warn(`⚠️  Player ${player.name} already in room ${player.roomID}`);
			return ;
		}

		if (this.waitingPlayers.includes(player))
		{
			console.warn(`⚠️  Player ${player.name} already waiting`);
			return ;
		}

		if (this.waitingPlayers.length > 0)
		{
			const opponent = this.waitingPlayers.shift()!;

			this.createMatch(player, opponent);
		}
		else
		{
			this.waitingPlayers.push(player);

			console.log(`⏳ Player ${player.name} added to waiting list (${this.waitingPlayers.length} waiting)`);
		}
	}

	private createMatch(player1: Player, player2: Player): void
	{
		const roomID	= uuidv4();
		const room		= new GameRoom(roomID);

		room.addPlayer(player1);
		room.addPlayer(player2);

		this.gameRooms.set(roomID, room);

		console.log(`🎮 Match created: ${player1.name} vs ${player2.name} (Room: ${roomID})`);
	}

	private handleInput(player: Player, vertical: number): void
	{
		player.updateInput(vertical);
	}

	private handleDisconnect(player: Player): void
	{
		console.log(`👋 Player disconnected: ${player.name} (${player.id})`);

		// Remove from waiting list
		const waitingIndex = this.waitingPlayers.indexOf(player);

		if (waitingIndex !== -1)
		{
			this.waitingPlayers.splice(waitingIndex, 1);
		}

		// Remove from room
		if (player.roomID)
		{
			const room = this.gameRooms.get(player.roomID);

			if (room)
			{
				room.removePlayer(player.id);
				
				// Delete room if empty
				if (room.isEmpty())
				{
					room.dispose();

					this.gameRooms.delete	(player.roomID);

					console.log				(`🗑️  Room ${player.roomID} deleted (empty)`);
				}
			}
		}

		this.players.delete(player.id);
	}

	private sendError(player: Player, message: string): void
	{
		const errorMessage: ErrorMessage =
		{
			type: ServerMessageType.ERROR,
			message
		};

		player.send(errorMessage);
	}

	public getStats(): void
	{
		console.log('\n📊 Server Stats:');
		console.log(`   Players: ${this.players.size}`);
		console.log(`   Waiting: ${this.waitingPlayers.length}`);
		console.log(`   Rooms  : ${this.gameRooms.size}`);
		console.log('');
	}
}

const server = new PongServer(8080);

setInterval(() =>
{
	server.getStats();
}, 30000);

process.on('SIGINT', () =>
{
	console.log	('\n👋 Shutting down server...');
	process.exit(0);
});
