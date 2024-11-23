#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data type

void DFSRec(vector<vector<Pair>>&, vector<bool>&, int);
void DFS(vector<vector<Pair>>&, int);
void bfs(vector<vector<Pair>>&, int);

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    cout << "DFS starting from vertex 0:" << endl;
    DFS(graph.adjList, 0);
    cout << endl << "BFS starting from vertex 0:" << endl;
    bfs(graph.adjList, 0);

    return 0;
}

// Recursive function for DFS traversal
void DFSRec(vector<vector<Pair>> &adj, vector<bool> &visited, int s){
  
    visited[s] = true;

    // Print the current vertex
    cout << s << " ";

    // Recursively visit all adjacent vertices
    // that are not visited yet
    for (Pair i : adj[s])
        if (visited[i.first] == false)
            DFSRec(adj, visited, i.first);
}

// Main DFS function that initializes the visited array
// and call DFSRec
void DFS(vector<vector<Pair>> &adj, int s){
    vector<bool> visited(adj.size(), false);
    DFSRec(adj, visited, s);
}

void bfs(vector<vector<Pair>>& adj, int s) 
{
    // Create a queue for BFS
    queue<int> q;  
    
    // Initially mark all the vertices as not visited
    // When we push a vertex into the q, we mark it as 
    // visited
    vector<bool> visited(adj.size(), false);

    // Mark the source node as visited and 
    // enqueue it
    visited[s] = true;
    q.push(s);

    // Iterate over the queue
    while (!q.empty()) {
      
        // Dequeue a vertex from queue and print it
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        // Get all adjacent vertices of the dequeued 
        // vertex curr If an adjacent has not been 
        // visited, mark it visited and enqueue it
        for (Pair x : adj[curr]) {
            if (!visited[x.first]) {
                visited[x.first] = true;
                q.push(x.first);
            }
        }
    }
}