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
import { Color3, MeshBuilder, StandardMaterial, Vector3 } from '@babylonjs/core';

const engine = new GameEngine({
	canvasId: 'gameCanvas',
	antialias: true,
	targetFPS: 60
});

const sceneManager = new SceneManager(engine);

sceneManager.setupDefaultCamera();
sceneManager.setupDefaultLighting();

const scene = sceneManager.getScene();

const world = new World();

world.addSystem(new InputSystem());
world.addSystem(new MovementSystem());
world.addSystem(new CollisionSystem());
world.addSystem(new RenderSystem());

const collisionSystem = world.getSystem('CollisionSystem') as CollisionSystem;

const BALL_SPEED = 6;
const ARENA_WIDTH = 20;
const ARENA_HEIGHT = 12;

const ground = MeshBuilder.CreateGround('ground', { 
	width: ARENA_WIDTH, 
	height: ARENA_HEIGHT 
}, scene);
const groundMaterial = new StandardMaterial('groundMat', scene);

groundMaterial.diffuseColor = new Color3(0.1, 0.1, 0.15);
ground.material = groundMaterial;

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

engine.registerUpdateCallback((deltaTime: number) => {
	world.update(deltaTime);
	
	// Clamp paddle positions
	const paddle1Transform = paddle1Entity.getComponent<TransformComponent>('Transform');
	const paddle2Transform = paddle2Entity.getComponent<TransformComponent>('Transform');
	
	const halfArena = ARENA_HEIGHT / 2;
	const paddleHalfHeight = 1.5;
	
	if (paddle1Transform) {
		if (paddle1Transform.position.z < -halfArena + paddleHalfHeight) {
			paddle1Transform.position.z = -halfArena + paddleHalfHeight;
		}
		if (paddle1Transform.position.z > halfArena - paddleHalfHeight) {
			paddle1Transform.position.z = halfArena - paddleHalfHeight;
		}
	}
	
	if (paddle2Transform) {
		if (paddle2Transform.position.z < -halfArena + paddleHalfHeight) {
			paddle2Transform.position.z = -halfArena + paddleHalfHeight;
		}
		if (paddle2Transform.position.z > halfArena - paddleHalfHeight) {
			paddle2Transform.position.z = halfArena - paddleHalfHeight;
		}
	}
	
	// Reset ball if it goes out of bounds
	const ballTransform = ballEntity.getComponent<TransformComponent>('Transform');
	const ballVelocity = ballEntity.getComponent<VelocityComponent>('Velocity');
	
	if (ballTransform && ballVelocity) {
		if (Math.abs(ballTransform.position.x) > ARENA_WIDTH / 2 + 2) {
			console.log('🎯 GOAL! Resetting ball...');
			ballTransform.position.set(0, 0.5, 0);
			ballVelocity.linear.set(
				BALL_SPEED * (Math.random() > 0.5 ? 1 : -1),
				0,
				BALL_SPEED * (Math.random() - 0.5)
			);
		}
	}
});

engine.setScene(scene);
engine.start();

console.log('🏓 Pong Physics Prototype!');
console.log('');
console.log('🎯 Controls:');
console.log('  👤 Player 1 (Blue): W/S');
console.log('  👤 Player 2 (Red): ↑/↓');
console.log('');
console.log('⚽ Ball bounces off paddles and walls!');
console.log('🎯 Goal detection active!');
