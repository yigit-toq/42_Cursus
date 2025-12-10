import type { Component } from '../core/Component';

export interface InputMapping
{
	horizontal	?: { negative: string; positive: string };
	vertical	?: { negative: string; positive: string };

	action1		?: string;
	action2		?: string;
}

export class InputComponent implements Component
{
	private			axisValues	: Map<string, number> = new Map();

	public readonly	type		: string = 'Input';

	public			enabled		: boolean = true;
	public			mapping		: InputMapping;

	constructor(mapping: InputMapping)
	{
		this.mapping = mapping;
	}

	public getAxis		(axisName: string): number
	{
		return this.axisValues.get(axisName) || 0;
	}

	public setEnabled	(enabled: boolean): void
	{
		this.enabled = enabled;
	}
}
