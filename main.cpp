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
int minDistance(int[], bool[]);

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

    //int kruskalMST();
};

// To represent Disjoint Sets 
/*
struct DisjointSets 
{ 
    int *parent, *rnk; 
    int n; 
  
    // Constructor. 
    DisjointSets(int n) 
    { 
        // Allocate memory 
        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1]; 
  
        // Initially, all vertices are in 
        // different sets and have rank 0. 
        for (int i = 0; i <= n; i++) 
        { 
            rnk[i] = 0; 
  
            //every element is parent of itself 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' 
    // Path Compression 
    int find(int u) 
    { 
        /* Make the parent of the nodes in the path 
        from u--> parent[u] point to parent[u] 
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    // Union by rank 
    void merge(int x, int y) 
    { 
        x = find(x), y = find(y); 
  
        /* Make tree with smaller height 
        a subtree of the other tree 
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
};*/

/* Functions returns weight of the MST*/
/*
int Graph::kruskalMST() 
{ 
    int mst_wt = 0; // Initialize result 
  
    // Sort edges in increasing order on basis of cost 
    //sort(adjList.begin(), adjList.end()); 
  
    // Create disjoint sets 
    DisjointSets ds(SIZE); 
  
    // Iterate through all sorted edges 
    vector<vector<Pair>>::iterator it; 
    for (it=adjList.begin(); it!=adjList.end(); it++) 
    { 
        int u = it->second.first;
        int v = it->second.second;
  
        int set_u = ds.find(u); 
        int set_v = ds.find(v); 
  
        // Check if the selected edge is creating 
        // a cycle or not (Cycle is created if u 
        // and v belong to same set) 
        if (set_u != set_v) 
        { 
            // Current edge will be in the MST 
            // so print it 
            cout << u << " - " << v << endl; 
  
            // Update MST weight 
            mst_wt += it->first; 
  
            // Merge two sets 
            ds.merge(set_u, set_v); 
        } 
    } 
  
    return mst_wt; 
}*/

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,6},{0,2,4},{2,3,4},{3,6,12},{2,6,4},{5,6,12},{4,5,18},{2,4,8},{2,5,10},{6,7,10},{7,8,5}
    };

    // Creates graph
    Graph graph(edges);

    int choice = 1;
    while (choice != 0)
    {
        do
        {
            cout << "Character Pathing Network Menu:" << endl;
            cout << "[1] Display character pathing network" << endl;
            cout << "[2] Visit all Locations (BFS)" << endl;
            cout << "[3] Visit all Locations (DFS)" << endl;
            cout << "[4] Calculate shortest paths" << endl;
            cout << "[0] Exit" << endl;
            cout << "Enter your choice:" << endl;
            cin >> choice;
        } while (choice < 0 || choice > 4);
        
        switch (choice)
        {
        case 1:
            // Prints adjacency list representation of graph
            graph.printGraph();
            break;
        case 2:
            cout << "Layer-by-Layer Network Inspect (BFS) from Point 0 (Starting Point):" << endl << "Purpose: Visit all Locations";
            cout << "==========================" << endl;
            bfs(graph.adjList, 0);
            cout << endl;
            break;
        case 3:
            cout << "Network Trace (DFS) from Point 0 (Starting Point):" << endl << "Purpose: Visit all Locations";
            cout << "==========================" << endl;
            DFS(graph.adjList, 0);
            cout << endl;
            break;
        case 4:
            cout << "Shortest path from node 0:" << endl;
            shortestPath(graph.adjList, 0);
            break;
        default:
            break;
        }
    }

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

void shortestPath(vector<vector<Pair>>& adj, int src)
{
    int dist[SIZE]; // The output array.  dist[i] will hold the
                 // shortest
    // distance from src to i

    bool sptSet[SIZE]; // sptSet[i] will be true if vertex i is
                    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized

    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < SIZE; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < SIZE - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < SIZE; v++)

            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && adj[u][v].second
                && dist[u] != INT_MAX
                && dist[u] + adj[u][v].second < dist[v])
                dist[v] = dist[u] + adj[u][v].second;
    }

    // print the constructed distance array
    for (int i = 0; i < SIZE; i++)
        cout << "0 -> " << i << " : " << dist[i] << endl;
    cout << endl;
}

int minDistance(int dist[], bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < SIZE; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}