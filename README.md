# 42_Cursus

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

# cub3d

A simple 3D raycasting game engine inspired by Wolfenstein 3D, written in C using the MiniLibX graphics library. This project is part of the 42 School curriculum and aims to teach the basics of raycasting, graphics, and game engine architecture.

---

## 📽️ Demo

![cub3D](https://github.com/user-attachments/assets/e2914311-8c13-48ea-a9d4-c2c7e7994c40)

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Project Structure](#project-structure)
- [Map Format](#map-format)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Bonus Features](#bonus-features)
- [Dependencies](#dependencies)
- [Norminette](#norminette)
- [Author](#author)
- [42 Global Rules](#42-global-rules)

---

## Description

**cub3d** is a graphical project that introduces you to raycasting and basic game engine concepts. The goal is to render a 3D environment from a 2D map using the MiniLibX library. The project includes both a mandatory part (basic raycasting, textures, player movement) and a bonus part (minimap, sound, animated sprites, doors, weapons, enemies, etc).

---

## Features

- Raycasting engine (Wolfenstein 3D style)
- Texture mapping for walls, floor, and ceiling
- Player movement and rotation (keyboard and mouse)
- Map parsing and validation (custom .cub format)
- Error handling and input validation
- Modular code structure (mandatory/bonus separation)
- Bonus: Minimap, audio, animated sprites, doors, weapons, enemies, etc.

---

## Project Structure

- `projects/mandatory/` : Main source files for the mandatory part
- `projects/bonus/`     : Source files for the bonus part (minimap, sound, etc)
- `includes/`           : Header files (structs, macros, function prototypes)
- `libraries/`          : External libraries (libft, minilibx)
- `assets/`             : Textures (`.xpm`), sounds (`.wav`), sprites
- `maps/` or `libraries/maps/` : Example map files (`.cub`)
- `Makefile`            : Build system

---

## Map Format

Map files (`.cub`) define the world and resources. Example:

```plaintext
NO      ./assets/textures/env/1.xpm   # North wall texture
SO      ./assets/textures/env/2.xpm   # South wall texture
WE      ./assets/textures/env/3.xpm   # West wall texture
EA      ./assets/textures/env/4.xpm   # East wall texture
F       140,140,140                   # Floor color (RGB)
C       180,240,255                   # Ceiling color (RGB)

				1111
	111111111111111001
	101000000000011001
	100000000000011011
	100000100000011001
	100000000000000001
	101011110000011001
	...
```

**Legend:**
- `1` = Wall
- `0` = Floor
- `N`, `S`, `E`, `W` = Player start position and direction
- `D` = Door (bonus)
- `A` = Enemy (bonus)
- Spaces are ignored

**Bonus map keys:**
- `GR` = Ground texture
- `WP` = Background/wallpaper
- `CR` = Crosshair texture

---

## Installation

```sh
make
```

- Requires: `gcc`, `make`, and dependencies for MiniLibX (X11 for Linux, OpenGL for macOS).
- The Makefile will automatically clone and build `libft` and `minilibx` if not present.

---

## Usage

```sh
./cub3d <map_file.cub>
```

- Example: `./cub3d libraries/maps/ascent_mandatory.cub`

---

## Controls

- `W/A/S/D` or Arrow keys: Move/rotate player
- Mouse: Look around (bonus)
- `ESC`: Exit the game
- `SPACE`: Interact (open/close doors, bonus)
- `MOUSE1`: Fire weapon (bonus)

---

## Bonus Features

- Minimap rendering
- Animated sprites (weapons, enemies, doors)
- Sound effects (SDL2, .wav)
- Multiple weapons (knife, vandal, skills)
- Enemies with basic AI
- Doors (open/close)
- Crosshair, HUD, FPS counter
- Skybox, ground textures, background

---

## Dependencies

- [MiniLibX](https://github.com/42Paris/minilibx-linux) (graphics)
- [libft](https://github.com/yigit-toq/42_Cursus) (custom C library)
- [SDL2](https://www.libsdl.org/) (for audio, bonus)

---

## Norminette

To check code style:

```sh
make norminette
```

---

## Author

- [ytop](mailto:ytop@student.42kocaeli.com.tr)
- [doerkova](doerkova@student.42kocaeli.com.tr)

---

## 42 Global Rules

- No unauthorized external code
- No code generators or copy-paste from the internet
- All code must be written and understood by you
- Respect the [subject PDF](https://github.com/42Paris/minilibx-linux) and 42's evaluation rules

---
