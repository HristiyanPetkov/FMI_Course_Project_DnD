#include <iomanip>
#include "Item.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include "Spell.hpp"

Item::Item(const std::string& name, double bonus)
: name(name), bonus(bonus){}

double Item::applyBonus(double damage) const {
    return damage * getBonusMultiplier();
}

double Item::getBonusMultiplier() const {
    return bonus / 100;
}

Item *Item::clone() const {
    return new Item(*this);
}

std::ostream &Item::print(std::ostream &os) const {
    return os << getType() << ": " << name << " " << bonus << std::endl;
}

std::string Item::getType() const {
    return "Common Item";
}

void Item::serialize(std::ostream &os) const {
    os << std::quoted(name) << " " << bonus << std::endl;
}

Item* Item::deserialize(std::istream &is, ItemType type) {
    std::string name;
    double bonus;
    is >> std::quoted(name) >> bonus;

    switch(type) {
        case ItemType::ARMOR:
            return new Armor(name, bonus);
        case ItemType::WEAPON:
            return new Weapon(name, bonus);
        case ItemType::SPELL:
            return new Spell(name, bonus);
    }
    throw std::invalid_argument("Item type is not supported");
}

void Item::printSFML(sf::RenderWindow &window) {
    sf::Font font("resources/text_fonts/montserrat/Montserrat-Black.otf");
    sf::Text text(font);

    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f{window.getView().getSize() / 8.f });
    std::stringstream ss;
    ss << getType() << ": " << name << " " << bonus << std::endl;
    text.setString(ss.str());

    window.draw(text);
}
