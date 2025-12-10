import { CollisionComponent } from '../components/CollisionComponent';
import { TransformComponent } from '../components/TransformComponent';

import { CollisionDetection } from '../../physics/CollisionDetection';

import		{ Vector3 } from '@babylonjs/core/Maths/math.vector';

import		{ System } from '../core/System';

import type { Entity } from '../core/Entity';

export interface CollisionEvent
{
	entityA		: Entity;
	entityB		: Entity;

	normal		: Vector3;

	penetration	: number;
}

export class CollisionSystem extends System
{
	private collisionCallbacks: Map<number, (event: CollisionEvent) => void> = new Map();

	constructor()
	{
		super('CollisionSystem', ['Collision', 'Transform']);
	}

	public update(entities: Entity[], _deltaTime: number): void
	{
		for (const entity of entities)
		{
			const collision = entity.getComponent<CollisionComponent>('Collision');
			const transform = entity.getComponent<TransformComponent>('Transform');

			if (!collision || !collision.enabled || !transform) continue ;

			collision.updateBounds(transform.position, transform.scale);
		}

		for (let i = 0; i < entities.length; i++)
		{
			const entityA		= entities[i];
			const collisionA	= entityA.getComponent<CollisionComponent>('Collision');

			if (!collisionA || !collisionA.enabled) continue ;

			for (let j = i + 1; j < entities.length; j++)
			{
				const entityB		= entities[j];
				const collisionB	= entityB.getComponent<CollisionComponent>('Collision');

				if (!collisionB || !collisionB.enabled) continue ;

				if (!collisionA.canCollideWith(collisionB.layer)) continue ;
				if (!collisionB.canCollideWith(collisionA.layer)) continue ;

				// Collision detection
				if (CollisionDetection.checkAABB(collisionA.bounds, collisionB.bounds))
				{
					const normal		= CollisionDetection.getCollisionNormal	(
						collisionA.bounds,
						collisionB.bounds
					);
					const penetration	= CollisionDetection.getPenetrationDepth(
						collisionA.bounds,
						collisionB.bounds
					);

					if (!collisionA.isTrigger && !collisionB.isTrigger)
					{
						const transformA = entityA.getComponent<TransformComponent>('Transform');
						const transformB = entityB.getComponent<TransformComponent>('Transform');
						
						if (transformA && transformB)
						{
							const correction = normal.scale(penetration * 0.5);

							const isAStatic = collisionA.isStatic;
							const isBStatic = collisionB.isStatic;
							
							if (isAStatic && isBStatic) 
							{
								// Both static - no correction
							}
							else if (isAStatic)
							{
								// Only A is static - move B
								transformB.position.addInPlace		(correction.scale(2));
							}
							else if (isBStatic)
							{
								// Only B is static - move A
								transformA.position.subtractInPlace	(correction.scale(2));
							}
							else
							{
								// Both dynamic - push both
								transformA.position.subtractInPlace	(correction);

								transformB.position.addInPlace		(correction);
							}
						}
					}

					const event: CollisionEvent =
					{
						entityA	,
						entityB	,
						normal	,
						penetration
					};

					// Trigger callbacks
					this.triggerCollisionCallback(entityA.id, event);
					this.triggerCollisionCallback(entityB.id, event);
				}
			}
		}
	}

	public registerCollisionCallback	(entityId: number, callback: (event: CollisionEvent) => void): void
	{
		this.collisionCallbacks.set		(entityId, callback);
	}

	private triggerCollisionCallback	(entityId: number, event: CollisionEvent): void
	{
		const callback = this.collisionCallbacks.get(entityId);

		if (callback)
			callback(event);
	}

	public unregisterCollisionCallback	(entityId: number): void
	{
		this.collisionCallbacks.delete	(entityId);
	}
}
