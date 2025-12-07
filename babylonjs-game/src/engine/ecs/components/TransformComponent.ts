import { AbstractMesh, Vector3 } from '@babylonjs/core';
import type { Component } from '../core/Component';

export class TransformComponent implements Component
{
	public readonly type = 'Transform';
	
	public position: Vector3;
	public rotation: Vector3;
	public scale: Vector3;

	constructor(
		position: Vector3 = Vector3.Zero(),
		rotation: Vector3 = Vector3.Zero(),
		scale: Vector3 = new Vector3(1, 1, 1)
	) {
		this.position = position.clone();
		this.rotation = rotation.clone();
		this.scale = scale.clone();
	}

	public applyToMesh(mesh: AbstractMesh): void
	{
		mesh.position.copyFrom(this.position);
		mesh.rotation.copyFrom(this.rotation);
		mesh.scaling.copyFrom(this.scale);
	}

	public copyFromMesh(mesh: AbstractMesh): void
	{
		this.position.copyFrom(mesh.position);
		this.rotation.copyFrom(mesh.rotation);
		this.scale.copyFrom(mesh.scaling);
	}

	public clone(): TransformComponent
	{
		return new TransformComponent(this.position, this.rotation, this.scale);
	}
}
