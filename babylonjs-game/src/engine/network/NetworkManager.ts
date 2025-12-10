import { GameStateManager	} from '../game/GameStateManager';
import { GameState			} from '../game/GameState';
import
{
	ClientMessageType,
	ServerMessageType,
	type WelcomeMessage,
	type GameOverMessage,
	type GameStateMessage,
	type MatchFoundMessage,
	type GoalScoredMessage,
} from './MessageTypes';

import { WebSocketClient	} from './WebSocketClient';

export class NetworkManager
{
	private static instance	: NetworkManager;
	
	private client			: WebSocketClient;

	private playerId		: string | null = null;

	private playerNumber	: 1 | 2  | null = null;

	private stateManager	: GameStateManager;

	private isMultiplayer	: boolean = false;

	private onConnectedCallbacks	: Array<() => void> = [];

	private onGameStateCallbacks	: Array<(state: GameStateMessage) => void> = [];
	private onMatchFoundCallbacks	: Array<(data: MatchFoundMessage) => void> = [];

	private onDisconnectedCallbacks	: Array<() => void> = [];

	private constructor()
	{
		this.client			= new WebSocketClient('ws://localhost:8080');

		this.stateManager	= GameStateManager.getInstance();

		this.setupMessageHandlers();
	}

	public static getInstance(): NetworkManager
	{
		if (!NetworkManager.instance)
		{
			 NetworkManager.instance = new NetworkManager();
		}

		return NetworkManager.instance;
	}

	private setupMessageHandlers(): void
	{
		this.client.on(ServerMessageType.WELCOME, (message: WelcomeMessage) =>
		{
			this.playerId = message.playerId;

			console.log(`✅ Connected! Player ID: ${this.playerId}`);

			this.triggerConnectedCallbacks();
		});

		this.client.on(ServerMessageType.MATCH_FOUND, (message: MatchFoundMessage) =>
		{
			this.playerNumber = message.playerNumber;

			console.log(`🎮 Match found! You are Player ${this.playerNumber}`);
			console.log(`Opponent: ${message.opponentName || 'Anonymous'}`);
			
			this.isMultiplayer = true;

			this.stateManager.setState		(GameState.Playing);
			
			this.triggerMatchFoundCallbacks	(message);
		});

		this.client.on(ServerMessageType.GAME_STATE, (message: GameStateMessage) =>
		{
			this.triggerGameStateCallbacks(message);
		});

		this.client.on(ServerMessageType.GOAL_SCORED, (message: GoalScoredMessage) =>
		{
			console.log(`⚽ Goal! Player ${message.scorer} scored!`);
			console.log(`Score: ${message.score.player1} - ${message.score.player2}`);
		});

		this.client.on(ServerMessageType.GAME_OVER, (message: GameOverMessage) =>
		{
			console.log(`🏆 Game Over! Player ${message.winner} wins!`);
			console.log(`Final Score: ${message.finalScore.player1} - ${message.finalScore.player2}`);
			
			this.stateManager.setState(GameState.GameOver);

			this.isMultiplayer = false;
		});

		this.client.on(ServerMessageType.OPPONENT_DISCND, () =>
		{
			console.log	('👋 Opponent disconnected');

			alert		('Opponent disconnected. Returning to menu...');

			this.stateManager.setState(GameState.Menu);

			this.isMultiplayer = false;
		});

		this.client.on(ServerMessageType.ERROR, (message: any) =>
		{
			console.error('❌ Server error:', message.message);
		});
	}

	public async connect(playerName?: string): Promise<void>
	{
		await this.client.connect();

		this.client.send
		({
			type: ClientMessageType.CONNECT,
			playerName
		});
	}

	public findMatch(): void
	{
		if (!this.client.isConnected())
		{
			console.error('❌ Not connected to server');
			return ;
		}

		console.log('🔍 Looking for match...');

		this.client.send
		({
			type: ClientMessageType.FIND_MATCH
		});
	}

	public sendInput(vertical: number): void
	{
		if (!this.isMultiplayer || !this.client.isConnected())
		{
			console.warn('⚠️  Cannot send input: Not in multiplayer or not connected');
			return ;
		}

		console.log(`📤 Sending input to server: ${vertical}`);

		this.client.send
		({
			type		: ClientMessageType.INPUT,
			input		: { vertical },
			timestamp	: Date.now()
		});
	}

	public disconnect(): void
	{
		this.client.disconnect();

		this.playerId		= null;
		this.playerNumber	= null;

		this.isMultiplayer	= false;

		this.triggerDisconnectedCallbacks();
	}

	public getPlayerNumber(): 1 | 2 | null
	{
		return this.playerNumber;
	}	

	public isInMultiplayer(): boolean
	{
		return this.isMultiplayer;
	}

	public onConnected		(callback: () => void): void
	{
		this.onConnectedCallbacks.		push(callback);
	}

	public onGameState		(callback: (state: GameStateMessage) => void): void
	{
		this.onGameStateCallbacks.		push(callback);
	}

	public onMatchFound		(callback: (data: MatchFoundMessage) => void): void
	{
		this.onMatchFoundCallbacks.		push(callback);
	}

	public onDisconnected	(callback: () => void): void
	{
		this.onDisconnectedCallbacks.	push(callback);
	}

	private triggerConnectedCallbacks		(): void
	{
		this.onConnectedCallbacks.		forEach(cb => cb());
	}

	private triggerGameStateCallbacks		(other: GameStateMessage): void
	{
		this.onGameStateCallbacks.		forEach(cb => cb(other));
	}

	private triggerMatchFoundCallbacks		(other: MatchFoundMessage): void
	{
		this.onMatchFoundCallbacks.		forEach(cb => cb(other));
	}

	private triggerDisconnectedCallbacks	(): void
	{
		this.onDisconnectedCallbacks.	forEach(cb => cb());
	}

	public async getLatency(): Promise<number>
	{
		return this.client.measureLatency();
	}
}
