import { Vector3 } from '@babylonjs/core';

import { AABB } from './Bounds';

export class CollisionDetection
{
	public static checkAABB(a: AABB, b: AABB): boolean
	{
		return a.intersects(b);
	}

	public static getCollisionNormal(a: AABB, b: AABB): Vector3
	{
		const centerA = a.getCenter();
		const centerB = b.getCenter();

		const delta = centerB.subtract(centerA);

		const aSize = a.getSize();
		const bSize = b.getSize();
		
		const overlapX = (aSize.x + bSize.x) * 0.5 - Math.abs(delta.x);
		const overlapY = (aSize.y + bSize.y) * 0.5 - Math.abs(delta.y);
		const overlapZ = (aSize.z + bSize.z) * 0.5 - Math.abs(delta.z);

		if (overlapX < overlapY && overlapX < overlapZ)
		{
			return new Vector3(Math.sign(delta.x), 0, 0);
		}
		else if (overlapY < overlapZ)
		{
			return new Vector3(0, Math.sign(delta.y), 0);
		}
		else
		{
			return new Vector3(0, 0, Math.sign(delta.z));
		}
	}

	public static getPenetrationDepth(a: AABB, b: AABB): number
	{
		const xOverlap = Math.min(a.max.x - b.min.x, b.max.x - a.min.x);
		const yOverlap = Math.min(a.max.y - b.min.y, b.max.y - a.min.y);
		const zOverlap = Math.min(a.max.z - b.min.z, b.max.z - a.min.z);
		
		return Math.min(xOverlap, yOverlap, zOverlap);
	}

	public static reflect(velocity: Vector3, normal: Vector3): Vector3
	{
		// v' = v - 2(v·n)n
		const dot = Vector3.Dot	(velocity, normal);

		return velocity.subtract(normal.scale(2 * dot));
	}
}
