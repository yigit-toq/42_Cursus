"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ServerMessageType = exports.ClientMessageType = void 0;
var ClientMessageType;
(function (ClientMessageType) {
    ClientMessageType["CONNECT"] = "CONNECT";
    ClientMessageType["DISCONNECT"] = "DISCONNECT";
    ClientMessageType["FIND_MATCH"] = "FIND_MATCH";
    ClientMessageType["INPUT"] = "INPUT";
    ClientMessageType["PING"] = "PING";
})(ClientMessageType || (exports.ClientMessageType = ClientMessageType = {}));
var ServerMessageType;
(function (ServerMessageType) {
    ServerMessageType["PONG"] = "PONG";
    ServerMessageType["ERROR"] = "ERROR";
    ServerMessageType["WELCOME"] = "WELCOME";
    ServerMessageType["GAME_OVER"] = "GAME_OVER";
    ServerMessageType["GAME_STATE"] = "GAME_STATE";
    ServerMessageType["MATCH_FOUND"] = "MATCH_FOUND";
    ServerMessageType["GOAL_SCORED"] = "GOAL_SCORED";
    ServerMessageType["OPPONENT_DISCND"] = "OPPONENT_DISCND";
})(ServerMessageType || (exports.ServerMessageType = ServerMessageType = {}));
//# sourceMappingURL=MessageTypes.js.map