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

# push_swap - Efficient Stack Sorting Algorithm

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**Sort integers on two stacks using the minimum number of operations**

</div>

---

## 📑 Table of Contents

- [About The Project](#about-the-project)
- [Learning Objectives](#learning-objectives)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
  - [Basic Usage](#basic-usage)
  - [Available Operations](#available-operations)
  - [Examples](#examples)
- [Project Structure](#project-structure)
- [Technical Implementation](#technical-implementation)
- [Resources](#resources)
- [License](#license)
- [Contact](#contact)

---

## 📖 About The Project

**push_swap** is an algorithm project that challenges you to sort a stack of integers using the minimum number of operations. You have two stacks (A and B) and a limited set of operations to manipulate them. The goal is to sort stack A in ascending order with optimal efficiency.

This project teaches you about algorithm complexity, optimization techniques, and choosing the right sorting strategy based on input size.

### Built With

- **Language:** C
- **Compiler:** gcc/clang
- **Build System:** Makefile
- **Norm:** 42 Norm compliant

---

## 🎯 Learning Objectives

This project taught me:

- **Algorithm Complexity:** Understanding Big O notation and time complexity analysis
- **Sorting Algorithms:** Implementing and optimizing various sorting strategies
- **Radix Sort:** Using bit manipulation for efficient sorting of large datasets
- **Selection Sort:** Implementing optimized selection sort for small datasets
- **Stack Operations:** Manipulating data structures with limited operations
- **Optimization:** Finding the most efficient solution for different input sizes
- **Algorithm Selection:** Choosing appropriate algorithms based on data size

---

## 🚀 Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yigit-toq/42_Cursus.git
cd 42_Cursus
git checkout 02-push_swap
```

2. Compile the project
```bash
make
```

This will create the `push_swap` executable

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

```bash
./push_swap [list of integers]
```

The program outputs the list of operations needed to sort the stack:

```bash
./push_swap 3 2 1
# Output:
sa
rra
```

### Available Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the first 2 elements of stack A |
| `sb` | Swap the first 2 elements of stack B |
| `ss` | `sa` and `sb` at the same time |
| `pa` | Push the first element of B to A |
| `pb` | Push the first element of A to B |
| `ra` | Rotate stack A (shift up all elements by 1) |
| `rb` | Rotate stack B (shift up all elements by 1) |
| `rr` | `ra` and `rb` at the same time |
| `rra` | Reverse rotate stack A (shift down all elements by 1) |
| `rrb` | Reverse rotate stack B (shift down all elements by 1) |
| `rrr` | `rra` and `rrb` at the same time |

### Examples

**Example 1: Sort 3 Numbers**
```bash
./push_swap 2 1 3
# Output:
sa
```

**Example 2: Sort 5 Numbers**
```bash
./push_swap 5 4 3 2 1
# Output:
pb
pb
sa
pa
pa
ra
ra
```

**Example 3: Sort with Arguments in Quotes**
```bash
./push_swap "3 2 1 4 5"
# Output:
pb
sa
pa
```

**Example 4: Already Sorted**
```bash
./push_swap 1 2 3 4 5
# Output: (no operations, already sorted)
```

**Example 5: Large Random Set**
```bash
./push_swap $(seq 1 100 | shuf)
# Output: (list of operations to sort 100 numbers)
```

---

## 📁 Project Structure

```
push_swap/
├── sources/
│   ├── push_swap.c          # Main program and stack creation
│   ├── push_swap_utils.c    # Utility functions (atoi, sort check)
│   ├── action.c             # Stack operations (swap, push, rotate)
│   ├── radix_sort.c         # Radix sort algorithm for large sets
│   └── selection_sort.c     # Selection sort for small sets
├── includes/
│   ├── push_swap.h          # Project header
│   ├── libft.h              # Libft header
│   └── ft_printf.h          # Printf header
├── libft/                   # Libft library
├── Makefile                 # Build automation
└── README.md                # Project documentation
```

---

## 🔧 Technical Implementation

### Key Design Decisions

1. **Algorithm Selection:** Different algorithms based on stack size
   - 2 elements: Simple swap
   - 3 elements: Specialized three-sort
   - 4-32 elements: Selection sort
   - 32+ elements: Radix sort with indexing

2. **Radix Sort:** Uses bit manipulation to sort indexed values efficiently
3. **Stack Indexing:** Converts actual values to indices for radix sort
4. **Input Validation:** Checks for duplicates, invalid numbers, and integer overflow
5. **Error Handling:** Displays "Error" for invalid input

### Implementation Example

**Radix Sort Algorithm**
```c
void radix_sort(t_manager *manager)
{
    int max_bits = get_max_bits(manager);
    int i = 0;
    
    while (i < max_bits && !sort_check(manager->a, manager->size_a))
    {
        int size = manager->size_a;
        int j = 0;
        
        while (j < size)
        {
            if ((manager->a[0] >> i) & 1)
                rotate_stack(manager, manager->a, manager->size_a, 1);
            else
                push_stack(manager, manager->a, manager->b, &manager->size_a);
            j++;
        }
        i++;
    }
    
    // Push all back from B to A
    while (manager->size_b > 0)
        push_stack(manager, manager->b, manager->a, &manager->size_b);
}
```

**Stack Operations**
```c
// Swap: Exchange first two elements
void swap_stack(t_manager *manager, int *stack, int size, int flag)
{
    int temp = stack[0];
    stack[0] = stack[1];
    stack[1] = temp;
    
    if (flag == 1)
        ft_printf("sa\n");
    else if (flag == 2)
        ft_printf("sb\n");
}

// Push: Move top element from one stack to another
void push_stack(t_manager *manager, int *from, int *to, int *size_from)
{
    // Shift all elements in 'to' stack down
    // Insert element at top of 'to' stack
    // Remove element from 'from' stack
    // Update sizes
}

// Rotate: Shift all elements up (first becomes last)
void rotate_stack(t_manager *manager, int *stack, int size, int flag)
{
    int temp = stack[0];
    int i = 0;
    
    while (i < size - 1)
    {
        stack[i] = stack[i + 1];
        i++;
    }
    stack[size - 1] = temp;
}
```

### Algorithm Complexity

| Algorithm | Best Case | Average Case | Worst Case | Space |
|-----------|-----------|--------------|------------|-------|
| **Two elements** | O(1) | O(1) | O(1) | O(1) |
| **Three elements** | O(1) | O(1) | O(1) | O(1) |
| **Selection Sort** | O(n²) | O(n²) | O(n²) | O(1) |
| **Radix Sort** | O(kn) | O(kn) | O(kn) | O(n) |

*k = number of bits (typically 32 for int)*

### Optimization Strategy

```
Input Size → Algorithm Choice
─────────────────────────────
2            → Simple swap (1 operation)
3            → Specialized 3-sort (2-3 operations)
4-32         → Selection sort (~O(n²))
33+          → Radix sort (~O(kn))
```

### How Radix Sort Works

1. **Index Conversion**: Convert actual values to indices (0, 1, 2, 3, ...)
2. **Bit-by-Bit Processing**: Process each bit from LSB to MSB
3. **Bit Check**: Check if current bit is 0 or 1
4. **Stack Distribution**: 
   - If bit is 0 → push to stack B
   - If bit is 1 → rotate in stack A
5. **Merge Back**: Push all elements from B back to A
6. **Repeat**: Continue for all bits until sorted

---

## 📚 Resources

- [Sorting Algorithms](https://en.wikipedia.org/wiki/Sorting_algorithm)
- [Radix Sort](https://en.wikipedia.org/wiki/Radix_sort)
- [Big O Notation](https://en.wikipedia.org/wiki/Big_O_notation)
- [Stack Data Structure](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))
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
