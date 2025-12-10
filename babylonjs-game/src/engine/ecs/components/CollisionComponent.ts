import type { Component } from '../core/Component';

import		{ Vector3 } from '@babylonjs/core';

import		{ AABB } from '../../physics/Bounds';

export enum CollisionLayer
{
	Default	= 1 << 0,	// 1
	Player	= 1 << 1,	// 2
	Ball	= 1 << 2,	// 4
	Wall	= 1 << 3,	// 8
	Trigger	= 1 << 4	// 16 (for scoring zones)
}

export class CollisionComponent implements Component
{
	public readonly type = 'Collision';

	public mask		: number;
	public layer	: CollisionLayer;

	public bounds	: AABB;

	public enabled	: boolean = true;

	public isStatic	: boolean;
	public isTrigger: boolean;

	constructor(
		size		: Vector3,
		mask		: number			= 0xFFFFFFFF,
		layer		: CollisionLayer	= CollisionLayer.Default,
		isStatic	: boolean			= false,
		isTrigger	: boolean			= false
	) {
		this.bounds		= AABB.fromCenterAndSize(Vector3.Zero(), size);
		this.mask		= mask;
		this.layer		= layer;
		this.isStatic	= isStatic;
		this.isTrigger	= isTrigger;
	}

	public canCollideWith	(layer: CollisionLayer): boolean
	{
		return (this.mask & layer) !== 0;
	}

	public updateBounds		(position: Vector3, scale: Vector3): void
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
