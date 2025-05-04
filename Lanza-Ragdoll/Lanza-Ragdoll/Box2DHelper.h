#pragma once

#include <Box2D/Box2D.h>

class Box2DHelper {
public:
    static b2Body* CreateRectangularDynamicBody(b2World* world, float width, float height, float density, float friction, float restitution);
    static b2Body* CreateCircularDynamicBody(b2World* world, float radius, float density, float friction, float restitution);
    static void CreateRevoluteJoint(b2World* world, b2Body* bodyA, b2Vec2 anchor, b2Body* bodyB, float lowerAngle, float upperAngle,
        float motorSpeed, float maxMotorTorque, bool enableMotor, bool enableLimit);
};
