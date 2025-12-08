import { Player } from './Player';
import { GameState } from '../game/GameState';
import { ServerMessageType, type GameStateMessage, type GoalScoredMessage, type GameOverMessage } from '../network/MessageTypes';

export class GameRoom
{
	public	id			: string;

	public	player1		: Player | null = null;
	public	player2		: Player | null = null;

	public	isActive	: boolean = false;

	public	gameState	: GameState;

	public	tickRate	: number = 60;

	private	tickInterval: NodeJS.Timeout | null = null;
	private	lastTickTime: number = Date.now();

	constructor (id: string)
	{
		this.id = id;

		this.gameState = new GameState();
	}

	public addPlayer(player: Player): boolean
	{
		if (!this.player1)
		{
			this.player1	= player;
			player.roomID	= this.id;
			player.playerN	= 1;

			console.log(`🎮 Player ${player.name} joined room ${this.id} as Player 1`);
			return true;
		}
		else if (!this.player2)
		{
			this.player2	= player;
			player.roomID	= this.id;
			player.playerN	= 2;

			console.log(`🎮 Player ${player.name} joined room ${this.id} as Player 2`);
			return true;
		}

		return false;
	}

	public removePlayer(playerId: string): void
	{
		if (this.player1?.id === playerId)
		{
			console.log(`👋 Player 1 (${this.player1.name}) left room ${this.id}`);
			this.player1 = null;
		}
		if (this.player2?.id === playerId)
		{
			console.log(`👋 Player 2 (${this.player2.name}) left room ${this.id}`);
			this.player2 = null;
		}

		// Stop game if any player disconnects
		if (this.isActive)
		{
			this.stopGame();

			this.notifyOpponentDisconnected();
		}
	}

	public isEmpty(): boolean
	{
		return  !this.player1 &&  !this.player2;
	}

	public isFull(): boolean
	{
		return !!this.player1 && !!this.player2;
	}

	private startGame(): void
	{
		if (!this.player1 || !this.player2)
		{
			console.error('❌ Cannot start game: Room not full');
			return ;
		}

		console.log(`🎮 Starting game in room ${this.id}`);

		this.isActive		= true;

		this.gameState.reset();

		this.lastTickTime	= Date.now();

		this.player1.send({
			type		: ServerMessageType.MATCH_FOUND,
			roomId		: this.id,
			playerNumber: 1,
			opponentName: this.player2.name
		});

		this.player2.send({
			type		: ServerMessageType.MATCH_FOUND,
			roomId		: this.id,
			playerNumber: 2,
			opponentName: this.player1.name
		});

		this.startGameLoop();
	}

	private startGameLoop(): void
	{
		const tickDuration = 1000 / this.tickRate; // ms per tick

		this.tickInterval = setInterval(() => {
			this.tick();
		}, tickDuration);

		console.log(`⏱️  Game loop started (${this.tickRate} ticks/sec)`);
	}

	private tick(): void
	{
		if (!this.isActive || !this.player1 || !this.player2) return ;

		const now		= Date.now();
		const deltaTime	= (now - this.lastTickTime) / 1000; // Convert to seconds

		this.lastTickTime = now;

		const player1Input = this.player1.input;
		const player2Input = this.player2.input;

		this.player1.paddlePos = this.gameState.paddle1Position;
		this.player2.paddlePos = this.gameState.paddle2Position;

		const prevScore = { ...this.gameState.score };

		this.gameState.update(deltaTime, {player1: player1Input, player2: player2Input});

		if (
			this.gameState.score.player1 !== prevScore.player1 ||
			this.gameState.score.player2 !== prevScore.player2
		)
		{
			this.handleGoal(prevScore);
		}

		if (this.gameState.isGameOver)
		{
			this.handleGameOver();

			return ;
		}

		this.broadcastGameState();
	}

	private broadcastGameState(): void
	{
		if (!this.player1 || !this.player2) return ;

		const message: GameStateMessage =
		{
			type: ServerMessageType.GAME_STATE,
			timestamp: Date.now(),

			ball:
			{
				position:
				{
					x: this.gameState.ballPosition.x,
					y: this.gameState.ballPosition.y,
					z: this.gameState.ballPosition.z
				}
			},

			paddle1:
			{
				z: this.gameState.paddle1Position
			},
			paddle2:
			{
				z: this.gameState.paddle2Position
			},

			score:
			{
				player1: this.gameState.score.player1,
				player2: this.gameState.score.player2
			}
		};

		this.player1.send(message);
		this.player2.send(message);
	}

	private handleGoal(previousScore: { player1: number; player2: number }): void
	{
		if (!this.player1 || !this.player2) return ;

		const scorer = this.gameState.score.player1 > previousScore.player1 ? 1 : 2;

		const message: GoalScoredMessage =
		{
			type: ServerMessageType.GOAL_SCORED,

			scorer,

			score:
			{
				player1: this.gameState.score.player1,
				player2: this.gameState.score.player2
			}
		};

		this.player1.send(message);
		this.player2.send(message);

		console.log(`⚽ Goal! Player ${scorer} scored. Score: ${this.gameState.score.player1} - ${this.gameState.score.player2}`);
	}

	private handleGameOver(): void
	{
		if (!this.player1 || !this.player2) return ;

		const winner = this.gameState.score.player1 >= this.gameState.maxScore ? 1 : 2;

		const message: GameOverMessage =
		{
			type: ServerMessageType.GAME_OVER,

			winner,

			finalScore:
			{
				player1: this.gameState.score.player1,
				player2: this.gameState.score.player2
			}
		};

		this.player1.send(message);
		this.player2.send(message);

		console.log(`🏆 Game Over! Player ${winner} wins! Final score: ${this.gameState.score.player1} - ${this.gameState.score.player2}`);

		this.stopGame();
	}

	private notifyOpponentDisconnected(): void
	{
		const remainingPlayer = this.player1 || this.player2;

		if (remainingPlayer)
		{
			remainingPlayer.send({
				type: ServerMessageType.OPPONENT_DISCND
			});
		}
	}

	private stopGame(): void
	{
		if (this.tickInterval)
		{
			clearInterval(this.tickInterval);

			this.tickInterval = null;
		}

		this.isActive = false;

		console.log(`⏹️  Game stopped in room ${this.id}`);
	}

	public dispose(): void
	{
		this.stopGame();

		this.player1 = null;
		this.player2 = null;
	}
}
