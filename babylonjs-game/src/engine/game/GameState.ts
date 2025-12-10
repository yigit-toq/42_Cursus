export enum GameState
{
	Menu		= 'MENU',
	Paused		= 'PAUSED',
	Playing		= 'PLAYING',
	GameOver	= 'GAME_OVER'
}

export interface GameStateChangeEvent
{
	from		: GameState;
	to			: GameState;
	timestamp	: number;
}
