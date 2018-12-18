# Zombie-Game
A 2D single Player game in C++

# Table of Contents:
  1. About
     - Gameplay
  2. Requirements
     - Hardware Requirements
     - Software Requirements
  3. Documentation
  4. Build Instructions
  5. Issues
  6. Improvements
 
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

# Requirements
## Hardware Requirements
- CPU: 1.2 GHz or Higher
- GPU: Embedded Graphics or Better
- Ram: 2Gb or higher
- OS: Windows 7/8/10

## Software Requirements
- Microsoft Visual Studio 2015 or Higher
- SDL
- GLM
- OpenGL

# Documentation
## Bengine: The Game Engine

### Basic First Principles: 
#### Windows
#### Timing
### 2D Camera
### Resource Manager, Textures and Sprites
### Input Manager
### Rendering
### Cache
### Error Handling


## ZombieGame: The Game

### Agents
#### Humans
#### Player
#### Zombies

### Gun

### Game Loop

# Build Instructions

# Issues

# Improvements
  
  
