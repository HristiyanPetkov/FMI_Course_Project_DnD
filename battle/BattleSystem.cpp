#include "BattleSystem.hpp"
#include <ctime>

bool BattleSystem::battle(Character &character, Monster &monster) {
    std::cout << "A battle begins!\n";
    srand(time(nullptr));
    bool playerTurn = (rand() % 2 == 0);

    while (character.isAlive() && monster.isAlive()) {
        std::cout << "Character: " << character.getCurrentHealth() << ", Monster: " << monster.getCurrentHealth() << std::endl;
        if (playerTurn) {
            Character::AttackType type = Character::chooseAttack();
            character.dealDamage(monster, type);
        } else {
            monster.dealDamage(character);
        }
        playerTurn = !playerTurn;
    }

    std::cout << "End: Character: " << character.getCurrentHealth() << ", Monster: " << monster.getCurrentHealth() << std::endl;

    if (character.isAlive()) {
        std::cout << "Player wins!\n";
        character.heal();
        return true;
    } else {
        std::cout << "Player died!\n";
        return false;
    }
}

bool BattleSystem::battle(Character &character, Monster &monster, sf::RenderWindow &window) {
    Character::AttackType type;
    bool attackToBeMade = false;
    srand(time(nullptr));
    bool playerTurn = (rand() % 2 == 0);

    sf::View monsterInfo, battleActions, characterInfo;

    monsterInfo.setViewport(sf::FloatRect({0.f, 0.f}, {0.75f, 0.75f}));
    battleActions.setViewport(sf::FloatRect({0.f, 0.75f}, {0.75f, 0.25f}));
    characterInfo.setViewport(sf::FloatRect({0.75f, 0.f}, {0.25f, 0.35f}));

    while (character.isAlive() && monster.isAlive() && window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return true;
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Num1:
                        attackToBeMade = true;
                        type = Character::AttackType::WEAPON;
                        break;
                    case sf::Keyboard::Scancode::Num2:
                        attackToBeMade = true;
                        type = Character::AttackType::SPELL;
                        break;
                    case sf::Keyboard::Scancode::Escape:
                        window.close();
                        return true;
                    default: break;
                }
            }

            if (const auto resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea({0, 0}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
        }

        if (attackToBeMade && playerTurn) {
            attackToBeMade = false;
            playerTurn = !playerTurn;
            character.dealDamage(monster, type);
        } else if(!playerTurn) {
            playerTurn = !playerTurn;
            monster.dealDamage(character);
        }

        window.clear(sf::Color::Black);
        window.setView(monsterInfo);
        monster.printSFML(window);
        window.setView(battleActions);

        sf::RectangleShape shape(battleActions.getSize());
        shape.setPosition(battleActions.getViewport().position);
        shape.setFillColor(sf::Color::White);

        window.draw(shape);

        sf::Font font("resources/text_fonts/montserrat/Montserrat-Black.otf");
        sf::Text text(font, "1. Weapon");

        text.setScale(battleActions.getViewport().getCenter() * 2.f);
        text.setPosition(window.getView().getSize() / 8.f + sf::Vector2f(0.f, battleActions.getCenter().y * 0.5f));
        text.setCharacterSize(64);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Black);

        window.draw(text);

        text.setString("2. Spell");
        text.move({shape.getSize().x / 2.F, 0.f});
        text.setFillColor(sf::Color::Black);
        window.draw(text);

        window.setView(characterInfo);
        character.printSFML(window);
        window.display();
    }

    if (character.isAlive()) {
        character.heal();
        return true;
    } else {
        return false;
    }
}
