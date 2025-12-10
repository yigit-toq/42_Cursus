export interface GameConfig
{
	canvasId	: string;
	antialias?	: boolean;
	targetFPS?	: number ;
}

export interface Vec3
{
	x: number;
	y: number;
	z: number;
}

export interface Vec2
{
	x: number;
	y: number;
}

export enum GameState
{
	IDLE		= 'idle',
	PAUSED		= 'paused',
	PLAYING		= 'playing',
	GAME_OVER	= 'game_over',
}

export type UpdateFunction = (deltaTime: number) => void;
export type RenderFunction = () => void;
