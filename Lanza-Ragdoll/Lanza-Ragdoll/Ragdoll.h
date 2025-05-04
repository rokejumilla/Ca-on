#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class Ragdoll {
public:
    Ragdoll(b2World* world, b2Vec2 position);
    void Draw(sf::RenderWindow& window);
    void ApplyImpulseToTorso(b2Vec2 impulse);

private:
    b2Body* head;
    b2Body* torso;
    b2Body* leftArm;
    b2Body* rightArm;
    b2Body* leftLeg;
    b2Body* rightLeg;
};
