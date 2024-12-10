#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

int main() {
    // Créer une fenêtre
    sf::RenderWindow window(sf::VideoMode(600, 900), "GIF en Background avec SFML");

    // Charger les frames dans des textures
    std::vector<sf::Texture> frames;
    int frameCount = 10; // Supposons que votre GIF a 10 frames
    for (int i = 0; i < frameCount; ++i) {
        sf::Texture texture;
        std::string filename = "frame" + std::to_string(i) + ".gif"; // Exemple : frame0.png, frame1.png...
        if (!texture.loadFromFile(filename)) {
            return -1; // Gestion d'erreur si une frame est introuvable
        }
        frames.push_back(texture);
    }

    // Créer un sprite pour afficher les frames
    sf::Sprite sprite;
    sprite.setTexture(frames[0]); // Commencer avec la première frame
    sprite.setScale(1.3f, 1.3f);
    sprite.setPosition(50, 0);

    // Variables pour gérer l'animation
    sf::Clock clock;           // Pour mesurer le temps écoulé
    int currentFrame = 0;      // Frame actuellement affichée
    float frameDuration = 0.1f; // Durée d'une frame en secondes (par exemple, 0.1s = 10 fps)

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Changer de frame après un certain temps
        if (clock.getElapsedTime().asSeconds() > frameDuration) {
            clock.restart();
            currentFrame = (currentFrame + 1) % frames.size(); // Passer à la frame suivante (boucle)
            sprite.setTexture(frames[currentFrame]);          // Mettre à jour la texture du sprite
        }

        // Dessiner la scène
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
