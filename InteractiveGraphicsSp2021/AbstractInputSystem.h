#pragma once
#ifndef ABSTRACT_INPUT_SYSTEM
#define ABSTRACT_INPUT_SYSTEM

#include <map>
#include <string>

enum class KeyState {
   Not_Pressed, Pressed
};

class AbstractInputSystem
{
protected:
   std::map<std::string, int> _keyBindings;

public:
   virtual void RegisterKey(const std::string& key, int whichKey) {
      _keyBindings[key] = whichKey;
   }
   virtual KeyState GetKeyState(const std::string& key) = 0;
};

#endif

