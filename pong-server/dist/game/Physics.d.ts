export interface Vector3 {
    x: number;
    y: number;
    z: number;
}
export interface AABB {
    min: Vector3;
    max: Vector3;
}
export declare class Physics {
    static createAABB(out: AABB, center: Vector3, size: Vector3): AABB;
    static emptyAABB(): AABB;
    static checkAABBCollision(a: AABB, b: AABB): boolean;
    static getCollisionNormal(a: AABB, b: AABB): Vector3;
    static reflect(velocity: Vector3, normal: Vector3): Vector3;
    static normalize(v: Vector3): Vector3;
    static scale(v: Vector3, scalar: number): Vector3;
}
//# sourceMappingURL=Physics.d.ts.map