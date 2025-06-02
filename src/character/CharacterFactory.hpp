#ifndef FMI_COURSE_PROJECT_DND_CHARACTERFACTORY_HPP
#define FMI_COURSE_PROJECT_DND_CHARACTERFACTORY_HPP

#include "Character.hpp"

/**
 * @class CharacterFactory
 * @ingroup Character
 * @brief A factory class for creating Character objects.
 *
 * Provides utility methods for creating characters from user input.
 */
class CharacterFactory {
public:
    /**
     * @brief Creates a Character object based on user input.
     * @note used only for terminal implementation
     * @return A new Character instance.
     */
    static Character createCharacterFromUserInput();
};

#endif
