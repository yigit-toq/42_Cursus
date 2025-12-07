import { GameState, GameStateChangeEvent } from './GameState';

export class GameStateManager
{
	private static instance: GameStateManager;
	
	private currentState: GameState = GameState.Menu;
	private previousState: GameState | null = null;
	private stateChangeCallbacks: Map<GameState, Array<(event: GameStateChangeEvent) => void>> = new Map();
	private globalCallbacks: Array<(event: GameStateChangeEvent) => void> = [];

	private constructor()
	{
		// Private constructor for singleton
	}

	public static getInstance(): GameStateManager
	{
		if (!GameStateManager.instance)
		{
			GameStateManager.instance = new GameStateManager();
		}
		return GameStateManager.instance;
	}

	public getCurrentState(): GameState
	{
		return this.currentState;
	}

	public getPreviousState(): GameState | null
	{
		return this.previousState;
	}

	public setState(newState: GameState): void
	{
		if (this.currentState === newState)
		{
			console.warn(`Already in state: ${newState}`);
			return ;
		}

		const event: GameStateChangeEvent = {
			from: this.currentState,
			to: newState,
			timestamp: Date.now()
		};

		console.log(`🎮 State Change: ${event.from} → ${event.to}`);

		this.previousState = this.currentState;
		this.currentState = newState;

		this.triggerCallbacks(newState, event);
	}

	public isState(state: GameState): boolean
	{
		return this.currentState === state;
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
		this.currentState = GameState.Menu;
		this.previousState = null;
	}
}
