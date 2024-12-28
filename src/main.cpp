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

  audio.start();
  input.start();
  physics.start();
  renderer.start();

  audio.shutdown();
  input.shutdown();
  physics.shutdown();
  renderer.shutdown();
}
