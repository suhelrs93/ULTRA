#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main() {
  // Read the Florida graph from the DIMACS file.
  vector<vector<int>> graph;
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u - 1].push_back(make_pair(v - 1, w));
  }

  // Generate 200 randomly selected source-destination pairs.
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, n - 1);
  vector<pair<int, int>> sd_pairs;
  for (int i = 0; i < 200; i++) {
    sd_pairs.push_back(make_pair(dis(gen), dis(gen)));
  }

  // Run Dijkstra's algorithm for each source-destination pair.
  double total_runtime = 0.0;
  for (auto sd_pair : sd_pairs) {
    int source = sd_pair.first;
    int destination = sd_pair.second;

    // Start timer.
    auto start = chrono::high_resolution_clock::now();

    // Run Dijkstra's algorithm.
    vector<int> distances(n, INT_MAX);
    distances[source] = 0;
    set<pair<int, int>> pq;
    pq.insert(make_pair(0, source));
    while (!pq.empty()) {
      int u = pq.begin()->second;
      pq.erase(pq.begin());

      for (auto v : graph[u]) {
        int w = v.second;
        int d = distances[u] + w;
        if (d < distances[v.first]) {
          distances[v.first] = d;
          pq.insert(make_pair(d, v.first));
        }
      }
    }

    // Stop timer.
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    total_runtime += duration.count();
  }

  // Print the total runtime.
  cout << "Total runtime in seconds for 200 random Dijkstra: " << total_runtime << endl;

  return 0;
}
