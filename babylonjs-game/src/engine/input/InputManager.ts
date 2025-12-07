export class InputManager
{
	private static instance: InputManager;

	private keysPressed: Set<string> = new Set();
	private keysDown: Set<string> = new Set();
	private keysUp: Set<string> = new Set();

	private mousePosition: { x: number; y: number } = { x: 0, y: 0 };
	private mouseButtons: Set<number> = new Set();

	private canvas: HTMLCanvasElement | null = null;

	private constructor()
	{

	}

	public static getInstance()
	{
		if (!InputManager.instance)
		{
			InputManager.instance = new InputManager();
		}
		return InputManager.instance;
	}

	public initialize(canvas: HTMLCanvasElement): void
	{
		this.canvas = canvas;
		this.setupKeyboardListeners();
		this.setupMouseListeners();
	}

	private setupKeyboardListeners(): void
	{
		window.addEventListener('keydown', (event) =>
		{
			if (!this.keysPressed.has(event.code)) {
				this.keysDown.add(event.code);
			}
			this.keysPressed.add(event.code);
		});
		window.addEventListener('keyup', (event) =>
		{
			this.keysPressed.delete(event.code);
			this.keysUp.add(event.code);
		});
	}

	private setupMouseListeners(): void
	{
		if (!this.canvas) return;

		this.canvas.addEventListener('mousemove', (event) =>
		{
			const rect = this.canvas!.getBoundingClientRect();
			this.mousePosition.x = event.clientX - rect.left;
			this.mousePosition.y = event.clientY - rect.top;
		});

		this.canvas.addEventListener('mousedown', (event) =>
		{
			this.mouseButtons.add(event.button);
		});

		this.canvas.addEventListener('mouseup', (event) =>
		{
			this.mouseButtons.delete(event.button);
		});
	}

	public isKeyPressed(keyCode: string): boolean
	{
		return this.keysPressed.has(keyCode);
	}

	public isKeyDown(keyCode: string): boolean
	{
		return this.keysDown.has(keyCode);
	}

	public isKeyUp(keyCode: string): boolean
	{
		return this.keysUp.has(keyCode);
	}

	public isMouseButtonPressed(button: number): boolean
	{
		return this.mouseButtons.has(button);
	}

	public getMousePosition(): { x: number; y: number }
	{
		return { ...this.mousePosition };
	}

	public update(): void
	{
		this.keysDown.clear();
		this.keysUp.clear();
	}

	public getAxis(positiveKey: string, negativeKey: string): number
	{
		let axis = 0;
		if (this.isKeyPressed(positiveKey)) axis += 1;
		if (this.isKeyPressed(negativeKey)) axis -= 1;
		return axis;
	}


	public dispose(): void
	{
		this.keysPressed.clear();
		this.keysDown.clear();
		this.keysUp.clear();
		this.mouseButtons.clear();
	}
}
