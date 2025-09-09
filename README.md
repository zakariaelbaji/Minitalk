minitalk - A Simple Client-Server Communication Program in C
Table of Contents

### Overview

### Features

### Getting Started

### Prerequisites

### Installation

### Usage

### Testing

### Overview

minitalk is a client-server communication program built in C.
The goal of this project is to implement data transfer between two processes using UNIX signals (SIGUSR1 and SIGUSR2).

This project was developed as part of the 42 curriculum and provides a practical exercise in:

Process communication

Signal handling

Bitwise operations

Synchronization between client and server

### Features

✅ Client sends a string message to the server, character by character, using only signals.
✅ Server receives the message and prints it to standard output.
✅ Communication is fully asynchronous.
✅ Supports sending all standard ASCII characters.
✅ Error handling for invalid inputs (e.g., wrong PID).

### Prerequisites

Ensure you have the following installed:

A C compiler (e.g., gcc, clang)

make (GNU Make)

### Installation

Clone the repository:
```
git clone https://github.com/YOUR_USERNAME/minitalk
cd minitalk
```
Build the executables:
```
make
```
This will compile the project and generate two executables:

server

client

### Usage

Start the server
```
./server
```
This will print the server’s PID (Process ID), for example:
```
Server PID: 12345
```
Run the client with the server PID and your message
```
./client 12345 "Hi i'm Zakaria"
```
The server will receive the message and display it in its terminal
