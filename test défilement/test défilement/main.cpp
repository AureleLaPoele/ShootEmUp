#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

int main() {
    // Cr�er une fen�tre
    sf::RenderWindow window(sf::VideoMode(600, 800), "Background Anim� et D�filant avec SFML");

    // Charger les frames du GIF
    std::vector<sf::Texture> frames;
    int frameCount = 14; // Supposons que le GIF a 14 frames
    for (int i = 0; i < frameCount; ++i) {
        sf::Texture texture;
        std::string filename = "frame" + std::to_string(i) + ".gif"; // Exemple : frame0.gif, frame1.gif...
        if (!texture.loadFromFile(filename)) {
            return -1; // Gestion d'erreur si une frame est introuvable
        }
        frames.push_back(texture);
    }

    sf::Texture texture;
    if (!texture.loadFromFile("foreground.png")) {
        return -1;
    }

    // Cr�er deux sprites pour le d�filement
    sf::Sprite background1(frames[0]);
    sf::Sprite background2(frames[0]);
    sf::Sprite foreground1(texture);
    sf::Sprite foreground2(texture);

    float foregroundScaleFactor = 0.8f; // R�duire � 50% de la taille originale

    // Mise � l'�chelle pour agrandir les sprites
    float scaleX = static_cast<float>(window.getSize().x) / frames[0].getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / frames[0].getSize().y;

    float scaleXfore = static_cast<float>(window.getSize().x) / texture.getSize().x * foregroundScaleFactor;
    float scaleYfore = scaleXfore; // Garder le ratio d'aspect pour �viter l'�tirement

    background1.setScale(scaleX, scaleY);
    background2.setScale(scaleX, scaleY);
    foreground1.setScale(scaleXfore, scaleYfore);
    foreground2.setScale(scaleXfore, scaleYfore);

    // Positionner les deux sprites initialement pour un d�filement vertical
    background1.setPosition(0, 0);
    background2.setPosition(0, frames[0].getSize().y * scaleY);
    foreground1.setPosition(100, 0);
    foreground2.setPosition(10, texture.getSize().y * scaleYfore);

    // Variables pour l'animation
    sf::Clock frameClock;       // Pour le changement de frame
    sf::Clock scrollClock;      // Pour le d�filement
    int currentFrame = 0;       // Frame actuellement affich�e
    float frameDuration = 0.1f; // Dur�e d'une frame en secondes (par exemple, 0.1s = 10 fps)
    float scrollSpeed = 250.0f; // Vitesse de d�filement (pixels par seconde)
    float scrollSpeedfore = 100.0f;

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Mettre � jour l'animation des frames
        if (frameClock.getElapsedTime().asSeconds() > frameDuration) {
            frameClock.restart();
            currentFrame = (currentFrame + 1) % frames.size(); // Passer � la frame suivante
            background1.setTexture(frames[currentFrame]);
            background2.setTexture(frames[currentFrame]);
        }

        // D�filement vertical
        float deltaTime = scrollClock.restart().asSeconds();
        float offset = scrollSpeed * deltaTime;
        float offsetfore = scrollSpeedfore * deltaTime;

        background1.move(0, offset);
        background2.move(0, offset);
        foreground1.move(0, offsetfore);
        foreground2.move(0, offsetfore);

        // R�initialiser la position des sprites pour le d�filement continu
        if (background1.getPosition().y >= window.getSize().y) {
            background1.setPosition(0, background2.getPosition().y - background1.getGlobalBounds().height);
        }
        if (background2.getPosition().y >= window.getSize().y) {
            background2.setPosition(0, background1.getPosition().y - background2.getGlobalBounds().height);
        }

        if (foreground1.getPosition().y >= window.getSize().y) {
            foreground1.setPosition(0, foreground2.getPosition().y - foreground1.getGlobalBounds().height);
        }
        if (foreground2.getPosition().y >= window.getSize().y) {
            foreground2.setPosition(0, foreground1.getPosition().y - foreground2.getGlobalBounds().height);
        }

        // Dessiner la sc�ne
        window.clear();
        window.draw(background1);
        window.draw(background2);
        window.draw(foreground1);
        window.draw(foreground2);
        window.display();
    }

    return 0;
}
