#include "BaseGraphicsScene.h"

BaseGraphicsScene::~BaseGraphicsScene()
{
   for (auto iterator = _shaders.begin(); iterator != _shaders.end(); iterator++) {
      delete iterator->second;
      _shaders.erase(iterator);
   }
   _shaders.clear();

   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      delete iterator->second;
      _objects.erase(iterator);
   }
   _objects.clear();
}

void BaseGraphicsScene::Render()
{
   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      iterator->second->Render();
   }
}
