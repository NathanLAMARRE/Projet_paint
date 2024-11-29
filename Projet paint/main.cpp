#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    // Cr�er la premi�re fen�tre SFML (Fen�tre principale)
    sf::RenderWindow window1(sf::VideoMode(1100, 700), "Fen�tre Principale");

    // Cr�er la deuxi�me fen�tre SFML (Fen�tre secondaire)
    sf::RenderWindow window2(sf::VideoMode(1000,600), "Fen�tre Secondaire");

    // Vecteur pour stocker les points dans la premi�re fen�tre
    std::vector<sf::CircleShape> points;

    // Couleur des points (rouge et blanc)
    sf::Color pointColor = sf::Color::Red;
    sf::Color pointColor2 = sf::Color::White;

    // Variable pour d�tecter si le bouton gauche ou droit est maintenu enfonc�
    bool isLeftButtonPressed = false;
    bool isRightButtonPressed = false;

    // Cr�ation du texte
    sf::Font font;
    if (!font.loadFromFile("C:/Users/nlamarre/Desktop/arial.ttf")) {  // Remplacer "arial.ttf" par le chemin de votre police
        std::cerr << "Erreur de chargement de la police." << std::endl;
        return -1;  // Si la police n'est pas trouv�e, on quitte le programme
    }

    // Variable pour contenir la cha�ne de texte entr�e
    std::string userInput;

    // Cr�ation du texte pour la fen�tre secondaire
    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(24);  // Taille de la police
    text2.setFillColor(sf::Color::Black);  // Couleur du texte
    text2.setPosition(0, 0);  // Position initiale du texte dans la fen�tre secondaire

    // Cr�ation du texte pour la fen�tre principale
    sf::Text text1;
    text1.setFont(font);
    text1.setCharacterSize(24);  // Taille de la police
    text1.setFillColor(sf::Color::Black);  // Couleur du texte
    text1.setPosition(10, 10);  // Position initiale du texte dans la fen�tre principale

    while (window1.isOpen() || window2.isOpen()) {
        sf::Event event;

        // G�rer les �v�nements de la premi�re fen�tre
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isLeftButtonPressed = true;  // Le bouton gauche est enfonc�
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isRightButtonPressed = true;  // Le bouton droit est enfonc�
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isLeftButtonPressed = false;  // Le bouton gauche est rel�ch�
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isRightButtonPressed = false;  // Le bouton droit est rel�ch�
                }
            }
        }

        // Si le bouton gauche est maintenu enfonc�, ajouter des points rouges � chaque mouvement de souris
        if (isLeftButtonPressed) {
            sf::CircleShape point(2.5);  // Rayon du cercle = 2.5 pixels
            point.setFillColor(pointColor);
            point.setPosition(sf::Mouse::getPosition(window1).x - 2.5, sf::Mouse::getPosition(window1).y - 2.5);
            points.push_back(point);
        }

        // Si le bouton droit est maintenu enfonc�, ajouter des points blancs � chaque mouvement de souris
        if (isRightButtonPressed) {
            sf::CircleShape point(10);  // Rayon du cercle = 10 pixels
            point.setFillColor(pointColor2);
            point.setPosition(sf::Mouse::getPosition(window1).x - 10, sf::Mouse::getPosition(window1).y - 10);
            points.push_back(point);
        }

        // Nettoyer la premi�re fen�tre
        window1.clear(sf::Color::White);

        // Dessiner tous les points dans la premi�re fen�tre
        for (const auto& point : points) {
            window1.draw(point);
        }

        // Mettre � jour le texte dans la fen�tre principale pour qu'il affiche le texte saisi
        text1.setString("Tu dois dessiner: " + userInput);  // Afficher le texte saisi dans la fen�tre principale

        // Dessiner le texte dans la fen�tre principale
        window1.draw(text1);

        // Afficher tout ce qui a �t� dessin� dans la fen�tre principale
        window1.display();

        // G�rer les �v�nements et afficher la deuxi�me fen�tre (ici, juste une fen�tre vide)
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8) {  // Backspace pour supprimer
                    if (!userInput.empty()) {
                        userInput.pop_back();  // Enlever le dernier caract�re
                    }
                }
                else if (event.text.unicode < 128) {  // Si c'est un caract�re ASCII valide
                    userInput += static_cast<char>(event.text.unicode);  // Ajouter le caract�re � la cha�ne
                }
            }
        }

        // Mettre � jour le texte dans la fen�tre secondaire avec ce que l'utilisateur a saisi
        text2.setString("Que doit dessiner le joueur ?\n " + userInput);  // Afficher le texte saisi dans la fen�tre secondaire

        // Nettoyer la deuxi�me fen�tre
        window2.clear(sf::Color::White);

        // Dessiner le texte dans la fen�tre secondaire
        window2.draw(text2);

        // Afficher tout ce qui a �t� dessin� dans la deuxi�me fen�tre
        window2.display();
    }

    return 0;
}

