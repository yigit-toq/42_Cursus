"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Physics = void 0;
class Physics {
    static createAABB(out, center, size) {
        const hx = size.x * 0.5;
        const hy = size.y * 0.5;
        const hz = size.z * 0.5;
        out.min.x = center.x - hx;
        out.min.y = center.y - hy;
        out.min.z = center.z - hz;
        out.max.x = center.x + hx;
        out.max.y = center.y + hy;
        out.max.z = center.z + hz;
        return out;
    }
    static emptyAABB() {
        return {
            min: { x: 0, y: 0, z: 0 },
            max: { x: 0, y: 0, z: 0 }
        };
    }
    static checkAABBCollision(a, b) {
        return !(a.max.x < b.min.x ||
            a.min.x > b.max.x ||
            a.max.y < b.min.y ||
            a.min.y > b.max.y ||
            a.max.z < b.min.z ||
            a.min.z > b.max.z);
    }
    static getCollisionNormal(a, b) {
        // Center delta
        const dx = ((b.min.x + b.max.x) - (a.min.x + a.max.x)) * 0.5;
        const dy = ((b.min.y + b.max.y) - (a.min.y + a.max.y)) * 0.5;
        const dz = ((b.min.z + b.max.z) - (a.min.z + a.max.z)) * 0.5;
        // Half-size sums
        const overlapX = ((a.max.x - a.min.x) + (b.max.x - b.min.x)) * 0.5 - Math.abs(dx);
        const overlapY = ((a.max.y - a.min.y) + (b.max.y - b.min.y)) * 0.5 - Math.abs(dy);
        const overlapZ = ((a.max.z - a.min.z) + (b.max.z - b.min.z)) * 0.5 - Math.abs(dz);
        // Choose minimum penetration axis
        if (overlapX <= overlapY && overlapX <= overlapZ) {
            return { x: Math.sign(dx), y: 0, z: 0 };
        }
        if (overlapY <= overlapZ) {
            return { x: 0, y: Math.sign(dy), z: 0 };
        }
        return { x: 0, y: 0, z: Math.sign(dz) };
    }
    static reflect(velocity, normal) {
        const dot = velocity.x * normal.x + velocity.y * normal.y + velocity.z * normal.z;
        return {
            x: velocity.x - 2 * dot * normal.x,
            y: velocity.y - 2 * dot * normal.y,
            z: velocity.z - 2 * dot * normal.z
        };
    }
    static normalize(v) {
        const length = Math.sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        if (length === 0)
            return { x: 0, y: 0, z: 0 };
        return {
            x: v.x / length,
            y: v.y / length,
            z: v.z / length
        };
    }
    static scale(v, scalar) {
        return {
            x: v.x * scalar,
            y: v.y * scalar,
            z: v.z * scalar
        };
    }
}
exports.Physics = Physics;
//# sourceMappingURL=Physics.js.map