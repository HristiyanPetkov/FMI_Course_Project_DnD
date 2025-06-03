#ifndef FMI_COURSE_PROJECT_DND_TILE_HPP
#define FMI_COURSE_PROJECT_DND_TILE_HPP
#include <SFML/Graphics.hpp>
#include "../../character/Character.hpp"


class Tile {
public:
    virtual void apply(Character& character);
    virtual char getDisplayCharacter() const = 0;
    virtual bool isEmpty();
    virtual Tile* changeOnExpended();
    virtual void serialize(std::ostream& os) const;
    static Tile* deserialize(std::istream &is);
    virtual ~Tile() = default;
    virtual Tile* clone() const = 0;

    void renderSFML(sf::RenderWindow& window, float x, float y, float tileSizeX, float tileSizeY);
    virtual void apply(Character& character, sf::RenderWindow& window);
protected:
    virtual sf::Color getColor() = 0;
};


#endif
