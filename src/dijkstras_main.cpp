#include "dijkstras.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <graph_file> <source_vertex> <destination_vertex>" << endl;
        return 1;
    }

    string filename = argv[1];
    int source = stoi(argv[2]);
    int destination = stoi(argv[3]);

    Graph G;
    try {
        file_to_graph(filename, G);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    if (source < 0 || source >= G.numVertices || destination < 0 || destination >= G.numVertices) {
        cerr << "Error: Source or destination vertex out of range" << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    
    if (distances[destination] == INF) {
        cout << "No path exists from vertex " << source << " to vertex " << destination << endl;
        return 0;
    }

    vector<int> path = extract_shortest_path(distances, previous, destination);
    print_path(path, distances[destination]);

    return 0;
}