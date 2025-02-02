# Cub3D
This project is a simple yet captivating **pseudo-3D game** built using **raycasting**! This project is a fun demonstration of basic game development concepts like rendering, raycasting, and 3D perspective, all within a 2D grid. It features a first-person perspective where the player can navigate through a maze-like environment.

Project is made by [Viktoriia](https://github.com/vkuznets23) and [Jere](https://github.com/Jerehirvonenn)

## Features
- **Raycasting Engine**: Implements the core of the game’s graphics, simulating a 3D environment using 2D raycasting.
- **Player Movement**: Navigate through a maze using arrow keys or WASD.
- **Textured Walls**: Walls are rendered with textures, giving the game a pseudo-3D effect.

## Installation
``` bash
git clone https://github.com/vkuznets23/cub3d.git cub3d
cd cub3d
make
```

## Usage
To run the game, simply execute the following command after the build:
``` bash
./cub3d map.cub
```
Where map.cub is the map file that defines the maze and the environment. You can create your own .cub file or use the example provided in the repository

## Controls
* WASD: Move the player
* Arrows left/right: Look around
* ESC: Exit the game

## Map Format
The game uses a .cub file to define the map. A sample map file is included in the repository. Here's a basic overview of the file format
``` txt
NO ./textures/north.png  # Texture for the North wall
SO ./textures/south.png  # Texture for the South wall
EA ./textures/east.png   # Texture for the East wall
WE ./textures/west.png   # Texture for the West wall

F 220,100,0  # Floor color
C 255,255,255  # Ceiling color

111111
100001
101101
101101
100001
111111
```
* **NO, SO, EA, WE:** Paths to the wall textures
* **F, C:** RGB values for the floor and ceiling colors
* **Map:** A grid of numbers where 1 represents a wall, and 0 represents an empty space

## Acknowledgements
1. Thanks to Hive Helsinki for providing the learning materials and inspiration for this project.
2. MinilibX library for graphics handling.

## Contribution
Contributions are welcome! If you spot any bugs, feel free to open an issue.
