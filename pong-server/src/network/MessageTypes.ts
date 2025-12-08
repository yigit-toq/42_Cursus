export enum ClientMessageType
{
	CONNECT = 'CONNECT',
	DISCONNECT = 'DISCONNECT',
	FIND_MATCH = 'FIND_MATCH',
	INPUT = 'INPUT',
	PING = 'PING'
}

export enum ServerMessageType
{
	WELCOME = 'WELCOME',
	GAME_STATE = 'GAME_STATE',
	MATCH_FOUND = 'MATCH_FOUND',
	GOAL_SCORED = 'GOAL_SCORED',
	GAME_OVER = 'GAME_OVER',
	PONG = 'PONG',
	ERROR = 'ERROR',
	OPPONENT_DISCONNECTED = 'OPPONENT_DISCONNECTED'
}

// Client Messages
export interface ConnectMessage
{
	type: ClientMessageType.CONNECT;
	playerName?: string;
}

export interface FindMatchMessage
{
	type: ClientMessageType.FIND_MATCH;
}

export interface InputMessage
{
	type: ClientMessageType.INPUT;

	input:
	{
		vertical: number;
	}

	timestamp: number;
}

export interface PingMessage
{
	type: ClientMessageType.PING;
	timestamp: number;
}

// Server Messages
export interface WelcomeMessage
{
	type: ServerMessageType.WELCOME;
	playerId: string;
	serverTime: number;
}

export interface MatchFoundMessage
{
	type: ServerMessageType.MATCH_FOUND;
	roomId: string;
	playerNumber: 1 | 2;
	opponentName?: string;
}

export interface GameStateMessage
{
	type: ServerMessageType.GAME_STATE;
	timestamp: number;

	ball:
	{
		position: { x: number; y: number; z: number; };
	};

	paddle1:
	{
		position: { z: number; };
	};
	paddle2:
	{
		position: { z: number; };
	};

	score:
	{
		player1: number;
		player2: number;
	};
}

export interface GoalScoredMessage
{
	type: ServerMessageType.GOAL_SCORED;
	scoringPlayer: 1 | 2;

	score:
	{
		player1: number;
		player2: number;
	};
}

export interface GameOverMessage
{
	type: ServerMessageType.GAME_OVER;

	winner: 1 | 2;

	finalScore:
	{
		player1: number;
		player2: number;
	};
}

export interface OpponentDisconnectedMessage
{
	type: ServerMessageType.OPPONENT_DISCONNECTED;
}

export interface PongMessage
{
	type: ServerMessageType.PONG;
	timestamp: number;
}

export interface ErrorMessage
{
	type: ServerMessageType.ERROR;
	message: string;
}

export type ClientMessage = 
	| ConnectMessage 
	| FindMatchMessage 
	| InputMessage 
	| PingMessage;

export type ServerMessage = 
	| WelcomeMessage 
	| MatchFoundMessage 
	| GameStateMessage 
	| GoalScoredMessage
	| GameOverMessage 
	| OpponentDisconnectedMessage 
	| PongMessage 
	| ErrorMessage;
