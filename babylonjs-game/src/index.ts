// Core Engine
export { GameLoop	} from './engine/core/GameLoop';
export { GameEngine	} from './engine/core/GameEngine';

// Input System
export { InputManager } from './engine/input/InputManager';

// Render System
export { SceneManager } from './engine/render/SceneManager';

// Physics
export { AABB				} from './engine/physics/Bounds';
export { CollisionDetection	} from './engine/physics/CollisionDetection';

// Game Management
export { GameState			} from './engine/game/GameState';
export { GameManager		} from './engine/game/GameManager';
export { GameStateManager	} from './engine/game/GameStateManager';

export type { GameStateChangeEvent							} from './engine/game/GameState';
export type { PlayerScore, GameConfig as GameManagerConfig	} from './engine/game/GameManager';

// UI System
export { UIManager		} from './engine/ui/UIManager';
export { HUDController	} from './engine/ui/HUDController';
export { MenuController	} from './engine/ui/MenuController';

// Network System (YENİ)
export { NetworkManager		} from './engine/network/NetworkManager';
export { WebSocketClient	} from './engine/network/WebSocketClient';

export { ClientMessageType, ServerMessageType } from './engine/network/MessageTypes';
export type
{
	ClientMessage,
	ServerMessage,

	WelcomeMessage,

	GameOverMessage,
	GameStateMessage,

	MatchFoundMessage,

	GoalScoredMessage,
} from './engine/network/MessageTypes';

// ECS Core
export { World	} from './engine/ecs/core/World';
export { Entity	} from './engine/ecs/core/Entity';
export { System	} from './engine/ecs/core/System';

export type { Component, ComponentConstructor } from './engine/ecs/core/Component';

// ECS Components
export { MeshComponent			} from './engine/ecs/components/MeshComponent';
export { InputComponent			} from './engine/ecs/components/InputComponent';
export { VelocityComponent		} from './engine/ecs/components/VelocityComponent';
export { TransformComponent		} from './engine/ecs/components/TransformComponent';

export { CollisionComponent, CollisionLayer	} from './engine/ecs/components/CollisionComponent';

export type { InputMapping		} from './engine/ecs/components/InputComponent';

// ECS Systems
export { InputSystem			} from './engine/ecs/systems/InputSystem';
export { RenderSystem			} from './engine/ecs/systems/RenderSystem';
export { MovementSystem			} from './engine/ecs/systems/MovementSystem';
export { CollisionSystem		} from './engine/ecs/systems/CollisionSystem';

export type { CollisionEvent	} from './engine/ecs/systems/CollisionSystem';

// Types
export type { GameConfig		} from './types/index';
