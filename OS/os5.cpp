#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class PageReplacement {
public:
    void FIFO(vector<int>& pages, int capacity) {
        vector<int> memory;
        int pageFaults = 0;

        cout << "FIFO Page Replacement:" << endl;
        for (int page : pages) {
            auto it = find(memory.begin(), memory.end(), page);
            if (it == memory.end()) {  
                pageFaults++;
                if (memory.size() < capacity)
                    memory.push_back(page);
                else {
                    memory.erase(memory.begin());
                    memory.push_back(page);
                }
            }
            display(memory);
        }
        cout << "Total Page Faults: " << pageFaults << endl << endl;
    }

    void LRU(vector<int>& pages, int capacity) {
        vector<int> memory;
        unordered_map<int, int> recent; 
        int pageFaults = 0;

        cout << "LRU Page Replacement:" << endl;
        for (int i = 0; i < pages.size(); i++) {
            int page = pages[i];
            if (find(memory.begin(), memory.end(), page) == memory.end()) { 
                pageFaults++;
                if (memory.size() < capacity)
                    memory.push_back(page);
                else {
                    int lruPage = memory[0], lruIndex = recent[memory[0]];
                    for (int memPage : memory) {
                        if (recent[memPage] < lruIndex) {
                            lruPage = memPage;
                            lruIndex = recent[memPage];
                        }
                    }
                    memory.erase(find(memory.begin(), memory.end(), lruPage));
                    memory.push_back(page);
                }
            }
            recent[page] = i;
            display(memory);
        }
        cout << "Total Page Faults: " << pageFaults << endl << endl;
    }

    void Optimal(vector<int>& pages, int capacity) {
        vector<int> memory;
        int pageFaults = 0;

        cout << "Optimal Page Replacement:" << endl;
        for (int i = 0; i < pages.size(); i++) {
            int page = pages[i];
            if (find(memory.begin(), memory.end(), page) == memory.end()) {
                pageFaults++;
                if (memory.size() < capacity)
                    memory.push_back(page);
                else {
                    int farthest = -1, replaceIndex = -1;
                    for (int j = 0; j < memory.size(); j++) {
                        int memPage = memory[j];
                        int nextUse = find(pages.begin() + i + 1, pages.end(), memPage) - pages.begin();
                        if (nextUse > farthest || nextUse == pages.size()) {
                            farthest = nextUse;
                            replaceIndex = j;
                        }
                    }
                    memory[replaceIndex] = page;
                }
            }
            display(memory);
        }
        cout << "Total Page Faults: " << pageFaults << endl << endl;
    }

private:
    void display(vector<int>& memory) {
        for (int page : memory)
            cout << page << " ";
        cout << endl;
    }
};

int main() {
    int capacity;
    cout << "Enter memory capacity (number of frames): ";
    cin >> capacity;

    int n;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page sequence: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    PageReplacement pr;
    pr.FIFO(pages, capacity);
    pr.LRU(pages, capacity);
    pr.Optimal(pages, capacity);

    return 0;
}
