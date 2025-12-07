/**
 * Fixed-timestep game loop implementation
 * Separates game logic (update) from rendering
 * Ensures deterministic gameplay across different frame rates
 * 
 * Based on "Fix Your Timestep!" article by Glenn Fiedler
 * https://gafferongames.com/post/fix_your_timestep/
 */

export class GameLoop
{
	private readonly targetFPS: number;
	private readonly FixedDeltaTime: number;
	private accumulator: number = 0;
	private lastTime: number = 0;
	private isRunning: boolean = false;
	private animatoinFrameId: number | null = null;

	constructor(targetFPS: number = 60)
	{
		this.targetFPS = targetFPS;
		this.FixedDeltaTime = 1000 / this.targetFPS;
	}

	public start(updateCallback: (deltaTime: number) => void, renderCallback: () => void): void
	{
		this.isRunning = true;
		this.lastTime = performance.now();

		const loop = (currentTime: number): void =>
		{
			if (!this.isRunning) return ;

			const frameTime = currentTime - this.lastTime;
			this.lastTime = currentTime;

			this.accumulator += Math.min(frameTime, 200);

			while (this.accumulator >= this.FixedDeltaTime)
			{
				updateCallback(this.FixedDeltaTime / 1000);
				this.accumulator -= this.FixedDeltaTime;
			}

			renderCallback();

			this.animatoinFrameId = requestAnimationFrame(loop);
		};

		this.animatoinFrameId = requestAnimationFrame(loop);
	}

	public stop(): void
	{
		this.isRunning = false;

		if (this.animatoinFrameId !== null)
		{
			cancelAnimationFrame(this.animatoinFrameId);
			this.animatoinFrameId = null;
		}
	}

	public getTargetFPS(): number
	{
		return this.targetFPS;
	}

	public getFixedDeltaTime(): number
	{
		return this.FixedDeltaTime / 1000;
	}

	public isActive(): boolean
	{
		return this.isRunning;
	}
}
