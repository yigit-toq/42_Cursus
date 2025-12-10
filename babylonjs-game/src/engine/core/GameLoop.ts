export class GameLoop
{
	private readonly FixedDeltaTime	: number;
	private readonly targetFPS		: number;

	private accumulator				: number = 0;
	private lastTime				: number = 0;

	private isRunning				: boolean = false;

	private animatoinFrameID		: number | null = null;

	constructor(targetFPS: number = 60)
	{
		this.targetFPS		= targetFPS;

		this.FixedDeltaTime	= 1000 / this.targetFPS;
	}

	public start(updateCallback: (deltaTime: number) => void, renderCallback: () => void): void
	{
		this.isRunning	= true;
		this.lastTime	= performance.now();

		const loop = (currentTime: number): void =>
		{
			if (!this.isRunning) return ;

			const frameTime	= currentTime - this.lastTime;
			this.lastTime	= currentTime;

			this.accumulator += Math.min(frameTime, 200);

			while (this.accumulator >= this.FixedDeltaTime)
			{
				updateCallback(this.FixedDeltaTime / 1000);

				this.accumulator -= this.FixedDeltaTime;
			}

			renderCallback();

			this.animatoinFrameID = requestAnimationFrame(loop); // will be checked
		};

		this.animatoinFrameID = requestAnimationFrame(loop);
	}

	public stop	(): void
	{
		this.isRunning = false;

		if (this.animatoinFrameID !== null)
		{
			cancelAnimationFrame(this.animatoinFrameID);

			this.animatoinFrameID = null;
		}
	}

	public isActive(): boolean
	{
		return this.isRunning;
	}

	public getTargetFPS		(): number
	{
		return this.targetFPS;
	}

	public getFixedDeltaTime(): number
	{
		return this.FixedDeltaTime / 1000;
	}
}
