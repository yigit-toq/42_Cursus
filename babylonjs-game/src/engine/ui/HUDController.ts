import { GameStateManager	} from '../game/GameStateManager';
import { GameManager		} from '../game/GameManager';
import { GameState			} from '../game/GameState';

import { UIManager			} from './UIManager';

import { Control, TextBlock	} from '@babylonjs/gui';

export class HUDController
{
	private uiManager	: UIManager;

	private scoreText	: TextBlock | null = null;
	private statusText	: TextBlock | null = null;

	private gameManager	: GameManager;
	private stateManager: GameStateManager;

	constructor()
	{
		this.uiManager		= UIManager			.getInstance();
		this.gameManager	= GameManager		.getInstance();
		this.stateManager	= GameStateManager	.getInstance();
	}

	public initialize(): void
	{
		this.createStatusDisplay();
		this.createScoreDisplay	();

		this.setupCallbacks		();

		console.log('🎮 HUD initialized');
	}

	private createScoreDisplay(): void
	{
		this.scoreText				= new TextBlock('scoreText');
		this.scoreText.top			= '30px';

		this.scoreText.text			= 'Score: 0 - 0';
		this.scoreText.color		= 'white';

		this.scoreText.fontSize		= 48;
		this.scoreText.fontFamily	= 'monospace';

		this.scoreText.textVerticalAlignment	= Control.VERTICAL_ALIGNMENT_TOP;
		this.scoreText.textHorizontalAlignment	= Control.HORIZONTAL_ALIGNMENT_CENTER;


		this.uiManager.addElement('scoreText' ,this.scoreText);
	}

	private createStatusDisplay(): void
	{
		this.statusText				= new TextBlock('statusText');
		this.statusText.top			= '120px';

		this.statusText.text		= 'Press SPACE to Start';

		this.statusText.color		= 'rgba(255, 255, 255, 0.7)';

		this.statusText.fontSize	= 24;
		this.statusText.fontFamily	= 'Arial';

		this.statusText.textVerticalAlignment	= Control.VERTICAL_ALIGNMENT_TOP;
		this.statusText.textHorizontalAlignment	= Control.HORIZONTAL_ALIGNMENT_CENTER;

		this.uiManager.addElement('statusText', this.statusText);
	}

	private setupCallbacks(): void
	{
		this.stateManager.onStateChange	((event) =>
		{
			this.updateStatus			(event.to);
		});

		this.gameManager.onScoreChange	((scores) =>
		{
			this.updateScore			(scores.player1, scores.player2);
		});

		this.gameManager.onGameOver		((winner) =>
		{
			this.showGameOver			(winner);
		});
	}

	private updateScore(player1Score: number, player2Score: number): void
	{
		if (this.scoreText)
		{
			this.scoreText.text = `Score: ${player1Score} - ${player2Score}`;
		}
	}

	private updateStatus(state: GameState): void
	{
		if (!this.statusText) return ;

		switch (state)
		{
			case GameState.Menu:
				this.statusText.text		= 'Press SPACE to Start';
				this.statusText.isVisible	= true ;
				break;
			case GameState.Paused:
				this.statusText.text		= 'PAUSED\nPress SPACE to Resume';
				this.statusText.isVisible	= true ;
				break;
			case GameState.Playing:
				this.statusText.isVisible	= false;
				break;
			case GameState.GameOver:
				break;
		}
	}

	private showGameOver(winner: 'player1' | 'player2'): void
	{
		if (!this.statusText) return ;

		const playerName	= winner === 'player1' ? 'Player 1' : 'Player 2';

		const color			= winner === 'player1' ? '#4A9EFF' : '#FF4A4A';
		
		this.statusText.text		= `${playerName} WINS!\nPress SPACE to Restart`;
		this.statusText.color		= color;

		this.statusText.fontSize	= 32;

		this.statusText.isVisible	= true;
	}

	public show(): void
	{
		this.uiManager.showElement('scoreText'	);
		this.uiManager.showElement('statusText'	);
	}

	public hide(): void
	{
		this.uiManager.hideElement('scoreText'	);
		this.uiManager.hideElement('statusText'	);
	}

	public dispose(): void
	{
		this.scoreText	= null;

		this.statusText	= null;
	}
}