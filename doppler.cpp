#include <SFML/Graphics.hpp>
#include <vector>

#define WIDTH 1000
#define HEIGHT 800
#define WAVE_SPEED 100.f
#define WAVE_TIME 0.25f
#define MAX_WAVES 25

struct Wave {
    float x,y;
    float radius;
};

int main() {
    // Antialiasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "DopplerEffect", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::CircleShape source(5.f);
    source.setFillColor(sf::Color::Red);    
    source.setOrigin(5.f, 5.f); 
    
    std::vector<Wave> waves;

    sf::Clock spawn_clock;

    sf::Clock clock;

    window.setMouseCursorVisible(false);
    
    while (window.isOpen()) {

        float dt = clock.restart().asSeconds();
        // events
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }    

        // get the mouse pos
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        source.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // clock for wave spawning
        if (spawn_clock.getElapsedTime().asSeconds() > WAVE_TIME) {
            waves.push_back({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y), 0.f});
            spawn_clock.restart();
        }

        for (int i = 0 ; i < waves.size() ; i++) {
            waves[i].radius += WAVE_SPEED * dt;
        }

        if (waves.size() > MAX_WAVES) {
            waves.erase(waves.begin());
        }

        window.clear();

        // drawing 
        for (const auto& w : waves) {
            sf::CircleShape waveShape(w.radius);
            waveShape.setFillColor(sf::Color::Transparent);
            waveShape.setOutlineThickness(2.f);
            waveShape.setOutlineColor(sf::Color::White);

            waveShape.setOrigin(w.radius, w.radius);
            waveShape.setPosition(w.x, w.y);

            window.draw(waveShape);
        }

        window.draw(source);
        window.display();
    }
    return 0;
}