#ifndef MANAGERS_HPP
#define MANAGERS_HPP

#include <typeindex>
#include <vector>
#include <iostream>
#include <queue>

class ManagerBase {
 public:
  virtual ~ManagerBase() = default;

  virtual std::type_index type() const = 0;

  virtual void start() = 0;
  virtual void shutdown() = 0;

  const std::vector<std::type_index>& getDependencies() const {
    return dependencies;
  }

 protected:
  std::vector<std::type_index> dependencies;
};

template <typename T>
class Manager : public ManagerBase {
 public:
  std::type_index type() const override { return typeid(T); }

  void start() override {
    std::cout << "Starting manager: " << type().name() << '\n';
  }

  void shutdown() override {
    std::cout << "Shutting down manager: " << type().name() << '\n';
  }

  template <typename Dep>
  void addDependency() {
    dependencies.push_back(std::type_index(typeid(Dep)));
  }
};

#endif

std::vector<ManagerBase*> topologicalSort(std::vector<ManagerBase*> managers) {
  std::unordered_map<std::type_index, std::vector<std::type_index>>
      adjacencyList;
  std::unordered_map<std::type_index, int> dependecyCount;

  std::unordered_map<std::type_index, ManagerBase*> managerMap;
  for (auto& manager : managers) {
    managerMap[manager->type()] = manager;
  }

  for (auto& manager : managers) {
    dependecyCount[manager->type()] = 0;
  }

  for (auto& manager : managers) {
    for (auto& dependency : manager->getDependencies()) {
      adjacencyList[dependency].push_back(manager->type());
      dependecyCount[manager->type()]++;
    }
  }

  std::queue<std::type_index> zeroDependencies;
  for (auto& kv : dependecyCount) {
    if (kv.second == 0) {
      zeroDependencies.push(kv.first);
    }
  }

  std::vector<ManagerBase*> result;
  result.reserve(managers.size());

  while (!zeroDependencies.empty()) {
    auto current = zeroDependencies.front();
    zeroDependencies.pop();
    result.push_back(managerMap[current]);

    for (auto& adjacent : adjacencyList[current]) {
      dependecyCount[adjacent]--;
      if (dependecyCount[adjacent] == 0) {
        zeroDependencies.push(adjacent);
      }
    }
  }

  if (result.size() != managers.size()) {
    throw std::runtime_error("Not a DAG");
  }

  return result;
}
