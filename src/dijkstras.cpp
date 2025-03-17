#include "dijkstras.h"
#include <algorithm> 

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> dist(G.numVertices, INF);
    previous.resize(G.numVertices, -1);
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (dist_u > dist[u]) continue;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
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
    
    set<int> visited;
    
    for (int v = destination; v != -1; v = previous[v]) {
        if (visited.find(v) != visited.end()) {
            return vector<int>();
        }
        visited.insert(v);
        path.push_back(v);
        
        if (previous[v] >= static_cast<int>(previous.size())) {
            return vector<int>();
        }
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