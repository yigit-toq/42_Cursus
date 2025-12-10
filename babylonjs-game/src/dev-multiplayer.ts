import { Color3, MeshBuilder, StandardMaterial, Vector3 } from '@babylonjs/core';

import { TransformComponent	} from './engine/ecs/components/TransformComponent';
import { VelocityComponent	} from './engine/ecs/components/VelocityComponent';
import { InputComponent		} from './engine/ecs/components/InputComponent';
import { MeshComponent		} from './engine/ecs/components/MeshComponent';

import { CollisionSystem	} from './engine/ecs/systems/CollisionSystem';
import { MovementSystem		} from './engine/ecs/systems/MovementSystem';
import { RenderSystem		} from './engine/ecs/systems/RenderSystem';
import { InputSystem		} from './engine/ecs/systems/InputSystem';

import { World				} from './engine/ecs/core/World';

import { MenuController		} from './engine/ui/MenuController';
import { HUDController		} from './engine/ui/HUDController';
import { UIManager			} from './engine/ui/UIManager';

import { GameEngine			} from './engine/core/GameEngine';

import { GameManager		} from './engine/game/GameManager';

import { SceneManager		} from './engine/render/SceneManager';

import { GameStateMessage, MatchFoundMessage	} from './engine/network/MessageTypes';
import { NetworkManager							} from './engine/network/NetworkManager';

import * as GUI from '@babylonjs/gui';

// Initialize engine
const engine = new GameEngine({
	canvasId : 'gameCanvas',
	antialias: true,
	targetFPS: 60
});

const sceneManager = new SceneManager(engine);

sceneManager.setupDefaultCamera		();
sceneManager.setupDefaultLighting	();

const scene = sceneManager.getScene	();

// const inputManager = engine.getInputManager();

const gameManager		= GameManager	.getInstance();
const networkManager	= NetworkManager.getInstance();

gameManager.initialize({
	maxScore	: 3,
	ballSpeed	: 6,
	paddleSpeed	: 8
});

// Initialize UI
const uiManager			= UIManager.getInstance();
uiManager		.initialize(scene);

const hudController		= new HUDController ();
hudController	.initialize();

const menuController	= new MenuController();
menuController	.initialize();

// Create ECS World
const world = new World();

// Add systems
world.addSystem(new InputSystem		());
world.addSystem(new RenderSystem	());
world.addSystem(new MovementSystem	());
world.addSystem(new CollisionSystem	());

// Game constants
const ARENA_WIDTH	= 20;
const ARENA_HEIGHT	= 12;

// Create ground
const ground					= MeshBuilder.CreateGround('ground',
{ 
	width	: ARENA_WIDTH,
	height	: ARENA_HEIGHT
}, scene);
const groundMaterial			= new StandardMaterial('groundMat', scene);

groundMaterial.diffuseColor		= new Color3(0.1, 0.1, 0.15);

ground.material					= groundMaterial;

// Create walls
const wallMaterial				= new StandardMaterial('wallMat', scene);

wallMaterial.diffuseColor		= new Color3(0.3, 0.3, 0.4);

const topWallMesh				= MeshBuilder.CreateBox('topWall',
{
	width	: ARENA_WIDTH,
	height	: 1,
	depth	: 0.5
}, scene);
topWallMesh.position.y			= 0.5;
topWallMesh.position.z			= -ARENA_HEIGHT / 2;

topWallMesh.material			= wallMaterial;

const botWallMesh				= MeshBuilder.CreateBox('botWall',
{
	width	: ARENA_WIDTH,
	height	: 1,
	depth	: 0.5
}, scene);
botWallMesh.position.y			= 0.5;
botWallMesh.position.z			= +ARENA_HEIGHT / 2;

botWallMesh.material			= wallMaterial;

// Player 1 Paddle
const paddle1Mesh				= MeshBuilder.CreateBox('paddle1',
{
	width	: 0.5,
	height	: 1,
	depth	: 3
}, scene);
const paddle1Material			= new StandardMaterial('paddle1Mat', scene);

paddle1Material.diffuseColor	= new Color3(0.2, 0.6, 1);
paddle1Material.emissiveColor	= new Color3(0.1, 0.3, 0.5);

paddle1Mesh.material			= paddle1Material;

const paddle1Entity = world.createEntity('Player1Paddle');
paddle1Entity.addComponent(new TransformComponent(
	new Vector3(-ARENA_WIDTH / 2 + 1, 0.5, 0)
));
paddle1Entity.addComponent(new MeshComponent(paddle1Mesh));
paddle1Entity.addComponent(new VelocityComponent());

// Player 2 Paddle
const paddle2Mesh = MeshBuilder.CreateBox('paddle2',
{
	width	: 0.5,
	height	: 1,
	depth	: 3
}, scene);
const paddle2Material			= new StandardMaterial('paddle2Mat', scene);

paddle2Material.diffuseColor	= new Color3(1, 0.3, 0.3);
paddle2Material.emissiveColor	= new Color3(0.5, 0.1, 0.1);

paddle2Mesh.material			= paddle2Material;

const paddle2Entity = world.createEntity('Player2Paddle');
paddle2Entity.addComponent(new TransformComponent(
	new Vector3(ARENA_WIDTH / 2 - 1, 0.5, 0)
));
paddle2Entity.addComponent(new MeshComponent(paddle2Mesh));
paddle2Entity.addComponent(new VelocityComponent());

// Ball
const ballMesh					= MeshBuilder.CreateSphere	('ball'		, { diameter: 0.8 }, scene);
const ballMaterial				= new StandardMaterial		('ballMat'	, scene);

ballMaterial.diffuseColor		= new Color3(1, 1, 0.2);
ballMaterial.emissiveColor		= new Color3(0.8, 0.8, 0.1);

ballMesh.material				= ballMaterial;

const ballEntity = world.createEntity('Ball');
ballEntity.addComponent(new TransformComponent(
	new Vector3(0, 0.5, 0)
));
ballEntity.addComponent(new MeshComponent(ballMesh));
ballEntity.addComponent(new VelocityComponent());

// Multiplayer UI
const connectButton = GUI.Button.CreateSimpleButton('connectButton', 'CONNECT TO SERVER');
connectButton.top					= '-50px';

connectButton.color					= 'white';

connectButton.width					= '250px';
connectButton.height				= '60px' ;

connectButton.zIndex				= 10;

connectButton.fontSize				= 20;

connectButton.fontWeight			= 'bold';

connectButton.background			= '#4A9EFF';

connectButton.cornerRadius			= 10;

connectButton.verticalAlignment		= GUI.Control.VERTICAL_ALIGNMENT_CENTER;
connectButton.horizontalAlignment	= GUI.Control.HORIZONTAL_ALIGNMENT_CENTER;

connectButton.isPointerBlocker		= true;

const findMatchButton = GUI.Button.CreateSimpleButton('findMatchButton', 'FIND MATCH');
findMatchButton.top					= '30px';

findMatchButton.color				= 'white';

findMatchButton.width				= '250px';
findMatchButton.height				= '60px' ;

findMatchButton.zIndex				= 10;

findMatchButton.fontSize			= 20;

findMatchButton.isVisible			= false;

findMatchButton.fontWeight			= 'bold';

findMatchButton.background			= '#4AFF9E';

findMatchButton.cornerRadius		= 10;

findMatchButton.verticalAlignment	= GUI.Control.VERTICAL_ALIGNMENT_CENTER;
findMatchButton.horizontalAlignment	= GUI.Control.HORIZONTAL_ALIGNMENT_CENTER;

findMatchButton.isPointerBlocker	= true;

const statusText = new GUI.TextBlock('networkStatus');
statusText.top						= '120px';
statusText.text						= 'Click CONNECT to start';
statusText.color					= 'rgba(255, 255, 255, 0.7)';
statusText.zIndex					= 5;
statusText.fontSize					= 18;
statusText.verticalAlignment		= GUI.Control.VERTICAL_ALIGNMENT_CENTER;
statusText.horizontalAlignment		= GUI.Control.HORIZONTAL_ALIGNMENT_CENTER;

uiManager.addElement('networkStatus'	, statusText);
uiManager.addElement('connectButton'	, connectButton);
uiManager.addElement('findMatchButton'	, findMatchButton);

networkManager.onConnected(() =>
{
	console.log('✅ Connected to server!');

	connectButton	.isVisible = false;
	findMatchButton	.isVisible = true ;

	statusText.text = 'Connected! Click FIND MATCH';
});

networkManager.onMatchFound((data: MatchFoundMessage) =>
{
	console.log(`🎮 Match found! You are Player ${data.playerNumber}`);
	console.log(`📊 Match data:`, data);

	findMatchButton.isVisible = false;

	statusText.text = `Playing as Player ${data.playerNumber}`;

	const myPaddle = data.playerNumber === 1 ? paddle1Entity : paddle2Entity;
	
	console.log(`🎮 Setting up input for paddle:`, myPaddle.name);
	
	const inputMapping =
	{
		vertical:
		{
			negative: data.playerNumber === 1 ? 'KeyS' : 'ArrowDown',
			positive: data.playerNumber === 1 ? 'KeyW' : 'ArrowUp'
		}
	};
	myPaddle.addComponent(new InputComponent(inputMapping));

	console.log(`⌨️ Input mapping:`, inputMapping);
	
	console.log(`✅ Input component added!`);

	const testInput = () =>
	{
		const inputComp = myPaddle.getComponent<InputComponent>('Input');

		if (inputComp)
		{
			console.log(`🎮 Current vertical axis: ${inputComp.getAxis('vertical')}`);
		}
	};

	setInterval(testInput, 2000);
});

networkManager.onGameState((state: GameStateMessage) =>
{
	const ballTransform = ballEntity.getComponent<TransformComponent>('Transform');

	if (ballTransform)
	{
		ballTransform.position.set(state.ball.position.x, state.ball.position.y, state.ball.position.z);
	}

	const paddle1Transform = paddle1Entity.getComponent<TransformComponent>('Transform');
	if (paddle1Transform)
	{
		paddle1Transform.position.z = state.paddle1.z;
	}

	const paddle2Transform = paddle2Entity.getComponent<TransformComponent>('Transform');
	if (paddle2Transform)
	{
		paddle2Transform.position.z = state.paddle2.z;
	}

	const currentScores = gameManager.getScores();

	if (currentScores.player1 !== state.score.player1 || 
		currentScores.player2 !== state.score.player2)
	{
		gameManager['scores'] = state.score;
		gameManager['triggerScoreCallbacks']();
	}
});

networkManager.onDisconnected(() =>
{
	console.log('👋 Disconnected from server');

	connectButton	.isVisible = true ;

	findMatchButton	.isVisible = false;

	statusText.text = 'Disconnected. Click CONNECT to reconnect';
});

connectButton.onPointerClickObservable.add(async () =>
{
	statusText.text = 'Connecting...';

	try
	{
		await networkManager.connect('Player');
	}
	catch (error)
	{
		console.error('❌ Connection failed:', error);
		statusText.text = 'Connection failed. Try again.';
	}
});

findMatchButton.onPointerClickObservable.add(() =>
{
	statusText.text = 'Finding match...';

	networkManager.findMatch();
});

// Send input to server
let lastInputSent = 0;

// Send input every 50ms
const INPUT_SEND_RATE = 50;

// Game loop
engine.registerUpdateCallback((deltaTime: number) =>
{
	if (networkManager.isInMultiplayer())
	{
		const inputSystem = world.getSystem('InputSystem') as InputSystem;

		if (inputSystem)
		{
			inputSystem.update(world.getEntities(), deltaTime);

			const myPaddleNumber = networkManager.getPlayerNumber();

			if (myPaddleNumber)
			{
				// const myPaddle = myPaddleNumber === 1 ? paddle1Entity : paddle2Entity;
				// const inputComp = myPaddle.getComponent<InputComponent>('Input');
				
				// if (inputComp)
				// {
				// 	const vertical = inputComp.getAxis('vertical');

				// 	if (!window['lastLoggedInput'] || window['lastLoggedInput'] !== vertical)
				// 	{
				// 		console.log(`⌨️  Input changed: ${vertical}`);

				// 		window['lastLoggedInput'] = vertical;
				// 	}
				// }
			}
		}

		const now = Date.now();

		if (now - lastInputSent > INPUT_SEND_RATE)
		{
			const myPaddleNumber = networkManager.getPlayerNumber();
			
			if (myPaddleNumber)
			{
				const myPaddle	= myPaddleNumber === 1 ? paddle1Entity : paddle2Entity;
				const inputComp	= myPaddle.getComponent<InputComponent>('Input');
				
				if (inputComp)
				{
					const vertical = inputComp.getAxis('vertical');

					networkManager.sendInput(vertical);
				}
			}
			
			lastInputSent = now;
		}

		const renderSystem = world.getSystem('RenderSystem') as RenderSystem;

		if (renderSystem)
		{
			renderSystem.update(world.getEntities(), deltaTime);
		}
	}
	else
	{
		const renderSystem = world.getSystem('RenderSystem') as RenderSystem;

		if (renderSystem)
		{
			renderSystem.update(world.getEntities(), deltaTime);
		}
	}
});

// Start engine
engine.setScene	(scene);
engine.start	();

console.log('🌐 Multiplayer Pong - Network Test');
console.log('');
console.log('🎮 Instructions:');

console.log('1. Click CONNECT TO SERVER');
console.log('2. Click FIND MATCH');
console.log('3. Play!');
console.log('');
console.log('💡 Open two browser tabs to test!');
