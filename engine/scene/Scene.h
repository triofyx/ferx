#pragma once

#include <memory>
#include <vector>
#include "Cube.h"

class Scene {
public:
  Scene()=default;
  ~Scene()=default;

  void AddCube(const std::shared_ptr<Cube>& cube);
  std::shared_ptr<Cube> GetCubeByName(const std::string& name);
  const std::vector<std::shared_ptr<Cube>>& GetCubes() const;

private:
  std::vector<std::shared_ptr<Cube>> cubes; // TODO: Change into entities
};