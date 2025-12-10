import type { Entity } from "./Entity";

export abstract class System
{
	public readonly name				: string;

	private			enabled				: boolean = true;

	protected		requiredComponents	: string[];

	constructor(name: string, requiredComponents: string[] = [])
	{
		this.name				= name;
		this.requiredComponents	= requiredComponents;
	}

	public matchesEntity(entity: Entity): boolean
	{
		return entity.hasComponents(...this.requiredComponents);
	}

	public abstract update(entities: Entity[], deltaTime: number): void;

	public onInit	?(): void;

	public onDestroy?(): void;

	public isEnabled (): boolean
	{
		return this.enabled;
	}

	public setEnabled(enabled: boolean): void
	{
		this.enabled = enabled;
	}
}
