#include "TreasureTile.hpp"
#include "EmptyTile.hpp"
#include "../../item/Armor.hpp"
#include "../../item/Spell.hpp"

TreasureTile::TreasureTile(Item *item, ItemType type)
: item(item->clone()), type(type) {}

TreasureTile::TreasureTile(const Item& item, ItemType type)
: item(item.clone()), type(type) {}

TreasureTile::TreasureTile(const TreasureTile &other)
: item(other.item->clone()), type(other.type) {}

TreasureTile &TreasureTile::operator=(const TreasureTile &other) {
    TreasureTile copy(other);
    std::swap(item, copy.item);
    std::swap(type, copy.type);

    return *this;
}

void TreasureTile::apply(Character &character) {
    item->print();
    std::cout << "Eqip item? ";
    char choice;
    std::cin >> choice;
    if(std::tolower(choice) == 'y') {
        character.equipItem(item, type);
    }
}

char TreasureTile::getDisplayCharacter() const {
    return 'T';
}

Tile *TreasureTile::clone() const {
    return new TreasureTile(*this);
}

TreasureTile::~TreasureTile() {
    delete item;
}

Tile *TreasureTile::generateRandomTreasureTile(unsigned int level) {
    srand(time(nullptr));
    ItemType genType = static_cast<ItemType>(rand() % 3);

    switch(genType) {
        case ItemType::ARMOR:
            return new TreasureTile(Armor("Armor", getBonusFromLevel(level)), ItemType::ARMOR);
        case ItemType::WEAPON:
            return new TreasureTile(Weapon("Sword", getBonusFromLevel(level)), ItemType::WEAPON);
        case ItemType::SPELL:
            return new TreasureTile(Spell("Spell", getBonusFromLevel(level)), ItemType::SPELL);
        default:
            throw std::invalid_argument("Invalid item Type");
    }
}

double TreasureTile::getBonusFromLevel(unsigned int level) {
    double bonus = 20;
    for(size_t i = 1; i < level; ++i) {
        bonus *= 1.1;
    }
    return bonus;
}

Tile *TreasureTile::changeOnExpended() {
    delete this;
    return new EmptyTile();
}

void TreasureTile::serialize(std::ostream &os) const {
    os << getDisplayCharacter() << " " << type << " ";
    item->serialize(os);
}

sf::Color TreasureTile::getColor() {
    return sf::Color::Yellow;
}

void TreasureTile::apply(Character &character, sf::RenderWindow &window) {
    bool choiceMade = false;
    sf::View itemInfo, equipActions, characterInfo;

    itemInfo.setViewport(sf::FloatRect({0.f, 0.f}, {0.75f, 0.75f}));
    equipActions.setViewport(sf::FloatRect({0.f, 0.75f}, {0.75f, 0.25f}));
    characterInfo.setViewport(sf::FloatRect({0.75f, 0.f}, {0.25f, 0.35f}));

    while(!choiceMade && window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Y:
                        choiceMade = true;
                        character.equipItem(item, type);
                        return;
                        break;
                    case sf::Keyboard::Scancode::N:
                        choiceMade = true;
                        return;
                        break;
                    case sf::Keyboard::Scancode::Escape:
                        window.close();
                    default: break;
                }
            }
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea({0, 0}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
        }

        window.clear(sf::Color::Black);
        window.setView(itemInfo);
        item->printSFML(window);
        window.setView(equipActions);

        sf::RectangleShape shape(equipActions.getSize());
        shape.setPosition(equipActions.getViewport().position);
        shape.setFillColor(sf::Color::White);

        window.draw(shape);

        sf::Font font("resources/text_fonts/montserrat/Montserrat-Black.otf");
        sf::Text text(font, "Y for yes");

        text.setScale(equipActions.getViewport().getCenter() * 2.f);
        text.setPosition(window.getView().getSize() / 8.f + sf::Vector2f(0.f, equipActions.getCenter().y * 0.5f));
        text.setCharacterSize(64);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Black);

        window.draw(text);

        text.setString("N for no");
        text.move({shape.getSize().x / 2.F, 0.f});
        text.setFillColor(sf::Color::Black);
        window.draw(text);

        window.setView(characterInfo);
        character.printSFML(window);
        window.display();
    }
}
