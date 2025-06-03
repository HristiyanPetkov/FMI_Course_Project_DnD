#include "Character.hpp"

#include <utility>
#include <cstring>
#include <iomanip>
#include "../item/Armor.hpp"
#include "../item/Weapon.hpp"
#include "../item/Spell.hpp"
#include "../monster/Monster.hpp"

Character::Character()
: name(), characterClass(CharacterClass::Human), strength(0), mana(0), maxHealth(0), currentHealth(0),
  armor(nullptr), weapon(nullptr), spell(nullptr) {}

Character::Character(std::string  name, CharacterClass characterClass)
: name(std::move(name)), characterClass(characterClass), strength(0), mana(0), maxHealth(0), currentHealth(0),
  armor(nullptr), weapon(nullptr), spell(nullptr)
{
    setInitialStats();
    setInitialEquipment();
}

void Character::setInitialStats() {
    switch(characterClass) {
        case CharacterClass::Human:
            strength = 45;
            mana = 30;
            maxHealth = 80;
            currentHealth = 80;
            break;
        case CharacterClass::Mage:
            strength = 25;
            mana = 70;
            maxHealth = 100;
            currentHealth = 100;
            break;
        case CharacterClass::Warrior:
            strength = 60;
            mana = 25;
            maxHealth = 120;
            currentHealth = 120;
            break;
        default:
            throw std::invalid_argument("Character class is not defined");
    }
}

void Character::setInitialEquipment() {
    armor = new Armor("Clothes", 0);
    weapon = new Weapon("Basic sword", 20);
    spell = new Spell("Fireball", 20);
}

Character::Character(const Character &other)
: name(other.name),
  characterClass(other.characterClass),
  strength(other.strength),
  mana(other.mana),
  maxHealth(other.maxHealth),
  currentHealth(other.currentHealth),
  armor(nullptr),
  weapon(nullptr),
  spell(nullptr)
{
    copyEquipment(other);
}

Character &Character::operator=(const Character &other) {
    Character copy(other);
    swap(copy);

    return *this;
}

Character::~Character() {
    delete armor;
    delete weapon;
    delete spell;
}

void Character::takeDamage(double damage) {
    currentHealth = std::max(0.0, currentHealth - armor->applyBonus(damage));
}

void Character::heal() {
    if(currentHealth > maxHealth * 0.5) {
        currentHealth = std::min(currentHealth + 0.2 * maxHealth, static_cast<double>(maxHealth));
    } else {
        currentHealth = 0.5 * maxHealth;
    }
}

void Character::copyEquipment(const Character& other) {
    if(other.armor != nullptr) {
        armor = other.armor->clone();
    }
    if(other.weapon != nullptr) {
        weapon = other.weapon->clone();
    }
    if(other.spell != nullptr) {
        spell = other.spell->clone();
    }
}

void Character::swap(Character &other) {
    using std::swap;
    swap(name, other.name);
    swap(characterClass, other.characterClass);
    swap(strength, other.strength);
    swap(mana, other.mana);
    swap(maxHealth, other.maxHealth);
    swap(currentHealth, other.currentHealth);
    swap(armor, other.armor);
    swap(weapon, other.weapon);
    swap(spell, other.spell);
}

std::ostream &Character::print(std::ostream &os) const {
    os << name << "(" << characterClass << ")" << std::endl;
    os << "Strength: " << strength << ", Mana: " << mana << ", Health: " << currentHealth << "\\" << maxHealth << std::endl;
    os << "Equipment: " << std::endl;
    armor->print(os);
    weapon->print(os);
    return spell->print(os);
}

void Character::dealDamage(Monster &monster, Character::AttackType attackType) const {
    switch(attackType) {
        case AttackType::WEAPON:
            monster.takeDamage(weapon->applyBonus(static_cast<double>(strength)));
            break;
        case AttackType::SPELL:
            monster.takeDamage(spell->applyBonus(static_cast<double>(mana)));
            break;
    }
}

bool Character::isAlive() const {
    return currentHealth != 0;
}

void Character::equipItem(const Item *item, ItemType itemType) {
    if (!item) return;

    switch(itemType) {
        case ItemType::ARMOR:
            delete armor;
            armor = item->clone();
            break;
        case ItemType::WEAPON:
            delete weapon;
            weapon = item->clone();
            break;
        case ItemType::SPELL:
            delete spell;
            spell = item->clone();
            break;
    }
}

double Character::getCurrentHealth() const {
    return currentHealth;
}

Character::AttackType Character::chooseAttack() {
    while(true) {
        std::cout << "Attack type: 1.Weapon, 2.Spell" << std::endl;
        std::string choice;
        std::cin >> choice;
        if(choice == "1" || choice == "Weapon") {
            return Character::AttackType::WEAPON;
        } else if(choice == "2" || choice == "Spell") {
            return Character::AttackType::SPELL;
        } else {
            std::cout << "Invalid attack type" << std::endl;
        }
    }
}

void Character::levelUp() {
    unsigned attrPoints = 30, inputPoints;
    std::string stat;
    std::cout << "Level UP!" << std::endl;
    while(attrPoints != 0) {
        std::cout << "You have " << attrPoints << " points left" << std::endl;
        std::cout << "Increase stat(stat points): ";
        std::cin >> stat >> inputPoints;
        std::cin.clear();
        if(attrPoints >= inputPoints) {
            attrPoints -= inputPoints;
            increaseStat(stat, inputPoints);
        } else {
            std::cout << "You don't have enough points for that" << std::endl;
        }
    }
}

void Character::increaseStat(const std::string& stat, unsigned int points) {
    if(stat == "strength") {
        strength += points;
    } else if(stat == "mana") {
        mana += points;
    } else if(stat == "hp") {
        maxHealth += points;
        currentHealth += points;
    } else {
        throw std::invalid_argument("Invalid stat");
    }
}

void Character::serialize(std::ostream &os) const {
    os << std::quoted(name) << " " << characterClass << " " << strength << " " << mana << " " << maxHealth << " " << currentHealth << std::endl;
    armor->serialize(os);
    weapon->serialize(os);
    spell->serialize(os);
}

void Character::deserialize(std::istream &is) {
    is >> std::quoted(name) >> characterClass >> strength >> mana >> maxHealth >> currentHealth;
    armor = Item::deserialize(is, ItemType::ARMOR);
    weapon = Item::deserialize(is, ItemType::WEAPON);
    spell = Item::deserialize(is, ItemType::SPELL);
}

void Character::serializeForHighScore(std::ostream &os) const {
    os << std::quoted(name) << " " << characterClass << " " << strength << " " << mana << " " << maxHealth << std::endl;
}

void Character::deserializeForHighScore(std::istream &is) {
    is >> std::quoted(name) >> characterClass >> strength >> mana >> maxHealth;
}

bool Character::operator>(const Character &other) const {
    return name > other.name;
}

bool Character::operator<(const Character &other) const {
    return name < other.name;
}

void Character::printSFML(sf::RenderWindow& window) {
    sf::Font font("resources/text_fonts/montserrat/Montserrat-Black.otf");
    sf::Text text(font);

    text.setPosition(sf::Vector2f{ window.getView().getSize() / 8.f });
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    std::stringstream ss;
    ss << name << ", " << characterClass << std::endl;
    ss << "S: " << strength << std::endl;
    ss << "M: " << mana << std::endl;
    ss << "Hp: " << currentHealth << "/" << maxHealth << std::endl;
    armor->print(ss);
    weapon->print(ss);
    spell->print(ss);

    text.setString(ss.str());
    window.draw(text);
}

void Character::levelUpSFML(sf::RenderWindow &window) {
    int attrPoints = 30, inputPoints = 0;
    bool attrPicked = false, inputPointsPicked = false;
    std::string stat, errorMessage;
    sf::View fullScreen(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));
    window.setView(fullScreen);

    sf::Font font("resources/text_fonts/montserrat/Montserrat-Black.otf");
    sf::Text text(font);

    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    window.setView(window.getDefaultView());

    while (window.isOpen() && attrPoints > 0) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Escape:
                        window.close();
                        return;
                    case sf::Keyboard::Scancode::Z:
                        if(!attrPicked) {
                            stat = "strength";
                        }
                        attrPicked = true;
                        break;
                    case sf::Keyboard::Scancode::X:
                        if(!attrPicked) {
                            stat = "mana";
                        }
                        attrPicked = true;
                        break;
                    case sf::Keyboard::Scancode::C:
                        if(!attrPicked) {
                            stat = "hp";
                        }
                        attrPicked = true;
                        break;
                    case sf::Keyboard::Scancode::Enter:
                        inputPointsPicked = true;
                        break;
                    case sf::Keyboard::Scancode::Backspace:
                        inputPoints /= 10;
                        break;
                    default:
                        if (keyPressed->scancode >= sf::Keyboard::Scancode::Num1 &&
                            keyPressed->scancode <= sf::Keyboard::Scancode::Num0 &&
                            attrPicked) {

                            inputPoints = (inputPoints * 10) +
                                    static_cast<int>(sf::Keyboard::getDescription(
                                            keyPressed->scancode).operator std::string().c_str()[0]
                                            - '0');
                        }
                        break;
                }
            }

            if (const auto resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea({0, 0}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
        }

        if(attrPicked && inputPointsPicked) {
            if(attrPoints >= inputPoints) {
                increaseStat(stat, inputPoints);
                attrPoints -= inputPoints;
                stat = "";
                inputPointsPicked = false;
                attrPicked = false;
                inputPoints = 0;
                errorMessage = "";
            } else {
                errorMessage = "You dont have enough attribute points";
                inputPointsPicked = false;
                inputPoints = 0;
            }
        }

        window.clear(sf::Color::Black);

        std::string pointsLeftMessage = "You have " + std::to_string(attrPoints) + " points left\n";
        if(!attrPicked) {
            text.setString(pointsLeftMessage + "Z. Strength, X. Mana, C. Hp");
        } else {
            text.setString(pointsLeftMessage + "Increase stats by: \n" + std::to_string(inputPoints) + '\n' + errorMessage);
        }
        text.setPosition(sf::Vector2f{ window.getView().getSize() / 8.f });
        window.draw(text);

        window.display();
    }
}