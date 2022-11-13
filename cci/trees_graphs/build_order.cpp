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
// In order words to make `d` you have to make `a`

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <map>
#include <vector>

#include "cci/utils.hpp"

// Handles cyclic graphs as well
std::vector<char> GetBuildOrder2(
    std::vector<char> projects,
    std::vector<std::array<char, 2>> &dependencies) {
  // Build deps graph
  // Graph is built in a wat project -> [dep]
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

  // Topological sort - Kahn algo
  std::vector<char> vertices_without_deps;
  const auto fill_vertices_without_deps = [&vertices_without_deps, &projects,
                                           &graph] {
    for (const auto project : projects) {
      if (!graph.contains(project)) {
        vertices_without_deps.push_back(project);
      }
    }
  };
  fill_vertices_without_deps();

  std::vector<char> order;
  order.reserve(projects.size());
  while (!vertices_without_deps.empty()) {
    const auto project = vertices_without_deps.front();
    vertices_without_deps.erase(vertices_without_deps.begin());
    order.push_back(project);
    for (auto it = graph.begin(); it != graph.end(); ++it) {
      if (auto found_dep = std::ranges::find(it->second, project);
          found_dep != it->second.end()) {
        it->second.erase(found_dep);
        if (it->second.empty()) {
          vertices_without_deps.push_back(it->first);
        }
      }
    }
  }

  if (order.size() == projects.size()) {
    return order;
  }
  return {};
}

// Does not handle cyclic graphs
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

  auto unfinished_projects = projects;
  std::vector<char> order;
  // order.reserve(projects.size());
  // Repeat until all projects are finished
  auto current_project_iterator{unfinished_projects.begin()};
  while (!unfinished_projects.empty()) {
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

  std::vector<std::array<char, 2>> dependencies_cycle{
      {'a', 'd'}, {'f', 'b'}, {'b', 'd'}, {'f', 'a'}, {'d', 'c'}, {'a', 'f'}};

  auto order = GetBuildOrder(projects, dependencies);
  PrintContainer(order);
  auto order2 = GetBuildOrder2(projects, dependencies);
  PrintContainer(order2);
  auto order3 = GetBuildOrder2(projects, dependencies_cycle);
  PrintContainer(order3);
  return 0;
}
