import type { WebSocket } from 'ws';
export declare class Player {
    id: string;
    name: string;
    socket: WebSocket;
    roomID: string | null;
    playerN: 1 | 2 | null;
    isReady: boolean;
    lastPing: number;
    paddlePos: number;
    input: number;
    constructor(id: string, socket: WebSocket, name?: string);
    send(data: any): void;
    isConnected(): boolean;
    updateInput(vertical: number): void;
    reset(): void;
}
//# sourceMappingURL=Player.d.ts.map