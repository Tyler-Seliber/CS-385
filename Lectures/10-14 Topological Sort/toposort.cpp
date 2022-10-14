#include <iostream>
#include <vector>
#include <algorithm> // For the fill function.
#include <queue>

using namespace std;

// The graph argument really is a pointer to the array, but we can use
// it as if it were the array itself.
vector<int> toposort(vector<int> graph[], int V) {
    // The indegree of each vertex, stored as a dynamic array of ints
    int *indegree = new int[V];
    // Initialize indegree to all zeroes:
    fill(indegree, indegree + V, 0);

    // Compute the indegree of each vertex.
    // We loop over every vertex v1 in the graph: (v1 is the source of each edge)
    // these two loops together run E times
    for (int v1 = 0; v1 < V; v1++) { // V is size of array
        // then loop over every edge <v1, v2>:
        for (int v2: graph[v1]) {
            // and increase the corresponding indegree of v2:
            indegree[v2]++;
        }
        // Another way to do the same thing (note the use of size_t
        // for the loop index because that's the return type of the
        // size() method for a vector):
        //for(size_t j = 0; j < graph[v1].size(); j++) {
        //    int v2 = graph[v1][j];
        //    indegree[v2]++;
        //}
    }

    // Initialize the set S (using a queue): it will contain all vertices with indegree of 0
    queue<int> S;
    // fill S with all vertices with indegree of 0
    for (int vertex = 0; vertex < V; vertex++) {
        if (indegree[vertex] == 0) {
            S.push(vertex);
        }
    }

    // Initialize the list L to be empty: (stores the result of topological sort)
    vector<int> L;
    // and run the topological sort algorithm (Khan's algorithm):
    while (!S.empty()) { // as long as queue isn't empty
        int vertex = S.front(); // For queue. - gets first element in the queue, but doesn't remove it
        //int vertex = S.top(); // For priority queue.
        S.pop(); // pop doesn't return anything, which is why it's separate
        L.push_back(vertex);
        // loop over all neighbors of vertex, simulate removing it from the graph
        for (int adjacent: graph[vertex]) {
            // reduce that neighbor's indegree, simulating removing the edge
            indegree[adjacent]--;
            // if that neighbor's indegree is now 0, add it to S
            if (indegree[adjacent] == 0) {
                S.push(adjacent);
            }
        }
    }

    // Check for a cycle in the graph: (make sure every indegree is 0)
    // (could also compare length of L (L.length(), make sure it's equal to V)
    for (int vertex = 0; vertex < V; vertex++) {
        if (indegree[vertex] > 0) {
            // There is a cycle so whatever is in L is useless, so
            // clear L.
            L.clear();
            break;
        }
    }

    // Clean up the memory we allocated:
    delete[] indegree;
    return L;
}

/* The expected input format is:
 *
 * number_of_vertices number_of_edges
 *
 * on the first input line, followed by one line for each edge with
 * the following format for each line:
 *
 * source_vertex destination_vertex
 *
 * Vertex numbers start at zero (to keep things simple).
 */
int main() {
    int V; // Number of vertices.
    int E; // Number of edges.
    cin >> V >> E; // input automatically handled

    // Make an adjacency list in a simple, straightforward manner: an
    // array of vectors of integers.
    // adjacency list is smaller and faster for a graph that isn't dense.
    // instead of using a linked list, will implement it using vectors -> a dynamic array of vectors
    vector<int> *graph = new vector<int>[V];
    // ^ an array of V elements where each element is a vector of integers

    // For each edge e = <v1, v2>, we insert v2 into graph[v1].
    // an edge is a pair of vertices, where v1 is source and v2 is destination
    while (E--) { // while E is not 0
        // read two numbers from input
        int v1, v2;
        cin >> v1 >> v2;
        // insert the edge into the graph
        graph[v1].push_back(v2);
    }
    // To keep things simple we assume that the edges are listed in
    // the input by increasing v2 (for a given v1), otherwise we would
    // have to sort here each vector one by one after reading the whole
    // input and before calling the toposort function.
    // Whether we sort or not, we still get a correct topological
    // order as result, but if we want to get the same result as in the
    // lecture notes then we need to sort if we cannot guarantee
    // that the input is already sorted in the right way.

    // so here you would loop over every vector and sort them in increasing one by one to get the output we want for this class. we can use quick sort

    vector<int> order = toposort(graph, V);

//    if (order.size() > 0) {
////        for (int vertex: order) {
////            cout << vertex << " ";
////        }
////        cout << endl;
////    } else {
////        cout << "toposort failed" << endl;
////    }

    if (order.empty()) {
        cout << "failed" << endl;
    } else {
        for (int v: order) {
            cout << v << " ";
        }
        cout << endl;
    }

    // remember to delete the graph to prevent memory leak
    delete[] graph;
    return 0;
}
