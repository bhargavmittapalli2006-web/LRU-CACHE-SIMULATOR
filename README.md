# LRU Cache Simulator

> **Stack-Based Cache Replacement Algorithm · C++17 · Terminal Application**

```
  ██╗     ██████╗ ██╗   ██╗
  ██║     ██╔══██╗██║   ██║   LRU Cache Simulator  v1.0
  ██║     ██████╔╝██║   ██║   Vardhaman College of Engineering
  ██║     ██╔══██╗██║   ██║   CSE Department · Summer Project 2025–26
  ███████╗██║  ██║╚██████╔╝
  ╚══════╝╚═╝  ╚═╝ ╚═════╝
```

---

## Team

| Role | Name |
|------|------|
| **Team Leader** | M Sai Bhargav |
| **Member** | M Harshith Kumar |
| **Member** | E Adithya |
| **Member** | K Yeswanth |
| **Member** | G Rithik |
| **Mentor** | G Siddhartha |

---

## Overview

This project is a fully interactive **LRU (Least Recently Used) Cache Simulator** that runs in the terminal. It demonstrates how an operating system decides which page to remove from limited cache memory when a new page needs to be loaded.

The simulator is built in **C++17** using a **stack** as the core data structure. It processes page requests one at a time or in bulk, detects cache hits and misses, evicts the least recently used page when the cache is full, and displays live statistics after every operation.

---

## How LRU Works

```
  Cache holds N pages.  Top of stack = Most Recently Used (MRU)
                        Bottom of stack = Least Recently Used (LRU)

  ┌──────────────────────┐
  │  MRU  (most recent)  │
  ├──────────────────────┤
  │     Page  4          │  ← accessed 1 step ago
  ├──────────────────────┤
  │     Page  2          │  ← accessed 2 steps ago
  ├──────────────────────┤
  │     Page  7          │  ← accessed longest ago
  ├──────────────────────┤
  │  LRU  (least recent) │  ← EVICTED when cache is full
  └──────────────────────┘

  CACHE HIT  → Page already exists → move it to the top (MRU)
  CACHE MISS → Page is new
               If cache not full → simply push to top
               If cache is full  → remove bottom (LRU), push to top
```

---

## Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Access a Page** | Request a single page and see a hit or miss result instantly |
| 2 | **Batch Access** | Enter a full page-reference string (e.g. `1 2 3 1 4 2`) and process all at once |
| 3 | **Display Cache** | Visual box-drawn stack showing MRU → LRU order with colour coding |
| 4 | **Statistics** | Live hit count, miss count, total requests, hit ratio %, and miss ratio % |
| 5 | **Clear Cache** | Reset the cache and all statistics for a fresh simulation |
| 6 | **Colour-Coded UI** | Green = hit · Red = miss/evict · Yellow = LRU · Cyan = headers |

---

## Project Structure

```

LRU-CACHE-SIMULATOR/ 
│
 ├── main.cpp 
 ├── README.md
 └── screenshots/ 
    ├── homescreen.png 
    ├── mainmenu.png 
    ├── cache_hit.png 
    ├── statistics.png 
    └── exit.png
  └──docs/
    ├──presentation.pptx
    

-

## Requirements

| Tool | Minimum Version |
|------|----------------|
| C++ Compiler (g++) | C++17 or later |
| Terminal | Any ANSI-compatible terminal |
| OS | Linux · macOS · Windows (with ANSI support) |

> **Windows note:** The program automatically runs `chcp 65001` on startup to enable UTF-8 and ANSI colour output in the Windows terminal.

---

## Compile & Run

**Step 1 — Compile**
```bash
g++ -std=c++17 -o lru_cache lru_cache.cpp
```

**Step 2 — Run**

```bash
# Linux / macOS
./lru_cache

# Windows
lru_cache.exe
```

**Step 3 — Usage**

When the program starts, enter a cache size (e.g. `3`). Then choose an option from the menu and follow the prompts.

---

## Sample Session

```
  Enter cache capacity: 3

  > 1  (Access a Page)
  Enter page number: 7

  ── Accessing Page : 7 ──────────────────────────
  Result  : CACHE MISS  ✗
  Page 7 not found in cache.

  Cache State  [1/3]
  ┌──────────────────────┐
  │  MRU  (most recent)  │
  ├──────────────────────┤
  │     Page  7          │
  ├──────────────────────┤
  │  LRU  (least recent) │
  └──────────────────────┘

  > 4  (Statistics)
  Cache Hits     :  2
  Cache Misses   :  5
  Total Requests :  7
  Hit  Ratio     :  28.6%
  Miss Ratio     :  71.4%
```

---

## Data Structures Used

### Stack `std::stack<int>`
The primary data structure for the cache.
- **Top** of the stack always holds the most recently used page (MRU).
- **Bottom** of the stack always holds the least recently used page (LRU).
- On a **hit**, the page is removed from its current position and pushed back to the top.
- On a **miss** with a full cache, the bottom element is removed before pushing the new page.

### Vector `std::vector<int>`
Used only for display purposes — the stack is temporarily flattened into a vector so pages can be printed from MRU to LRU in the visual box layout.

---

## Complexity

| Operation | Time | Notes |
|-----------|------|-------|
| `isPresent()` | O(n) | Linear scan through stack copy |
| `removePage()` | O(n) | Rebuild stack without target page |
| `removeLRU()` | O(n) | Pop to bottom, discard, restore |
| `accessPage()` | O(n) | Calls the above as needed |

> **Note:** A real-world production LRU cache achieves **O(1)** for all operations using a doubly-linked list combined with a hash map. The stack-based approach used here is intentional — it clearly illustrates the MRU/LRU concept for educational purposes.

---

## Key Concepts Covered

**Data Structures**
- Stack (push, pop, top, traversal)
- Vector (indexed display)

**Cache Management**
- Cache hit and miss detection
- LRU page replacement policy
- Dynamic cache state management

**C++ Programming**
- Object-Oriented Programming (class, encapsulation, methods)
- ANSI escape codes for terminal colour output
- Input validation and error handling
- `istringstream` for batch input parsing

---

## Future Improvements

- [ ] GUI visualiser using Qt or SFML
- [ ] Support for FIFO, Optimal, and LFU replacement algorithms
- [ ] Side-by-side algorithm comparison with performance charts
- [ ] File-based page reference string input
- [ ] Real-time cache analytics with hit/miss trend graph
- [ ] Unit tests for each cache operation

---

## Use Cases

- Operating systems — page replacement simulation
- Data Structures & Algorithms coursework
- Memory management concept demonstration
- C++ OOP and stack implementation practice

---

## Learning Outcomes

After studying this project you will understand:

- How the LRU cache replacement algorithm works step by step
- How a stack models recency of access (MRU at top, LRU at bottom)
- How to build a clean, interactive terminal application in C++
- How to display live statistics and track algorithm performance
- How to write readable, well-commented object-oriented C++ code

---

## License

Academic project — Vardhaman College of Engineering, CSE Department, 2025–26.
Not intended for commercial use.