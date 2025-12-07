import type { Scene } from '@babylonjs/core';
import { AdvancedDynamicTexture, Control } from '@babylonjs/gui';

export class UIManager
{
	private static instance: UIManager;

	private advancedTexture: AdvancedDynamicTexture | null = null;
	private uiElements: Map<string, Control> = new Map();

	private constructor() {}

	public static getInstance(): UIManager
	{
		if (!UIManager.instance)
		{
			UIManager.instance = new UIManager();
		}
		return UIManager.instance;
	}

	public initialize(scene: Scene): void
	{
		this.advancedTexture = AdvancedDynamicTexture.CreateFullscreenUI('UI', true, scene);
		console.log('🎨 UI System initialized');
	}

	public getTexture(): AdvancedDynamicTexture
	{
		if (!this.advancedTexture)
		{
			throw new Error('UI not initialized. Call initialize() first.');
		}
		return this.advancedTexture;
	}

	public addElement(name: string, element: Control): void
	{
		this.uiElements.set(name, element);
		this.advancedTexture?.addControl(element);
	}

	public getElement(name: string): Control | undefined
	{
		return this.uiElements.get(name);
	}

	public removeElement(name: string): void
	{
		const element = this.uiElements.get(name);

		if (element) {
			this.advancedTexture?.removeControl(element);
			this.uiElements.delete(name);
		}
	}

	public showElement(name: string): void
	{
		const element = this.uiElements.get(name);

		if (element)
		{
			element.isVisible = true;
		}
	}

	public hideElement(name: string): void
	{
		const element = this.uiElements.get(name);

		if (element)
		{
			element.isVisible = false;
		}
	}

	public clear(): void
	{
		this.advancedTexture?.dispose();
		this.uiElements.clear();
	}

	public dispose(): void
	{
		this.clear();
		this.advancedTexture = null;
	}
}
