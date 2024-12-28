#ifndef MANAGERS_HPP
#define MANAGERS_HPP

#include <typeindex>
#include <vector>
#include <iostream>

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
