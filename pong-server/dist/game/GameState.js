"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.GameState = void 0;
const Physics_1 = require("./Physics");
class GameState {
    // Arena properties
    ARENA_W = 20;
    ARENA_H = 12;
    // Paddle properties
    PADDLE_W = 0.5;
    PADDLE_H = 1;
    PADDLE_DEPTH = 3;
    PADDLE_SPEED = 8;
    // Ball properties
    BALL_RADIUS = 0.4;
    BALL_SPEED = 10;
    // Game state
    ballPosition;
    ballVelocity;
    paddle1Position;
    paddle2Position;
    score;
    maxScore = 3;
    isGameOver = false;
    constructor() {
        this.ballPosition = { x: 0, y: 0.5, z: 0 };
        this.ballVelocity = this.getBallVelocity();
        this.paddle1Position = 0;
        this.paddle2Position = 0;
        this.score = { player1: 0, player2: 0 };
    }
    update(deltaTime, playerInput) {
        if (this.isGameOver)
            return;
        this.updatePaddles(deltaTime, playerInput);
        this.updateBall(deltaTime);
        this.checkCollisions();
        this.checkScore();
    }
    updatePaddles(deltaTime, playerInput) {
        this.updateSinglePaddle("paddle1Position", playerInput.player1, deltaTime);
        this.updateSinglePaddle("paddle2Position", playerInput.player2, deltaTime);
    }
    updateSinglePaddle(key, input, deltaTime) {
        this[key] += input * this.PADDLE_SPEED * deltaTime;
        const halfArena = this.ARENA_H * 0.5;
        const paddleHalf = this.PADDLE_DEPTH * 0.5;
        const min = -halfArena + paddleHalf;
        const max = +halfArena - paddleHalf;
        this[key] = Math.max(min, Math.min(max, this[key]));
    }
    updateBall(deltaTime) {
        this.ballPosition.x += this.ballVelocity.x * deltaTime;
        this.ballPosition.y += this.ballVelocity.y * deltaTime;
        this.ballPosition.z += this.ballVelocity.z * deltaTime;
    }
    handlePaddleCollision(ballAABB, paddleAABB, isLeft) {
        if (!Physics_1.Physics.checkAABBCollision(ballAABB, paddleAABB))
            return;
        const normal = Physics_1.Physics.getCollisionNormal(ballAABB, paddleAABB);
        this.ballVelocity = Physics_1.Physics.reflect(this.ballVelocity, normal);
        if (isLeft) {
            this.ballPosition.x = paddleAABB.max.x + this.BALL_RADIUS;
        }
        else {
            this.ballPosition.x = paddleAABB.min.x - this.BALL_RADIUS;
        }
        // Ball speed-up (%5)
        const speed = Math.hypot(this.ballVelocity.x, this.ballVelocity.y, this.ballVelocity.z);
        const n = Physics_1.Physics.normalize(this.ballVelocity);
        this.ballVelocity = Physics_1.Physics.scale(n, speed * 1.05);
    }
    checkCollisions() {
        const ballAABB = this.getBallAABB();
        const halfArena = this.ARENA_H * 0.5;
        const botLimit = -halfArena + this.BALL_RADIUS;
        const topLimit = +halfArena - this.BALL_RADIUS;
        if (this.ballPosition.z <= botLimit) {
            this.ballPosition.z = botLimit;
            this.ballVelocity.z = +Math.abs(this.ballVelocity.z);
        }
        else if (this.ballPosition.z >= topLimit) {
            this.ballPosition.z = topLimit;
            this.ballVelocity.z = -Math.abs(this.ballVelocity.z);
        }
        // --- Paddle collisions ---
        this.handlePaddleCollision(ballAABB, this.getPaddle1AABB(), true);
        this.handlePaddleCollision(ballAABB, this.getPaddle2AABB(), false);
    }
    checkScore() {
        const halfArena = this.ARENA_W * 0.5;
        if (this.ballPosition.x < -halfArena) {
            this.score.player2++;
            this.resetBall();
        }
        else if (this.ballPosition.x > +halfArena) {
            this.score.player1++;
            this.resetBall();
        }
        if (this.score.player1 >= this.maxScore || this.score.player2 >= this.maxScore) {
            this.isGameOver = true;
        }
    }
    resetBall() {
        this.ballPosition = { x: 0, y: 0.5, z: 0 };
        this.ballVelocity = this.getBallVelocity();
    }
    getBallVelocity() {
        const maxAngle = Math.PI / 6;
        const angle = (Math.random() * 2 - 1) * maxAngle;
        const dir = Math.random() < 0.5 ? -1 : 1;
        const speed = this.BALL_SPEED;
        return {
            x: Math.cos(angle) * speed * dir,
            y: 0,
            z: Math.sin(angle) * speed
        };
    }
    getBallAABB() {
        const size = this.BALL_RADIUS * 2;
        return Physics_1.Physics.createAABB(Physics_1.Physics.emptyAABB(), this.ballPosition, { x: size, y: size, z: size });
    }
    getPaddle1AABB() {
        const x = -this.ARENA_W / 2 + 1;
        return Physics_1.Physics.createAABB(Physics_1.Physics.emptyAABB(), { x, y: 0.5, z: this.paddle1Position }, { x: this.PADDLE_W, y: this.PADDLE_H, z: this.PADDLE_DEPTH });
    }
    getPaddle2AABB() {
        const x = +this.ARENA_W / 2 - 1;
        return Physics_1.Physics.createAABB(Physics_1.Physics.emptyAABB(), { x, y: 0.5, z: this.paddle2Position }, { x: this.PADDLE_W, y: this.PADDLE_H, z: this.PADDLE_DEPTH });
    }
    reset() {
        this.ballPosition = { x: 0, y: 0.5, z: 0 };
        this.ballVelocity = this.getBallVelocity();
        this.paddle1Position = 0;
        this.paddle2Position = 0;
        this.score = { player1: 0, player2: 0 };
        this.isGameOver = false;
    }
}
exports.GameState = GameState;
//# sourceMappingURL=GameState.js.map