#include <SFML/Graphics.hpp>
#include "entity.h";
#include "player.h";
#include "levelsystem.h";

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

Player p1;

void Load() {
    p1.setPosition(Vector2f(400, 300));

    ls::loadLevelFile("C:/Users/Dylan/year3_games_summer/res/maps/maze_2.txt");

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }
}

void Reset() {

}

void Update(RenderWindow& window)
{
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
    //update player 1
    p1.Update(dt);
}

void Render(RenderWindow& window) {
    //render player 1
    p1.Render(window);
    ls::Render(window);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "tile_engine");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}