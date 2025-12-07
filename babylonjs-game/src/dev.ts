/**
 * Development entry point
 * 
 * This file is only used during development with Vite.
 * It demonstrates how to use the game engine.
 */

import { GameEngine } from './engine/core/GameEngine';
import { SceneManager } from './engine/render/SceneManager';
import { MeshBuilder, Vector3, StandardMaterial, Color3 } from '@babylonjs/core';

// Initialize the engine
const gameEngine = new GameEngine({
  canvasId: 'gameCanvas',
  antialias: true,
  adaptToDeviceRatio: true,
});

// Create scene manager
const sceneManager = new SceneManager(gameEngine);

// Setup camera and lighting
sceneManager.setupDefaultCamera(new Vector3(0, 0, 0));
sceneManager.setupDefaultLighting();

// Get the scene
const scene = sceneManager.getScene();

// Add a test sphere
const sphere = MeshBuilder.CreateSphere('sphere', { diameter: 2 }, scene);
sphere.position.y = 1;

const sphereMaterial = new StandardMaterial('sphereMat', scene);
sphereMaterial.diffuseColor = new Color3(0.4, 0.7, 1.0);
sphere.material = sphereMaterial;

// Add a ground
const ground = MeshBuilder.CreateGround('ground', { width: 10, height: 10 }, scene);
const groundMaterial = new StandardMaterial('groundMat', scene);
groundMaterial.diffuseColor = new Color3(0.2, 0.2, 0.25);
ground.material = groundMaterial;

// Set the scene and start the engine
gameEngine.setScene(scene);
gameEngine.start();

console.log('✅ Game Engine initialized successfully!');
console.log('📦 Engine:', gameEngine);
console.log('🎬 Scene:', scene);

// Cleanup on page unload
window.addEventListener('beforeunload', () => {
  gameEngine.dispose();
});
