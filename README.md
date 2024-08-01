# 2D Evolution Game

Welcome to the **2D Evolution Game**! This game allows local multiplayer where each player controls an organism composed of different types of cells, each with unique properties and interactions. Players can move their organisms, gain energy, and evolve by adding new cells.

## Features

- **Local Multiplayer**: Play with friends in a local multiplayer setting.
- **Organism Control**: Each player controls an organism with a variety of cells.
- **Cell Types**: Cells have different properties and interactions, such as:
  - **Mouth Cells**: Eat food to gain energy.
  - **Attack Cells**: Attack and kill opponent organisms.
- **Energy and Evolution**: Gain energy to evolve and add new cells to your organism.

## Prerequisites

Before you start, ensure you have the following installed on your system:

- **SDL2 Library**: The Simple DirectMedia Layer 2 library is required to run the game.

## Installation

Follow these steps to build and run the game:

1. **Install SDL2**:

   - On Ubuntu/Debian:

     ```bash
     sudo apt-get install libsdl2-dev
     ```
   - On macOS (using Homebrew):
	 
     ```bash
     brew install sdl2
     ```
   - On Windows:
     - Download the SDL2 development library from the [SDL2 website](https://www.libsdl.org/download-2.0.php) and follow the instructions for installation.

2. **Clone the Repository**:
   ```bash
   git clone https://github.com/Sunit-Shrestha/Evolution-Game.git
   ```
3. **Navigate to the Project Directory:**

```bash
cd Evolution-Game
```
4. **Build the Project:**

```bash
make
```
4. **Run the Game:**

```bash
./bin/main
```
## Usage
- **Control Your Organism:** Use keyboard controls to move your organism around.

- **Interact with Cells:** Each cell type has unique actions. Use them to gain energy and combat opponents.

- **Evolve Your Organism:** Accumulate energy to add new cells and evolve your organism. The game will prompt you when you have enough energy to evolve.

## Controls
- **Movement:** Arrow keys and WASD keys.

## Contributing
If you'd like to contribute to this project, please fork the repository and submit a pull request. Ensure that your changes are well-documented and tested.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Contact
For any questions or issues, please contact sunitshrsth@gmail.com

Happy gaming!