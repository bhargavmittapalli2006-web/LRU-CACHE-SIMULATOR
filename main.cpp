#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
using namespace std;
class LRUCacheSimulator {
private:
    stack<int> cache;
    int cacheSize;
    int currentSize;
    int hits;
    int misses;
 // Check if page exists in cache
    bool isPresent(int page) {
        stack<int> temp = cache;
         while (!temp.empty()) {
            if (temp.top() == page) {
                return true;
            }
            temp.pop();
        }
          return false;
    }
// Remove a page from stack
    void removePage(int page) {
        stack<int> temp;
    while (!cache.empty()) {
            if (cache.top() != page) {
                temp.push(cache.top());
            }
            cache.pop();
        }
    while (!temp.empty()) {
            cache.push(temp.top());
            temp.pop();
        }
    }
// Remove least recently used page (bottom element)
    void removeLRU() {
        stack<int> temp;
  // Move elements except bottom one
        while (cache.size()>1) {
            temp.push(cache.top());
            cache.pop();
        }
    cout << "\nLeast Recently Used Page Removed : " << cache.top() << endl;
        cache.pop();
    while (!temp.empty()) {
            cache.push(temp.top());
            temp.pop();
        }
        currentSize--;
    }
public:
    LRUCacheSimulator(int size) {
        cacheSize = size;
        currentSize = 0;
        hits = 0;
        misses = 0;
    }
 // Access a page
    void accessPage(int page) {
        cout << "\n======================================" << endl;
        cout << "Accessing Page : " << page << endl;
        cout << "======================================" << endl;
    if (isPresent(page)) {
            hits++;
            cout << "Result : CACHE HIT" << endl;
            cout << "Page already exists in cache." << endl;
            removePage(page);
            cache.push(page);
        }
        else {
            misses++;
            cout << "Result : CACHE MISS" << endl;
            cout << "Page not found in cache." << endl;
          if (currentSize == cacheSize) {
                removeLRU();
            }
            cache.push(page);
            currentSize++;
        }
          displayCache();
    }
// Display cache contents
    void displayCache() {
        cout << "\nCurrent Cache Status" << endl;
        cout << "------------------------" << endl;
        if (cache.empty()) {
            cout << "Cache is Empty" << endl;
            return;
        }
        stack<int> temp = cache;
        vector<int> elements;
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        cout << "Most Recently Used" << endl;
        cout << "        TOP" << endl;
        cout << "         |" << endl;
        for (int i = 0; i < elements.size(); i++) {
            cout << "        [ " << elements[i] << " ]" << endl;
        }
        cout << "         |" << endl;
        cout << "Least Recently Used" << endl;
    }
    // Display statistics
    void showStatistics() {
        cout << "\n======================================" << endl;
        cout << "        CACHE STATISTICS" << endl;
        cout << "======================================" << endl;
        cout << "Total Cache Hits   : " << hits << endl;
        cout << "Total Cache Misses : " << misses << endl;
       int total = hits + misses;
       cout << "Total Requests     : " << total << endl;
        if (total > 0) {
            double hitRatio = (double)hits / total;
            cout << fixed << setprecision(2);
            cout << "Hit Ratio          : " << hitRatio << endl;
        }
        else {
            cout << "Hit Ratio          : 0" << endl;
        }
    }
};

int main() {
    int cacheSize;
    cout << "==========================================" << endl;
    cout << "       LRU CACHE SIMULATOR" << endl;
    cout << "==========================================" << endl;
    cout << "\nEnter Cache Size : ";
    cin >> cacheSize;
    LRUCacheSimulator simulator(cacheSize);
   int choice;
do {
        cout << "\n==========================================" << endl;
        cout << "                MAIN MENU" << endl;
        cout << "==========================================" << endl;
        cout << "1. Access a Page" << endl;
        cout << "2. Display Cache" << endl;
        cout << "3. Show Statistics" << endl;
        cout << "4. Exit Program" << endl;
        cout << "==========================================" << endl;
        cout << "\nEnter Your Choice : ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int page;
            cout << "\nEnter Page Number : ";
            cin >> page;
            simulator.accessPage(page);
            break;
        }

        case 2:
            simulator.displayCache();
            break;
        case 3:
            simulator.showStatistics();
            break;
        case 4:
            cout << "\n==========================================" << endl;
            cout << "Thank You for Using LRU Cache Simulator" << endl;
            cout << "Program Closed Successfully" << endl;
            cout << "==========================================" << endl;
            break;
       default:
            cout << "\nInvalid Choice! Please Try Again." << endl;
        }
        } while (choice != 4);

    return 0;}
