import { UIManager } from './UIManager';
import { Button, Rectangle, TextBlock } from '@babylonjs/gui';

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
		const container = new Rectangle('mainMenu');
		container.width = '400px';
		container.height = '300px';
		container.cornerRadius = 20;
		container.color = 'white';
		container.thickness = 2;
		container.background = 'rgba(0, 0, 0, 0.8)';
		
		const title = new TextBlock();
		title.text = 'PONG';
		title.color = 'white';
		title.fontSize = 64;
		title.fontWeight = 'bold';
		title.top = '-80px';
		
		const startButton = Button.CreateSimpleButton('startButton', 'START GAME');
		startButton.width = '200px';
		startButton.height = '50px';
		startButton.color = 'white';
		startButton.cornerRadius = 10;
		startButton.background = '#4A9EFF';
		startButton.top = '20px';
		startButton.fontSize = 20;
		startButton.fontWeight = 'bold';
		
		startButton.onPointerClickObservable.add(() => {
			onStart();
			this.hideMainMenu();
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
