"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.GameRoom = void 0;
const MessageTypes_1 = require("../network/MessageTypes");
const GameState_1 = require("../game/GameState");
class GameRoom {
    id;
    player1 = null;
    player2 = null;
    isActive = false;
    tickRate = 60;
    tickCount = 0;
    gameState;
    lastTickTime = Date.now();
    tickInterval = null;
    constructor(id) {
        this.id = id;
        this.gameState = new GameState_1.GameState();
    }
    addPlayer(player) {
        if (!this.player1) {
            this.player1 = player;
            player.roomID = this.id;
            player.playerN = 1;
            console.log(`🎮 Player ${player.name} joined room ${this.id} as Player 1`);
            return true;
        }
        else if (!this.player2) {
            this.player2 = player;
            player.roomID = this.id;
            player.playerN = 2;
            console.log(`🎮 Player ${player.name} joined room ${this.id} as Player 2`);
            this.startGame();
            return true;
        }
        return false;
    }
    removePlayer(playerId) {
        if (this.player1?.id === playerId) {
            console.log(`👋 Player 1 (${this.player1.name}) left room ${this.id}`);
            this.player1 = null;
        }
        if (this.player2?.id === playerId) {
            console.log(`👋 Player 2 (${this.player2.name}) left room ${this.id}`);
            this.player2 = null;
        }
        if (this.isActive) {
            this.stopGame();
            this.notifyOpponentDisconnected();
        }
    }
    isEmpty() {
        return !this.player1 && !this.player2;
    }
    isFull() {
        return !!this.player1 && !!this.player2;
    }
    startGame() {
        if (!this.player1 || !this.player2) {
            console.error('❌ Cannot start game: Room not full');
            return;
        }
        console.log(`🎮 Starting game in room ${this.id}`);
        this.isActive = true;
        this.gameState.reset();
        this.lastTickTime = Date.now();
        this.player1.send({
            type: MessageTypes_1.ServerMessageType.MATCH_FOUND,
            roomId: this.id,
            playerNumber: 1,
            opponentName: this.player2.name
        });
        this.player2.send({
            type: MessageTypes_1.ServerMessageType.MATCH_FOUND,
            roomId: this.id,
            playerNumber: 2,
            opponentName: this.player1.name
        });
        this.startGameLoop();
    }
    startGameLoop() {
        const tickDuration = 1000 / this.tickRate; // ms per tick
        this.tickInterval = setInterval(() => {
            this.tick();
        }, tickDuration);
        console.log(`⏱️  Game loop started (${this.tickRate} ticks/sec)`);
    }
    tick() {
        if (!this.isActive || !this.player1 || !this.player2)
            return;
        const now = Date.now();
        const deltaTime = (now - this.lastTickTime) / 1000;
        this.lastTickTime = now;
        if (this.tickCount < 10) // debug
         {
            console.log(`⏱️  Tick ${this.tickCount}: P1 input=${this.player1.input}, P2 input=${this.player2.input}`);
            this.tickCount++;
        }
        const player1Input = this.player1.input;
        const player2Input = this.player2.input;
        this.player1.paddlePos = this.gameState.paddle1Position;
        this.player2.paddlePos = this.gameState.paddle2Position;
        const previousScore = { ...this.gameState.score };
        this.gameState.update(deltaTime, { player1: player1Input, player2: player2Input });
        // Check for goals
        if (this.gameState.score.player1 !== previousScore.player1 ||
            this.gameState.score.player2 !== previousScore.player2) {
            this.handleGoal(previousScore);
        }
        if (this.gameState.isGameOver) {
            this.handleGameOver();
            return;
        }
        this.broadcastGameState();
    }
    broadcastGameState() {
        if (!this.player1 || !this.player2)
            return;
        const message = {
            type: MessageTypes_1.ServerMessageType.GAME_STATE,
            timestamp: Date.now(),
            ball: {
                position: {
                    x: this.gameState.ballPosition.x,
                    y: this.gameState.ballPosition.y,
                    z: this.gameState.ballPosition.z
                }
            },
            paddle1: {
                z: this.gameState.paddle1Position
            },
            paddle2: {
                z: this.gameState.paddle2Position
            },
            score: {
                player1: this.gameState.score.player1,
                player2: this.gameState.score.player2
            }
        };
        this.player1.send(message);
        this.player2.send(message);
    }
    handleGoal(previousScore) {
        if (!this.player1 || !this.player2)
            return;
        const scorer = this.gameState.score.player1 > previousScore.player1 ? 1 : 2;
        const message = {
            type: MessageTypes_1.ServerMessageType.GOAL_SCORED,
            scorer,
            score: {
                player1: this.gameState.score.player1,
                player2: this.gameState.score.player2
            }
        };
        this.player1.send(message);
        this.player2.send(message);
        console.log(`⚽ Goal! Player ${scorer} scored. Score: ${this.gameState.score.player1} - ${this.gameState.score.player2}`);
    }
    handleGameOver() {
        if (!this.player1 || !this.player2)
            return;
        const winner = this.gameState.score.player1 >= this.gameState.maxScore ? 1 : 2;
        const message = {
            type: MessageTypes_1.ServerMessageType.GAME_OVER,
            winner,
            finalScore: {
                player1: this.gameState.score.player1,
                player2: this.gameState.score.player2
            }
        };
        this.player1.send(message);
        this.player2.send(message);
        console.log(`🏆 Game Over! Player ${winner} wins! Final score: ${this.gameState.score.player1} - ${this.gameState.score.player2}`);
        this.stopGame();
    }
    notifyOpponentDisconnected() {
        const remainingPlayer = this.player1 || this.player2;
        if (remainingPlayer) {
            remainingPlayer.send({
                type: MessageTypes_1.ServerMessageType.OPPONENT_DISCND
            });
        }
    }
    stopGame() {
        if (this.tickInterval) {
            clearInterval(this.tickInterval);
            this.tickInterval = null;
        }
        this.isActive = false;
        console.log(`⏹️  Game stopped in room ${this.id}`);
    }
    dispose() {
        this.stopGame();
        this.player1 = null;
        this.player2 = null;
    }
}
exports.GameRoom = GameRoom;
//# sourceMappingURL=GameRoom.js.map