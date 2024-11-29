#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    // Créer la première fenêtre SFML (Fenêtre principale)
    sf::RenderWindow window1(sf::VideoMode(1100, 700), "Fenêtre Principale");

    // Créer la deuxième fenêtre SFML (Fenêtre secondaire)
    sf::RenderWindow window2(sf::VideoMode(1000,600), "Fenêtre Secondaire");

    // Vecteur pour stocker les points dans la première fenêtre
    std::vector<sf::CircleShape> points;

    // Couleur des points (rouge et blanc)
    sf::Color pointColor = sf::Color::Red;
    sf::Color pointColor2 = sf::Color::White;

    // Variable pour détecter si le bouton gauche ou droit est maintenu enfoncé
    bool isLeftButtonPressed = false;
    bool isRightButtonPressed = false;

    // Création du texte
    sf::Font font;
    if (!font.loadFromFile("C:/Users/nlamarre/Desktop/arial.ttf")) {  // Remplacer "arial.ttf" par le chemin de votre police
        std::cerr << "Erreur de chargement de la police." << std::endl;
        return -1;  // Si la police n'est pas trouvée, on quitte le programme
    }

    // Variable pour contenir la chaîne de texte entrée
    std::string userInput;

    // Création du texte pour la fenêtre secondaire
    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(24);  // Taille de la police
    text2.setFillColor(sf::Color::Black);  // Couleur du texte
    text2.setPosition(0, 0);  // Position initiale du texte dans la fenêtre secondaire

    // Création du texte pour la fenêtre principale
    sf::Text text1;
    text1.setFont(font);
    text1.setCharacterSize(24);  // Taille de la police
    text1.setFillColor(sf::Color::Black);  // Couleur du texte
    text1.setPosition(10, 10);  // Position initiale du texte dans la fenêtre principale

    while (window1.isOpen() || window2.isOpen()) {
        sf::Event event;

        // Gérer les événements de la première fenêtre
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isLeftButtonPressed = true;  // Le bouton gauche est enfoncé
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isRightButtonPressed = true;  // Le bouton droit est enfoncé
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isLeftButtonPressed = false;  // Le bouton gauche est relâché
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isRightButtonPressed = false;  // Le bouton droit est relâché
                }
            }
        }

        // Si le bouton gauche est maintenu enfoncé, ajouter des points rouges à chaque mouvement de souris
        if (isLeftButtonPressed) {
            sf::CircleShape point(2.5);  // Rayon du cercle = 2.5 pixels
            point.setFillColor(pointColor);
            point.setPosition(sf::Mouse::getPosition(window1).x - 2.5, sf::Mouse::getPosition(window1).y - 2.5);
            points.push_back(point);
        }

        // Si le bouton droit est maintenu enfoncé, ajouter des points blancs à chaque mouvement de souris
        if (isRightButtonPressed) {
            sf::CircleShape point(10);  // Rayon du cercle = 10 pixels
            point.setFillColor(pointColor2);
            point.setPosition(sf::Mouse::getPosition(window1).x - 10, sf::Mouse::getPosition(window1).y - 10);
            points.push_back(point);
        }

        // Nettoyer la première fenêtre
        window1.clear(sf::Color::White);

        // Dessiner tous les points dans la première fenêtre
        for (const auto& point : points) {
            window1.draw(point);
        }

        // Mettre à jour le texte dans la fenêtre principale pour qu'il affiche le texte saisi
        text1.setString("Tu dois dessiner: " + userInput);  // Afficher le texte saisi dans la fenêtre principale

        // Dessiner le texte dans la fenêtre principale
        window1.draw(text1);

        // Afficher tout ce qui a été dessiné dans la fenêtre principale
        window1.display();

        // Gérer les événements et afficher la deuxième fenêtre (ici, juste une fenêtre vide)
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8) {  // Backspace pour supprimer
                    if (!userInput.empty()) {
                        userInput.pop_back();  // Enlever le dernier caractère
                    }
                }
                else if (event.text.unicode < 128) {  // Si c'est un caractère ASCII valide
                    userInput += static_cast<char>(event.text.unicode);  // Ajouter le caractère à la chaîne
                }
            }
        }

        // Mettre à jour le texte dans la fenêtre secondaire avec ce que l'utilisateur a saisi
        text2.setString("Que doit dessiner le joueur ?\n " + userInput);  // Afficher le texte saisi dans la fenêtre secondaire

        // Nettoyer la deuxième fenêtre
        window2.clear(sf::Color::White);

        // Dessiner le texte dans la fenêtre secondaire
        window2.draw(text2);

        // Afficher tout ce qui a été dessiné dans la deuxième fenêtre
        window2.display();
    }

    return 0;
}

