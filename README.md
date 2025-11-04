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

---

# so_long - Minerman! Pro

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**A 2D game where you collect items and escape while avoiding enemies**

</div>

---

## 📑 Table of Contents

- [About The Project](#about-the-project)
- [Learning Objectives](#learning-objectives)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
  - [Basic Usage](#basic-usage)
  - [Game Controls](#game-controls)
  - [Map Format](#map-format)
- [Project Structure](#project-structure)
- [Technical Implementation](#technical-implementation)
- [Resources](#resources)
- [License](#license)
- [Contact](#contact)

---

## 📖 About The Project

**so_long** (Minerman! Pro) is a 2D game project where you navigate a miner through a map, collecting all collectables while avoiding enemies, and reaching the exit. The project introduces game programming concepts using the MiniLibX graphics library.

This is version 3 of the project, featuring animated sprites, enemy AI, dynamite mechanics, explosion effects, and a score counter - making it a complete game experience.

### Built With

- **Language:** C
- **Graphics Library:** MiniLibX
- **Compiler:** gcc/clang
- **Build System:** Makefile
- **Norm:** 42 Norm compliant

---

## 🎯 Learning Objectives

This project taught me:

- **Graphics Programming:** Working with MiniLibX for window management and rendering
- **Game Loop:** Implementing frame-based game logic and animations
- **Event Handling:** Capturing keyboard input and responding to user actions
- **Sprite Animation:** Creating smooth character and object animations
- **Pathfinding:** Implementing flood fill algorithm for map validation
- **Collision Detection:** Handling player-enemy and player-object collisions
- **Game Design:** Creating engaging gameplay mechanics (enemies, explosions, scoring)

---

## 🚀 Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yigit-toq/42_Cursus.git
cd 42_Cursus
git checkout 02-so_long
cd so_long_v3
```

2. Compile the project
```bash
make
```

This will automatically:
- Clone and compile MiniLibX (Linux or macOS version)
- Compile libft library
- Create `so_long` executable

3. Compile bonus version (with enemies and animations)
```bash
make bonus
```

Creates `so_long_bonus` executable

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

**Mandatory Version:**
```bash
./so_long maps/map.ber
```

**Bonus Version:**
```bash
./so_long_bonus maps/map.ber
```

### Game Controls

| Key | Action |
|-----|--------|
| `W` or `↑` | Move Up |
| `A` or `←` | Move Left |
| `S` or `↓` | Move Down |
| `D` or `→` | Move Right |
| `SPACE` | Place Dynamite (Bonus) |
| `ESC` | Exit Game |

### Map Format

Maps are `.ber` files with the following characters:

| Character | Description |
|-----------|-------------|
| `0` | Empty space (walkable ground) |
| `1` | Wall (impassable) |
| `C` | Collectable (keys/items to collect) |
| `E` | Exit (door - opens when all collectables gathered) |
| `P` | Player starting position |
| `A` | Enemy (Bonus only) |

**Map Rules:**
- Must be rectangular
- Must be surrounded by walls (`1`)
- Must contain exactly 1 player (`P`)
- Must contain exactly 1 exit (`E`)
- Must contain at least 1 collectable (`C`)
- Must have a valid path from player to all collectables and exit
- Enemies (`A`) are optional (bonus feature)

**Example Map:**
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

---

## 📁 Project Structure

```
so_long_v3/
├── projects/
│   ├── mandatory/              # Mandatory version
│   │   ├── so_long.c          # Main program
│   │   ├── 0-graphic/         # Graphics and rendering
│   │   ├── 1-control/         # Player controls and error handling
│   │   └── 2-map/             # Map parsing and validation
│   │
│   └── bonus/                  # Bonus version
│       ├── so_long.c          # Main program with bonus features
│       ├── 0-animation/       # Sprite animations
│       ├── 1-graphic/         # Graphics with image loading
│       ├── 2-control/         # Enhanced controls
│       ├── 3-enemy/           # Enemy AI and movement
│       └── 4-map/             # Map handling
│
├── includes/
│   ├── so_long.h              # Mandatory header
│   ├── so_long_bonus.h        # Bonus header
│   └── utils/                 # Utility headers (macros)
│
├── libraries/
│   ├── libft/                 # Libft library
│   └── minilibx/              # MiniLibX graphics library
│
├── textures/
│   ├── 0-environment/         # Ground and wall sprites
│   ├── 1-collectable/         # Key/item animations (9 frames)
│   ├── 2-explosion/           # Explosion effects
│   ├── 3-dynamite/            # Dynamite sprites
│   ├── 4-enemy/               # Enemy animations (4 directions)
│   ├── 5-player/              # Player animations (4 directions + death)
│   └── 6-door/                # Door animations (locked/unlocked)
│
├── Makefile                   # Build automation
└── README.md                  # Project documentation
```

---

## 🔧 Technical Implementation

### Key Design Decisions

1. **Animation System:** Frame-based animations for all moving entities
2. **Enemy AI:** Simple pathfinding with directional movement
3. **Collision Detection:** Grid-based collision with tile checking
4. **Flood Fill Validation:** Ensures map is solvable before starting
5. **Event-Driven Architecture:** Hooks for keyboard input and frame updates
6. **Multi-Platform Support:** Automatic detection and compilation for Linux/macOS

### Game Features

**Mandatory:**
- Basic movement (WASD or Arrow keys)
- Collect all items
- Reach the exit
- Display move counter in terminal
- Window management (close button, ESC key)

**Bonus:**
- ✨ **Animated Sprites:** 9-frame animations for collectables, player, enemies
- 🚶 **Directional Player:** Different sprites for 4 directions (F/B/L/R)
- 👾 **Enemy AI:** Patrolling enemies with collision detection
- 💣 **Dynamite Mechanic:** Place explosives to defeat enemies
- 💥 **Explosion Effects:** Animated explosions
- 🚪 **Animated Door:** Door opens when all items collected
- 📊 **On-Screen Display:** Move counter and score displayed in game
- 💀 **Death Animation:** Player death effect on enemy collision

### Implementation Example

**Animation System:**
```c
// Player animation structure
typedef struct s_player
{
    void            *img;           // Current sprite image
    char            direction;      // F/B/L/R
    int             frame;          // Current animation frame
    int             death;          // Death state flag
    unsigned int    speed;          // Movement speed
    int             transform[2];   // Position [x, y]
}   t_player;

// Frame update in game loop
int draw_init(t_game *game)
{
    static int frame = 0;
    
    frame++;
    if (frame % PLAYER_SPEED == 0)
        animate_player(game);      // Update player frame
    
    if (frame % ENEMY_SPEED == 0)
        animate_enemy(game);       // Update enemy frame
    
    render_frame(game);            // Draw everything
    return (0);
}
```

**Enemy Movement:**
```c
void enemy_movement(t_game *game, t_enemy *enemy)
{
    // Check valid directions
    int valid_dirs[4] = {0, 0, 0, 0};  // Up, Down, Left, Right
    
    // Try to move towards player
    if (enemy->transform[1] > game->player->transform[1])
        attempt_move(game, enemy, UP);
    else if (enemy->transform[1] < game->player->transform[1])
        attempt_move(game, enemy, DOWN);
    
    if (enemy->transform[0] > game->player->transform[0])
        attempt_move(game, enemy, LEFT);
    else if (enemy->transform[0] < game->player->transform[0])
        attempt_move(game, enemy, RIGHT);
    
    // Update enemy sprite based on direction
    update_enemy_sprite(game, enemy);
}
```

**Map Validation (Flood Fill):**
```c
void map_validation(t_game *game)
{
    int **visited = create_2d_array(game->map->h, game->map->w);
    
    // Start flood fill from player position
    flood_fill(game, visited, 
               game->player->y, 
               game->player->x);
    
    // Check if all collectables and exit are reachable
    if (!all_reachable(game, visited))
        error_controller(game, 'M', "Invalid map: unreachable items", 0);
    
    free_2d_array(visited);
}
```

### Graphics Pipeline

1. **Initialization:** Create window and load all sprite images
2. **Game Loop:** 
   - Process keyboard input
   - Update game logic (movement, collisions)
   - Update animations (increment frames)
   - Render frame (draw map, entities, UI)
3. **Event Handling:** Respond to key presses and window events
4. **Cleanup:** Free all allocated memory and images

---

## 📚 Resources

- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Game Loop Patterns](https://gameprogrammingpatterns.com/game-loop.html)
- [Flood Fill Algorithm](https://en.wikipedia.org/wiki/Flood_fill)
- [Sprite Animation Techniques](https://en.wikipedia.org/wiki/Sprite_(computer_graphics))
- [42 Norm](https://github.com/42School/norminette)

---

## 📄 License

This project is part of the 42 School curriculum. Code is free to use for educational purposes.

---

## 📬 Contact

**Yiğit Top** - [@yigit-toq](https://github.com/yigit-toq)

---

<div align="center">

**Made with ☕ at 42 Kocaeli**

*This project was completed as part of the 42 School curriculum.*

</div>
