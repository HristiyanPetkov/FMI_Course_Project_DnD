# 🎲 DnD Tile-Based RPG Game

A tile-based dungeon crawler built in C++ with terminal and SFML graphics modes. Traverse procedurally generated mazes, collect treasures, and fight monsters in a Dungeons & Dragons-inspired setting.

---

## ⚙️ Requirements

- C++20 or later
- [CMake](https://cmake.org/) ≥ 3.22
- Git (for cloning with submodules)
- A modern compiler (e.g., g++, clang++, MSVC)

---

## 🚀 How to Run

### 1. Clone the repository (with submodules)

```bash
> git clone --recurse-submodules https://github.com/HristiyanPetkov/FMI_Course_Project_DnD.git
> cd FMI_Course_Project_DnD
```

If you forgot `--recurse-submodules`, run:
```bash
> git submodule update --init --recursive
```

---

### 2. Build the project with CMake

```bash
> mkdir build
> cd build
> cmake ..
> cmake --build .
```

---

### 3. Run the game
After building, run the game executable using one of the following flags:
- Terminal/Console Mode:
```bash
> ./DnD_application -t
```
- Load from Save File:
```bash
> ./DnD_application -s savefile.txt
```
- View High Scores(if no amount is given prints top 10):
```bash
> ./DnD_application -h "amount"
```
If no flag is passed, the game will launch in graphical (SFML) mode by default.

---

## 📚 Documentation

To generate Doxygen documentation:

```bash
> doxygen Doxyfile
```

---

## 📌 Notes

- Ensure your system has SFML development libraries installed **if not using the submodule directly**.
- On Linux, you might need to install SFML dependencies:
```bash
> sudo apt install libsfml-dev
```
- SFML is included as a submodule in external/SFML, and CMake is configured to build it alongside the project.

---

## 🔮 Future development

- Sound effects and music (optional)
- Add settings/configuration menu
- Improve character stats and leveling
