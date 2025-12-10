import { Scene, ArcRotateCamera, HemisphericLight, Vector3 } from '@babylonjs/core';

import type { GameEngine } from '../core/GameEngine';

export class SceneManager
{
	private scene: Scene;
	private light: HemisphericLight | null = null;
	private camera: ArcRotateCamera | null = null;

	constructor(gameEngine: GameEngine)
	{
		this.scene				= new Scene(gameEngine.getEngine());
		this.scene.clearColor	= { r: 0.1, g: 0.1, b: 0.15, a: 1.0 } as any;
	}

	public setupDefaultLighting(): HemisphericLight
	{
		this.light = new HemisphericLight(
			'light',

			new Vector3(0, 1, 0),

			this.scene
		);

		this.light.intensity = 1;
		
		return this.light;
	}

	public setupDefaultCamera(target: Vector3 = Vector3.Zero()): ArcRotateCamera
	{
		this.camera = new ArcRotateCamera(
			'camera',
			Math.PI / 2,
			Math.PI / 3,
			10,
			target,
			this.scene
		);

		this.camera.attachControl(true);

		this.camera.lowerRadiusLimit = 5;
		this.camera.upperRadiusLimit = 20;

		this.camera.inputs.attached.keyboard.detachControl();
		
		return this.camera;
	}

	public getCamera(): ArcRotateCamera | null
	{
		return this.camera;
	}

	public getScene	(): Scene
	{
		return this.scene ;
	}

	public dispose	(): void
	{
		this.scene.dispose();
	}
}
