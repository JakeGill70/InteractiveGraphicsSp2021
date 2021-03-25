#include "GraphicsWindow.h"

GraphicsWindow::GraphicsWindow(int width, int height, const std::string& title)
   : _width(width), _height(height), _title(title), _showState(WindowShowState::Normal)
{
}
