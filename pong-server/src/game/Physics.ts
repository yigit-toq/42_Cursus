export interface Vector3
{
	x: number;
	y: number;
	z: number;
}

export interface AABB
{
	min: Vector3;
	max: Vector3;
}

export class Physics
{
	public static createAABB(out: AABB, center: Vector3, size: Vector3): AABB
	{
		const hx = size.x * 0.5;
		const hy = size.y * 0.5;
		const hz = size.z * 0.5;

		out.min.x = center.x - hx;
		out.min.y = center.y - hy;
		out.min.z = center.z - hz;

		out.max.x = center.x + hx;
		out.max.y = center.y + hy;
		out.max.z = center.z + hz;

		return out;
	}

	public static emptyAABB(): AABB
	{
		return {
			min: { x: 0, y: 0, z: 0 },
			max: { x: 0, y: 0, z: 0 }
		};
	}

	public static checkAABBCollision(a: AABB, b: AABB): boolean
	{
		return !(
			a.max.x < b.min.x ||
			a.min.x > b.max.x ||
			a.max.y < b.min.y ||
			a.min.y > b.max.y ||
			a.max.z < b.min.z ||
			a.min.z > b.max.z
		);
	}

	public static getCollisionNormal(a: AABB, b: AABB): Vector3
	{
		// Center delta
		const dx = ((b.min.x + b.max.x) - (a.min.x + a.max.x)) * 0.5;
		const dy = ((b.min.y + b.max.y) - (a.min.y + a.max.y)) * 0.5;
		const dz = ((b.min.z + b.max.z) - (a.min.z + a.max.z)) * 0.5;

		// Half-size sums
		const overlapX = ( (a.max.x - a.min.x) + (b.max.x - b.min.x) ) * 0.5 - Math.abs(dx);
		const overlapY = ( (a.max.y - a.min.y) + (b.max.y - b.min.y) ) * 0.5 - Math.abs(dy);
		const overlapZ = ( (a.max.z - a.min.z) + (b.max.z - b.min.z) ) * 0.5 - Math.abs(dz);

		// Choose minimum penetration axis
		if (overlapX <= overlapY && overlapX <= overlapZ)
		{
			return { x: Math.sign(dx), y: 0, z: 0 };
		}
		if (overlapY <= overlapZ)
		{
			return { x: 0, y: Math.sign(dy), z: 0 };
		}

		return { x: 0, y: 0, z: Math.sign(dz) };
	}

	public static reflect(velocity: Vector3, normal: Vector3): Vector3
	{
		const dot = velocity.x * normal.x + velocity.y * normal.y + velocity.z * normal.z;

		return {
			x: velocity.x - 2 * dot * normal.x,
			y: velocity.y - 2 * dot * normal.y,
			z: velocity.z - 2 * dot * normal.z
		};
	}

	public static normalize(v: Vector3): Vector3
	{
		const length = Math.sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

		if (length === 0) return { x: 0, y: 0, z: 0 };

		return {
			x: v.x / length,
			y: v.y / length,
			z: v.z / length
		};
	}

	public static scale(v: Vector3, scalar: number): Vector3
	{
		return {
			x: v.x * scalar,
			y: v.y * scalar,
			z: v.z * scalar
		};
	}
}
