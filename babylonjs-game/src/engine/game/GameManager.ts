import { GameStateManager } from './GameStateManager';
import { GameState } from './GameState';

export interface PlayerScore
{
	player1: number;
	player2: number;
}

export interface GameConfig
{
	maxScore: number;
	ballSpeed: number;
	paddleSpeed: number;
}

export class GameManager
{
	private static instance: GameManager;
	
	private stateManager: GameStateManager;
	private scores: PlayerScore = { player1: 0, player2: 0 };
	private config: GameConfig;
	private scoreCallbacks: Array<(scores: PlayerScore) => void> = [];
	private gameOverCallbacks: Array<(winner: 'player1' | 'player2') => void> = [];

	private constructor()
	{
		this.stateManager = GameStateManager.getInstance();
		this.config = {
			maxScore: 5,
			ballSpeed: 6,
			paddleSpeed: 8
		};
	}

	public static getInstance(): GameManager
	{
		if (!GameManager.instance) {
			GameManager.instance = new GameManager();
		}
		return GameManager.instance;
	}

	public initialize(config?: Partial<GameConfig>): void
	{
		if (config) {
			this.config = { ...this.config, ...config };
		}
		this.reset();
	}

	public startGame(): void
	{
		this.stateManager.setState(GameState.Playing);
		console.log('🎮 Game Started!');
	}

	public pauseGame(): void
	{
		if (this.stateManager.isState(GameState.Playing))
		{
			this.stateManager.setState(GameState.Paused);
			console.log('⏸️  Game Paused');
		}
	}

	public resumeGame(): void
	{
		if (this.stateManager.isState(GameState.Paused))
		{
			this.stateManager.setState(GameState.Playing);
			console.log('▶️  Game Resumed');
		}
	}

	public endGame(winner: 'player1' | 'player2'): void
	{
		this.stateManager.setState(GameState.GameOver);
		console.log(`🏆 Game Over! Winner: ${winner}`);

		this.gameOverCallbacks.forEach(cb => cb(winner));
	}

	public reset(): void
	{
		this.scores = { player1: 0, player2: 0 };
		this.stateManager.reset();
		this.triggerScoreCallbacks();
		console.log('🔄 Game Reset');
	}


	public addScore(player: 'player1' | 'player2'): void
	{
		this.scores[player]++;
		console.log(`🎯 ${player} scored! Score: ${this.scores.player1} - ${this.scores.player2}`);
		
		this.triggerScoreCallbacks();

		if (this.scores[player] >= this.config.maxScore)
		{
			this.endGame(player);
		}
	}

	public getScores(): PlayerScore
	{
		return { ...this.scores };
	}

	public getConfig(): GameConfig
	{
		return { ...this.config };
	}

	public onScoreChange(callback: (scores: PlayerScore) => void): void
	{
		this.scoreCallbacks.push(callback);
	}

	public onGameOver(callback: (winner: 'player1' | 'player2') => void): void
	{
		this.gameOverCallbacks.push(callback);
	}

	private triggerScoreCallbacks(): void
	{
		this.scoreCallbacks.forEach(cb => cb(this.getScores()));
	}

	public isGameActive(): boolean
	{
		return this.stateManager.isState(GameState.Playing);
	}

	public isGamePaused(): boolean
	{
		return this.stateManager.isState(GameState.Paused);
	}
}
