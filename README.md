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

# philosophers - The Dining Philosophers Problem

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**Solve the classic dining philosophers problem with threads and mutexes**

</div>

---

## 📑 Table of Contents

- [About The Project](#about-the-project)
- [Learning Objectives](#learning-objectives)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
  - [Basic Usage](#basic-usage)
  - [Parameters](#parameters)
  - [Examples](#examples)
- [Project Structure](#project-structure)
- [Technical Implementation](#technical-implementation)
- [Resources](#resources)
- [License](#license)
- [Contact](#contact)

---

## 📖 About The Project

**philosophers** is a classic synchronization problem that demonstrates the challenges of concurrent programming. The project simulates philosophers sitting at a round table, where they alternate between eating, thinking, and sleeping. Each philosopher needs two forks to eat, but there are only as many forks as philosophers.

The challenge is to prevent deadlocks, race conditions, and ensure no philosopher starves while maintaining proper synchronization between threads.

### Built With

- **Language:** C
- **Threading:** POSIX Threads (pthread)
- **Synchronization:** Mutexes
- **Compiler:** gcc/clang
- **Build System:** Makefile
- **Norm:** 42 Norm compliant

---

## 🎯 Learning Objectives

This project taught me:

- **Multithreading:** Creating and managing multiple threads with pthread
- **Mutex Synchronization:** Using mutexes to protect shared resources
- **Race Conditions:** Understanding and preventing race conditions
- **Deadlock Prevention:** Implementing strategies to avoid deadlocks
- **Thread Lifecycle:** Managing thread creation, execution, and termination
- **Time Management:** Precise timing with `gettimeofday()` and `usleep()`
- **Concurrent Programming:** Thinking about parallel execution and shared state

---

## 🚀 Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yigit-toq/42_Cursus.git
cd 42_Cursus
git checkout 03-philosophers
cd philo
```

2. Compile the project
```bash
make
```

This will create the `philo` executable

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
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Parameter | Description | Unit |
|-----------|-------------|------|
| `number_of_philosophers` | Number of philosophers and forks | Integer |
| `time_to_die` | Time before a philosopher dies if not eating | Milliseconds |
| `time_to_eat` | Time it takes for a philosopher to eat | Milliseconds |
| `time_to_sleep` | Time a philosopher spends sleeping | Milliseconds |
| `[number_of_times_each_philosopher_must_eat]` | **Optional:** Simulation stops when all philosophers eat this many times | Integer |

**Rules:**
- All times are in milliseconds
- Philosophers are numbered from 1 to N
- Philosopher 1 sits next to philosopher N
- Any philosopher can die if they don't eat within `time_to_die` milliseconds
- Philosophers don't communicate with each other
- Philosophers don't know if another is about to die

### Examples

**Example 1: Basic Simulation**
```bash
./philo 5 800 200 200
```
- 5 philosophers
- Die after 800ms without eating
- Eating takes 200ms
- Sleeping takes 200ms
- Runs until a philosopher dies

**Example 2: Limited Eating**
```bash
./philo 5 800 200 200 7
```
- Same as Example 1
- Stops when all philosophers have eaten 7 times

**Example 3: Tight Timing (Survival Challenge)**
```bash
./philo 4 410 200 200
```
- 4 philosophers
- Must eat within 410ms (tight timing)
- Tests synchronization efficiency

**Example 4: Single Philosopher**
```bash
./philo 1 800 200 200
```
- 1 philosopher (should die - only one fork available)

**Example 5: Many Philosophers**
```bash
./philo 10 410 200 200
```
- 10 philosophers
- Tests scalability and proper mutex handling

### Output Format

The program outputs timestamped messages:
```
[timestamp_in_ms] [philosopher_id] has taken a fork 🍴
[timestamp_in_ms] [philosopher_id] is eating 🍝
[timestamp_in_ms] [philosopher_id] is sleeping 😴
[timestamp_in_ms] [philosopher_id] is thinking 💭
[timestamp_in_ms] [philosopher_id] died 😵
```

**Example Output:**
```
0 1 has taken a fork 🍴
0 1 has taken a fork 🍴
0 1 is eating 🍝
0 3 has taken a fork 🍴
0 3 has taken a fork 🍴
0 3 is eating 🍝
200 1 is sleeping 😴
200 3 is sleeping 😴
200 2 has taken a fork 🍴
200 2 has taken a fork 🍴
200 2 is eating 🍝
```

---

## 📁 Project Structure

```
philo/
├── sources/
│   ├── 1-main.c           # Main program and initialization
│   ├── 0-philo.c          # Thread creation and philosopher routine
│   └── 2-utils.c          # Utility functions (timing, error handling)
├── includes/
│   └── philo.h            # Header file with structures and prototypes
├── Makefile               # Build automation
└── README.md              # Project documentation
```

---

## 🔧 Technical Implementation

### Key Design Decisions

1. **Mutex per Fork:** Each fork is protected by its own mutex
2. **Even/Odd Strategy:** Even philosophers start eating slightly delayed to reduce contention
3. **Death Monitor:** Separate monitoring thread checks for philosopher deaths
4. **Protected State:** All shared state access is mutex-protected
5. **Precise Timing:** Uses `gettimeofday()` for millisecond precision

### Data Structures

```c
typedef struct s_philo
{
    struct s_data   *data;          // Pointer to shared data
    pthread_mutex_t *left_fork;     // Left fork mutex
    pthread_mutex_t *right_fork;    // Right fork mutex
    pthread_t       thread;         // Philosopher thread
    int             id;             // Philosopher ID (1-N)
    int             eat_count;      // Number of times eaten
    long long       eat_last;       // Timestamp of last meal
}   t_philo;

typedef struct s_data
{
    pthread_mutex_t *fork;          // Array of fork mutexes
    pthread_mutex_t m_eat;          // Protects eat_count and eat_last
    pthread_mutex_t m_dead;         // Protects death flag
    pthread_mutex_t m_print;        // Protects printing
    pthread_mutex_t m_ready;        // Synchronizes thread start
    t_philo         *philo;         // Array of philosophers
    long long       arguments[5];   // Command line arguments
    int             p_count;        // Number of philosophers created
    int             p_dead;         // Death flag
}   t_data;
```

### Philosopher Routine

```c
void *routine(t_philo *philo)
{
    // Wait for all threads to be created
    pthread_mutex_lock(&philo->data->m_ready);
    pthread_mutex_unlock(&philo->data->m_ready);
    
    // Single philosopher case (will die)
    if (philo->data->arguments[0] == 1)
    {
        print_message(philo, "has taken a fork", YELLOW);
        usleep(philo->data->arguments[1] * 1000);
        print_message(philo, "died", RED);
        return (NULL);
    }
    
    // Even philosophers start with delay
    if (!(philo->id % 2))
        usleep(philo->data->arguments[2] * 1000);
    
    // Main loop: eat, sleep, think
    while (!is_dead(philo->data))
    {
        take_forks(philo);
        eat(philo);
        release_forks(philo);
        sleep_and_think(philo);
    }
    
    return (NULL);
}
```

### Deadlock Prevention Strategy

The key to preventing deadlocks is the **even/odd strategy**:

1. **Even-numbered philosophers** (2, 4, 6, ...) start with a delay
2. This creates a staggered start pattern
3. Reduces the chance of all philosophers grabbing their left fork simultaneously
4. Allows odd-numbered philosophers to complete their first meal
5. Creates a natural rotation of fork availability

### Death Monitor

```c
int death_control(t_data *data)
{
    int i;
    long long current_time;
    long long time_since_last_meal;
    
    while (1)
    {
        i = 0;
        while (i < data->arguments[0])
        {
            pthread_mutex_lock(&data->m_eat);
            current_time = get_time();
            time_since_last_meal = current_time - data->philo[i].eat_last;
            
            // Check if philosopher died
            if (time_since_last_meal > data->arguments[1])
            {
                pthread_mutex_unlock(&data->m_eat);
                print_message(&data->philo[i], "died", RED);
                var_int(&data->m_dead, &data->p_dead, 1, SET);
                return (FAILURE);
            }
            
            // Check if all have eaten enough times
            if (data->arguments[4] != -1 && 
                data->philo[i].eat_count >= data->arguments[4])
            {
                // All philosophers ate enough times
                if (++complete == data->arguments[0])
                    return (SUCCESS);
            }
            
            pthread_mutex_unlock(&data->m_eat);
            i++;
        }
        usleep(1000);  // Check every 1ms
    }
}
```

### Synchronization Flow

```
1. Main thread creates data structures
2. Main thread creates fork mutexes
3. Main thread creates philosopher threads
4. All philosopher threads wait at m_ready mutex
5. Main thread releases m_ready (all start simultaneously)
6. Death monitor starts checking
7. Philosophers execute their routines
8. Monitor detects death or completion
9. Main thread joins all philosopher threads
10. Cleanup and exit
```

---

## 📚 Resources

- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [pthread man pages](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Mutex Tutorial](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)
- [Race Conditions](https://en.wikipedia.org/wiki/Race_condition)
- [Deadlock Prevention](https://en.wikipedia.org/wiki/Deadlock#Prevention)
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
