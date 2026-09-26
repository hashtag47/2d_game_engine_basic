#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

class MovementSystem : public System
{
public:
  MovementSystem()
  {
    // TODO:
    // RequireComponent<TranformComponent>();
    // RequireComponent<...>();
  }

  void Update()
  {
    // TODO:
    //  Loop all entities that the system is interested in
    for (auto entity : GetEntity())
    {
      // TODO: Update entity position based on its velocity
      //  every frame of the game loop
    }
  }
}
#endif