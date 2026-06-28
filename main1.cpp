/*
 * ============================================================
 *  LRU Cache Simulator  —  Vardhaman College of Engineering
 *  CSE Department  |  Summer Project 2025-26
 *  ============================================================
 *  Compile:  g++ -std=c++17 -o lru_cache lru_cache.cpp
 *  Run:      ./lru_cache
 * ============================================================
 *
 *  HOW LRU WORKS:
 *  - Cache holds a fixed number of pages in memory.
 *  - On a CACHE HIT  → page already in cache; move it to top
 *                       (most recently used position).
 *  - On a CACHE MISS → page not in cache; if cache is full,
 *                       evict the bottom element (least recently
 *                       used), then push the new page to top.
 *  - A stack is used to simulate MRU (top) → LRU (bottom) order.
 *
 *  COMPLEXITY:
 *  - accessPage()  : O(n)  — stack scan for hit/miss check
 *  - removePage()  : O(n)  — rebuild stack without target page
 *  - removeLRU()   : O(n)  — pop to bottom, remove, restore
 *  NOTE: For O(1) access, upgrade to doubly-linked list + hashmap.
 * ============================================================
 */

#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;

// ==========================================
// ANSI COLOR CODES FOR UI STYLING
// ==========================================
const string RESET   = "\033[0m";
const string BOLD    = "\033[1m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string RED     = "\033[31m";
const string CYAN    = "\033[36m";
const string BLUE    = "\033[34m";
const string GRAY    = "\033[90m";
const string MAGENTA = "\033[35m";
const string DIM     = "\033[2m";

// ==========================================
// Utility: print a horizontal divider line
// ==========================================
void printDivider() {
    cout << GRAY << "  " << string(54, '-') << RESET << "\n";
}

// ==========================================
// Utility: print a section header
// ==========================================
void printHeader(const string& title) {
    cout << "\n" << CYAN << BOLD << "  ══ " << title << " ══" << RESET << "\n\n";
}

// ==========================================
// LRU Cache Simulator Class
// ==========================================
class LRUCacheSimulator {
private:
    stack<int> cache;   // top = MRU, bottom = LRU
    int cacheSize;      // maximum number of pages allowed
    int currentSize;    // pages currently in cache
    int hits;           // total cache hit count
    int misses;         // total cache miss count

    // ----------------------------------------------------------
    // isPresent() — scans the stack to check if 'page' exists.
    // Uses a temporary copy so original stack is not modified.
    // O(n) time.
    // ----------------------------------------------------------
    bool isPresent(int page) {
        stack<int> temp = cache;        // copy; don't touch original
        while (!temp.empty()) {
            if (temp.top() == page) return true;
            temp.pop();
        }
        return false;
    }

    // ----------------------------------------------------------
    // removePage() — rebuilds stack without the target page.
    // All other pages retain their relative order.
    // Called on a CACHE HIT before pushing page back to top.
    // ----------------------------------------------------------
    void removePage(int page) {
        stack<int> temp;
        while (!cache.empty()) {
            if (cache.top() != page)    // keep every page except target
                temp.push(cache.top());
            cache.pop();
        }
        // Restore remaining pages in original order
        while (!temp.empty()) {
            cache.push(temp.top());
            temp.pop();
        }
    }

    // ----------------------------------------------------------
    // removeLRU() — evicts the bottom element (least recently
    // used). Temporarily pops everything above it into a helper
    // stack, discards the bottom, then restores the rest.
    // ----------------------------------------------------------
    void removeLRU() {
        stack<int> temp;
        // Pop all but the bottom element into temp
        while (cache.size() > 1) {
            temp.push(cache.top());
            cache.pop();
        }
        // Bottom element is now on top — this is the LRU page
        cout << RED << "  [↑] Evicted LRU page : " << BOLD << cache.top()
             << RESET << "\n";
        cache.pop();    // evict it

        // Restore the remaining pages
        while (!temp.empty()) {
            cache.push(temp.top());
            temp.pop();
        }
        currentSize--;
    }

public:
    // Constructor — initialise cache with given size
    LRUCacheSimulator(int size)
        : cacheSize(size), currentSize(0), hits(0), misses(0) {}

    // ----------------------------------------------------------
    // accessPage() — main logic entry point.
    // Determines HIT or MISS, updates cache, displays result.
    // ----------------------------------------------------------
    void accessPage(int page) {
        printDivider();
        cout << BOLD << CYAN << "  Accessing Page : " << page << RESET << "\n";
        printDivider();

        if (isPresent(page)) {
            // ── CACHE HIT ──────────────────────────────────────
            hits++;
            cout << GREEN << BOLD << "  Result  : CACHE HIT  ✓\n" << RESET;
            cout << DIM   << "  Page " << page << " already in cache — moved to MRU.\n" << RESET;

            removePage(page);   // pull it out of its current position
            cache.push(page);   // push it back as most recently used
        } else {
            // ── CACHE MISS ─────────────────────────────────────
            misses++;
            cout << RED  << BOLD << "  Result  : CACHE MISS  ✗\n" << RESET;
            cout << DIM  << "  Page " << page << " not found in cache.\n" << RESET;

            if (currentSize == cacheSize) {
                // Cache is full — must evict LRU before inserting
                cout << YELLOW << "  Cache full (" << cacheSize << "/" << cacheSize
                     << ") — evicting LRU page...\n" << RESET;
                removeLRU();
            }
            // Insert new page as most recently used (top of stack)
            cache.push(page);
            currentSize++;
        }

        displayCache();     // show updated cache state after every access
    }

    // ----------------------------------------------------------
    // displayCache() — visual stack representation.
    // Top of stack = MRU, bottom = LRU.
    // ----------------------------------------------------------
    void displayCache() {
        cout << "\n" << BOLD << "  Cache State  ["
             << currentSize << "/" << cacheSize << "]\n" << RESET;
        printDivider();

        if (cache.empty()) {
            cout << DIM << "  (cache is empty)\n" << RESET;
            printDivider();
            return;
        }

        // Flatten stack into a vector (index 0 = top = MRU)
        stack<int> temp = cache;
        vector<int> pages;
        while (!temp.empty()) {
            pages.push_back(temp.top());
            temp.pop();
        }

        cout << GRAY << "  ┌──────────────────────┐\n" << RESET;
        cout << CYAN << "  │  MRU  (most recent)  │\n" << RESET;
        cout << GRAY << "  ├──────────────────────┤\n" << RESET;

        for (int i = 0; i < (int)pages.size(); i++) {
            // Highlight MRU (top) in green, LRU (bottom) in yellow
            if (i == 0)
                cout << GREEN;
            else if (i == (int)pages.size() - 1)
                cout << YELLOW;
            else
                cout << RESET;

            cout << "  │     Page  " << left << setw(12) << pages[i]
                 << "│" << RESET << "\n";

            if (i < (int)pages.size() - 1)
                cout << GRAY << "  ├──────────────────────┤\n" << RESET;
        }

        cout << GRAY << "  ├──────────────────────┤\n" << RESET;
        cout << YELLOW << "  │  LRU  (least recent) │\n" << RESET;
        cout << GRAY << "  └──────────────────────┘\n" << RESET;
        printDivider();
    }

    // ----------------------------------------------------------
    // showStatistics() — displays hits, misses, hit ratio.
    // ----------------------------------------------------------
    void showStatistics() {
        printHeader("CACHE STATISTICS");
        int total = hits + misses;

        cout << "  " << BOLD << "Cache Size   : " << RESET << CYAN << cacheSize << RESET << "\n";
        cout << "  " << BOLD << "Pages Loaded : " << RESET << CYAN << currentSize << RESET << "\n\n";

        printDivider();
        cout << GREEN << "  Cache Hits      : " << BOLD << hits   << RESET << "\n";
        cout << RED   << "  Cache Misses    : " << BOLD << misses << RESET << "\n";
        cout << CYAN  << "  Total Requests  : " << BOLD << total  << RESET << "\n";
        printDivider();

        if (total > 0) {
            double hitRatio  = (double)hits  / total * 100.0;
            double missRatio = (double)misses / total * 100.0;
            cout << fixed << setprecision(1);
            cout << GREEN  << "  Hit  Ratio      : " << BOLD << hitRatio  << "%" << RESET << "\n";
            cout << YELLOW << "  Miss Ratio      : " << BOLD << missRatio << "%" << RESET << "\n";
        } else {
            cout << DIM << "  No requests made yet.\n" << RESET;
        }
        printDivider();
    }

    // ----------------------------------------------------------
    // runBatch() — processes a sequence of pages at once.
    // Useful for testing with a predefined reference string.
    // ----------------------------------------------------------
    void runBatch() {
        printHeader("BATCH ACCESS");
        cout << DIM << "  Enter space-separated page numbers (e.g. 1 2 3 1 4 2):\n" << RESET;
        cout << GREEN << "  > " << RESET;

        string line;
        getline(cin, line);     // read the whole line as one input

        if (line.empty()) {
            cout << RED << "  No pages entered.\n" << RESET;
            return;
        }

        // Parse each number from the line
        vector<int> pages;
        int num;
        istringstream iss(line);
        while (iss >> num) pages.push_back(num);

        cout << "\n  Processing " << CYAN << pages.size()
             << RESET << " page request(s)...\n";

        for (int p : pages) accessPage(p);

        cout << GREEN << "\n  [✓] Batch complete.\n" << RESET;
    }

    // clearCache() — resets cache and stats for a fresh run
    void clearCache() {
        cache = stack<int>();
        currentSize = 0;
        hits   = 0;
        misses = 0;
        cout << GREEN << "  [✓] Cache cleared. Stats reset.\n" << RESET;
    }
};

// ==========================================
// Display the main menu UI
// ==========================================
void displayMenu(int cacheSize) {
    cout << "\n";
    cout << GRAY << " ┌──────────────────────────────────────────────┐\n" << RESET;
    cout << BLUE << " │  ██╗     ██████╗ ██╗   ██╗                   │\n" << RESET;
    cout << BLUE << " │  ██║     ██╔══██╗██║   ██║  " << RESET << BOLD << "LRU Cache" << BLUE << "       │\n" << RESET;
    cout << BLUE << " │  ██║     ██████╔╝██║   ██║  " << RESET << GRAY << "Simulator" << BLUE << "       │\n" << RESET;
    cout << BLUE << " │  ██║     ██╔══██╗██║   ██║                   │\n" << RESET;
    cout << BLUE << " │  ███████╗██║  ██║╚██████╔╝                   │\n" << RESET;
    cout << BLUE << " │  ╚══════╝╚═╝  ╚═╝ ╚═════╝                    │\n" << RESET;
    cout << GRAY << " └──────────────────────────────────────────────┘\n\n" << RESET;

    cout << GRAY << " Vardhaman College of Engineering  ·  CSE Dept\n";
    cout << " Summer Project 2025-26\n";
    cout << " ------------------------------------------------\n\n" << RESET;

    cout << CYAN << BOLD << " Active Cache Size : " << RESET
         << CYAN << cacheSize << RESET << "\n\n";

    cout << YELLOW << BOLD << " MAIN MENU\n" << RESET;
    cout << GRAY << " ------------------------------------------------\n\n" << RESET;

    cout << GREEN << " [1] " << RESET << "Access a Page     " << GRAY << "Single page request\n"     << RESET;
    cout << GREEN << " [2] " << RESET << "Batch Access      " << GRAY << "Multiple pages at once\n"  << RESET;
    cout << GREEN << " [3] " << RESET << "Display Cache     " << GRAY << "Show MRU → LRU stack\n"   << RESET;
    cout << GREEN << " [4] " << RESET << "Show Statistics   " << GRAY << "Hits · Misses · Ratio\n"  << RESET;
    cout << CYAN  << " [5] " << RESET << "Clear Cache       " << GRAY << "Reset cache and stats\n"  << RESET;
    cout << RED   << " [0] " << RESET << "Exit              " << GRAY << "Quit the simulator\n\n"   << RESET;

    cout << GRAY << " ------------------------------------------------\n" << RESET;
    cout << GRAY << " ✦ Stack top = MRU  |  Stack bottom = LRU\n\n"       << RESET;

    cout << GREEN << " → " << GRAY << "Enter your choice and press Enter...\n" << RESET;
    cout << GREEN << "\n > " << RESET;
}

// ==========================================
// main()
// ==========================================
void loadingScreen()
{
    system("cls");

    cout << CYAN << BOLD;
    cout << "\n";
    cout << "=========================================================\n";
    cout << "             LRU CACHE SIMULATOR\n";
    cout << "=========================================================\n";
    cout << RESET;

    cout << "\nInitializing Project...\n\n";

    cout << "Loading ";

    for(int i = 0; i <= 30; i++)
    {
        cout << char(219);
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(70));
    }

    cout << " 100%\n";

    this_thread::sleep_for(chrono::milliseconds(500));

    cout << GREEN << "\nProject Loaded Successfully!\n" << RESET;

    this_thread::sleep_for(chrono::milliseconds(1200));

    system("cls");
}
int main() {
    #ifdef _WIN32
system("chcp 65001 > nul");
#endif
loadingScreen();
    // Enable UTF-8 / ANSI on Windows terminals

    cout << "\n";
    cout << CYAN << BOLD;
    cout << "  ╔══════════════════════════════════════════════╗\n";
    cout << "  ║       LRU CACHE SIMULATOR  —  v1.0           ║\n";
    cout << "  ║   Vardhaman College of Engineering, CSE      ║\n";
    cout << "  ╚══════════════════════════════════════════════╝\n";
    cout << RESET << "\n";

    // Ask user for cache size once at startup
    int cacheSize = 0;
    while (cacheSize <= 0) {
        cout << YELLOW << "  Enter cache capacity (number of pages): " << RESET;
        if (!(cin >> cacheSize) || cacheSize <= 0) {
            cout << RED << "  Please enter a positive integer.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cacheSize = 0;
        }
    }
    cin.ignore();   // discard trailing newline after integer input

    LRUCacheSimulator sim(cacheSize);

    int choice;
    bool running = true;

    while (running) {
        displayMenu(cacheSize);

        // Safely read integer choice; reject non-numeric input
        if (!(cin >> choice)) {
            cout << RED << "  Invalid input. Please enter a number (0-5).\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();   // clear newline before any getline calls below

        switch (choice) {
            case 1: {
                // Single page access
                printHeader("ACCESS PAGE");
                int page;
                cout << YELLOW << "  Enter page number : " << RESET;
                if (!(cin >> page)) {
                    cout << RED << "  Invalid page number.\n" << RESET;
                    cin.clear();
                }
                cin.ignore();
                sim.accessPage(page);
                break;
            }
            case 2:
                // Batch access — reads a line of space-separated page numbers
                sim.runBatch();
                break;

            case 3:
                // Show current stack state
                printHeader("CACHE DISPLAY");
                sim.displayCache();
                break;

            case 4:
                // Print hit/miss/ratio stats
                sim.showStatistics();
                break;

            case 5:
                // Wipe cache clean — optionally let user resize
                printHeader("CLEAR CACHE");
                sim.clearCache();
                break;

            case 0:
                cout << "\n" << YELLOW << BOLD;
                cout << "  ╔══════════════════════════════════════════╗\n";
                cout << "  ║  Thank you for using LRU Cache Simulator ║\n";
                cout << "  ║  Vardhaman College of Engineering, CSE   ║\n";
                cout << "  ╚══════════════════════════════════════════╝\n";
                cout << RESET << "\n";
                running = false;
                break;

            default:
                cout << RED << "\n  Invalid choice. Please select 0 to 5.\n" << RESET;
        }
    }

    return 0;
}