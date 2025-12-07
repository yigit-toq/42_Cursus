import { Vector3 } from '@babylonjs/core';

export class AABB
{
	public min: Vector3;
	public max: Vector3;

	constructor(min: Vector3, max: Vector3)
	{
		this.min = min.clone();
		this.max = max.clone();
	}

	public static fromCenterAndSize(center: Vector3, size: Vector3): AABB
	{
		const halfSize = size.scale(0.5);

		const min = center.subtract(halfSize);
		const max = center.add(halfSize);

		return new AABB(min, max);
	}

	public updatePosition(center: Vector3, size: Vector3): void
	{
		const halfSize = size.scale(0.5);

		this.min = center.subtract(halfSize);
		this.max = center.add(halfSize);
	}

	public intersects(other: AABB): boolean
	{
		return (this.min.x <= other.max.x && this.max.x >= other.min.x) &&
			   (this.min.y <= other.max.y && this.max.y >= other.min.y) &&
			   (this.min.z <= other.max.z && this.max.z >= other.min.z);
	}

	public getCenter(): Vector3
	{
		return this.min.add(this.max).scale(0.5);
	}

	public getSize(): Vector3
	{
		return this.max.subtract(this.min);
	}

	public clone(): AABB
	{
		return new AABB(this.min, this.max);
	}
}
