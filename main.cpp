#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 9;
const string arr[9] = {"Starting Point", "Abandonded Building", "Battlefield", "Main City", "Raider Territory", "Second City", "Minefield", "Third City", "Sea"};

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data type

void DFSRec(vector<vector<Pair>>&, vector<bool>&, int);
void DFS(vector<vector<Pair>>&, int);
void bfs(vector<vector<Pair>>&, int);
void shortestPath(vector<vector<Pair>>&, int);

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
        cout << "Character Pathing Network:" << endl << "==========================" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Point " << i << " (" << arr[i] << ") connects to:" << endl;
            for (Pair v : adjList[i])
                cout << " -> Point " << v.first << " (Pacing: " << v.second << " km)" << endl;
        }
        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,6},{0,2,4},{2,3,4},{3,6,12},{2,6,4},{5,6,12},{4,5,18},{2,4,8},{2,5,10},{6,7,10},{7,8,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    cout << "Network Trace (DFS) from Point 0 (Starting Point):" << endl << "Purpose: Visit all Locations";
    cout << "==========================" << endl;
    DFS(graph.adjList, 0);
    cout << endl;
    cout << "Layer-by-Layer Network Inspect (BFS) from Point 0 (Starting Point):" << endl << "Purpose: Visit all Locations";
    cout << "==========================" << endl;
    bfs(graph.adjList, 0);
    cout << endl;

    cout << "Shortest path from node 0:" << endl;
    shortestPath(graph.adjList, 0);

    return 0;
}

// Recursive function for DFS traversal
void DFSRec(vector<vector<Pair>> &adj, vector<bool> &visited, int s){
  
    visited[s] = true;

    // Print the current vertex
    cout << "Current Position at Point " << s << " (" << arr[s] << ")" << endl;
    for (Pair v : adj[s])
    {
        if (!visited[v.first])
        {
            cout << " -> Potential move to Point " << v.first << " (" << arr[v.first] << ") - Pacing: " << v.second << " km" << endl;
        }
    }

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
        cout << "Current Position at Point " << curr << " (" << arr[curr] << ")" << endl;

        // Get all adjacent vertices of the dequeued 
        // vertex curr If an adjacent has not been 
        // visited, mark it visited and enqueue it
        for (Pair x : adj[curr]) {
            if (!visited[x.first]) {
                cout << " -> Potential move to Point " << x.first << " (" << arr[x.first] << ") - Pacing: " << x.second << " km" << endl;
                visited[x.first] = true;
                q.push(x.first);
            }
        }
    }
}

void shortestPath(vector<vector<Pair>>& adj, int s)
{
    int path;

    for (int i = 0; i < adj.size(); i++) {
            path = 0;
            
            cout << "0 -> " << i << " : ";
            for (Pair v : adj[i])
                cout << " -> Point " << v.first << " (Pacing: " << v.second << " km)" << endl;
        }
}