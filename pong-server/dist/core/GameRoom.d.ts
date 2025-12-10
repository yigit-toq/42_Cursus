import { GameState } from '../game/GameState';
import { Player } from './Player';
export declare class GameRoom {
    id: string;
    player1: Player | null;
    player2: Player | null;
    isActive: boolean;
    tickRate: number;
    private tickCount;
    gameState: GameState;
    private lastTickTime;
    private tickInterval;
    constructor(id: string);
    addPlayer(player: Player): boolean;
    removePlayer(playerId: string): void;
    isEmpty(): boolean;
    isFull(): boolean;
    private startGame;
    private startGameLoop;
    private tick;
    private broadcastGameState;
    private handleGoal;
    private handleGameOver;
    private notifyOpponentDisconnected;
    private stopGame;
    dispose(): void;
}
//# sourceMappingURL=GameRoom.d.ts.map