"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Player = void 0;
class Player {
    id;
    name;
    input = 0;
    socket;
    roomID = null;
    playerN = null;
    isReady = false;
    lastPing = Date.now();
    paddlePos = 0;
    constructor(id, socket, name) {
        this.socket = socket;
        this.id = id;
        this.name = name || `Player_${id}`;
    }
    send(data) {
        if (this.socket.readyState === 1) {
            this.socket.send(JSON.stringify(data));
        }
    }
    isConnected() {
        return this.socket.readyState === 1;
    }
    updateInput(vertical) {
        this.input = Math.max(-1, Math.min(1, vertical));
    }
    reset() {
        this.isReady = false;
        this.input = 0;
        this.paddlePos = 0;
    }
}
exports.Player = Player;
//# sourceMappingURL=Player.js.map