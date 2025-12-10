import { Button, Rectangle, TextBlock } from '@babylonjs/gui';

import { UIManager } from './UIManager';

export class MenuController
{
	private uiManager: UIManager;

	constructor()
	{
		this.uiManager = UIManager.getInstance();
	}

	public initialize(): void
	{
		console.log('📋 Menu system initialized');
	}

	public createMainMenu(onStart: () => void): void
	{
		const container				= new Rectangle('mainMenu');
		container.color				= 'white'	;

		container.width				= '400px'	;
		container.height			= '300px'	;

		container.thickness			= 2			;

		container.background		= 'rgba(0, 0, 0, 0.8)';

		container.cornerRadius		= 20		;
		
		const title					= new TextBlock();
		title.top					= '80px'	;

		title.text					= 'PONG'	;
		title.color					= 'white'	;

		title.fontSize				= 60		;

		title.fontWeight			= 'bold'	;
		
		const startButton			= Button.CreateSimpleButton('startButton', 'START GAME');
		startButton.top				= '20px'	;

		startButton.color			= 'white'	;

		startButton.width			= '200px'	;
		startButton.height			= '50px '	;

		startButton.fontSize		= 20		;

		startButton.fontWeight		= 'bold'	;

		startButton.background		= '#60aaffff';

		startButton.cornerRadius	= 10		;
		
		startButton.onPointerClickObservable.add(() =>
		{
			onStart				();

			this.hideMainMenu	();
		});
		
		container.addControl(title);
		container.addControl(startButton);
		
		this.uiManager.addElement('mainMenu', container);
	}

	public showMainMenu(): void
	{
		this.uiManager.showElement('mainMenu');
	}

	public hideMainMenu(): void
	{
		this.uiManager.hideElement('mainMenu');
	}

	public dispose(): void
	{
	}
}
