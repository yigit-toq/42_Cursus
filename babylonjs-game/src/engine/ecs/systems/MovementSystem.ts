import { System } from '../core/System';
import type { Entity } from '../core/Entity';
import { TransformComponent } from '../components/TransformComponent';
import { VelocityComponent } from '../components/VelocityComponent';

export class MovementSystem extends System
{
	constructor() {
		super('MovementSystem', ['Transform', 'Velocity']);
	}

	public update(entities: Entity[], deltaTime: number): void
	{
		for (const entity of entities)
		{
			const transform = entity.getComponent<TransformComponent>('Transform');
			const velocity = entity.getComponent<VelocityComponent>('Velocity');

			if (!transform || !velocity) continue;

			const linearDelta = velocity.linear.scale(deltaTime);
			transform.position.addInPlace(linearDelta);

			const angularDelta = velocity.angular.scale(deltaTime);
			transform.rotation.addInPlace(angularDelta);
		}
	}
}
