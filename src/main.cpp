#include "managers.hpp"

class AudioManager : public Manager<AudioManager> {};
class InputManager : public Manager<InputManager> {};
class PhysicsManager : public Manager<PhysicsManager> {};
class RendererManager : public Manager<RendererManager> {};

int main() {
  AudioManager audio;
  InputManager input;
  PhysicsManager physics;
  RendererManager renderer;

  audio.addDependency<InputManager>();
  input.addDependency<PhysicsManager>();
  physics.addDependency<RendererManager>();

  auto managers = topologicalSort({&audio, &input, &physics, &renderer});
  for (auto& manager : managers) {
    manager->start();
  }

  for (auto it = managers.rbegin(); it != managers.rend(); ++it) {
    (*it)->shutdown();
  }
}
