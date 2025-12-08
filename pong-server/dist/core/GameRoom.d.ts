import { Player } from './Player';
import { GameState } from '../game/GameState';
export declare class GameRoom {
    id: string;
    player1: Player | null;
    player2: Player | null;
    isActive: boolean;
    gameState: GameState;
    tickRate: number;
    private tickInterval;
    private lastTickTime;
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