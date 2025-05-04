#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Lanza-Ragdoll"), world(b2Vec2(0.0f, -9.8f)) {
    // Suelo
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -1.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(40.0f, 1.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
}

void Game::Run() {
    sf::Clock clock;
    while (window.isOpen()) {
        ProcessEvents();
        float dt = clock.restart().asSeconds();
        Update(dt);
        Render();
    }
}

void Game::ProcessEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            HandleMouseClick(sf::Mouse::getPosition(window));
    }
}

void Game::Update(float dt) {
    world.Step(timeStep, velocityIterations, positionIterations);
}

void Game::Render() {
    window.clear(sf::Color::Black);

    for (auto& ragdoll : ragdolls) {
        ragdoll.Draw(window);
    }

    window.display();
}

void Game::HandleMouseClick(sf::Vector2i mousePosition) {
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);
    b2Vec2 spawnPos(worldPos.x / 30.f, (600 - worldPos.y) / 30.f);

    ragdolls.emplace_back(&world, spawnPos);
    b2Vec2 force(200.0f, 200.0f);
    ragdolls.back().ApplyImpulseToTorso(force);
}
