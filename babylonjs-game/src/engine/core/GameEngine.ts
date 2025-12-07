/**
 * GameEngine.ts
 * 
 * Core game engine class that manages:
 * - Babylon.js engine lifecycle
 * - Scene management
 * - Game loop initialization
 * 
 * This class serves as the entry point for the game engine and can be
 * easily integrated into any frontend application.
 */

import { Engine, Scene } from '@babylonjs/core';
import type { GameConfig } from '../../types/index';

export class GameEngine {
  private canvas: HTMLCanvasElement;
  private engine: Engine;
  private scene: Scene | null = null;
  private isRunning: boolean = false;

  constructor(config: GameConfig) {
    const canvas = document.getElementById(config.canvasId) as HTMLCanvasElement;
    
    if (!canvas) {
      throw new Error(`Canvas element with id "${config.canvasId}" not found`);
    }

    this.canvas = canvas;
    this.engine = new Engine(this.canvas, config.antialias ?? true, {
      preserveDrawingBuffer: true,
      stencil: true,
      adaptToDeviceRatio: config.adaptToDeviceRatio ?? true,
    });

    this.setupResizeHandler();
  }

  private setupResizeHandler(): void {
    window.addEventListener('resize', () => {
      this.engine.resize();
    });
  }

  public getEngine(): Engine {
    return this.engine;
  }

  public getScene(): Scene | null {
    return this.scene;
  }

  public setScene(scene: Scene): void {
    this.scene = scene;
  }

  public start(): void {
    if (!this.scene) {
      throw new Error('Scene must be set before starting the engine');
    }

    if (this.isRunning) {
      console.warn('Engine is already running');
      return;
    }

    this.isRunning = true;
    this.engine.runRenderLoop(() => {
      this.scene?.render();
    });
  }

  public stop(): void {
    this.isRunning = false;
    this.engine.stopRenderLoop();
  }

  public dispose(): void {
    this.stop();
    this.scene?.dispose();
    this.engine.dispose();
  }

  public getCanvas(): HTMLCanvasElement {
    return this.canvas;
  }

  public isEngineRunning(): boolean {
    return this.isRunning;
  }
}
