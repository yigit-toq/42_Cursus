export declare enum ClientMessageType {
    CONNECT = "CONNECT",
    DISCONNECT = "DISCONNECT",
    FIND_MATCH = "FIND_MATCH",
    INPUT = "INPUT",
    PING = "PING"
}
export declare enum ServerMessageType {
    PONG = "PONG",
    ERROR = "ERROR",
    WELCOME = "WELCOME",
    GAME_OVER = "GAME_OVER",
    GAME_STATE = "GAME_STATE",
    MATCH_FOUND = "MATCH_FOUND",
    GOAL_SCORED = "GOAL_SCORED",
    OPPONENT_DISCND = "OPPONENT_DISCND"
}
export interface ConnectMessage {
    type: ClientMessageType.CONNECT;
    playerName?: string;
}
export interface FindMatchMessage {
    type: ClientMessageType.FIND_MATCH;
}
export interface InputMessage {
    type: ClientMessageType.INPUT;
    input: {
        vertical: number;
    };
    timestamp: number;
}
export interface PingMessage {
    type: ClientMessageType.PING;
    timestamp: number;
}
export interface WelcomeMessage {
    type: ServerMessageType.WELCOME;
    playerId: string;
    serverTime: number;
}
export interface MatchFoundMessage {
    type: ServerMessageType.MATCH_FOUND;
    roomId: string;
    playerNumber: 1 | 2;
    opponentName?: string;
}
export interface GameStateMessage {
    type: ServerMessageType.GAME_STATE;
    timestamp: number;
    ball: {
        position: {
            x: number;
            y: number;
            z: number;
        };
    };
    paddle1: {
        z: number;
    };
    paddle2: {
        z: number;
    };
    score: {
        player1: number;
        player2: number;
    };
}
export interface GoalScoredMessage {
    type: ServerMessageType.GOAL_SCORED;
    scorer: 1 | 2;
    score: {
        player1: number;
        player2: number;
    };
}
export interface OpponentDiscndMsg {
    type: ServerMessageType.OPPONENT_DISCND;
}
export interface GameOverMessage {
    type: ServerMessageType.GAME_OVER;
    winner: 1 | 2;
    finalScore: {
        player1: number;
        player2: number;
    };
}
export interface ErrorMessage {
    type: ServerMessageType.ERROR;
    message: string;
}
export interface PongMessage {
    type: ServerMessageType.PONG;
    timestamp: number;
}
export type ClientMessage = FindMatchMessage | ConnectMessage | InputMessage | PingMessage;
export type ServerMessage = MatchFoundMessage | GoalScoredMessage | OpponentDiscndMsg | GameStateMessage | GameOverMessage | WelcomeMessage | ErrorMessage | PongMessage;
//# sourceMappingURL=MessageTypes.d.ts.map