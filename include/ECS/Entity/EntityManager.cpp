#include "EntityManager.h"
#include <algorithm>
void Manager::draw()
{
    for (auto &entity : entities)
    {
        entity->draw();
    }
}
void Manager::update()
{
    for (auto &entity : entities)
        entity->update();
}
void Manager::refresh()
{
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::unique_ptr<Entity> &mEntity)
                                  {
                                      return !mEntity->isActive();
                                  }),
                   std::end(entities));
}

Entity &Manager::addEntity()
{
    Entity *entity{new Entity{}};
    std::unique_ptr<Entity> uniquePtr{entity};
    entities.emplace_back(std::move(uniquePtr));
    return *entity;
}
void Manager::eraseEntity(Entity *entity)
{
}