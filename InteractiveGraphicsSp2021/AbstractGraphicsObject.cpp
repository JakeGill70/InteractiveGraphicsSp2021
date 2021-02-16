#include "AbstractGraphicsObject.h"
#include "AbstractRenderer.h"

void AbstractGraphicsObject::Render()
{
   _renderer->Render(this);
}
