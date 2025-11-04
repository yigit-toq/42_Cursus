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

# get_next_line - Reading Files Line by Line

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**A function that reads a file line by line efficiently**

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
- [Technical Implementation](#technical-implementation)
- [Resources](#resources)
- [License](#license)
- [Contact](#contact)

---

## 📖 About The Project

**get_next_line** is a project that challenges you to create a function that reads and returns a single line from a file descriptor. This function is extremely useful and will be used in many future projects throughout the 42 curriculum.

The function must handle multiple file descriptors simultaneously, work with different buffer sizes, and efficiently manage memory using static variables.

### Built With

- **Language:** C
- **Compiler:** gcc/clang
- **Build System:** Compiled with user programs
- **Norm:** 42 Norm compliant

---

## 🎯 Learning Objectives

This project taught me:

- **Static Variables:** Understanding how static variables persist across function calls
- **File Descriptors:** Working with file descriptors and the `read()` system call
- **Buffer Management:** Efficiently managing reading buffers of variable sizes
- **Memory Management:** Proper allocation, deallocation, and leak prevention
- **String Manipulation:** Advanced string operations for line extraction
- **Edge Case Handling:** Dealing with EOF, empty files, large files, and multiple FDs
- **Preprocessor Directives:** Using `#ifndef` for compile-time configuration (BUFFER_SIZE)

---

## 🚀 Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yigit-toq/42_Cursus.git
cd 42_Cursus
git checkout 01-get_next_line
```

2. Compile with your program
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_file.c -o your_program
```

3. Or use different buffer size
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c your_file.c -o your_program
```

---

## 💻 Usage

### Basic Usage

Include the header in your program:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Examples

**Example 1: Reading from a File**
```c
int     fd;
char    *line;

fd = open("file.txt", O_RDONLY);
line = get_next_line(fd);  // Returns first line
printf("%s", line);
free(line);

line = get_next_line(fd);  // Returns second line
printf("%s", line);
free(line);

close(fd);
```

**Example 2: Reading Until EOF**
```c
int     fd;
char    *line;

fd = open("file.txt", O_RDONLY);
while ((line = get_next_line(fd)) != NULL)
{
    printf("Line: %s", line);
    free(line);
}
close(fd);
```

**Example 3: Reading from Standard Input**
```c
char *line;

printf("Enter text: ");
while ((line = get_next_line(0)) != NULL)  // 0 = stdin
{
    printf("You entered: %s", line);
    free(line);
    if (line[0] == 'q')  // Exit on 'q'
        break;
}
```

**Example 4: Multiple File Descriptors**
```c
int     fd1, fd2;
char    *line1, *line2;

fd1 = open("file1.txt", O_RDONLY);
fd2 = open("file2.txt", O_RDONLY);

line1 = get_next_line(fd1);  // Read from file1
line2 = get_next_line(fd2);  // Read from file2
line1 = get_next_line(fd1);  // Read next line from file1

free(line1);
free(line2);
close(fd1);
close(fd2);
```

---

## 📁 Project Structure

```
get_next_line/
├── get_next_line.h          # Header file with prototypes
├── get_next_line.c          # Main function implementation
├── get_next_line_utils.c    # Helper functions
└── README.md                # Project documentation
```

**Function Overview:**

- **get_next_line.c**:
  - `get_next_line()` - Main function that returns next line
  - `free_backup()` - Manages backup memory
  - `newline_checker()` - Checks for newline character
  - `copy_to_backup()` - Copies buffer to backup
  - `line_or_backup()` - Extracts line or updates backup

---

## 🔧 Technical Implementation

### Key Design Decisions

1. **Static Variables:** Uses static variable to preserve data between function calls
2. **Buffer Management:** Configurable BUFFER_SIZE for read operations
3. **Memory Efficiency:** Minimizes allocations and deallocations
4. **Line Extraction:** Efficiently extracts lines ending with `\n`
5. **Multiple FD Support:** Can handle multiple file descriptors simultaneously

### Implementation Example

```c
char *get_next_line(int fd)
{
    static char *backup = NULL;
    char        *line;
    char        buffer[BUFFER_SIZE + 1];
    int         size;

    size = BUFFER_SIZE;
    while (size > 0)
    {
        size = read(fd, buffer, BUFFER_SIZE);
        if ((size == 0 && !backup) || size == -1)
            return (free_backup(&backup, 0));
        
        buffer[size] = '\0';
        backup = copy_to_backup(backup, buffer);
        
        if (newline_checker(backup))
        {
            line = line_or_backup(backup, 1);
            if (!line)
                return (free_backup(&backup, 0));
            backup = line_or_backup(backup, 0);
            return (line);
        }
    }
    return (free_backup(&backup, 1));
}
```

### How It Works

1. **Read Loop**: Reads BUFFER_SIZE bytes from file descriptor
2. **Buffer Accumulation**: Appends read data to static backup
3. **Newline Detection**: Checks if backup contains `\n`
4. **Line Extraction**: Extracts line up to and including `\n`
5. **Backup Update**: Saves remaining content for next call
6. **EOF Handling**: Returns remaining content when file ends

### Buffer Size Impact

| Buffer Size | Performance | Memory |
|-------------|-------------|--------|
| 1 | Slow (many read calls) | Minimal |
| 42 | Balanced | Moderate |
| 1024 | Fast (fewer read calls) | Higher |
| 1000000 | Fastest for large files | Very high |

---

## 📚 Resources

- [read() man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [File Descriptors](https://en.wikipedia.org/wiki/File_descriptor)
- [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)
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
