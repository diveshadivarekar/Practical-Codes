#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void displayFrames(const vector<int>& frames) {
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i] == -1) {
            cout << "E ";
        } else {
            cout << frames[i] << " ";
        }
    }
    cout << endl;
}

int LRU(const vector<int>& pages, int frameSize) {
    vector<int> frames(frameSize, -1);
    unordered_map<int, int> lastUsed;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            pageFaults++;

            if (find(frames.begin(), frames.end(), -1) != frames.end()) {
                *find(frames.begin(), frames.end(), -1) = page;
            } else {
                int lruPage = frames[0], lruIndex = lastUsed[frames[0]];
                for (int j = 1; j < frames.size(); j++) {
                    if (lastUsed[frames[j]] < lruIndex) {
                        lruPage = frames[j];
                        lruIndex = lastUsed[frames[j]];
                    }
                }
                replace(frames.begin(), frames.end(), lruPage, page);
            }
        }
        lastUsed[page] = i;
        displayFrames(frames);
    }
    return pageFaults;
}

int Optimal(const vector<int>& pages, int frameSize) {
    vector<int> frames(frameSize, -1);
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            pageFaults++;
            if (find(frames.begin(), frames.end(), -1) != frames.end()) {
                *find(frames.begin(), frames.end(), -1) = page;
            } else {
                int farthest = -1, replaceIndex = -1;
                for (int j = 0; j < frames.size(); j++) {
                    int nextUse = find(pages.begin() + i + 1, pages.end(), frames[j]) - pages.begin();
                    if (nextUse > farthest || nextUse == pages.size()) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }
                frames[replaceIndex] = page;
            }
        }
        displayFrames(frames);
    }
    return pageFaults;
}

int main() {
    int frameSize, numPages;
    cout << "Enter number of frames: ";
    cin >> frameSize;
    cout << "Enter number of pages: ";
    cin >> numPages;

    vector<int> pages(numPages);
    cout << "Enter page reference sequence: ";
    for (int i = 0; i < numPages; i++) {
        cin >> pages[i];
    }

    cout << "\n--- LRU Page Replacement ---\n";
    int lruFaults = LRU(pages, frameSize);
    cout << "Total Page Faults (LRU): " << lruFaults << endl;

    cout << "\n--- Optimal Page Replacement ---\n";
    int optimalFaults = Optimal(pages, frameSize);
    cout << "Total Page Faults (Optimal): " << optimalFaults << endl;

    return 0;
}
