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

# minitalk - Inter-Process Communication Using Signals

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logoColor=black)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**A simple client-server communication program using UNIX signals**

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

**minitalk** is a communication program that demonstrates inter-process communication (IPC) using UNIX signals. The project consists of a server and a client program, where the client sends a string message to the server using only two signals: `SIGUSR1` and `SIGUSR2`.

The challenge is to transmit text data bit by bit through signals, requiring a deep understanding of signal handling, bit manipulation, and process communication.

### Built With

- **Language:** C
- **Compiler:** gcc/clang
- **Build System:** Makefile
- **Norm:** 42 Norm compliant

---

## 🎯 Learning Objectives

This project taught me:

- **UNIX Signals:** Understanding signal handling with `signal()`, `SIGUSR1`, and `SIGUSR2`
- **Bit Manipulation:** Converting characters to bits and reconstructing them
- **Process Communication:** Using PID (Process ID) for inter-process messaging
- **Signal Safety:** Handling asynchronous signal delivery and timing issues
- **Binary Operations:** Bitwise operations (shift, OR, AND) for data transmission
- **System Calls:** Working with `kill()`, `getpid()`, `pause()`, and `usleep()`
- **Client-Server Architecture:** Implementing basic client-server communication

---

## 🚀 Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yigit-toq/42_Cursus.git
cd 42_Cursus
git checkout 02-minitalk
```

2. Compile the project
```bash
make
```

This will create two executables: `server` and `client`

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

**Step 1: Start the server**
```bash
./server
```
The server will display its PID (Process ID):
```
Server Connected!
Server PID -> 12345
```

**Step 2: Send a message from client**

In another terminal:
```bash
./client [SERVER_PID] [MESSAGE]
```

Example:
```bash
./client 12345 "Hello, 42!"
```

The server terminal will display:
```
Hello, 42!
```

### Examples

**Example 1: Simple Message**
```bash
# Terminal 1
./server
# Output: Server PID -> 12345

# Terminal 2
./client 12345 "Minitalk test"
# Server displays: Minitalk test
```

**Example 2: Multiple Messages**
```bash
# Terminal 1
./server
# Output: Server PID -> 12345

# Terminal 2
./client 12345 "First message"
./client 12345 "Second message"
./client 12345 "Third message"

# Server displays:
# First message
# Second message
# Third message
```

**Example 3: Special Characters**
```bash
./client 12345 "Hello! @#$% 42 School 🚀"
# Server displays: Hello! @#$% 42 School 🚀
```

**Example 4: Long Text**
```bash
./client 12345 "This is a very long message to test the signal transmission capability of the minitalk project. It should handle multiple words and sentences without any issues."
```

---

## 📁 Project Structure

```
minitalk/
├── sources/
│   ├── server.c             # Server program
│   └── client.c             # Client program
├── ft_printf/               # Printf library
│   ├── includes/
│   │   └── ft_printf.h
│   └── sources/
├── Makefile                 # Build automation
└── README.md                # Project documentation
```

**Program Overview:**

- **server.c**:
  - Displays its PID
  - Receives signals (SIGUSR1 and SIGUSR2)
  - Reconstructs characters from bits
  - Prints received messages

- **client.c**:
  - Takes PID and message as arguments
  - Converts each character to bits
  - Sends bits as signals to server
  - Uses `usleep()` for signal timing

---

## 🔧 Technical Implementation

### Key Design Decisions

1. **Bit-by-Bit Transmission:** Each character (8 bits) is sent as 8 separate signals
2. **Signal Mapping:** SIGUSR1 = bit 1, SIGUSR2 = bit 0
3. **Static Variables:** Server uses static variables to maintain state between signals
4. **Timing Control:** Client uses `usleep()` to prevent signal loss
5. **Binary Reconstruction:** Server rebuilds characters using bitwise operations

### Implementation Example

**Server: Receiving and Reconstructing**
```c
static void handler_bit(int signal)
{
    static int bit;
    static int i;

    if (signal == SIGUSR1)
        i |= (1 << bit);    // Set bit to 1
    bit++;
    
    if (bit == 8)           // Full character received
    {
        ft_printf("%c", i);
        bit = 0;
        i = 0;
    }
}

int main(void)
{
    ft_printf("Server PID -> %d\n", getpid());
    while (1)
    {
        signal(SIGUSR1, handler_bit);
        signal(SIGUSR2, handler_bit);
        pause();            // Wait for signal
    }
}
```

**Client: Sending Bits**
```c
static void send_bit(int pid, char *string, int length)
{
    int bit;
    int index;

    index = 0;
    while (index < length)
    {
        bit = 0;
        while (bit < 8)
        {
            if ((string[index] >> bit) & 1)
                kill(pid, SIGUSR1);    // Send 1
            else
                kill(pid, SIGUSR2);    // Send 0
            bit++;
            usleep(100);               // Timing delay
        }
        index++;
    }
}
```

### How It Works

1. **Server Start**: Server starts and displays its PID
2. **Client Send**: Client receives PID and message
3. **Bit Conversion**: Each character is broken into 8 bits
4. **Signal Transmission**: Each bit is sent as SIGUSR1 (1) or SIGUSR2 (0)
5. **Bit Reception**: Server receives signals and reconstructs bits
6. **Character Assembly**: After 8 bits, server prints the character
7. **Message Complete**: Process repeats for entire message

### Signal Flow Diagram

```
Character 'A' (ASCII 65 = 01000001)

Client:                          Server:
'A' = 01000001
  ↓
bit 0 = 1 → SIGUSR1 →           bit |= (1 << 0)
bit 1 = 0 → SIGUSR2 →           bit |= (0 << 1)
bit 2 = 0 → SIGUSR2 →           bit |= (0 << 2)
bit 3 = 0 → SIGUSR2 →           bit |= (0 << 3)
bit 4 = 0 → SIGUSR2 →           bit |= (0 << 4)
bit 5 = 0 → SIGUSR2 →           bit |= (0 << 5)
bit 6 = 1 → SIGUSR1 →           bit |= (1 << 6)
bit 7 = 0 → SIGUSR2 →           bit |= (0 << 7)
                                      ↓
                                  Print 'A'
```

---

## 📚 Resources

- [Signal Handling in C](https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html)
- [kill() man page](https://man7.org/linux/man-pages/man2/kill.2.html)
- [signal() man page](https://man7.org/linux/man-pages/man2/signal.2.html)
- [Bitwise Operations](https://en.wikipedia.org/wiki/Bitwise_operation)
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
