<div align="center">

# My progress
|Circle | Project | Language | Description | Score | 
|:-----:|:-------:|:--------:|:-----------:|:-----:|
|00| [libft](https://github.com/yigit-toq/42_Cursus/tree/0-libft) | C | Create your custom C library | 125% |
|01| [ft_printf](https://github.com/yigit-toq/42_Cursus/tree/1-ft_printf) | C | Recreate printf | 100% |
|01| [get_next_line](https://github.com/yigit-toq/42_Cursus/tree/2-get_next_line) | C | Read files line by line | 100% |
|02| [minitalk](https://github.com/yigit-toq/42_Cursus/tree/3-minitalk) | C | Message system using signals | 100% |
|02| [push_swap](https://github.com/yigit-toq/42_Cursus/tree/5-push_swap) | C | Stack sorting algorithms | 100% |
|02| [so_long](https://github.com/yigit-toq/42_Cursus/tree/4-so_long) | C | 2D map-based game | 100% |
|03| [minishell](https://github.com/yigit-toq/42_Cursus/tree/7-minishell) | C | Simple command-line shell | 100% |
|03| [philosophers](https://github.com/yigit-toq/42_Cursus/tree/6-philosophers) | C | Deadlock resolution simulation | 100% |
|04| [cub3d](https://github.com/yigit-toq/42_Cursus/tree/8-cub3d) | C | 3D raycasting game | 125%
|04| [cpp00](https://github.com/yigit-toq/42_Cursus/tree/04-cpp00) | C++ | CPP exercise | 100%
|04| [cpp01](https://github.com/yigit-toq/42_Cursus/tree/04-cpp01) | C++ | CPP exercise | 100%
|04| [cpp02](https://github.com/yigit-toq/42_Cursus/tree/04-cpp02) | C++ | CPP exercise | 100%
|04| [cpp03](https://github.com/yigit-toq/42_Cursus/tree/04-cpp03) | C++ | CPP exercise | 100%
|04| [cpp04](https://github.com/yigit-toq/42_Cursus/tree/04-cpp04) | C++ | CPP exercise | 100%
|05| [cpp05](https://github.com/yigit-toq/42_Cursus/tree/05-cpp05) | C++ | CPP exercise | 100%
|05| [cpp06](https://github.com/yigit-toq/42_Cursus/tree/05-cpp06) | C++ | CPP exercise | 100%
|05| [cpp07](https://github.com/yigit-toq/42_Cursus/tree/05-cpp07) | C++ | CPP exercise | 100%
|05| [cpp08](https://github.com/yigit-toq/42_Cursus/tree/05-cpp08) | C++ | CPP exercise | 100%
|05| [cpp09](https://github.com/yigit-toq/42_Cursus/tree/05-cpp09) | C++ | CPP exercise | 100%
|05| [ft_irc](https://github.com/yigit-toq/42_Cursus/tree/05-ft_irc) | C++ | IRC Server | 100%

# cub3d - 3D Raycasting Game Engine

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-125%2F100-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**A Wolfenstein 3D inspired raycasting engine with bonus features**

---

## 📽️ Demo

![cub3D](https://github.com/user-attachments/assets/e2914311-8c13-48ea-a9d4-c2c7e7994c40)

---

</div>

## 📑 Table of Contents

- [About The Project](#about-the-project)
- [Learning Objectives](#learning-objectives)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
  - [Basic Usage](#basic-usage)
  - [Map Format](#map-format)
  - [Controls](#controls)
- [Project Structure](#project-structure)
- [Technical Implementation](#technical-implementation)
- [Bonus Features](#bonus-features)
- [Resources](#resources)
- [License](#license)
- [Contact](#contact)

---

## 📖 About The Project

**cub3d** is a 3D graphical project inspired by the legendary **Wolfenstein 3D**, which is considered the first FPS (First Person Shooter) game. Using the raycasting technique, this project renders a 3D perspective from a 2D map, creating an immersive first-person experience.

This project teaches fundamental concepts of computer graphics, game engine architecture, and mathematical transformations. It includes both mandatory features (basic raycasting) and extensive bonus features (minimap, animations, enemies, sounds, weapons).

### Built With

- **Language:** C
- **Graphics Library:** MiniLibX
- **Audio Library:** SDL2 (bonus)
- **Custom Library:** libft
- **Compiler:** gcc/clang
- **Build System:** Makefile
- **Norm:** 42 Norm compliant

---

## 🎯 Learning Objectives

This project taught me:

- **Raycasting Algorithm:** Understanding and implementing the DDA (Digital Differential Analysis) algorithm
- **3D Projection:** Converting 2D maps to 3D perspective views
- **Texture Mapping:** Applying textures to walls and sprites
- **Vector Mathematics:** Working with 2D vectors, angles, and trigonometry
- **Graphics Programming:** Using MiniLibX for pixel manipulation and rendering
- **Map Parsing:** Reading and validating custom map formats
- **Game Loop:** Implementing a real-time rendering loop
- **Event Handling:** Processing keyboard and mouse inputs
- **Memory Management:** Efficient handling of textures and graphics data
- **Sprite Rendering:** Drawing 2D sprites in a 3D environment
- **Animation Systems:** Creating frame-based animations
- **Audio Integration:** Synchronizing sound effects with game events

---

## 🚀 Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yigit-toq/42_Cursus.git
cd 42_Cursus
git checkout 04-cub3d
```

2. Install dependencies (Linux)
```bash
# MiniLibX dependencies
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# SDL2 for audio (bonus)
sudo apt-get install libsdl2-dev libsdl2-mixer-dev
```

3. Compile the project
```bash
# Compile mandatory version
make

# Compile bonus version
make bonus

# Compile both
make all
```

4. (Optional) Clean object files
```bash
make clean
```

5. (Optional) Remove all compiled files
```bash
make fclean
```

6. (Optional) Recompile everything
```bash
make re
```

---

## 💻 Usage

### Basic Usage

```bash
# Mandatory version
./cub3d <map_file.cub>

# Bonus version
./cub3d_bonus <map_file.cub>
```

### Examples

```bash
# Run mandatory version with Ascent map
./cub3d libraries/maps/ascent_mandatory.cub

# Run bonus version with Ascent map (includes enemies, sounds, weapons)
./cub3d_bonus libraries/maps/ascent_bonus.cub
```

### Map Format

Map files use the `.cub` extension and define textures, colors, and layout.

**Basic Structure:**
```
NO      ./assets/textures/env/1.xpm
SO      ./assets/textures/env/2.xpm
WE      ./assets/textures/env/3.xpm
EA      ./assets/textures/env/4.xpm
F       140,140,140
C       180,240,255

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

**Map Elements:**
- `1` = Wall
- `0` = Empty space (floor)
- `N`, `S`, `E`, `W` = Player start position and direction
- Spaces = Void (outside the map)

**Texture Identifiers:**
- `NO` = North wall texture
- `SO` = South wall texture
- `WE` = West wall texture
- `EA` = East wall texture
- `F` = Floor color (R,G,B)
- `C` = Ceiling color (R,G,B)

**Bonus Map Elements:**
- `D` = Door
- `A` = Enemy spawn point
- `GR` = Ground texture
- `WP` = Background/wallpaper texture
- `CR` = Crosshair texture

**Map Rules:**
- Map must be closed/surrounded by walls
- Only one player start position
- Must contain only valid characters
- Colors must be in RGB format (0-255)
- Texture paths must be valid

### Controls

**Mandatory:**
- `W` / `↑` = Move forward
- `S` / `↓` = Move backward
- `A` = Strafe left
- `D` = Strafe right
- `←` = Rotate camera left
- `→` = Rotate camera right
- `ESC` = Exit game

**Bonus:**
- `Mouse Movement` = Look around
- `Mouse Left Click` = Fire weapon
- `SPACE` = Open/close doors
- `Q` = Use special ability (Reyna's skill)
- `1` = Switch to knife
- `2` = Switch to vandal

---

## 📁 Project Structure

```
cub3d/
├── projects/
│   ├── mandatory/
│   │   ├── cub3d.c               # Main program
│   │   ├── init.c                # Initialization
│   │   ├── 0-file/               # File parsing
│   │   │   ├── file1.c
│   │   │   └── file2.c
│   │   ├── 1-utils/              # Utility functions
│   │   │   ├── utils1.c
│   │   │   ├── utils2.c
│   │   │   ├── utils3.c
│   │   │   └── utils4.c
│   │   ├── 2-error/              # Error handling
│   │   │   └── error.c
│   │   ├── 3-raycast/            # Raycasting engine
│   │   │   └── raycasting1.c
│   │   ├── 4-graphics/           # Graphics rendering
│   │   │   └── graphics.c
│   │   └── 5-controller/         # Input handling
│   │       └── controller.c
│   └── bonus/
│       ├── cub3d.c               # Main program (bonus)
│       ├── init.c                # Initialization (bonus)
│       ├── 0-file/               # File parsing (bonus)
│       ├── 1-utils/              # Utilities + audio
│       │   ├── audio.c           # SDL2 audio system
│       │   ├── utils1.c
│       │   ├── utils2.c
│       │   ├── utils3.c
│       │   └── utils4.c
│       ├── 2-error/              # Error handling
│       ├── 3-raycast/            # Advanced raycasting
│       │   ├── raycasting1.c
│       │   ├── raycasting2.c
│       │   ├── render1.c
│       │   └── render2.c
│       ├── 4-graphics/           # Graphics + minimap
│       │   ├── graphics.c
│       │   └── minimap.c
│       └── 5-controller/         # Controllers + animations
│           ├── animation1.c
│           ├── animation2.c
│           ├── controller1.c
│           ├── controller2.c
│           └── progress.c
├── includes/
│   ├── cub3d_mandatory.h         # Mandatory header
│   ├── cub3d_bonus.h             # Bonus header
│   ├── bonus/
│   │   └── audio.h               # Audio system header
│   ├── other/
│   │   ├── mandatory/
│   │   │   ├── macro.h           # Mandatory macros
│   │   │   └── struct.h          # Mandatory structures
│   │   └── bonus/
│   │       ├── macro.h           # Bonus macros
│   │       └── struct.h          # Bonus structures
│   └── utils/
│       ├── libft.h
│       ├── get_next_line/
│       ├── parser/
│       └── printf/
├── assets/
│   ├── textures/                 # Wall, floor, sprite textures
│   │   ├── char/                 # Character sprites
│   │   │   ├── enemy/
│   │   │   └── reyna/
│   │   │       ├── q/            # Skill animations
│   │   │       └── r/            # Ultimate animations
│   │   ├── env/                  # Environment textures
│   │   │   ├── background/
│   │   │   └── door/
│   │   └── gun/                  # Weapon sprites
│   │       ├── knife/
│   │       └── vandal/
│   └── sounds/                   # Audio files (.wav)
├── libraries/
│   └── maps/                     # Map files
│       ├── ascent_mandatory.cub
│       └── ascent_bonus.cub
├── Makefile                      # Build automation
└── README.md                     # Project documentation
```

---

## 🔧 Technical Implementation

### Raycasting Algorithm

The core of the project is the **DDA (Digital Differential Analysis)** algorithm:

1. **Ray Generation:** For each vertical screen column, cast a ray from player position
2. **DDA Traversal:** Step through the map grid until hitting a wall
3. **Distance Calculation:** Calculate perpendicular distance to avoid fisheye effect
4. **Wall Height:** Calculate wall slice height based on distance
5. **Texture Mapping:** Map texture coordinates to screen coordinates

**Key Formulas:**

```c
// Ray direction
rayDirX = dirX + planeX * cameraX;
rayDirY = dirY + planeY * cameraX;

// DDA step calculation
deltaDistX = abs(1 / rayDirX);
deltaDistY = abs(1 / rayDirY);

// Perpendicular distance (avoid fisheye)
perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

// Wall height
lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
```

### Data Structures

```c
// Main game structure
typedef struct s_data
{
    void        *mlx;                // MiniLibX instance
    void        *win;                // Window pointer
    void        *img;                // Image buffer
    char        *addr;               // Image address
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    
    // Player
    double      posX;                // Player X position
    double      posY;                // Player Y position
    double      dirX;                // Direction vector X
    double      dirY;                // Direction vector Y
    double      planeX;              // Camera plane X
    double      planeY;              // Camera plane Y
    
    // Map
    char        **map;               // 2D map array
    int         map_width;
    int         map_height;
    
    // Textures
    t_texture   textures[4];         // North, South, East, West
    int         floor_color;         // Floor RGB color
    int         ceiling_color;       // Ceiling RGB color
    
    // Bonus
    t_sprite    *sprites;            // Sprite array
    int         sprite_count;
    t_audio     *audio;              // Audio system
    t_weapon    *weapon;             // Current weapon
    int         minimap_enabled;
}   t_data;

// Texture structure
typedef struct s_texture
{
    void        *img;                // Texture image
    char        *addr;               // Texture data
    int         width;
    int         height;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}   t_texture;

// Sprite structure (bonus)
typedef struct s_sprite
{
    double      x;                   // World X position
    double      y;                   // World Y position
    int         texture;             // Texture index
    double      distance;            // Distance from player
    int         type;                // Enemy, item, etc.
    t_animation *anim;               // Animation data
}   t_sprite;
```

### Rendering Pipeline

```
1. Clear screen (ceiling and floor colors)
2. For each screen column (x = 0 to SCREEN_WIDTH):
   a. Calculate ray direction
   b. Perform DDA to find wall hit
   c. Calculate wall distance
   d. Calculate wall slice height
   e. Get texture coordinates
   f. Draw textured wall slice
3. Sort sprites by distance
4. For each sprite:
   a. Calculate sprite screen position
   b. Calculate sprite dimensions
   c. Draw sprite with transparency
5. Draw minimap (bonus)
6. Draw weapon/HUD (bonus)
7. Display image to window
```

### Player Movement

```c
// Forward/backward movement
if (key == W)
{
    if (map[(int)(posY)][(int)(posX + dirX * moveSpeed)] == '0')
        posX += dirX * moveSpeed;
    if (map[(int)(posY + dirY * moveSpeed)][(int)(posX)] == '0')
        posY += dirY * moveSpeed;
}

// Rotation
if (key == LEFT)
{
    oldDirX = dirX;
    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    
    oldPlaneX = planeX;
    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}
```

### Texture Mapping

```c
// Calculate texture X coordinate
int texX = (int)(wallX * texWidth);
if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
    texX = texWidth - texX - 1;

// Calculate texture Y coordinate for each pixel
double step = 1.0 * texHeight / lineHeight;
double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;

for (int y = drawStart; y < drawEnd; y++)
{
    int texY = (int)texPos & (texHeight - 1);
    texPos += step;
    
    int color = texture[texHeight * texY + texX];
    put_pixel(img, x, y, color);
}
```

---

## 🎁 Bonus Features

This implementation includes extensive bonus features:

### 1. Minimap
- Real-time top-down view of the map
- Player position and direction indicator
- Fog of war effect
- Interactive minimap (shows enemies, doors)

### 2. Animated Sprites
- **Weapons:** Knife and Vandal with fire/idle/take animations
- **Characters:** Reyna character with skills (Q and R abilities)
- **Enemies:** Animated enemy sprites with AI
- **Doors:** Open/close animations

### 3. Audio System (SDL2)
- Background music
- Weapon sound effects (shooting, reload)
- Footstep sounds
- Door sounds
- Enemy sounds
- Skill activation sounds

### 4. Interactive Elements
- **Doors:** Open and close with SPACE key
- **Enemies:** Basic AI with pathfinding
- **Weapons:** Multiple weapons with different stats
- **Skills:** Special abilities (Reyna's dismiss and empress)

### 5. Enhanced Graphics
- Ground textures (not just solid colors)
- Background/skybox textures
- Crosshair overlay
- Weapon sprites in first person
- Smooth animations (60 FPS)

### 6. Mouse Controls
- Mouse movement for camera rotation
- Mouse click for shooting
- Smooth mouse sensitivity

### 7. HUD Elements
- Health bar
- Ammo counter
- Skill cooldown indicators
- FPS counter

---

## 📚 Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Essential raycasting guide
- [Ray-Casting Tutorial For Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) - Original inspiration
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [SDL2 Documentation](https://wiki.libsdl.org/) - For audio
- [42 Norm](https://github.com/42School/norminette)
- [DDA Algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))

---

## 📄 License

This project is part of the 42 School curriculum. Code is free to use for educational purposes.

---

## 📬 Contact

**Yiğit Top** - [@yigit-toq](https://github.com/yigit-toq)

---

<div align="center">

**Made with 🎮 at 42 Kocaeli**

*This project was completed as part of the 42 School curriculum.*

*Inspired by Wolfenstein 3D and Valorant*

</div>
