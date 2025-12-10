import type { Component } from '../core/Component';

import		{ Vector3 } from '@babylonjs/core';

export class VelocityComponent implements Component
{
	public readonly type = 'Velocity';
	
	public linear	: Vector3;
	public angular	: Vector3;

	constructor(
		linear	: Vector3 = Vector3.Zero(),
		angular	: Vector3 = Vector3.Zero()
	)
	{
		this.linear		= linear	.clone();
		this.angular	= angular	.clone();
	}

	public setAngular	(x: number, y: number, z: number): void
	{
		this.angular.set(x, y, z);
	}

	public setLinear	(x: number, y: number, z: number): void
	{
		this.linear	.set(x, y, z);
	}

	public stop			(): void
	{
		this.angular.setAll(0);
		this.linear	.setAll(0);
	}
}
