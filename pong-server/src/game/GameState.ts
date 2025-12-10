import { Physics, type Vector3, type AABB } from "./Physics";

export class GameState
{
	// Arena properties
	public readonly ARENA_W: number = 20;
	public readonly ARENA_H: number = 12;

	// Paddle properties
	public readonly PADDLE_W: number = 0.5;
	public readonly PADDLE_H: number = 1;

	public readonly PADDLE_DEPTH: number = 3;
	public readonly PADDLE_SPEED: number = 8;

	// Ball properties
	public readonly BALL_RADIUS	: number = 0.4;
	public readonly BALL_SPEED	: number = 10;

	// Game state
	public ballPosition: Vector3;
	public ballVelocity: Vector3;

	public paddle1Position: number;
	public paddle2Position: number;

	public score: { player1: number; player2: number; };

	public maxScore		: number	= 3;

	public isGameOver	: boolean	= false;

	constructor()
	{
		this.ballPosition = { x: 0, y: 0.5, z: 0 };
		this.ballVelocity = this.getBallVelocity();
		this.paddle1Position = 0;
		this.paddle2Position = 0;
		this.score = { player1: 0, player2: 0 };
	}

	public update(deltaTime: number, playerInput: { player1: number; player2: number; }): void
	{
		if (this.isGameOver) return ;

		this.updatePaddles(deltaTime, playerInput);

		this.updateBall(deltaTime);

		this.checkCollisions();

		this.checkScore();
	}

	private updatePaddles(deltaTime: number, playerInput: { player1: number; player2: number }): void
	{
		this.updateSinglePaddle("paddle1Position", playerInput.player1, deltaTime);
		this.updateSinglePaddle("paddle2Position", playerInput.player2, deltaTime);
	}

	private updateSinglePaddle(key: "paddle1Position" | "paddle2Position", input: number, deltaTime: number): void
	{
		this[key] += input * this.PADDLE_SPEED * deltaTime;

		const halfArena		= this.ARENA_H * 0.5;
		const paddleHalf	= this.PADDLE_DEPTH * 0.5;

		const min = -halfArena + paddleHalf;
		const max = +halfArena - paddleHalf;

		this[key] = Math.max(min, Math.min(max, this[key]));
	}

	private updateBall(deltaTime: number): void
	{
		this.ballPosition.x += this.ballVelocity.x * deltaTime;
		this.ballPosition.y += this.ballVelocity.y * deltaTime;
		this.ballPosition.z += this.ballVelocity.z * deltaTime;
	}

	private handlePaddleCollision(ballAABB: AABB, paddleAABB: AABB, isLeft: boolean): void
	{
		if (!Physics.checkAABBCollision(ballAABB, paddleAABB)) return ;

		const normal = Physics.getCollisionNormal(ballAABB, paddleAABB);

		this.ballVelocity = Physics.reflect(this.ballVelocity, normal);

		if (isLeft)
		{
			this.ballPosition.x = paddleAABB.max.x + this.BALL_RADIUS;
		}
		else
		{
			this.ballPosition.x = paddleAABB.min.x - this.BALL_RADIUS;
		}

		// Ball speed-up (%5)
		const speed = Math.hypot(
			this.ballVelocity.x,
			this.ballVelocity.y,
			this.ballVelocity.z
		);

		const n = Physics.normalize(this.ballVelocity);

		this.ballVelocity = Physics.scale(n, speed * 1.05);
	}

	private checkCollisions(): void
	{
		const ballAABB	= this.getBallAABB();
		const halfArena	= this.ARENA_H * 0.5;

		const botLimit = -halfArena + this.BALL_RADIUS;
		const topLimit = +halfArena - this.BALL_RADIUS;

			 if (this.ballPosition.z <= botLimit)
		{
			this.ballPosition.z = botLimit;
			this.ballVelocity.z = +Math.abs(this.ballVelocity.z);
		}
		else if (this.ballPosition.z >= topLimit)
		{
			this.ballPosition.z = topLimit;
			this.ballVelocity.z = -Math.abs(this.ballVelocity.z);
		}

		// --- Paddle collisions ---
		this.handlePaddleCollision(ballAABB, this.getPaddle1AABB(), true );
		this.handlePaddleCollision(ballAABB, this.getPaddle2AABB(), false);
	}

	private checkScore(): void
	{
		const halfArena = this.ARENA_W * 0.5;

			 if (this.ballPosition.x < -halfArena)
		{
			this.score.player2++;
			this.resetBall();
		}
		else if (this.ballPosition.x > +halfArena)
		{
			this.score.player1++;
			this.resetBall();
		}

		if (this.score.player1 >= this.maxScore || this.score.player2 >= this.maxScore)
		{
			this.isGameOver = true;
		}
	}

	private resetBall(): void
	{
		this.ballPosition = { x: 0, y: 0.5, z: 0 };
		this.ballVelocity = this.getBallVelocity();
	}

	private getBallVelocity(): Vector3
	{
		const maxAngle	= Math.PI / 6;
		const angle		= (Math.random() * 2 - 1) * maxAngle;

		const dir = Math.random() < 0.5 ? -1 : 1;

		const speed = this.BALL_SPEED;

		return {
			x: Math.cos(angle) * speed * dir,
			y: 0,
			z: Math.sin(angle) * speed
		};
	}

	private getBallAABB(): AABB
	{
		const size = this.BALL_RADIUS * 2;

		return Physics.createAABB(
			Physics.emptyAABB(),
			this.ballPosition,
			{ x: size, y: size, z: size }
		);
	}

	private getPaddle1AABB(): AABB
	{
		const x = -this.ARENA_W / 2 + 1;

		return Physics.createAABB(
			Physics.emptyAABB(),
			{ x, y: 0.5, z: this.paddle1Position },
			{ x: this.PADDLE_W, y: this.PADDLE_H, z: this.PADDLE_DEPTH }
		);
	}

	private getPaddle2AABB(): AABB
	{
		const x = +this.ARENA_W / 2 - 1;

		return Physics.createAABB(
			Physics.emptyAABB(),
			{ x, y: 0.5, z: this.paddle2Position },
			{ x: this.PADDLE_W, y: this.PADDLE_H, z: this.PADDLE_DEPTH }
		);
	}

	public reset(): void
	{
		this.ballPosition = { x: 0, y: 0.5, z: 0 };
		this.ballVelocity = this.getBallVelocity();

		this.paddle1Position = 0;
		this.paddle2Position = 0;

		this.score = { player1: 0, player2: 0 };

		this.isGameOver = false;
	}
}
