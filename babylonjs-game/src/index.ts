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

// Rendering
export { SceneManager } from './engine/render/SceneManager';

// Types
export * from './types/index';
