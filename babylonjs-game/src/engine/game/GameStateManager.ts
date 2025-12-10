import { GameState, GameStateChangeEvent } from './GameState';

export class GameStateManager
{
	private static instance: GameStateManager;
	
	private currState			: GameState = GameState.Menu;
	private prevState			: GameState | null = null;

	private globalCallbacks		: Array<(event: GameStateChangeEvent) => void> = [];

	private stateChangeCallbacks: Map<GameState, Array<(event: GameStateChangeEvent) => void>> = new Map();

	private constructor() {}

	public static getInstance(): GameStateManager
	{
		if (!GameStateManager.instance)
		{
			 GameStateManager.instance = new GameStateManager();
		}

		return GameStateManager.instance;
	}

	public getCurrState(): GameState
	{
		return this.currState;
	}

	public getPrevState(): GameState | null
	{
		return this.prevState;
	}

	public setState(newState: GameState): void
	{
		if (this.currState === newState)
		{
			console.warn(`Already in state: ${newState}`);
			return ;
		}

		const event: GameStateChangeEvent =
		{
			from		: this.currState,
			to			: newState,
			timestamp	: Date.now()
		};

		console.log(`🎮 State Change: ${event.from} → ${event.to}`);

		this.prevState = this.currState;
		this.currState = newState;

		this.triggerCallbacks(newState, event);
	}

	public isState(state: GameState): boolean
	{
		return this.currState === state;
	}

	public onStateEnter(state: GameState, callback: (event: GameStateChangeEvent) => void): void
	{
		if (!this.stateChangeCallbacks.has(state))
		{
			 this.stateChangeCallbacks.set(state, []);
		}

			 this.stateChangeCallbacks.get(state)!.push(callback);
	}

	public onStateChange(callback: (event: GameStateChangeEvent) => void): void
	{
		this.globalCallbacks.push(callback);
	}

	private triggerCallbacks(state: GameState, event: GameStateChangeEvent): void
	{
		const callbacks = this.stateChangeCallbacks.get(state);

		if (callbacks)
		{
			callbacks.forEach(cb => cb(event));
		}

		this.globalCallbacks.forEach(cb => cb(event));
	}

	public reset(): void
	{
		this.currState = GameState.Menu;
		this.prevState = null;
	}
}
