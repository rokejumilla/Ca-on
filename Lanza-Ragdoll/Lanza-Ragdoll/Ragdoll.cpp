#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World* world, b2Vec2 position) {
    float headRadius = 0.7f;
    float torsoWidth = 1.0f;
    float torsoHeight = 4.0f;
    float limbWidth = 0.5f;
    float limbHeight = 3.0f;

    head = Box2DHelper::CreateCircularDynamicBody(world, headRadius, 1.0f, 0.3f, 0.3f);
    head->SetTransform(position, 0.0f);

    torso = Box2DHelper::CreateRectangularDynamicBody(world, torsoWidth, torsoHeight, 1.0f, 0.3f, 0.3f);
    torso->SetTransform(position + b2Vec2(0.0f, -torsoHeight / 2), 0.0f);

    leftArm = Box2DHelper::CreateRectangularDynamicBody(world, limbWidth, limbHeight, 1.0f, 0.3f, 0.3f);
    leftArm->SetTransform(position + b2Vec2(-torsoWidth / 2 - limbWidth / 2, -torsoHeight / 2 + limbHeight / 2), 0.0f);

    rightArm = Box2DHelper::CreateRectangularDynamicBody(world, limbWidth, limbHeight, 1.0f, 0.3f, 0.3f);
    rightArm->SetTransform(position + b2Vec2(torsoWidth / 2 + limbWidth / 2, -torsoHeight / 2 + limbHeight / 2), 0.0f);

    leftLeg = Box2DHelper::CreateRectangularDynamicBody(world, limbWidth, limbHeight, 1.0f, 0.3f, 0.3f);
    leftLeg->SetTransform(position + b2Vec2(-torsoWidth / 4, -torsoHeight - limbHeight / 2), 0.0f);

    rightLeg = Box2DHelper::CreateRectangularDynamicBody(world, limbWidth, limbHeight, 1.0f, 0.3f, 0.3f);
    rightLeg->SetTransform(position + b2Vec2(torsoWidth / 4, -torsoHeight - limbHeight / 2), 0.0f);

    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(0.0f, torsoHeight / 2), head, -0.5f * b2_pi, 0.5f * b2_pi, 0, 0, false, true);
    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(-torsoWidth / 2, torsoHeight / 2 - limbHeight / 2), leftArm, -0.5f * b2_pi, 0.5f * b2_pi, 0, 0, false, true);
    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(torsoWidth / 2, torsoHeight / 2 - limbHeight / 2), rightArm, -0.5f * b2_pi, 0.5f * b2_pi, 0, 0, false, true);
    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(-torsoWidth / 4, -torsoHeight / 2), leftLeg, -0.5f * b2_pi, 0.5f * b2_pi, 0, 0, false, true);
    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(torsoWidth / 4, -torsoHeight / 2), rightLeg, -0.5f * b2_pi, 0.5f * b2_pi, 0, 0, false, true);
}

void Ragdoll::ApplyImpulseToTorso(b2Vec2 impulse) {
    torso->ApplyLinearImpulseToCenter(impulse, true);
}

void Ragdoll::Draw(sf::RenderWindow& window) {
    auto drawBody = [&window](b2Body* body, sf::Color color) {
        for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
            if (f->GetShape()->GetType() == b2Shape::e_polygon) {
                auto* poly = static_cast<b2PolygonShape*>(f->GetShape());
                sf::ConvexShape convex;
                convex.setPointCount(poly->m_count);
                for (int i = 0; i < poly->m_count; ++i) {
                    b2Vec2 pt = body->GetWorldPoint(poly->m_vertices[i]);
                    convex.setPoint(i, sf::Vector2f(pt.x * 30.f, 600 - pt.y * 30.f));
                }
                convex.setFillColor(color);
                window.draw(convex);
            }
            else if (f->GetShape()->GetType() == b2Shape::e_circle) {
                auto* circle = static_cast<b2CircleShape*>(f->GetShape());
                sf::CircleShape shape(circle->m_radius * 30.f);
                b2Vec2 pos = body->GetWorldPoint(circle->m_p);
                shape.setOrigin(circle->m_radius * 30.f, circle->m_radius * 30.f);
                shape.setPosition(pos.x * 30.f, 600 - pos.y * 30.f);
                shape.setFillColor(color);
                window.draw(shape);
            }
        }
        };

    drawBody(torso, sf::Color::White);
    drawBody(head, sf::Color::Yellow);
    drawBody(leftArm, sf::Color::Red);
    drawBody(rightArm, sf::Color::Red);
    drawBody(leftLeg, sf::Color::Blue);
    drawBody(rightLeg, sf::Color::Blue);
}
