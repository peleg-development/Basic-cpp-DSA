#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Queue.h"

using namespace std;



class Graph {
public:
    // Data members
    unordered_map<int, unordered_set<int>> adjList; // Stores the graph as an adjacency list.

    // Constructor
    Graph() = default;

    // Destructor
    ~Graph() = default;

    // Method to add a vertex to the graph
    void addVertex(int vertex) {
            if (adjList.find(vertex) == adjList.end()) {
                    adjList[vertex];
                    return;
            }

            throw logic_error("Vertex with value already exists");

    }

    // Method to add an edge between two vertices
    void addEdge(int src, int dest) {
            if (adjList[src].find(dest) == adjList[src].end()) {
                    adjList[src].insert(dest);
                    adjList[dest].insert(src);
                    return;
            }

            throw logic_error("Vertices are already connected");

    }

    void removeVertex(int vertex) {
            if (adjList.find(vertex) == adjList.end()) {
                throw logic_error("Vertex not found in the graph");
            }

            for (int neighbor : adjList[vertex]) {
                adjList[neighbor].erase(vertex);
            }

            adjList.erase(vertex);
    }


    void removeEdge(int src, int dest) {
            if (adjList[src].find(dest) != adjList[src].end()) {
                    adjList[src].erase(dest);
                    adjList[dest].erase(src);
                    return;
            }

            throw logic_error("Edges arent connected");
    }

    // Method to check if there is an edge between two vertices
    bool hasEdge(int src, int dest) const;

    // Method to get the neighbors of a vertex
    vector<int> getNeighbors(int vertex) const;

    void printGraph() {
        for (const auto& kvPair : adjList) {
            cout << kvPair.first << ": [ ";

            for (const auto& edge : kvPair.second) {
                cout << edge << " ";
            }

            cout << "]" << endl;
        }
    }


    // Method to perform Depth-First Search (DFS)
    void DFS(int startVertex) {

    }

    // Method to perform Breadth-First Search (BFS)
    void BFS(int startVertex) const;
};



void runTests() {
    // Test Case 1: Remove Vertex Successfully
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addVertex(3);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
        g.printGraph();
        g.removeVertex(2);
        if (g.adjList.find(2) == g.adjList.end() &&
            g.adjList[1].find(2) == g.adjList[1].end() &&
            g.adjList[3].find(2) == g.adjList[3].end()) {
            cout << "Test Case 1 Passed: Vertex 2 removed successfully." << endl;
        } else {
            cout << "Test Case 1 Failed: Vertex 2 or its references were not removed correctly." << endl;
        }
    } catch (const exception& e) {
        cout << "Test Case 1 Failed: Exception occurred - " << e.what() << endl;
    }

    // Test Case 2: Remove Nonexistent Vertex
    try {
        Graph g;
        g.removeVertex(5); // Should throw an error
        cout << "Test Case 2 Failed: No error thrown for removing nonexistent vertex." << endl;
    } catch (const logic_error& e) {
        if (string(e.what()) == "Vertex not found in the graph") {
            cout << "Test Case 2 Passed: Correctly threw exception for nonexistent vertex." << endl;
        } else {
            cout << "Test Case 2 Failed: Incorrect error message." << endl;
        }
    } catch (...) {
        cout << "Test Case 2 Failed: Unexpected exception type." << endl;
    }

    // Test Case 3: Remove Edge Successfully
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addEdge(1, 2);
        g.removeEdge(1, 2);
        if (g.adjList[1].find(2) == g.adjList[1].end() &&
            g.adjList[2].find(1) == g.adjList[2].end()) {
            cout << "Test Case 3 Passed: Edge between 1 and 2 removed successfully." << endl;
        } else {
            cout << "Test Case 3 Failed: Edge between 1 and 2 was not removed properly." << endl;
        }
    } catch (const exception& e) {
        cout << "Test Case 3 Failed: Exception occurred - " << e.what() << endl;
    }

    // Test Case 4: Remove Nonexistent Edge
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(3);
        g.removeEdge(1, 3); // Should throw an error
        cout << "Test Case 4 Failed: No error thrown for removing nonexistent edge." << endl;
    } catch (const logic_error& e) {
        if (string(e.what()) == "Edges arent connected") {
            cout << "Test Case 4 Passed: Correctly threw exception for nonexistent edge." << endl;
        } else {
            cout << "Test Case 4 Failed: Incorrect error message." << endl;
        }
    } catch (...) {
        cout << "Test Case 4 Failed: Unexpected exception type." << endl;
    }

    // Test Case 5: Add Edge After Removing a Vertex
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addEdge(1, 2);
        g.removeVertex(2);
        g.addEdge(1, 2); // This should add vertex 2 again and connect it
        if (g.adjList.find(2) != g.adjList.end() &&
            g.adjList[1].find(2) != g.adjList[1].end()) {
            cout << "Test Case 5 Passed: Edge added successfully after removing and recreating vertex." << endl;
        } else {
            cout << "Test Case 5 Failed: Vertex 2 was not properly added or connected." << endl;
        }
    } catch (const exception& e) {
        cout << "Test Case 5 Failed: Exception occurred - " << e.what() << endl;
    }
}

int main() {
    runTests();


    cout << endl;
    return 0;
}