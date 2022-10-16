// Route Between Nodes: Given a directed graph, design an algorithm to find out
// whether there is a route between two nodes.

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

bool IsThereRoute(const std::map<int64_t, std::vector<int64_t>> &graph,
                  const int64_t start, const int64_t end) {
  std::list<int64_t> to_visit;
  std::set<int64_t> visited;

  to_visit.push_back(start);
  while (!to_visit.empty()) {
    const auto current_node = to_visit.front();
    visited.insert(current_node);
    to_visit.pop_front();
    if (current_node == end) {
      return true;
    }
    if (graph.contains(current_node)) {
      for (const auto elem : graph.at(current_node)) {
        if (!visited.contains(elem)) {
          to_visit.push_back(elem);
        }
      }
    }
  }

  return false;
}

int main() {
  std::map<int64_t, std::vector<int64_t>> graph{
      {0, {1, 2, 3}}, {1, {2, 4}}, {2, {1, 4, 5}}, {3, {6}}, {4, {7}},
  };

  std::cout << "Route between: " << 0 << " and " << 7 << ": "
            << static_cast<int64_t>(IsThereRoute(graph, 0, 7)) << std::endl;
  std::cout << "Route between: " << 4 << " and " << 1 << ": "
            << static_cast<int64_t>(IsThereRoute(graph, 4, 1)) << std::endl;
  return 0;
}