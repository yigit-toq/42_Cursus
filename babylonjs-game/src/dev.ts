import { GameEngine } from './engine/core/GameEngine';
import { SceneManager } from './engine/render/SceneManager';
import { World } from './engine/ecs/core/World';
import { TransformComponent } from './engine/ecs/components/TransformComponent';
import { MeshComponent } from './engine/ecs/components/MeshComponent';
import { VelocityComponent } from './engine/ecs/components/VelocityComponent';
import { InputComponent } from './engine/ecs/components/InputComponent';
import { CollisionComponent, CollisionLayer } from './engine/ecs/components/CollisionComponent';
import { MovementSystem } from './engine/ecs/systems/MovementSystem';
import { RenderSystem } from './engine/ecs/systems/RenderSystem';
import { InputSystem } from './engine/ecs/systems/InputSystem';
import { CollisionSystem, CollisionEvent } from './engine/ecs/systems/CollisionSystem';
import { CollisionDetection } from './engine/physics/CollisionDetection';
import { GameManager } from './engine/game/GameManager';
import { GameStateManager } from './engine/game/GameStateManager';
import { GameState } from './engine/game/GameState';
import { Color3, MeshBuilder, StandardMaterial, Vector3 } from '@babylonjs/core';
import { UIManager } from './engine/ui/UIManager';
import { HUDController } from './engine/ui/HUDController';
import { MenuController } from './engine/ui/MenuController';

// Initialize engine
const engine = new GameEngine({
	canvasId: 'gameCanvas',
	antialias: true,
	targetFPS: 60
});

const sceneManager = new SceneManager(engine);

sceneManager.setupDefaultCamera();
sceneManager.setupDefaultLighting();

const scene = sceneManager.getScene();

// Initialize Game Managers
const gameManager = GameManager.getInstance();
const stateManager = GameStateManager.getInstance();

	gameManager.initialize({
	maxScore: 3,        // First to 3 wins
	ballSpeed: 6,
	paddleSpeed: 8
});

// Initialize UI System
const uiManager = UIManager.getInstance();
uiManager.initialize(scene);

const hudController = new HUDController();
hudController.initialize();

const menuController = new MenuController();
menuController.initialize();

menuController.createMainMenu(() => {
	gameManager.startGame();
	resetBall();
});

// Create ECS World
const world = new World();

// Add systems
world.addSystem(new InputSystem());
world.addSystem(new MovementSystem());
world.addSystem(new CollisionSystem());
world.addSystem(new RenderSystem());

const collisionSystem = world.getSystem('CollisionSystem') as CollisionSystem;

// Game constants
const config = gameManager.getConfig();
const BALL_SPEED = config.ballSpeed;
const ARENA_WIDTH = 20;
const ARENA_HEIGHT = 12;

// Create ground
const ground = MeshBuilder.CreateGround('ground', { 
	width: ARENA_WIDTH, 
	height: ARENA_HEIGHT 
}, scene);
const groundMaterial = new StandardMaterial('groundMat', scene);

groundMaterial.diffuseColor = new Color3(0.1, 0.1, 0.15);
ground.material = groundMaterial;

// Top Wall
const topWallMesh = MeshBuilder.CreateBox('topWall', {
	width: ARENA_WIDTH,
	height: 1,
	depth: 0.5
}, scene);
const wallMaterial = new StandardMaterial('wallMat', scene);

wallMaterial.diffuseColor = new Color3(0.3, 0.3, 0.4);
topWallMesh.material = wallMaterial;

const topWallEntity = world.createEntity('TopWall');
topWallEntity.addComponent(new TransformComponent(
	new Vector3(0, 0.5, -ARENA_HEIGHT / 2)
));
topWallEntity.addComponent(new MeshComponent(topWallMesh));
topWallEntity.addComponent(new CollisionComponent(
	new Vector3(ARENA_WIDTH, 1, 0.5),
	CollisionLayer.Wall,
	CollisionLayer.Ball,
	false,
	true
));
topWallEntity.addComponent(new VelocityComponent());

// Bottom Wall
const bottomWallMesh = MeshBuilder.CreateBox('bottomWall', {
	width: ARENA_WIDTH,
	height: 1,
	depth: 0.5
}, scene);
bottomWallMesh.material = wallMaterial;

const bottomWallEntity = world.createEntity('BottomWall');
bottomWallEntity.addComponent(new TransformComponent(
	new Vector3(0, 0.5, ARENA_HEIGHT / 2)
));
bottomWallEntity.addComponent(new MeshComponent(bottomWallMesh));
bottomWallEntity.addComponent(new CollisionComponent(
	new Vector3(ARENA_WIDTH, 1, 0.5),
	CollisionLayer.Wall,
	CollisionLayer.Ball,
	false,
	true
));
bottomWallEntity.addComponent(new VelocityComponent());

// Player 1 Paddle
const paddle1Mesh = MeshBuilder.CreateBox('paddle1', {
	width: 0.5,
	height: 1,
	depth: 3
}, scene);
const paddle1Material = new StandardMaterial('paddle1Mat', scene);
paddle1Material.diffuseColor = new Color3(0.2, 0.6, 1);
paddle1Material.emissiveColor = new Color3(0.1, 0.3, 0.5);
paddle1Mesh.material = paddle1Material;

const paddle1Entity = world.createEntity('Player1Paddle');
paddle1Entity.addComponent(new TransformComponent(
	new Vector3(-ARENA_WIDTH / 2 + 1, 0.5, 0)
));
paddle1Entity.addComponent(new MeshComponent(paddle1Mesh));
paddle1Entity.addComponent(new VelocityComponent());

paddle1Entity.addComponent(new InputComponent({
	vertical: {
		negative: 'KeyS',
		positive: 'KeyW'
	}
}));
paddle1Entity.addComponent(new CollisionComponent(
	new Vector3(0.5, 1, 3),
	CollisionLayer.Player,
	CollisionLayer.Ball,
	false,
	true
));

// Player 2 Paddle
const paddle2Mesh = MeshBuilder.CreateBox('paddle2', {
	width: 0.5,
	height: 1,
	depth: 3
}, scene);
const paddle2Material = new StandardMaterial('paddle2Mat', scene);
paddle2Material.diffuseColor = new Color3(1, 0.3, 0.3);
paddle2Material.emissiveColor = new Color3(0.5, 0.1, 0.1);
paddle2Mesh.material = paddle2Material;

const paddle2Entity = world.createEntity('Player2Paddle');
paddle2Entity.addComponent(new TransformComponent(
	new Vector3(ARENA_WIDTH / 2 - 1, 0.5, 0)
));
paddle2Entity.addComponent(new MeshComponent(paddle2Mesh));
paddle2Entity.addComponent(new VelocityComponent());

paddle2Entity.addComponent(new InputComponent({
	vertical: {
		negative: 'ArrowDown',
		positive: 'ArrowUp'
	}
}));
paddle2Entity.addComponent(new CollisionComponent(
	new Vector3(0.5, 1, 3),
	CollisionLayer.Player,
	CollisionLayer.Ball,
	false,
	true
));

// Ball
const ballMesh = MeshBuilder.CreateSphere('ball', { diameter: 0.8 }, scene);
const ballMaterial = new StandardMaterial('ballMat', scene);
ballMaterial.diffuseColor = new Color3(1, 1, 0.2);
ballMaterial.emissiveColor = new Color3(0.8, 0.8, 0.1);
ballMesh.material = ballMaterial;

const ballEntity = world.createEntity('Ball');
ballEntity.addComponent(new TransformComponent(
	new Vector3(0, 0.5, 0)
));
ballEntity.addComponent(new MeshComponent(ballMesh));
ballEntity.addComponent(new VelocityComponent(
	new Vector3(BALL_SPEED, 0, BALL_SPEED * 0.5)
));
ballEntity.addComponent(new CollisionComponent(
	new Vector3(0.8, 0.8, 0.8),
	CollisionLayer.Ball,
	CollisionLayer.Player | CollisionLayer.Wall
));

collisionSystem.registerCollisionCallback(ballEntity.id, (event: CollisionEvent) =>
{
	const ball = event.entityA.id === ballEntity.id ? event.entityA : event.entityB;
	const other = event.entityA.id === ballEntity.id ? event.entityB : event.entityA;

	const ballVelocity = ball.getComponent<VelocityComponent>('Velocity');

	if (!ballVelocity) return ;

	const reflected = CollisionDetection.reflect(ballVelocity.linear, event.normal);
	ballVelocity.linear.copyFrom(reflected);

	const speed = ballVelocity.linear.length();
	ballVelocity.linear.normalize().scaleInPlace(speed * 1.01);

	console.log(`⚽ Ball hit ${other.name}!`);
});

function resetBall(): void
{
	const ballTransform = ballEntity.getComponent<TransformComponent>('Transform');
	const ballVelocity = ballEntity.getComponent<VelocityComponent>('Velocity');

	if (ballTransform && ballVelocity)
	{
		ballTransform.position.set(0, 0.5, 0);

		ballVelocity.linear.set(
			BALL_SPEED * (Math.random() > 0.5 ? 1 : -1),
			0,
			BALL_SPEED * (Math.random() - 0.5)
		);
	}
}

stateManager.onStateChange((event) => {
	console.log(`📊 State: ${event.from} → ${event.to}`);
});

gameManager.onScoreChange((scores) => {
	console.log(`📊 Score Update: ${scores.player1} - ${scores.player2}`);
});

gameManager.onGameOver((winner) => {
	console.log(`🏆 GAME OVER! Winner: ${winner.toUpperCase()}`);
	console.log('   Press SPACE to restart');
});

window.addEventListener('keydown', (event) =>
{
	if (event.code === 'Space')
	{
		if (stateManager.isState(GameState.Menu))
		{
			menuController.hideMainMenu();
			gameManager.startGame();
			resetBall();
		}
		else if (stateManager.isState(GameState.GameOver))
		{
			gameManager.reset();
			gameManager.startGame();
			resetBall();
		}
		else if (stateManager.isState(GameState.Playing))
		{
			gameManager.pauseGame();
		}
		else if (stateManager.isState(GameState.Paused))
		{
			gameManager.resumeGame();
		}
	}
	
	if (event.code === 'Escape')
	{
		if (stateManager.isState(GameState.Playing))
		{
			gameManager.pauseGame();
		}
	}
});


engine.registerUpdateCallback((deltaTime: number) =>
{
	if (gameManager.isGameActive())
	{
		world.update(deltaTime);
		
		// Clamp paddle positions
		const paddle1Transform = paddle1Entity.getComponent<TransformComponent>('Transform');
		const paddle2Transform = paddle2Entity.getComponent<TransformComponent>('Transform');
		
		const halfArena = ARENA_HEIGHT / 2;
		const paddleHalfHeight = 1.5;
		
		if (paddle1Transform)
		{
			if (paddle1Transform.position.z < -halfArena + paddleHalfHeight)
			{
				paddle1Transform.position.z = -halfArena + paddleHalfHeight;
			}
			if (paddle1Transform.position.z > halfArena - paddleHalfHeight)
			{
				paddle1Transform.position.z = halfArena - paddleHalfHeight;
			}
		}
		
		if (paddle2Transform)
		{
			if (paddle2Transform.position.z < -halfArena + paddleHalfHeight)
			{
				paddle2Transform.position.z = -halfArena + paddleHalfHeight;
			}
			if (paddle2Transform.position.z > halfArena - paddleHalfHeight)
			{
				paddle2Transform.position.z = halfArena - paddleHalfHeight;
			}
		}

		const ballTransform = ballEntity.getComponent<TransformComponent>('Transform');
		
		if (ballTransform)
		{
			if (ballTransform.position.x < -ARENA_WIDTH / 2)
			{
				gameManager.addScore('player2');
				resetBall();
			}
			else if (ballTransform.position.x > ARENA_WIDTH / 2)
			{
				gameManager.addScore('player1');
				resetBall();
			}
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
engine.setScene(scene);
engine.start();

console.log('🏓 Pong Game - Full UI System');
console.log('');
console.log('🎮 Controls:');
console.log('  SPACE   - Start/Pause/Resume/Restart');
console.log('  ESC     - Pause');
console.log('  W/S     - Player 1 (Blue)');
console.log('  ↑/↓     - Player 2 (Red)');
console.log('');
console.log('🎯 First to 3 points wins!');
console.log('🎨 UI: Score display + Status messages')
console.log('📋 Click START or press SPACE...');
