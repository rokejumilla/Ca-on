#include "Box2DHelper.h"

b2Body* Box2DHelper::CreateRectangularDynamicBody(b2World* world, float width, float height, float density, float friction, float restitution) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width / 2.0f, height / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;

    body->CreateFixture(&fixtureDef);
    return body;
}

b2Body* Box2DHelper::CreateCircularDynamicBody(b2World* world, float radius, float density, float friction, float restitution) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Body* body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;

    body->CreateFixture(&fixtureDef);
    return body;
}

void Box2DHelper::CreateRevoluteJoint(b2World* world, b2Body* bodyA, b2Vec2 anchor, b2Body* bodyB, float lowerAngle, float upperAngle,
    float motorSpeed, float maxMotorTorque, bool enableMotor, bool enableLimit) {
    b2RevoluteJointDef jointDef;
    jointDef.Initialize(bodyA, bodyB, anchor);
    jointDef.enableLimit = enableLimit;
    jointDef.lowerAngle = lowerAngle;
    jointDef.upperAngle = upperAngle;
    jointDef.enableMotor = enableMotor;
    jointDef.motorSpeed = motorSpeed;
    jointDef.maxMotorTorque = maxMotorTorque;

    world->CreateJoint(&jointDef);
}
