# 💬 Inter-Process Chat Application Using IPC

A terminal-based chat application developed in **C** that demonstrates Inter-Process Communication (IPC) using **Linux Named Pipes (FIFOs)**.

The application allows two independent users to exchange messages in real time through separate processes. It also maintains a timestamped chat history that can be viewed using a separate history viewer program.

## 📌 Project Overview

Inter-Process Communication (IPC) allows two or more processes to exchange information and coordinate their activities.

This project demonstrates how two independent processes can communicate using named pipes in a Linux environment.

The application uses:
- `fork()` to create child processes.
- `mkfifo()` to create named pipes.
- `read()` and `write()` for message communication.
- File handling to store chat history.
- Timestamps to record when messages are saved.

## 🎯 Objectives

- Understand the concept of Inter-Process Communication.
- Implement two-way communication using named pipes.
- Create child processes using `fork()`.
- Exchange messages between two independent users.
- Store messages with timestamps.
- Display saved conversations using a history viewer.
- Implement chat termination using `/exit`.

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C Programming | Application development |
| Ubuntu Linux | Execution environment |
| Windows Subsystem for Linux (WSL) | Linux environment on Windows |
| GCC | C compiler |
| VS Code | Code editor |
| Named Pipes (FIFO) | Inter-process communication |
| File Handling | Message history storage |

## ⚙️ System Architecture

The application uses two named FIFO pipes for bidirectional communication.

```text
             USER A
               |
          Process A
          /       \
       Parent     Child
       Send      Receive
          |         |
          v         ^
    +-------------------+
    |    FIFO A → B     |
    +-------------------+
          |         ^
          v         |
    +-------------------+
    |    FIFO B → A     |
    +-------------------+
          |         |
          ^         v
       Receive     Send
          \       /
          Process B
               |
             USER B
```

Both users have:
- A parent process responsible for sending messages.
- A child process responsible for receiving messages.

Messages are also saved in `chat_history.txt` with timestamps.

## 📂 Project Structure

```text
ipc-chat/
│
├── chat.c                # Main chat application
├── history.h             # Chat history functionality
├── chat_history.txt      # Saved chat messages
├── history_viewer.c      # Chat history viewer source
├── chat                  # Compiled chat executable
└── history_viewer        # Compiled history viewer
```

**Note:** Compiled executables are generated during compilation and do not need to be uploaded to GitHub. The history text file is generated when messages are saved.

## 🚀 Installation and Execution

### 1. Clone the repository

```bash
git clone https://github.com/sahasrayeruva/OS-final-Hackathon
```

### 2. Navigate to the project directory

```bash
cd ipc-chat-application
```

### 3. Compile the chat application

```bash
gcc -Wall -Wextra chat.c -o chat
```

### 4. Compile the history viewer

```bash
gcc -Wall -Wextra history_viewer.c -o history_viewer
```

### 5. Run User A

Open the first Ubuntu terminal:

```bash
./chat A
```

### 6. Run User B

Open a second Ubuntu terminal in the same project directory:

```bash
./chat B
```

### 7. Start chatting

Both users can now exchange messages through the FIFO pipes.

To terminate the conversation, enter:

```text
/exit
```

### 8. View chat history

After the chat sessions have ended, execute:

```bash
./history_viewer
```

This displays the previously saved messages and basic history statistics.

## 🧠 Core Concepts

### 1. Inter-Process Communication (IPC)
A mechanism that allows independent processes to exchange information.

### 2. fork()
A Linux system call used to create a child process from an existing process.

### 3. Named Pipes (FIFO)
A communication mechanism that allows processes to exchange data through a named pipe.

### 4. File Handling
Used to store chat messages in a text file for future viewing.

### 5. Process Management
The parent and child processes handle sending and receiving operations.

## 🧪 Features

- Two-user terminal-based chat.
- Bidirectional communication.
- Linux named FIFO pipes.
- Parent-child process creation.
- Timestamped message history.
- Separate chat history viewer.
- `/exit` command to terminate communication.

## 🔮 Future Enhancements

The following features are possible future improvements and are not part of the current implementation:

- Multi-user communication.
- Graphical user interface.
- Improved error handling.
- User authentication.
- Enhanced chat history management.

## 🎓 Learning Outcomes

Through this project, we gained practical knowledge of:

- Linux process creation using `fork()`.
- Inter-Process Communication mechanisms.
- Named pipe implementation using `mkfifo()`.
- Reading and writing data between processes.
- File handling in C.
- Compiling and executing C programs in Linux.

## 👨‍💻 Author

**[Your Name]**

Branch: Computer Science & Information Technology

Project: Inter-Process Chat Application Using IPC

## 📜 License

This project is intended for educational and academic purposes.

---

⭐ If you find this project useful, feel free to star the repository!
