// Build Order: You are given a list of projects and a list of dependencies
// (which is a list of pairs of projects, where the second project is dependent
// on the first project). All of a project's dependencies must be built before
// the project is. Find a build order that will allow the projects to be built.
// If there is no valid build order, return an error.
// EXAMPLE
// Input:
//     projects:  a, b, c, d, e, f
//     dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
// Output: f, e, a, b, d, c

#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <vector>

#include "cci/utils.hpp"

std::vector<char> GetBuildOrder(
    std::vector<char> &projects,
    std::vector<std::array<char, 2>> &dependencies) {
  // Build deps graph
  std::map<char, std::vector<char>> graph;
  for (const auto &project : projects) {
    std::vector<char> project_deps;
    for (const auto &dep : dependencies) {
      if (dep[1] == project) {
        project_deps.push_back(dep[0]);
      }
    }
    if (!project_deps.empty()) {
      graph[project] = std::move(project_deps);
    }
  }
  std::cout << "Graph: " << std::endl;
  for (const auto &[f, s] : graph) {
    std::cout << f << ": ";
    for (const auto elem : s) {
      std::cout << elem << ", ";
    }
    std::cout << std::endl;
  }
  auto unfinished_projects = projects;
  std::vector<char> order;
  order.reserve(projects.size());
  // Repeat until all projects are finished
  auto current_project_iterator{unfinished_projects.begin()};
  while (!unfinished_projects.empty()) {
    std::cout << "Size: " << unfinished_projects.size() << std::endl;
    if (current_project_iterator == unfinished_projects.end()) {
      current_project_iterator = unfinished_projects.begin();
    }
    if (!graph.contains(*current_project_iterator)) {
      order.push_back(*current_project_iterator);
      current_project_iterator =
          unfinished_projects.erase(current_project_iterator);
    } else if (std::all_of(graph[*current_project_iterator].begin(),
                           graph[*current_project_iterator].end(),
                           [&order](const auto dependency) {
                             return std::find(order.begin(), order.end(),
                                              dependency) != order.end();
                           })) {
      order.push_back(*current_project_iterator);
      current_project_iterator =
          unfinished_projects.erase(current_project_iterator);
    } else {
      ++current_project_iterator;
    }
  }

  return order;
}

int main() {
  std::cout << "Hello World!" << std::endl;
  std::vector<char> projects{'a', 'b', 'c', 'd', 'e', 'f'};
  std::vector<std::array<char, 2>> dependencies{
      {'a', 'd'}, {'f', 'b'}, {'b', 'd'}, {'f', 'a'}, {'d', 'c'}};

  auto order = GetBuildOrder(projects, dependencies);
  PrintContainer(order);
  return 0;
}
