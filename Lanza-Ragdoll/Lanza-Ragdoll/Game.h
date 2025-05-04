#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Ragdoll.h"

class Game {
public:
    Game();
    void Run();

private:
    void ProcessEvents();
    void Update(float dt);
    void Render();
    void HandleMouseClick(sf::Vector2i mousePosition);

    sf::RenderWindow window;
    b2World world;
    std::vector<Ragdoll> ragdolls;

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
};
