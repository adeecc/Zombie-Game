# Zombie-Game
A 2D single Player game in C++

# Table of Contents:
  1. About
     - Gameplay
  2. Documentation
  3. Build Instructions
     - Hardware Requirements
     - Software Requirements
  4. Issues
  5. Improvements
 
# About
This is a simple 2D game using [SDL](https://www.libsdl.org/) and [OpenGL] (https://www.opengl.org/). The game renders several sprite batches at once, along with relevant textures and employs the use of Shaders (Vertex and Fragment). OpenGL interacts directly with the GPU, while SDL does not, limitng the game performance by cpu bottlenecking. 
## Gameplay
The game is almost a simple single player RPG. 
### Controls:
- W: Forward
- S: Backward
- A: Left
- D: Right
- MouseButtonLeft: Firing the gun
- Number Keys: Selecting Gun (3 guns given by default)

The objective of the player (Blue Sprite) is to eliminate all "Zombies" (Green Sprites) before they turn all "Humans" (Red Sprites) to zombies. Humans turn to zombies on contact with other zombies. The game ends when the human comes in contact with a zombie, or all the zombies have been eliminated. 

## Default Guns:
- Magnum (1)
- Pump Shotgun (2)
- MP5 (3)

# Documentation


# Build Instructions
## Hardware Requirements
## Software Requirements

# Issues

# Improvements
  
  
