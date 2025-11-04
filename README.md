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

# Libft - Your First Custom C Library

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-125%2F100-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**Your very first own library - A collection of essential C functions that will be used throughout the 42 curriculum**

</div>

---

## 📑 Table of Contents

- [About The Project](#about-the-project)
- [Learning Objectives](#learning-objectives)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
  - [Basic Usage](#basic-usage)
  - [Examples](#examples)
- [Project Structure](#project-structure)
- [Function Categories](#function-categories)
  - [Character Functions](#character-functions)
  - [String Functions](#string-functions)
  - [Memory Functions](#memory-functions)
  - [Conversion Functions](#conversion-functions)
  - [File Descriptor Functions](#file-descriptor-functions)
  - [Linked List Functions (Bonus)](#linked-list-functions-bonus)
- [Technical Implementation](#technical-implementation)
- [Resources](#resources)
- [License](#license)
- [Contact](#contact)

---

## 📖 About The Project

**Libft** is the first project at 42 School, where you create your own C library by re-implementing standard C library functions from scratch. This library becomes a fundamental tool that you'll use and expand throughout your entire 42 journey.

The project teaches you to understand how these functions work under the hood, manage memory properly, and write clean, efficient code.

### Built With

- **Language:** C
- **Compiler:** gcc/clang
- **Build System:** Makefile
- **Norm:** 42 Norm compliant
- **Memory Safety:** Valgrind tested

---

## 🎯 Learning Objectives

This project taught me:

- **Memory Management:** Understanding pointers, dynamic allocation, and preventing memory leaks
- **String Manipulation:** Working with char arrays, null terminators, and string operations
- **Linked Lists:** Implementing and manipulating linked list data structures
- **Makefile Automation:** Creating efficient build systems with proper dependencies
- **Code Standards:** Writing clean, readable, and maintainable C code following the 42 Norm
- **Testing & Debugging:** Using tools like Valgrind to ensure code reliability
- **Code Reusability:** Creating a library that can be used across multiple projects
- **Edge Case Handling:** Thinking about all possible inputs and error conditions

---

## 🚀 Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yigit-toq/42_Cursus.git
cd 42_Cursus
git checkout 00-libft
```

2. Compile the library
```bash
make
```

3. (Optional) Compile with bonus functions
```bash
make bonus
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

Include the library in your C projects:

```c
#include "libft.h"

int main(void)
{
    char *str = ft_strdup("Hello, 42!");
    ft_putendl_fd(str, 1);
    free(str);
    return (0);
}
```

Compile your project with libft:

```bash
gcc -Wall -Wextra -Werror your_file.c libft.a -o your_program

./your_program
```

### Examples

**Example 1: String Manipulation**
```c
char *original = "  Hello, World!  ";
char *trimmed = ft_strtrim(original, " ");
// Result: "Hello, World!"
```

**Example 2: String Splitting**
```c
char **words = ft_split("Hello World 42", ' ');
// words[0] = "Hello"
// words[1] = "World"
// words[2] = "42"
// words[3] = NULL
```

**Example 3: Using ft_printf**
```c
ft_printf("Number: %d, String: %s, Hex: %x\n", 42, "test", 255);
// Output: Number: 42, String: test, Hex: ff
```

**Example 4: Linked List Operations**
```c
t_list *head = ft_lstnew("First");
ft_lstadd_back(&head, ft_lstnew("Second"));
ft_lstadd_back(&head, ft_lstnew("Third"));
int size = ft_lstsize(head);  // size = 3
```

---

## 📁 Project Structure

```
42_Cursus/
├── sources/
│   ├── mandatory/
│   │   ├── ft_itoa.c
│   │   ├── ft_atoi.c
│   │   ├── ft_bzero.c
│   │   ├── ft_calloc.c
│   │   ├── ft_isalnum.c
│   │   ├── ft_isalpha.c
│   │   ├── ft_isascii.c
│   │   ├── ft_isdigit.c
│   │   ├── ft_isprint.c
│   │   ├── ft_memchr.c
│   │   ├── ft_memcmp.c
│   │   ├── ft_memcpy.c
│   │   ├── ft_memset.c
│   │   ├── ft_memmove.c
│   │   ├── ft_putchar_fd.c
│   │   ├── ft_putendl_fd.c
│   │   ├── ft_putnbr_fd.c
│   │   ├── ft_putstr_fd.c
│   │   ├── ft_striteri.c
│   │   ├── ft_strchr.c
│   │   ├── ft_strcmp.c
│   │   ├── ft_strdup.c
│   │   ├── ft_strlen.c
│   │   ├── ft_substr.c
│   │   ├── ft_strjoin.c
│   │   ├── ft_strlcat.c
│   │   ├── ft_strlcpy.c
│   │   ├── ft_strmapi.c
│   │   ├── ft_strncmp.c
│   │   ├── ft_strnstr.c
│   │   ├── ft_strrchr.c
│   │   ├── ft_strtrim.c
│   │   ├── ft_tolower.c
│   │   ├── ft_toupper.c
│   │   └── ft_split.c
|   |
│   └── bonus/
│       ├── ft_lstadd_front_bonus.c
│       ├── ft_lstadd_back_bonus.c
│       ├── ft_lstdelone_bonus.c
│       ├── ft_lstclear_bonus.c
│       ├── ft_lstcopy_bonus.c
│       ├── ft_lstiter_bonus.c
│       ├── ft_lstlast_bonus.c
│       ├── ft_lstsize_bonus.c
│       ├── ft_lstsort_bonus.c
│       ├── ft_lstswap_bonus.c
│       ├── ft_lstmap_bonus.c
│       └── ft_lstnew_bonus.c
|
├── utils/
|   |
│   ├── 0-plist/
│   │   └── plist.c
|   |
│   ├── 1-printf/
│   │   ├── ft_printf/
│   │   │   ├── ft_printf.c
│   │   │   └── ft_printf_utils.c
|   |   |
│   │   └── ft_dprintf/
│   │       ├── ft_dprintf.c
│   │       └── ft_dprintf_utils.c
|   |
│   ├── 2-garbage/
│   │   ├── garbage_collector.c
│   │   └── garbage_collector_utils.c
|   |
│   └── 3-get_next_line/
│       └── get_next_line.c
|
├── objects/
├── Makefile
└── README.md
```

---

## 🔧 Function Categories

### Character Functions

Functions for checking and converting character types:

| Function | Description | Return |
|----------|-------------|--------|
| `ft_isalpha()` | Checks if character is alphabetic | 1 if true, 0 if false |
| `ft_isdigit()` | Checks if character is a digit | 1 if true, 0 if false |
| `ft_isalnum()` | Checks if character is alphanumeric | 1 if true, 0 if false |
| `ft_isascii()` | Checks if character is ASCII | 1 if true, 0 if false |
| `ft_isprint()` | Checks if character is printable | 1 if true, 0 if false |
| `ft_toupper()` | Converts character to uppercase | Uppercase character |
| `ft_tolower()` | Converts character to lowercase | Lowercase character |

### String Functions

Functions for string manipulation and analysis:

| Function | Description | Return |
|----------|-------------|--------|
| `ft_strlen()` | Calculates string length | Length of string |
| `ft_strchr()` | Locates first occurrence of character | Pointer to character or NULL |
| `ft_strrchr()` | Locates last occurrence of character | Pointer to character or NULL |
| `ft_strcmp()` | Compares two strings | Integer difference |
| `ft_strncmp()` | Compares n bytes of two strings | Integer difference |
| `ft_strnstr()` | Locates substring in string | Pointer to substring or NULL |
| `ft_strdup()` | Duplicates a string | Pointer to new string |
| `ft_strlcpy()` | Copies string with size limit | Total length attempted |
| `ft_strlcat()` | Concatenates strings with size limit | Total length attempted |
| `ft_substr()` | Extracts substring | New substring or NULL |
| `ft_strjoin()` | Joins two strings | New concatenated string or NULL |
| `ft_strtrim()` | Trims characters from string | New trimmed string or NULL |
| `ft_split()` | Splits string by delimiter | Array of strings or NULL |
| `ft_strmapi()` | Applies function to each character | New modified string or NULL |
| `ft_striteri()` | Applies function to each character (no return) | void |

### Memory Functions

Functions for memory operations:

| Function | Description | Return |
|----------|-------------|--------|
| `ft_memset()` | Fills memory with constant byte | Pointer to memory area |
| `ft_bzero()` | Zeros out memory area | void |
| `ft_memcpy()` | Copies memory area | Pointer to destination |
| `ft_memmove()` | Copies memory area (handles overlap) | Pointer to destination |
| `ft_memchr()` | Scans memory for character | Pointer to byte or NULL |
| `ft_memcmp()` | Compares memory areas | Integer difference |
| `ft_calloc()` | Allocates and zeros memory | Pointer to allocated memory |

### Conversion Functions

Functions for converting between data types:

| Function | Description | Return |
|----------|-------------|--------|
| `ft_atoi()` | Converts string to integer | Integer value |
| `ft_itoa()` | Converts integer to string | String representation or NULL |

### File Descriptor Functions

Functions for writing to file descriptors:

| Function | Description | Return |
|----------|-------------|--------|
| `ft_putchar_fd()` | Outputs character to file descriptor | void |
| `ft_putstr_fd()` | Outputs string to file descriptor | void |
| `ft_putendl_fd()` | Outputs string with newline to FD | void |
| `ft_putnbr_fd()` | Outputs integer to file descriptor | void |

### Linked List Functions (Bonus)

Functions for linked list operations:

| Function | Description | Return |
|----------|-------------|--------|
| `ft_lstadd_front()` | Adds element at beginning of list | void |
| `ft_lstadd_back()` | Adds element at end of list | void |
| `ft_lstdelone()` | Deletes one element | void |
| `ft_lstclear()` | Deletes and frees list | void |
| `ft_lstiter()` | Applies function to each element | void |
| `ft_lstcopy()` | Creates a copy of the list | New list or NULL |
| `ft_lstsort()` | Sorts list elements | void |
| `ft_lstswap()` | Swaps two list elements | void |
| `ft_lstsize()` | Counts elements in list | Number of elements |
| `ft_lstlast()` | Returns last element of list | Last element or NULL |
| `ft_lstnew()` | Creates new list element | New element or NULL |
| `ft_lstmap()` | Applies function and creates new list | New list or NULL |

## 🔍 Technical Implementation

### Key Design Decisions

1. **Null Safety:** All functions check for NULL parameters before processing
2. **Memory Management:** Proper allocation and deallocation using malloc/free
3. **Overlap Handling:** Functions like `ft_memmove()` handle overlapping memory regions
4. **Buffer Overflow Prevention:** Size-limited functions prevent buffer overflows
5. **Linked List Structure:** Custom `t_list` structure for flexible list operations

### Memory Management Example

```c
// ft_substr implementation showing proper memory handling
char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *substr;
    size_t  s_len;
    size_t  i;

    if (!s)
        return (NULL);
    s_len = ft_strlen(s);
    if (start >= s_len)
        return (ft_strdup(""));
    if (len > s_len - start)
        len = s_len - start;
    substr = (char *)malloc(sizeof(char) * (len + 1));
    if (!substr)
        return (NULL);
    i = 0;
    while (i < len)
    {
        substr[i] = s[start + i];
        i++;
    }
    substr[i] = '\0';
    return (substr);
}
```

### Makefile Features

- **Automatic dependency tracking**
- **Progress bar during compilation**
- **Color-coded output**
- **Separate compilation for bonus functions**
- **Object file organization**

---

## 📚 Resources

- [C Standard Library Reference](https://en.cppreference.com/w/c)
- [GNU C Library Manual](https://www.gnu.org/software/libc/manual/)
- [Valgrind Documentation](https://valgrind.org/docs/)
- [Makefile Tutorial](https://makefiletutorial.com/)
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
