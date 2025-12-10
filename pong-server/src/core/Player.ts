import type { WebSocket } from 'ws';

export class Player
{
	public id		: string;
	public name		: string;

	public input	: number		= 0;	

	public socket	: WebSocket;

	public roomID	: string | null = null;

	public playerN	: 1 | 2  | null = null;

	public isReady	: boolean		= false;

	public lastPing	: number		= Date.now();

	public paddlePos: number		= 0;

	constructor(id: string, socket: WebSocket, name?: string)
	{
		this.socket	= socket;
		this.id		= id;

		this.name = name || `Player_${id}`;
	}

	public send(data: any): void
	{
		if (this.socket.readyState === 1)
		{
			this.socket.send(JSON.stringify(data));
		}
	}

	public isConnected(): boolean
	{
		return this.socket.readyState === 1;
	}

	public updateInput(vertical: number): void
	{
		this.input = Math.max(-1, Math.min(1, vertical));
	}

	public reset(): void
	{
		this.isReady	= false;

		this.input		= 0;
		this.paddlePos	= 0;
	}
}
