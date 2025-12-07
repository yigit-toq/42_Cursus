import { GameEngine } from './engine/core/GameEngine';
import { SceneManager } from './engine/render/SceneManager';
import { World } from './engine/ecs/core/World';
import { TransformComponent } from './engine/ecs/components/TransformComponent';
import { MeshComponent } from './engine/ecs/components/MeshComponent';
import { VelocityComponent } from './engine/ecs/components/VelocityComponent';
import { MovementSystem } from './engine/ecs/systems/MovementSystem';
import { RenderSystem } from './engine/ecs/systems/RenderSystem';
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

world.addSystem(new MovementSystem());
world.addSystem(new RenderSystem());

const ground = MeshBuilder.CreateGround('ground', { width: 10, height: 10 }, scene);
const groundMaterial = new StandardMaterial('groundMat', scene);

groundMaterial.diffuseColor = new Color3(0.5, 0.5, 0.5);
ground.material = groundMaterial;

const sphereMesh = MeshBuilder.CreateSphere('sphere1', { diameter: 1 }, scene);
const sphereMaterial = new StandardMaterial('sphereMat', scene);

sphereMaterial.diffuseColor = new Color3(0.2, 0.4, 1);
sphereMesh.material = sphereMaterial;

const sphereEntity = world.createEntity('RotatingSphere');
sphereEntity.addComponent(new TransformComponent(
	new Vector3(-2, 1, 0)
));

sphereEntity.addComponent(new MeshComponent(sphereMesh));
sphereEntity.addComponent(new VelocityComponent(
	Vector3.Zero(),
	new Vector3(0, Math.PI / 2, 0)
));

const boxMesh = MeshBuilder.CreateBox('box1', { size: 1 }, scene);
const boxMaterial = new StandardMaterial('boxMat', scene);

boxMaterial.diffuseColor = new Color3(1, 0.6, 0.2);
boxMesh.material = boxMaterial;

const boxEntity = world.createEntity('MovingBox');
boxEntity.addComponent(new TransformComponent(
	new Vector3(2, 1, 0)
));

boxEntity.addComponent(new MeshComponent(boxMesh));
boxEntity.addComponent(new VelocityComponent(
	new Vector3(0, 0.5, 0),
	Vector3.Zero()
));

const cylinderMesh = MeshBuilder.CreateCylinder('cylinder1', { height: 1, diameter: 0.5 }, scene);
const cylinderMaterial = new StandardMaterial('cylinderMat', scene);

cylinderMaterial.diffuseColor = new Color3(0.2, 1, 0.4);
cylinderMesh.material = cylinderMaterial;

const cylinderEntity = world.createEntity('SpinningCylinder');
cylinderEntity.addComponent(new TransformComponent(
	new Vector3(0, 0.5, 2)
));

cylinderEntity.addComponent(new MeshComponent(cylinderMesh));
cylinderEntity.addComponent(new VelocityComponent(
	new Vector3(1, 0, 0),
	new Vector3(0, 0, Math.PI)
));

engine.registerUpdateCallback((deltaTime: number) =>
{
	world.update(deltaTime);
});

engine.setScene(scene);
engine.start();

console.log('🎮 ECS System Test Started!');
console.log(`📦 Entities: ${world.getEntityCount()}`);
console.log(`⚙️  Systems: ${world.getSystemCount()}`);
console.log('🔵 Sphere: Rotating on Y axis (Blue, left)');
console.log('🟧 Box: Moving up (Orange, right)');
console.log('🟢 Cylinder: Moving right + spinning (Green, center-front)');
