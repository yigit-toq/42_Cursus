import type { Component } from '../core/Component';
import { AABB } from '../../physics/Bounds';
import { Vector3 } from '@babylonjs/core';

export enum CollisionLayer
{
	Default = 1 << 0,	// 1
	Player = 1 << 1,	// 2
	Ball = 1 << 2,		// 4
	Wall = 1 << 3,		// 8
	Trigger = 1 << 4	// 16 (for scoring zones)
}

export class CollisionComponent implements Component
{
	public readonly type = 'Collision';
	
	public bounds: AABB;
	public layer: CollisionLayer;
	public mask: number;
	public isTrigger: boolean;
	public isStatic: boolean;
	public enabled: boolean = true;

	constructor(
		size: Vector3,
		layer: CollisionLayer = CollisionLayer.Default,
		mask: number = 0xFFFFFFFF,
		isTrigger: boolean = false,
		isStatic: boolean = false
	) {
		this.bounds = AABB.fromCenterAndSize(Vector3.Zero(), size);
		this.layer = layer;
		this.mask = mask;
		this.isTrigger = isTrigger;
		this.isStatic = isStatic;
	}

	public canCollideWith(layer: CollisionLayer): boolean
	{
		return (this.mask & layer) !== 0;
	}

	public updateBounds(position: Vector3, scale: Vector3): void
	{
		const size = this.bounds.getSize();

		const scaledSize = new Vector3(
			size.x * scale.x,
			size.y * scale.y,
			size.z * scale.z
		);

		this.bounds.updatePosition(position, scaledSize);
	}
}
