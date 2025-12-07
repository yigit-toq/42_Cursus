import type { Component } from '../core/Component';

export interface InputMapping
{
	vertical?: { negative: string; positive: string };
	horizontal?: { negative: string; positive: string };
	action1?: string;
	action2?: string;
}

export class InputComponent implements Component
{
	public readonly type = 'Input';
	
	public mapping: InputMapping;
	public enabled: boolean = true;

	constructor(mapping: InputMapping) {
		this.mapping = mapping;
	}

	public setEnabled(enabled: boolean): void {
		this.enabled = enabled;
	}
}
