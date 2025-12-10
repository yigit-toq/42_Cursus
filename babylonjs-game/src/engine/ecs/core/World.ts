import { Entity } from './Entity';
import { System } from './System';

export class World
{
	private systems				: System[] = [];

	private entities			: Map<number, Entity> = new Map();
	private entitiesToDestroy	: Set<number> = new Set();

	public createEntity(name?: string): Entity
	{
		const entity = new Entity(name);

		this .entities.set(entity.id, entity);

		return entity;
	}

	public getEntity(id: number): Entity | undefined
	{
		return this.entities.get(id);
	}

	public getEntities(): Entity[]
	{
		return Array.from(this.entities.values());
	}

	public getEntitiesWithComponents(...componentTypes: string[]): Entity[]
	{
		return this	.getEntities().filter(entity => 
			entity	.isActive	() && entity.hasComponents(...componentTypes)
		);
	}

	public destroyEntity(entityId: number): void
	{
		this.entitiesToDestroy.add(entityId);
	}

	public addSystem(system: System): this
	{
		this.systems.push(system);

		if (system.onInit)
		{
			system.onInit();
		}
		return this;
	}

	public removeSystem(systemName: string): boolean
	{
		const index = this.systems.findIndex(s => s.name === systemName);

		if (index !== -1)
		{
			const system = this.systems[index];

			if (system.onDestroy)
			{
				system.onDestroy();
			}
			this.systems.splice	(index, 1);

			return true;
		}

		return false;
	}

	public getSystem(name: string): System | undefined
	{
		return this.systems.find(s => s.name === name);
	}

	public update(deltaTime: number): void
	{
		for (const system of this.systems)
		{
			if (!system	.isEnabled	()) continue ;

			const matchingEntities = this.getEntities().filter(entity =>
				entity	.isActive	() && system.matchesEntity(entity)
			);

			system.update(matchingEntities, deltaTime);
		}

		this.cleanupDestroyedEntities();
	}

	private cleanupDestroyedEntities(): void
	{
		for (const id of this.entitiesToDestroy)
		{
			 const entity = this.entities.get(id);

			if (entity)
			{
				entity.destroy		()	;
				this.entities.delete(id);
			}
		}
		this.entitiesToDestroy.clear();
	}

	public clear(): void
	{
		for (const system of this.systems)
		{
			if (system.onDestroy)
				system.onDestroy();
		}
		this.systems = [];

		for (const entity of this.entities.values())
		{
			entity.destroy();
		}
		this.entities			.clear();
		this.entitiesToDestroy	.clear();
	}

	public getEntityCount(): number
	{
		return this.entities.size;
	}

	public getSystemCount(): number
	{
		return this.systems	.length;
	}
}
