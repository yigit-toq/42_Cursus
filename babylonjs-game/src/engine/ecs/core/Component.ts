export interface Component
{
	readonly type: string;
}

export type ComponentConstructor<T extends Component> = new (...args: any[]) => T;
