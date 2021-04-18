#pragma once
#ifndef ABSTRACT_KEY_BINDING
#define ABSTRACT_KEY_BINDING

#include "AbstractInputSystem.h"

class AbstractKeyBinding
{
protected:
   AbstractInputSystem* _inputSystem;

public:
   AbstractKeyBinding(AbstractInputSystem* inputSystem)
      : _inputSystem(inputSystem) {}

   virtual ~AbstractKeyBinding() {}

   virtual void SetBindings() = 0;
};

#endif
