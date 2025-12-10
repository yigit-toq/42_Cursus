import		{ InputManager	} from '../input/InputManager';

import type { GameConfig	} from '../../types/index';

import		{ Engine, Scene } from '@babylonjs/core';

import		{ GameLoop		} from './GameLoop';

export class GameEngine
{
	private scene			: Scene | null = null;

	private canvas			: HTMLCanvasElement;
	private engine			: Engine;

	private gameLoop		: GameLoop;
	private inputManager	: InputManager;

	private updateCallbacks	: Array<(deltaTime: number) => void> = [];

	constructor(config: GameConfig)
	{
		const canvas = document.getElementById(config.canvasId) as HTMLCanvasElement;

		if (!canvas)
			throw new Error(`Canvas element with id ${config.canvasId} not found`);

		this.canvas = canvas;
		this.engine = new Engine(this.canvas, config.antialias,
		{
			preserveDrawingBuffer	: true,
			stencil					: true
		});

		const targetFPS		= config.targetFPS || 60;

		this.gameLoop		= new GameLoop(targetFPS);

		this.inputManager	= InputManager.getInstance();
        this.inputManager.initialize(this.canvas);

		this.initializeEngine	();
	}

	private initializeEngine	(): void
	{
		window.addEventListener('resize', () =>
		{
			this.engine.resize();
		});
	}

	public getEngine(): Engine
	{
		return this.engine;
	}

	public getScene	(): Scene | null
	{
		return this.scene;
	}

	public setScene	(scene: Scene): void
	{
		this.scene = scene;
	}

	public getCanvas(): HTMLCanvasElement
	{
		return this.canvas;
	}

	public registerUpdateCallback	(callback: (deltaTime: number) => void): void
	{
		this.updateCallbacks.push	(callback);
	}

	public unregisterUpdateCallback	(callback: (deltaTime: number) => void): void
	{
		const index = this.updateCallbacks.indexOf(callback);

		if (index > -1)
			this.updateCallbacks.splice(index, 1);
	}

	public isRunning(): boolean
	{
		return this.gameLoop.isActive();
	}

	public start(): void
	{
		if (!this.scene)
			throw new Error('Scene not initialized. Call setScene() first.');

		const update = (deltaTime: number): void =>
		{
			this.updateCallbacks.forEach(cb => cb(deltaTime));

			this.inputManager	.update	();
		};

		const render = (): void =>
		{
			this.scene?.render();
		};

		this.gameLoop.start	(update, render);
	}

	public stop	(): void
	{
		this.gameLoop.stop	();
	}

	public dispose(): void
	{
		this.gameLoop.stop	();

		this.updateCallbacks = [];

		this.scene?.dispose	();
		this.engine.dispose	();
	}
}
