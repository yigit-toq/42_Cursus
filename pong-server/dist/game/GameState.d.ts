import { type Vector3 } from "./Physics";
export declare class GameState {
    readonly ARENA_W: number;
    readonly ARENA_H: number;
    readonly PADDLE_W: number;
    readonly PADDLE_H: number;
    readonly PADDLE_DEPTH: number;
    readonly PADDLE_SPEED: number;
    readonly BALL_RADIUS: number;
    readonly BALL_SPEED: number;
    ballPosition: Vector3;
    ballVelocity: Vector3;
    paddle1Position: number;
    paddle2Position: number;
    score: {
        player1: number;
        player2: number;
    };
    maxScore: number;
    isGameOver: boolean;
    constructor();
    update(deltaTime: number, playerInput: {
        player1: number;
        player2: number;
    }): void;
    private updatePaddles;
    private updateSinglePaddle;
    private updateBall;
    private handlePaddleCollision;
    private checkCollisions;
    private checkScore;
    private resetBall;
    private getBallVelocity;
    private getBallAABB;
    private getPaddle1AABB;
    private getPaddle2AABB;
    reset(): void;
}
//# sourceMappingURL=GameState.d.ts.map