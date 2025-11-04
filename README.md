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

# ft_irc - Internet Relay Chat Server

![42 School Badge](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logoColor=white)
![Language](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logoColor=white)
![Standard](https://img.shields.io/badge/Standard-C++98-00599C?style=for-the-badge)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**A fully functional IRC server implementation compatible with standard IRC clients**

</div>

---

## 📑 Table of Contents

- [About The Project](#about-the-project)
- [Learning Objectives](#learning-objectives)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
  - [Server Usage](#server-usage)
  - [Client Connection](#client-connection)
  - [Supported Commands](#supported-commands)
- [Project Structure](#project-structure)
- [Technical Implementation](#technical-implementation)
- [Bonus Features](#bonus-features)
- [Testing](#testing)
- [Resources](#resources)
- [License](#license)
- [Contact](#contact)

---

## 📖 About The Project

**ft_irc** is a fully functional IRC (Internet Relay Chat) server implementation written in C++98. The project implements the IRC protocol, allowing multiple clients to connect, communicate in channels, send private messages, and use various IRC commands.

IRC is one of the oldest and most widely used chat protocols on the internet. This project provides hands-on experience with network programming, socket management, non-blocking I/O, and the implementation of a real-world communication protocol.

### Built With

- **Language:** C++98
- **Networking:** BSD Sockets (TCP/IP)
- **I/O Multiplexing:** poll()
- **Protocol:** IRC (RFC 1459, RFC 2812)
- **Architecture:** Event-driven, non-blocking I/O
- **Compiler:** g++/clang++
- **Build System:** Makefile
- **Standard:** C++98 compliant

---

## 🎯 Learning Objectives

This project taught me:

- **Network Programming:** Understanding TCP/IP sockets and network communication
- **Socket API:** Creating, binding, listening, and accepting connections
- **I/O Multiplexing:** Using `poll()` for handling multiple clients simultaneously
- **Non-blocking I/O:** Managing asynchronous network operations
- **Protocol Implementation:** Following RFC specifications for IRC
- **Client-Server Architecture:** Designing scalable server applications
- **State Management:** Tracking client registration, authentication, and channels
- **Command Parsing:** Implementing a robust message parser
- **Error Handling:** Managing network errors and client disconnections
- **OOP Design:** Applying object-oriented principles in C++98
- **Memory Management:** Proper resource cleanup and leak prevention
- **Concurrency:** Handling multiple simultaneous connections without threads

---

## 🚀 Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yigit-toq/42_Cursus.git
cd 42_Cursus
git checkout 05-ft_irc
```

2. Compile the server
```bash
make
```

This will create the `ircserv` executable

3. (Optional) Compile the bonus (IRC bot)
```bash
make bonus
```

This will create the `assistant` executable

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

### Server Usage

**Start the server:**
```bash
./ircserv <port> <password>
```

**Parameters:**
- `<port>` - Port number for the server to listen on (1024-65535)
- `<password>` - Server password (required for clients to connect)

**Example:**
```bash
./ircserv 6667 mypassword
```

The server will start listening for connections on the specified port.

### Client Connection

You can connect to the server using any standard IRC client:

**Using netcat (for testing):**
```bash
nc localhost 6667
```

**Using irssi:**
```bash
irssi
/connect localhost 6667 mypassword
/nick YourNickname
/join #channel
```

**Using WeeChat:**
```bash
weechat
/server add myserver localhost/6667 -password=mypassword
/connect myserver
/nick YourNickname
/join #channel
```

**Using HexChat:**
1. Add new network
2. Server: `localhost/6667`
3. Set password: `mypassword`
4. Connect and join channels

### Supported Commands

#### Authentication Commands
```
PASS <password>              Set server password (must be first)
NICK <nickname>              Set or change your nickname
USER <username> 0 * :realname   Register your user information
```

#### Channel Commands
```
JOIN <channel>[,<channel>]   Join one or more channels
PART <channel> [message]     Leave a channel
TOPIC <channel> [topic]      View or set channel topic
INVITE <nickname> <channel>  Invite user to channel
KICK <channel> <user> [reason]  Kick user from channel
MODE <channel> <modes> [args]   Set channel modes
```

#### Messaging Commands
```
PRIVMSG <target> <message>   Send message to user or channel
NOTICE <target> <message>    Send notice (no auto-reply)
```

#### Information Commands
```
WHO <channel>                List users in channel
WHOIS <nickname>             Get information about user
LIST [channels]              List channels and topics
NAMES <channel>              List nicknames in channel
```

#### Server Commands
```
PING <server>                Ping server
PONG <server>                Pong response
QUIT [message]               Disconnect from server
```

#### Channel Modes

**User Modes:**
- `+o` / `-o` - Give/take channel operator privileges
- `+v` / `-v` - Give/take voice (ability to speak in moderated channel)

**Channel Modes:**
- `+i` / `-i` - Invite-only channel
- `+t` / `-t` - Only operators can change topic
- `+k` / `-k` - Set/remove channel key (password)
- `+l` / `-l` - Set/remove user limit

**Examples:**
```
MODE #channel +i              Make channel invite-only
MODE #channel +k password     Set channel password
MODE #channel +l 10           Set user limit to 10
MODE #channel +o nickname     Give operator status to user
MODE #channel -i              Remove invite-only mode
```

### Command Flow Example

```bash
# 1. Connect and authenticate
PASS mypassword
NICK alice
USER alice 0 * :Alice Smith

# 2. Join a channel
JOIN #general

# 3. Send messages
PRIVMSG #general :Hello everyone!
PRIVMSG bob :Hi Bob, private message

# 4. Channel operations (if operator)
MODE #general +t              # Only ops can change topic
TOPIC #general :Welcome to general chat
KICK #general spammer :Spamming is not allowed
INVITE charlie #general

# 5. Leave and disconnect
PART #general :Goodbye!
QUIT :Leaving server
```

---

## 📁 Project Structure

```
ft_irc/
├── sources/
│   ├── Main.cpp                    # Server entry point
│   ├── command/                    # IRC command implementations
│   │   ├── InviteCommand.cpp
│   │   ├── JoinCommand.cpp
│   │   ├── KickCommand.cpp
│   │   ├── ModeCommand.cpp
│   │   ├── NickCommand.cpp
│   │   ├── PartCommand.cpp
│   │   ├── PassCommand.cpp
│   │   ├── PrivCommand.cpp
│   │   ├── QuitCommand.cpp
│   │   └── UserCommand.cpp
│   │   ├── TopicCommand.cpp
│   ├── network/                    # Network layer
│   │   ├── PollHandler.cpp         # poll() event handling
│   │   └── Socket.cpp              # Socket wrapper
│   ├── process/                    # Core IRC entities
│   │   ├── Channel.cpp             # Channel management
│   │   ├── Client.cpp              # Client state
│   │   └── Server.cpp              # Main server logic
│   ├── protocol/                   # IRC protocol
│   │   ├── CommandHandler.cpp      # Command dispatching
│   │   └── Message.cpp             # Message parsing
│   ├── utils/                      # Utilities
│   │   ├── Logger.cpp              # Logging system
│   │   └── Utils.cpp               # Helper functions
│   └── bonus/                      # Bonus features
│       ├── Assistant.cpp           # IRC bot implementation
│       └── Main.cpp                # Bot entry point
├── includes/
│   ├── command/                    # Command headers
│   │   ├── InviteCommand.hpp
│   │   ├── JoinCommand.hpp
│   │   ├── KickCommand.hpp
│   │   ├── ModeCommand.hpp
│   │   ├── NickCommand.hpp
│   │   ├── PartCommand.hpp
│   │   ├── PassCommand.hpp
│   │   ├── PrivCommand.hpp
│   │   ├── QuitCommand.hpp
│   │   └── UserCommand.hpp
│   │   ├── TopicCommand.hpp
│   ├── network/
│   │   ├── PollHandler.hpp
│   │   └── Socket.hpp
│   ├── process/
│   │   ├── Channel.hpp
│   │   ├── Client.hpp
│   │   └── Server.hpp
│   ├── protocol/
│   │   ├── CommandHandler.hpp
│   │   └── Message.hpp
│   ├── utils/
│   │   ├── Logger.hpp
│   │   └── Utils.hpp
│   └── bonus/
│       └── Assistant.hpp           # Bot header
├── Makefile                        # Build automation
└── README.md                       # Documentation
```

---

## 🔧 Technical Implementation

### Architecture Overview

```
┌────────────────────────────────────────────┐
│              IRC Server                    │
├────────────────────────────────────────────┤
│  ┌──────────────────────────────────────┐  │
│  │         PollHandler                  │  │
│  │    (I/O Multiplexing with poll())    │  │
│  └──────────────────────────────────────┘  │
│                    ↓                       │
│  ┌──────────────────────────────────────┐  │
│  │         Server Socket                │  │
│  │   (Accept new connections)           │  │
│  └──────────────────────────────────────┘  │
│                    ↓                       │
│  ┌──────────────────────────────────────┐  │
│  │      Client Sockets (poll events)    │  │
│  │   ┌──────┐  ┌──────┐  ┌──────┐       │  │
│  │   │Client│  │Client│  │Client│ ...   │  │
│  │   └──────┘  └──────┘  └──────┘       │  │
│  └──────────────────────────────────────┘  │
│                    ↓                       │
│  ┌──────────────────────────────────────┐  │
│  │      Message Parser                  │  │
│  │  (Parse IRC protocol messages)       │  │
│  └──────────────────────────────────────┘  │
│                    ↓                       │
│  ┌──────────────────────────────────────┐  │
│  │    CommandHandler                    │  │
│  │  (Dispatch to command classes)       │  │
│  └──────────────────────────────────────┘  │
│                    ↓                       │
│  ┌──────────────────────────────────────┐  │
│  │  Command Implementations             │  │
│  │  PASS NICK USER JOIN PART PRIVMSG... │  │
│  └──────────────────────────────────────┘  │
│                    ↓                       │
│  ┌──────────────────────────────────────┐  │
│  │    Channel & Client Management       │  │
│  │  (State, permissions, messages)      │  │
│  └──────────────────────────────────────┘  │
└────────────────────────────────────────────┘
```

### Core Classes

#### 1. Server
The main server class that orchestrates everything:

```cpp
class Server
{
private:
    Socket                              _srvr_socket;
    PollHandler                         _poll_handler;
    std::map<int, Client*>              _clients;
    std::map<std::string, Channel*>     _channels;
    std::map<std::string, CommandHandler*> _cmds_handler;
    std::string                         _password;
    
public:
    Server(int port, std::string pass);
    void Start();                           // Main server loop
    void HandleNewConnection();             // Accept new client
    void HandleClientMessage(int fd);       // Process client data
    void ClientDisconnection(int fd);       // Clean up client
};
```

#### 2. Client
Represents a connected client:

```cpp
class Client
{
private:
    int                     _socket_fd;
    std::string             _nickname;
    std::string             _username;
    std::string             _realname;
    std::string             _hostname;
    bool                    _authenticated;
    bool                    _registered;
    std::string             _buffer;        // Partial message buffer
    
public:
    bool IsRegistered() const;
    void SendMessage(const std::string& msg);
    void AppendToBuffer(const std::string& data);
};
```

#### 3. Channel
Manages IRC channels:

```cpp
class Channel
{
private:
    std::string                     _name;
    std::string                     _topic;
    std::string                     _key;           // Password
    int                             _user_limit;
    bool                            _invite_only;
    bool                            _topic_restricted;
    std::map<Client*, bool>         _members;       // bool = is_operator
    std::set<Client*>               _invited;
    
public:
    void AddMember(Client* client, bool is_op);
    void RemoveMember(Client* client);
    void Broadcast(const std::string& msg, Client* exclude = NULL);
    bool HasMode(char mode) const;
};
```

#### 4. PollHandler
Manages I/O multiplexing with poll():

```cpp
class PollHandler
{
private:
    std::vector<struct pollfd>      _poll_fds;
    
public:
    void AddFd(int fd, short events);
    void RemoveFd(int fd);
    std::vector<struct pollfd> WaitForEvents(int timeout);
};
```

#### 5. Message
Parses IRC protocol messages:

```cpp
class Message
{
private:
    std::string         _prefix;        // :sender
    std::string         _command;       // PRIVMSG, JOIN, etc.
    std::vector<std::string> _params;   // Command parameters
    
public:
    Message(const std::string& raw);
    const std::string& GetCommand() const;
    const std::vector<std::string>& GetParams() const;
};
```

#### 6. CommandHandler (Abstract Base)
Command pattern for IRC commands:

```cpp
class CommandHandler
{
public:
    virtual void Execute(Server* server, Client* client, const Message& msg) = 0;
    virtual ~CommandHandler() {}
};

// Example implementation
class JoinCommand : public CommandHandler
{
public:
    void Execute(Server* server, Client* client, const Message& msg);
};
```

### Event Loop

```cpp
void Server::Start()
{
    while (true)
    {
        // Wait for events on any socket
        std::vector<struct pollfd> active_fds = _poll_handler.WaitForEvents(-1);
        
        for (size_t i = 0; i < active_fds.size(); i++)
        {
            if (active_fds[i].fd == _srvr_socket.GetFd())
            {
                // New connection
                if (active_fds[i].revents & POLLIN)
                    HandleNewConnection();
            }
            else
            {
                // Existing client activity
                if (active_fds[i].revents & POLLIN)
                    HandleClientMessage(active_fds[i].fd);
                if (active_fds[i].revents & (POLLHUP | POLLERR))
                    ClientDisconnection(active_fds[i].fd);
            }
        }
        
        CheckForTimeout();      // Disconnect idle clients
        CleanupUsers();         // Remove disconnected clients
        CleanupChnls();         // Remove empty channels
    }
}
```

### Message Processing

```cpp
void Server::HandleClientMessage(int fd)
{
    Client* client = _clients[fd];
    char buffer[BUFFER_SIZE];
    
    // Read data from socket
    int bytes = recv(fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes <= 0)
    {
        ClientDisconnection(fd);
        return;
    }
    
    buffer[bytes] = '\0';
    client->AppendToBuffer(buffer);
    
    // Process complete messages (ending with \r\n)
    std::string& buf = client->GetBuffer();
    size_t pos;
    while ((pos = buf.find("\r\n")) != std::string::npos)
    {
        std::string line = buf.substr(0, pos);
        buf.erase(0, pos + 2);
        
        Message msg(line);
        ProcessMessage(client, msg);
    }
}

void Server::ProcessMessage(Client* sender, const Message& msg)
{
    std::string cmd = msg.GetCommand();
    
    // Find command handler
    if (_cmds_handler.find(cmd) != _cmds_handler.end())
        _cmds_handler[cmd]->Execute(this, sender, msg);
    else
        SendsNumericReply(sender, ERR_UNKNOWNCOMMAND, cmd);
}
```

### IRC Numeric Replies

```cpp
// Success replies
#define RPL_WELCOME             001
#define RPL_TOPIC               332
#define RPL_NAMREPLY            353
#define RPL_ENDOFNAMES          366

// Error replies
#define ERR_NOSUCHNICK          401
#define ERR_NOSUCHCHANNEL       403
#define ERR_CANNOTSENDTOCHAN    404
#define ERR_TOOMANYCHANNELS     405
#define ERR_UNKNOWNCOMMAND      421
#define ERR_NONICKNAMEGIVEN     431
#define ERR_ERRONEUSNICKNAME    432
#define ERR_NICKNAMEINUSE       433
#define ERR_NOTONCHANNEL        442
#define ERR_USERONCHANNEL       443
#define ERR_NEEDMOREPARAMS      461
#define ERR_ALREADYREGISTRED    462
#define ERR_PASSWDMISMATCH      464
#define ERR_CHANNELISFULL       471
#define ERR_INVITEONLYCHAN      473
#define ERR_BADCHANNELKEY       475
#define ERR_CHANOPRIVSNEEDED    482
```

---

## 🎁 Bonus Features

### IRC Bot (Assistant)

The bonus part includes a fully functional IRC bot that can:

- **Auto-connect:** Connects to the server automatically with authentication
- **Command Response:** Responds to specific commands in channels
- **Quote System:** Shares inspirational quotes when asked
- **Time Information:** Provides current time on request
- **Greeting:** Welcomes users who join channels

**Bot Usage:**
```bash
# Start the bot
./assistant <server_ip> <port> <password> <bot_nickname>

# Example
./assistant localhost 6667 mypassword Assistant
```

**Bot Commands (in channel):**
```
!quote          Get an inspirational quote
!time           Get current server time
!help           Show available commands
!hello          Get a greeting from the bot
```

**Bot Architecture:**
```cpp
class Assistant
{
private:
    int                         _bot_socket;
    std::string                 _nickname;
    std::vector<std::string>    _quotes;
    
public:
    void ConnectToServer();
    void AuthAndRegister();
    void MainLoop();
    void ProcessMessage(const std::string& msg);
    void HandlerCommand(const std::string& sender, 
                       const std::string& channel, 
                       const std::string& message);
};
```

---

## 🧪 Testing

### Manual Testing

**Test basic connection:**
```bash
# Terminal 1: Start server
./ircserv 6667 test123

# Terminal 2: Connect with nc
nc localhost 6667
PASS test123
NICK alice
USER alice 0 * :Alice Smith
JOIN #test
PRIVMSG #test :Hello!
QUIT :Bye
```

**Test with multiple clients:**
```bash
# Connect 2-3 clients and test:
- Private messages between users
- Channel messages
- Channel modes (invite-only, password, limit)
- Operator commands (KICK, MODE, INVITE, TOPIC)
- User registration and nickname changes
```

### Testing with IRC Clients

1. **irssi:** Lightweight terminal client
2. **WeeChat:** Modern terminal client with colors
3. **HexChat:** GUI client for comprehensive testing
4. **Textual:** macOS native client

### Edge Cases to Test

- Invalid password
- Duplicate nicknames
- Joining non-existent channels
- Commands before registration
- Very long messages (>512 bytes)
- Rapid connect/disconnect
- Invalid channel names
- Permission violations (kick without op status)
- Buffer overflow attempts
- Multiple simultaneous commands

---

## 📚 Resources

- [RFC 1459 - IRC Protocol](https://tools.ietf.org/html/rfc1459) - Original IRC specification
- [RFC 2812 - IRC Client Protocol](https://tools.ietf.org/html/rfc2812) - Updated specification
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) - Socket programming guide
- [poll() man page](https://man7.org/linux/man-pages/man2/poll.2.html)
- [IRC Numeric Replies](https://www.alien.net.au/irc/irc2numerics.html)
- [Modern IRC Documentation](https://modern.ircdocs.horse/)
- [42 C++ Modules](https://github.com/42School/42-Cursus-CPP-Modules)

---

## 📄 License

This project is part of the 42 School curriculum. Code is free to use for educational purposes.

---

## 📬 Contact

**Yiğit Top** - [@yigit-toq](https://github.com/yigit-toq)

---

<div align="center">

**Made with 💬 at 42 Kocaeli**

*This project was completed as part of the 42 School curriculum.*

*Implementing internet history - IRC since 1988*

</div>
