/**
 * Main entry point for the Game Engine
 * 
 * This file exports all public APIs that can be used by:
 * - Frontend applications
 * - Backend integration
 * - Test suites
 * 
 * Usage example:
 * ```typescript
 * import { GameEngine, SceneManager } from '@ft-transcendence/game-engine';
 * 
 * const engine = new GameEngine({ canvasId: 'gameCanvas' });
 * const sceneManager = new SceneManager(engine);
 * // ... setup game
 * engine.start();
 * ```
 */

// Core Engine
export { GameEngine } from './engine/core/GameEngine';
export { GameLoop } from './engine/core/GameLoop';

// Render System
export { SceneManager } from './engine/render/SceneManager';

// Input System
export { InputManager } from './engine/input/InputManager';

// ECS Core
export { Entity } from './engine/ecs/core/Entity';
export { System } from './engine/ecs/core/System';
export { World } from './engine/ecs/core/World';
export type { Component, ComponentConstructor } from './engine/ecs/core/Component';

// ECS Components
export { TransformComponent } from './engine/ecs/components/TransformComponent';
export { MeshComponent } from './engine/ecs/components/MeshComponent';
export { VelocityComponent } from './engine/ecs/components/VelocityComponent';
export { InputComponent } from './engine/ecs/components/InputComponent';
export type { InputMapping } from './engine/ecs/components/InputComponent';

// ECS Systems
export { MovementSystem } from './engine/ecs/systems/MovementSystem';
export { RenderSystem } from './engine/ecs/systems/RenderSystem';
export { InputSystem } from './engine/ecs/systems/InputSystem';

// Types
export type { GameConfig } from './types/index';
