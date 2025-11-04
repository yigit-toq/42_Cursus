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

# ft_printf - Recreating printf

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**Recreate the famous printf function from the C standard library**

</div>

---

## 📑 Table of Contents

- [About The Project](#about-the-project)
- [Learning Objectives](#learning-objectives)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
  - [Basic Usage](#basic-usage)
  - [Format Specifiers](#format-specifiers)
  - [Examples](#examples)
- [Project Structure](#project-structure)
- [Technical Implementation](#technical-implementation)
- [Resources](#resources)
- [License](#license)
- [Contact](#contact)

---

## 📖 About The Project

**ft_printf** is the second project in the 42 curriculum that challenges you to recreate one of the most versatile and widely-used functions in C programming: `printf()`. This project deepens your understanding of variadic functions, string parsing, and formatted output.

The goal is to create a library containing `ft_printf()`, a function that mimics the behavior of the original printf, handling multiple conversion specifiers and returning the number of characters printed.

### Built With

- **Language:** C
- **Compiler:** gcc/clang
- **Build System:** Makefile
- **Norm:** 42 Norm compliant

---

## 🎯 Learning Objectives

This project taught me:

- **Variadic Functions:** Understanding how to use `va_list`, `va_start`, `va_arg`, and `va_end` from `<stdarg.h>`
- **Format String Parsing:** Analyzing format strings character by character to identify conversion specifiers
- **Type Conversions:** Converting different data types (int, unsigned int, pointers) to strings
- **Base Conversions:** Converting numbers to hexadecimal and handling different bases
- **Write System Call:** Working directly with `write()` for output operations
- **Error Management:** Handling write errors and propagating them correctly
- **Modular Design:** Breaking down complex problems into smaller, manageable functions

---

## 🚀 Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yigit-toq/42_Cursus.git
cd 42_Cursus
git checkout 01-ft_printf
```

2. Compile the library
```bash
make
```

This will create `libftprintf.a` static library.

3. (Optional) Clean object files
```bash
make clean
```

4. (Optional) Remove all compiled files
```bash
make fclean
```

5. (Optional) Recompile everything
```bash
make re
```

---

## 💻 Usage

### Basic Usage

Include the header and compile with the library:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s!\n", "42");
    ft_printf("Number: %d\n", 42);
    ft_printf("Hex: %x\n", 255);
    return (0);
}
```

Compile your program:

```bash
gcc -Wall -Wextra -Werror your_file.c libftprintf.a -o your_program

./your_program
```

### Format Specifiers

| Specifier | Description | Type | Example |
|-----------|-------------|------|---------|
| `%c` | Single character | `char` / `int` | `ft_printf("%c", 'A')` → A |
| `%s` | String of characters | `char *` | `ft_printf("%s", "Hello")` → Hello |
| `%p` | Pointer address | `void *` | `ft_printf("%p", ptr)` → 0x123ff |
| `%d` | Signed decimal integer | `int` | `ft_printf("%d", -42)` → -42 |
| `%i` | Signed decimal integer | `int` | `ft_printf("%i", 42)` → 42 |
| `%u` | Unsigned decimal integer | `unsigned int` | `ft_printf("%u", 42)` → 42 |
| `%x` | Hexadecimal (lowercase) | `unsigned int` | `ft_printf("%x", 255)` → ff |
| `%X` | Hexadecimal (uppercase) | `unsigned int` | `ft_printf("%X", 255)` → FF |
| `%%` | Percent sign | N/A | `ft_printf("%%")` → % |

### Examples

**Example 1: Basic String and Character**
```c
ft_printf("Character: %c, String: %s\n", 'A', "Hello");
// Output: Character: A, String: Hello
```

**Example 2: Numbers in Different Formats**
```c
int num = 42;
ft_printf("Decimal: %d, Unsigned: %u, Hex: %x, HEX: %X\n", num, num, num, num);
// Output: Decimal: 42, Unsigned: 42, Hex: 2a, HEX: 2A
```

**Example 3: Pointer Address**
```c
int *ptr = &num;
ft_printf("Pointer: %p\n", ptr);
// Output: Pointer: 0x7fff5fbff710
```

**Example 4: Negative Numbers**
```c
ft_printf("Negative: %d, As unsigned: %u\n", -42, -42);
// Output: Negative: -42, As unsigned: 4294967254
```

**Example 5: NULL String Handling**
```c
char *str = NULL;
ft_printf("String: %s\n", str);
// Output: String: (null)
```

**Example 6: Return Value**
```c
int len = ft_printf("Hello, %s! You are %d years old.\n", "Alice", 25);
ft_printf("Characters printed: %d\n", len);
// Output: Hello, Alice! You are 25 years old.
//         Characters printed: 35
```

---

## 📁 Project Structure

```
ft_printf/
├── ft_printf.h          # Header file with function prototypes
├── ft_printf.c          # Main printf function and format dispatcher
├── ft_printf_utils.c    # Helper functions for conversions
├── Makefile             # Build automation
└── README.md            # Project documentation
```

---

## 🔧 Technical Implementation

### Key Design Decisions

1. **Variadic Functions:** Uses `stdarg.h` to handle variable number of arguments
2. **Format Parsing:** Character-by-character parsing of format string
3. **Error Handling:** Proper write error detection and propagation
4. **Modular Structure:** Each conversion type has dedicated helper function
5. **Length Tracking:** Pointer-based counter for total characters printed

### Implementation Example

```c
// Main function structure
int ft_printf(const char *string, ...)
{
    va_list args;
    int     length;
    
    va_start(args, string);
    // Parse format string and handle conversions
    va_end(args);
    
    return (length);
}

// Hexadecimal conversion example
int ft_hexadecimal(unsigned long number, int *length, char c)
{
    char *base = (c == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";
    char buffer[16];
    int  i = 0;
    
    if (!number)
        return (ft_putchar('0', length));
    
    while (number)
    {
        buffer[i++] = base[number % 16];
        number /= 16;
    }
    
    while (i--)
        ft_putchar(buffer[i], length);
    
    return (1);
}
```

---

## 📚 Resources

- [printf man page](https://man7.org/linux/man-pages/man3/printf.3.html)
- [stdarg.h documentation](https://en.cppreference.com/w/c/variadic)
- [Variadic Functions Guide](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html)
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
