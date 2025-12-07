import { AbstractMesh } from '@babylonjs/core';
import type { Component } from '../core/Component';

export class MeshComponent implements Component
{
	public readonly type = 'Mesh';
	
	public mesh: AbstractMesh;
	public visible: boolean = true;

	constructor(mesh: AbstractMesh)
	{
		this.mesh = mesh;
	}

	public setVisible(visible: boolean): void
	{
		this.visible = visible;
		this.mesh.setEnabled(visible);
	}

	public dispose(): void
	{
		this.mesh.dispose();
	}
}
