export enum GameState
{
	Menu = 'MENU',
	Playing = 'PLAYING',
	Paused = 'PAUSED',
	GameOver = 'GAME_OVER'
}

export interface GameStateChangeEvent
{
	from: GameState;
	to: GameState;
	timestamp: number;
}
