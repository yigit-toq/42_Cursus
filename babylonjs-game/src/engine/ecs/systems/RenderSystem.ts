import { System } from '../core/System';
import type { Entity } from '../core/Entity';
import { TransformComponent } from '../components/TransformComponent';
import { MeshComponent } from '../components/MeshComponent';

export class RenderSystem extends System
{
	constructor()
	{
		super('RenderSystem', ['Transform', 'Mesh']);
	}

	public update(entities: Entity[], _deltaTime: number): void
	{
		for (const entity of entities)
		{
			const transform = entity.getComponent<TransformComponent>('Transform');
			const mesh = entity.getComponent<MeshComponent>('Mesh');

			if (!transform || !mesh) continue ;

			transform.applyToMesh(mesh.mesh);
		}
	}
}
