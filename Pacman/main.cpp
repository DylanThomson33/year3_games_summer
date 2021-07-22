#include <SFML/Graphics.hpp>
#include "enitity.h";
#include "player.h";
#include "ghost.h";
#include "system_renderer.h";

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

EntityManager em;

std::shared_ptr <Player> p1 = std::make_shared<Player>();
std::shared_ptr <Ghost> g1 = std::make_shared<Ghost>();
std::shared_ptr <Ghost> g2 = std::make_shared<Ghost>();
std::shared_ptr <Ghost> g3 = std::make_shared<Ghost>();
std::shared_ptr <Ghost> g4 = std::make_shared<Ghost>();



void Load() {
    g1->SetColour(sf::Color::Green);
    g1->setPosition(sf::Vector2f(150, 30));
    g2-> SetColour(sf::Color::Blue);
    g2->setPosition(sf::Vector2f(200, 234));
    g3->SetColour(sf::Color::Red);
    g3->setPosition(sf::Vector2f(50, 143));
    g4->SetColour(sf::Color::Magenta);
    g4->setPosition(sf::Vector2f(700, 356));

    em.list.push_back(p1);
    em.list.push_back(g1);
    em.list.push_back(g2);
    em.list.push_back(g3);
    em.list.push_back(g4);
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
    em.update(dt);
}

void Render(RenderWindow& window) {
    em.render(window);
    Renderer::render();
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PacMan");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}