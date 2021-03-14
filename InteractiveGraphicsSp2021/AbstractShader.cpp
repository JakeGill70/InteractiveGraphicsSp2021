#include "AbstractShader.h"

void AbstractShader::AddObjectToRender(const string& objectName, GraphicsObject* object)
{
   _objectsToRender[objectName] = object;
   vector<AbstractMesh*> meshes = _objectsToRender[objectName]->GetMeshes();
   AbstractMesh* mesh;
   for (auto it = meshes.begin(); it != meshes.end(); it++) {
      mesh = *it;
      mesh->SetBufferId(GenerateBuffer());
      if (mesh->IsIndexed()) {
         mesh->SetIndexedBufferId(GenerateBuffer());
      }
   }
}
