#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to, weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

struct CompareEdge {
    bool operator()(Edge const& e1, Edge const& e2) {
        return e1.weight > e2.weight;
    }
};

class Graph {
public:
    int n;
    vector<vector<Edge>> adjList;

    Graph(int n) {
        this->n = n;
        adjList.resize(n);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(Edge(v, weight));
        adjList[v].push_back(Edge(u, weight));
    }

    int primMST() {
        vector<bool> inMST(n, false);
        vector<int> minWeight(n, INT_MAX);
        minWeight[0] = 0;
        int totalCost = 0;

        priority_queue<Edge, vector<Edge>, CompareEdge> pq; 
        pq.push(Edge(0, 0));

        while (!pq.empty()) {
            Edge current = pq.top();
            pq.pop();

            int u = current.to;

            if (inMST[u]) continue;

            inMST[u] = true;
            totalCost += current.weight;

            for (Edge& neighbor : adjList[u]) {
                int v = neighbor.to;
                int weight = neighbor.weight;

                if (!inMST[v] && weight < minWeight[v]) {
                    minWeight[v] = weight;
                    pq.push(Edge(v, weight));
                }
            }
        }

        return totalCost;
    }
};

int main() {
    int n = 4;
    Graph g(n);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    int result = g.primMST();
    
    cout << "Minimum cost to connect all offices: " << result << endl;

    return 0;
}
