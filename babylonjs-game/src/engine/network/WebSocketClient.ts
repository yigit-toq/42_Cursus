import type { ClientMessage, ServerMessage } from './MessageTypes';

export class WebSocketClient
{
	private url						: string;
	private socket					: WebSocket | null = null;

	private isConnecting			: boolean = false;

	private reconnectDelay			: number = 2000;
	private reconnectAttempts		: number = 0;
	private maxReconnectAttempts	: number = 5;

	private messageHandlers			: Map<string, Array<(message: any) => void>> = new Map();

	constructor(url: string = 'ws://localhost:8080')
	{
		this.url = url;
	}

	public connect(): Promise<void>
	{
		return new Promise((resolve, reject) =>
		{
			if (this.socket?.readyState === WebSocket.OPEN)
			{
				resolve();
				return ;
			}

			if (this.isConnecting)
			{
				reject(new Error('Already connecting'));
				return ;
			}

			this.isConnecting = true;

			try
			{
				this.socket = new WebSocket(this.url);

				this.socket.onopen = () =>
				{
					console.log('✅ Connected to game server');

					this.reconnectAttempts	= 0;
					this.isConnecting		= false;

					resolve();
				};

				this.socket.onmessage = (event) =>
				{
					this.handleMessage(event.data);
				};

				this.socket.onclose = () =>
				{
					console.log('👋 Disconnected from game server');

					this.isConnecting = false;

					this.attemptReconnect();
				};

				this.socket.onerror = (error) =>
				{
					console.error('❌ WebSocket error:', error);

					this.isConnecting = false;

					reject(error);
				};
			}
			catch (error)
			{
				this.isConnecting = false;

				reject(error);
			}
		});
	}

	private attemptReconnect(): void
	{
		if (this.reconnectAttempts >= this.maxReconnectAttempts)
		{
			console.error('❌ Max reconnect attempts reached');
			return ;
		}

		this.reconnectAttempts++;

		console.log(`🔄 Reconnecting... (${this.reconnectAttempts}/${this.maxReconnectAttempts})`);

		setTimeout(() =>
		{
			this.connect().catch((error) =>
			{
				console.error('❌ Reconnect failed:', error);
			});
		}, this.reconnectDelay);
	}

	public send(message: ClientMessage): void
	{
		if (this.socket?.readyState !== WebSocket.OPEN)
		{
			console.error('❌ Cannot send message: Not connected');
			return ;
		}

		this.socket.send(JSON.stringify(message));
	}

	private handleMessage(data: string): void
	{
		try
		{
			const message: ServerMessage = JSON.parse	(data);

			const handlers	= this.messageHandlers.get	(message.type);

			if (handlers) 
				handlers	.forEach(handler => handler	(message));

			const gHandlers	= this.messageHandlers.get	('*');

			if (gHandlers)
				gHandlers	.forEach(handler => handler	(message));
		}
		catch (error)
		{
			console.error('❌ Error parsing server message:', error);
		}
	}

	public on(messageType: string, handler: (message: any) => void): void
	{
		if (!this.messageHandlers.has(messageType))
			 this.messageHandlers.set(messageType, []);

		this.messageHandlers.get(messageType)!.push(handler);
	}

	public off(messageType: string, handler: (message: any) => void): void
	{
		const handlers = this.messageHandlers.get(messageType);

		if (handlers)
		{
			const index = handlers.indexOf(handler);

			if (index !== -1)
				handlers.splice(index, 1);
		}
	}

	public isConnected(): boolean
	{
		return this.socket?.readyState === WebSocket.OPEN;
	}

	public disconnect(): void
	{
		if (this.socket)
		{
			this.socket.close();
			this.socket = null ;
		}

		this.reconnectAttempts = this.maxReconnectAttempts;
	}

	/**
	 * Get latency (ping)
	 */
	public async measureLatency(): Promise<number>
	{
		return new Promise((resolve) =>
		{
			const startTime		= Date.now();
			
			const handler		= () =>
			{
				const latency 	= Date.now() - startTime;

				this.off('PONG', handler);
				resolve	(latency);
			};

			this.on		('PONG', handler);

			this.send
			({
				type		: 'PING' as any,
				timestamp	: startTime
			});

			setTimeout(() =>
			{
				this.off('PONG', handler);
				resolve	(-1);
			}, 5000);
		});
	}
}
