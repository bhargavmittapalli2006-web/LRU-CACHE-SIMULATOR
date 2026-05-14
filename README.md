# LRU Cache Simulator
A Console Application powered by Stack Data Structure | C++

Vardhaman College of Engineering — CSE Department — Summer Project 2025–26

## Team

### Team Leader
M Sai Bhargav

### Team Members
M Harshith Kumar  
E Adithya  
K Yeswanth  
G Rithik  

### Mentor
G Siddhartha

---

## What is this?

A fully functional LRU Cache Simulator that runs in the terminal.

The project demonstrates the working of the Least Recently Used cache replacement algorithm using stack data structures implemented in C++.

The simulator processes page requests, identifies cache hits and misses, updates cache memory dynamically, and removes the least recently used page whenever the cache becomes full.

This project demonstrates practical implementation of Data Structures concepts through a real-world console application.

---

## Features

### Access Page
Allows the user to access pages dynamically through the console interface.

### Cache Hit Detection
Identifies whether the requested page already exists in cache memory.

### Cache Miss Detection
Detects pages that are not present in the cache.

### Least Recently Used Page Replacement
Automatically removes the least recently used page when cache reaches maximum capacity.

### Stack Based Cache Management
Maintains recently used pages using stack operations.

### Cache Visualization
Displays current cache contents from most recently used to least recently used.

### Cache Statistics
Displays total cache hits, cache misses, total requests, and hit ratio.

### Interactive Console Menu
Provides a user-friendly menu driven console application.

---

## Data Structures Used

### Stack
Used for cache storage and page management operations.

### Vector
Used for displaying cache contents properly in the console.

---

## File Structure

LRU-CACHE-SIMULATOR/
├── main.cpp
└── README.md

---

## How to Compile and Run

### Requirements

C++ Compiler  
Visual Studio Code or CodeBlocks

### Compile

```bash
g++ main.cpp -o lru
```

### Run

#### Linux or Mac

```bash
./lru
```

#### Windows

```bash
lru.exe
```

---

## How the Application Works

1. The application starts and asks the user to enter cache size.
2. User selects operations from the menu.
3. Pages are accessed dynamically through user input.
4. The simulator checks whether the page already exists in cache.
5. If the page exists, it becomes a Cache Hit.
6. If the page does not exist, it becomes a Cache Miss.
7. When cache becomes full, the least recently used page is removed.
8. Current cache status and statistics are displayed continuously.

---

## Concepts Used

### Stack Operations

Push  
Pop  
Top  
Traversal

### Cache Management

Cache Hit Detection  
Cache Miss Detection  
Least Recently Used Replacement

### Console Application Development

Menu Driven Programming  
User Interaction  
Formatted Console Output

### Object Oriented Programming in C++

Classes  
Functions  
Encapsulation

---

## Future Improvements

GUI based simulator using Qt or Java  
Graphical cache visualization  
Support for multiple cache replacement algorithms  
Performance comparison between LRU and FIFO  
File based page request system  
Real-time cache analytics dashboard

---

## Sample Use Cases

Operating System cache simulation  
Data Structures and Algorithms project  
Memory management demonstration  
Stack implementation practice  
Console application development practice

---

## Learning Outcomes

Understanding of LRU Cache Replacement Algorithm  
Practical implementation of Stack Data Structure  
Knowledge of Cache Memory Management  
Console Application Development in C++  
Git and GitHub Version Control Basics

---

## License

Academic Project — Vardhaman College of Engineering 2025–26