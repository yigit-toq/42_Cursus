import type { Component } from './Component';

export class Entity
{
	private static nextId = 0;

	public readonly id: number;
	public name: string;
	private components: Map<string, Component> = new Map();
	private active: boolean = true;

	constructor(name: string = 'Entity')
	{
		this.id = Entity.nextId++;
		this.name = name;
	}

	public addComponent<T extends Component>(component: T): this
	{
		this.components.set(component.type, component);
		return this;
	}

	public getComponent<T extends Component>(type: string): T | undefined
	{
		return this.components.get(type) as T | undefined;
	}

	public hasComponent(type: string): boolean
	{
		return this.components.has(type);
	}

	public removeComponent(type: string): boolean
	{
		return this.components.delete(type);
	}

	public getAllComponents(): Component[]
	{
		return Array.from(this.components.values());
	}

	public hasComponents(...types: string[]): boolean
	{
		return types.every(type => this.hasComponent(type));
	}

	public setActive(active: boolean): void
	{
		this.active = active;
	}

	public isActive(): boolean
	{
		return this.active;
	}

	public destroy(): void
	{
		this.active = false;
		this.components.clear();
	}
}
