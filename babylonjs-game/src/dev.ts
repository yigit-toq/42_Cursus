import { GameEngine } from './engine/core/GameEngine';
import { SceneManager } from './engine/render/SceneManager';
import { World } from './engine/ecs/core/World';
import { TransformComponent } from './engine/ecs/components/TransformComponent';
import { MeshComponent } from './engine/ecs/components/MeshComponent';
import { VelocityComponent } from './engine/ecs/components/VelocityComponent';
import { InputComponent } from './engine/ecs/components/InputComponent';
import { MovementSystem } from './engine/ecs/systems/MovementSystem';
import { RenderSystem } from './engine/ecs/systems/RenderSystem';
import { InputSystem } from './engine/ecs/systems/InputSystem';
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
world.addSystem(new RenderSystem());

const ground = MeshBuilder.CreateGround('ground', { width: 20, height: 20 }, scene);
const groundMaterial = new StandardMaterial('groundMat', scene);
groundMaterial.diffuseColor = new Color3(0.3, 0.3, 0.3);
ground.material = groundMaterial;

const paddle1Mesh = MeshBuilder.CreateBox('paddle1', { 
	width: 0.5, 
	height: 2, 
	depth: 0.5 
}, scene);
const paddle1Material = new StandardMaterial('paddle1Mat', scene);
paddle1Material.diffuseColor = new Color3(0.2, 0.6, 1);
paddle1Mesh.material = paddle1Material;

const paddle1Entity = world.createEntity('Player1Paddle');
paddle1Entity.addComponent(new TransformComponent(
	new Vector3(-8, 1, 0)
));
paddle1Entity.addComponent(new MeshComponent(paddle1Mesh));
paddle1Entity.addComponent(new VelocityComponent());
paddle1Entity.addComponent(new InputComponent({
	vertical: { 
		negative: 'KeyS',
		positive: 'KeyW'
	}
}));

const paddle2Mesh = MeshBuilder.CreateBox('paddle2', { 
	width: 0.5, 
	height: 2, 
	depth: 0.5 
}, scene);
const paddle2Material = new StandardMaterial('paddle2Mat', scene);
paddle2Material.diffuseColor = new Color3(1, 0.3, 0.3);
paddle2Mesh.material = paddle2Material;

const paddle2Entity = world.createEntity('Player2Paddle');
paddle2Entity.addComponent(new TransformComponent(
	new Vector3(8, 1, 0)
));
paddle2Entity.addComponent(new MeshComponent(paddle2Mesh));
paddle2Entity.addComponent(new VelocityComponent());
paddle2Entity.addComponent(new InputComponent({
	vertical: { 
		negative: 'ArrowDown',
		positive: 'ArrowUp'
	}
}));

const ballMesh = MeshBuilder.CreateSphere('ball', { diameter: 0.5 }, scene);
const ballMaterial = new StandardMaterial('ballMat', scene);
ballMaterial.diffuseColor = new Color3(1, 1, 0.2);
ballMaterial.emissiveColor = new Color3(0.5, 0.5, 0.1);
ballMesh.material = ballMaterial;

const ballEntity = world.createEntity('Ball');
ballEntity.addComponent(new TransformComponent(
	new Vector3(0, 1, 0)
));
ballEntity.addComponent(new MeshComponent(ballMesh));
ballEntity.addComponent(new VelocityComponent(
	new Vector3(3, 0, 0),
	new Vector3(0, Math.PI, 0)
));

engine.registerUpdateCallback((deltaTime: number) =>
{
	world.update(deltaTime);
});

engine.setScene(scene);
engine.start();

console.log('🎮 Input System Test - Pong Prototype!');
console.log('');
console.log('🎯 Controls:');
console.log('  👤 Player 1 (Blue, Left):');
console.log('     W = Up');
console.log('     S = Down');
console.log('');
console.log('  👤 Player 2 (Red, Right):');
console.log('     ↑ = Up');
console.log('     ↓ = Down');
console.log('');
console.log('⚽ Yellow Ball: Auto-moving (collision detection next!)');
console.log('');
console.log('💡 Tip: Use mouse to rotate camera view');
