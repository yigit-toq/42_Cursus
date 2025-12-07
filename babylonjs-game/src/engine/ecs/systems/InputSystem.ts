import { System } from '../core/System';
import type { Entity } from '../core/Entity';
import { InputComponent } from '../components/InputComponent';
import { VelocityComponent } from '../components/VelocityComponent';
import { InputManager } from '../../input/InputManager';

export class InputSystem extends System
{
	private inputManager: InputManager;

	constructor()
	{
		super('InputSystem', ['Input']);
		this.inputManager = InputManager.getInstance();
	}

	public update(entities: Entity[], _deltaTime: number): void
	{
		for (const entity of entities)
		{
			const input = entity.getComponent<InputComponent>('Input');

			if (!input || !input.enabled) continue;

			const velocity = entity.getComponent<VelocityComponent>('Velocity');

			if (!velocity) continue;

			if (input.mapping.vertical)
			{
				const verticalAxis = this.inputManager.getAxis(
					input.mapping.vertical.negative,
					input.mapping.vertical.positive
				);
				velocity.linear.z = verticalAxis * 5;
			}

			if (input.mapping.horizontal)
			{
				const horizontalAxis = this.inputManager.getAxis(
					input.mapping.horizontal.negative,
					input.mapping.horizontal.positive
				);
				velocity.linear.x = horizontalAxis * 5;
			}
		}
	}
}
