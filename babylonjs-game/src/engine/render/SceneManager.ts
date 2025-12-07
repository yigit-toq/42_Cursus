/**
 * SceneManager.ts
 * 
 * Manages Babylon.js scene lifecycle:
 * - Scene creation and configuration
 * - Camera setup
 * - Lighting configuration
 * - Basic scene utilities
 * 
 * This is a minimal implementation that can be extended with:
 * - Physics engine initialization
 * - Asset loading
 * - Post-processing effects
 */

import { Scene, ArcRotateCamera, HemisphericLight, Vector3 } from '@babylonjs/core';
import type { GameEngine } from '../core/GameEngine';

export class SceneManager {
  private scene: Scene;
  private camera: ArcRotateCamera | null = null;
  private light: HemisphericLight | null = null;

  constructor(gameEngine: GameEngine) {
    this.scene = new Scene(gameEngine.getEngine());
    this.scene.clearColor = { r: 0.1, g: 0.1, b: 0.15, a: 1.0 } as any;
  }

  public setupDefaultCamera(target: Vector3 = Vector3.Zero()): ArcRotateCamera {
    this.camera = new ArcRotateCamera(
      'camera',
      Math.PI / 2,
      Math.PI / 3,
      10,
      target,
      this.scene
    );
    this.camera.attachControl(true);
    this.camera.lowerRadiusLimit = 5;
    this.camera.upperRadiusLimit = 20;
    
    return this.camera;
  }

  public setupDefaultLighting(): HemisphericLight {
    this.light = new HemisphericLight(
      'light',
      new Vector3(0, 1, 0),
      this.scene
    );
    this.light.intensity = 0.7;
    
    return this.light;
  }

  public getScene(): Scene {
    return this.scene;
  }

  public getCamera(): ArcRotateCamera | null {
    return this.camera;
  }

  public dispose(): void {
    this.scene.dispose();
  }
}
