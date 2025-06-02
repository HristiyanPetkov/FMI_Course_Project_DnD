#include <cstring>
#include "src/game/Game.hpp"

void startSFML();

int main(int argc, char *argv[]) {
    if(argc > 1 && strcmp(argv[1], "-t") == 0) {
        Game game;
        if(argc > 2) {
            game = Game::loadFromFile(argv[1]);
        } else {
            game = Game(1);
        }
        game.start();
    } else {
        startSFML();
    }

    return 0;
}

void startSFML() {
    std::string characterName;
    CharacterClass characterClass;
    bool characterNameEntered = false, characterClassSelected = false, shiftPressed = false;
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Grid Game", sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    while (window.isOpen() && (!characterNameEntered || !characterClassSelected)) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Escape:
                        window.close();
                        return;
                    case sf::Keyboard::Scancode::LShift:
                    case sf::Keyboard::Scancode::RShift:
                        shiftPressed = true;
                        break;
                    case sf::Keyboard::Scancode::Enter:
                        characterNameEntered = true;
                        break;
                    case sf::Keyboard::Scancode::Num1:
                        if(characterNameEntered) {
                            characterClass = CharacterClass::Human;
                            characterClassSelected = true;
                        }
                        break;
                    case sf::Keyboard::Scancode::Num2:
                        if(characterNameEntered) {
                            characterClass = CharacterClass::Mage;
                            characterClassSelected = true;
                        }
                        break;
                    case sf::Keyboard::Scancode::Num3:
                        if(characterNameEntered) {
                            characterClass = CharacterClass::Warrior;
                            characterClassSelected = true;
                        }
                        break;
                    case sf::Keyboard::Scancode::Backspace:
                        characterName = characterName.substr(0, characterName.size()-1);
                        break;
                    default:
                        if (keyPressed->scancode >= sf::Keyboard::Scancode::A && keyPressed->scancode <= sf::Keyboard::Scancode::Z) {
                            char offsetForCapitalLetter = 0;
                            if(shiftPressed) {
                                shiftPressed = false;
                                offsetForCapitalLetter = -32;
                            }
                            characterName += sf::Keyboard::getDescription(keyPressed->scancode);
                            characterName[characterName.size() - 1] += offsetForCapitalLetter;
                        }
                        if(keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                            characterName += " ";
                        }
                        break;
                }
            }

            if (const auto resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea({0, 0}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
        }


        window.clear(sf::Color::Black);

        sf::Font font("resources/text_fonts/montserrat/Montserrat-Black.otf");
        sf::Text text(font);
        if(!characterNameEntered) {
            text.setString("Enter character name: \n" + characterName);
        } else {
            text.setString("1. Human, 2. Mage, 3. Warrior");
        }

        text.setPosition(sf::Vector2f{ window.getView().getSize() / 8.f });
        text.setCharacterSize(60);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        window.draw(text);

        window.display();
    }

    if(window.isOpen()) {
        Game game(Character(characterName, characterClass), 1);
        game.startSFML(window);
    }
}
