#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 12;

int pog = rand() % 100;
bool server = false;

Font font;
Text text;

Texture spritesheet;
vector<Ship*> ships;

sf::Vector2f speed = {(server? 100.0f : -100.0f), 0.0f };

void Load() {
    if (!spritesheet.loadFromFile("C:/Users/Dylan/year3_games_summer/res/img/invaders_sheet.png")) {
        cerr<< "Failed to load spritesheet!" << std::endl;
    }
    int x = 0;
    for (int r = 0; r < invaders_rows; ++r) {
        auto rect = sf::IntRect(x,0,32,32);
        for (int c = 0; c < invaders_columns; ++c) {
            Vector2f position(100 + (c * 50), 100 + (r * 50));
            auto inv = new Invader(rect, position);
            inv->speed = 20.f;
            ships.push_back(inv);
        }
        x += 32;
    }

    Player* player = new Player();
    player->speed = 200.0f;
    ships.push_back(player);
}
void Reset() {

}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    for (auto& s : ships) {
        s->Update(dt);
    };

    //update bullets
    Bullet::Update(dt);

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
}

void Render(RenderWindow& window) {
    // Draw Everything

    for (const auto s : ships) {
        window.draw(*s);
    }
    Bullet::Render(window);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}