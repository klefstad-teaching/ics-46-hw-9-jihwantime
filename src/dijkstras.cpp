#include "dijkstras.h"
#include <algorithm> 
#include <set>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> dist(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    
    dist[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (visited[u]) {
            continue;
        }
        
        visited[u] = true;
        
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                previous[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    
    if (destination < 0 || destination >= static_cast<int>(distances.size()) || 
        distances[destination] == INF) {
        return path; 
    }
    
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    
    reverse(path.begin(), path.end());
    
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (total == INF) {
        cout << "No path exists" << endl;
        return;
    }
    
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << endl;
    
    cout << "Total cost is " << total << endl;
}