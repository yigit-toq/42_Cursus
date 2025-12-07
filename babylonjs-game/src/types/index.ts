/**
 * Shared TypeScript types for the game engine
 * 
 * This file contains all shared type definitions, interfaces, and enums
 * used across the engine and game logic.
 */

export interface GameConfig {
  canvasId: string;
  width?: number;
  height?: number;
  antialias?: boolean;
  adaptToDeviceRatio?: boolean;
}

export interface Vec3 {
  x: number;
  y: number;
  z: number;
}

export interface Vec2 {
  x: number;
  y: number;
}

export enum GameState {
  IDLE = 'idle',
  PLAYING = 'playing',
  PAUSED = 'paused',
  GAME_OVER = 'game_over',
}

export type UpdateFunction = (deltaTime: number) => void;
export type RenderFunction = () => void;
