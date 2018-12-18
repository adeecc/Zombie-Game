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
A Game Engine is the backbone of a game, handling the rendering, error management, display, input managagemtn and other background tasks. It doesn't provide the logic for a game, and can be reused multiple times, eg: Unity3D. For this project I wrote my own basic game engine using C++ 17.

### Basic First Principles: 
#### Windows
SDL provides functions to create an external window to render the Sprites onto. It also provides functions to allow for detcting mouse events such as motion or a click, and key presses. 
#### Timing
The time between render of each individual frame is calculated and frame rate limited, so as to limit CPU and GPU Usage. Semi-fixed(delta time) Timestep is alos implemented, so that if the cpu is underperforming, the game speed doesnt slow down. 
### 2D Camera
The camera is used to provide easy scaling, and translation of the game world. It is also used to convert from normalized coordinated to world space coordinates, and vice versa. Camera Culling was also implemented to optimize the performance: A simple bounding box, and AABB collision test was used for this purpose.
### Sprites, Shaders and Textures 
A sprite is a two-dimensional image or animation that is integrated into a larger scene. Textures are mappings applied to Sprites. A shader is ised to apply this texture on the sprite. The sprites along wiht their shaders are rendered extremely efficiently through the spriteBatch class by using one vertex array object instead of many vertex buffer objects, sorting the "Glyphs" on the basis of their textures by using std::stable_sort to reduce GPU Overhead. The shaders (Vertex Shader: "colorShading.frag" and the fragment shader: "colorShading.vert") were writeen in version 130 of GL Structured Language. The GLSLProgram is used to load these shaders by using the OpenGL method: glCompileShader(). 

### Resource Manager and Cache
To make the Loading of textures and sprites even faster, Texture Caching was implemented, and used through the Resource Manager. Cache was implemented using a std::map (Ordered Map). ResourceManager was made into a statci class so that the entire game can use just one instance of it, removing redundancy in caching altogether.

### Input Manager
SDL methods were used to obtain mouse motion, left clicks, and key presses. Using a simple Unordered map, to track whether a key is beeing pressed down, continuous key input was obained. This allowed for player movement to be controlled through the keyboard, and firing through mouse motion and clicks. 

### Error Handling
To implement error checking, instead of using the deprecated try...throw...catch methods, a simple error and quit algorithm was implemented. All possible error scenarios where checked, and in casse it was satisfied the program would terminate with a relevant error message. 

## ZombieGame: The Game
The main logic of the game is handled by this: It provides the specific character arks, controls, abilities, and levels of a game. Here, the system, level data, and shaders are initialized. 

### Agents
These are the characters in a game. There three types of "Characters" in this game: Human and Zombie derive from Agents, and Player derives from Human. Humans are the provided with just random movements and minimal speeds, and zombies given a minimal AI to follow the nearest human and higher Health. PLayer is provided with higher health, Higher speed and guns to shoot down agents (Humans, or Zombies). 

#### Collision
Almost all sprites collide with each other in this game. Tow type of collisions were implemeted: one btween the agents, and one between an agent and the level. Agent with Agent collision uses simple AABB collision Logic, and Agent with level uses a Circle with square collision algorithm. This is also extended to enable camera culling which saves resources.

### Game Loop
In the main game loop after every frame, the victory and loss conditions are checked, inputs processed, agents and bullets updated, deltaTime Calculated, fps limited and then finally the game is drawn to the window.

# Build Instructions
Add SDL, GL and GLM to the list of dependancies, includes, deps, etc in visual studio for whichever mode is being used to compile. Bengine is compiled as a static library, and ZombieGame linked to it. 

# Issues
- Multiple types of textures are not rendered correctly in the level.

# Improvements
- [ ] Standardize the abilities of the agents and guns
- [ ] Font rendering
- [ ] Display score on screen, instead of terminal
- [ ] Display blood on killing of agents
- [ ] Audio Rendering
- [ ] Add some sort of absolute scoring system
- [ ] Optimizing the spriteBatch class even more
- [ ] Optimizing the camera
- [ ] Add more levels
  
