#include "PlateAnimation.h"
#include "ReferenceFrame.h"
#include "GraphicsObject.h"

void PlateAnimation::Update(double elapsedSeconds) {
    if (_object == nullptr) return;

    glm::vec3 up = { 0, 1, 0 };
    glm::vec3 right = { 1, 0, 0 };
    glm::vec3 flatUp = { 0,0,1 };

    float speed = 1.0f;

    if(_state == "First Raise"){
        _raiseHeight += (float)elapsedSeconds * speed;
        _object->frame.TranslateLocal((float)elapsedSeconds * speed * flatUp);

        if (_raiseHeight >= 1) {
            _state = "First Rotation";
        }
    }

    if (_state == "First Rotation") {
        float degreesToRotate = _degreesPerSecond * (float)elapsedSeconds;
        _object->frame.RotateLocal(degreesToRotate, { 1, 0, 0 });
        _degreesRotated += degreesToRotate;

        if (_degreesRotated >= 90) {
            _state = "Move Left";
        }
    }

    if (_state == "Move Left") {
        _lateralMovement += (float)elapsedSeconds * speed;
        _object->frame.TranslateLocal((float)elapsedSeconds * speed * -right);

        if (_lateralMovement >= 1) {
            _state = "Clean Lower";
        }
    }

    if (_state == "Clean Lower") {
        _raiseHeight -= (float)elapsedSeconds * speed;
        _object->frame.TranslateLocal((float)elapsedSeconds * speed * -up);

        if (_raiseHeight <= -1) {
            _state = "Clean Wait";
        }
    }

    if (_state == "Clean Wait") {
        _waitTime -= (float)elapsedSeconds;
        if (_waitTime <= 0) {
            _waitTime = 1;
            _state = "Clean Raise";
        }
    }

    if (_state == "Clean Raise") {
        _raiseHeight += (float)elapsedSeconds * speed;
        _object->frame.TranslateLocal((float)elapsedSeconds * speed * up);

        if (_raiseHeight >= 1) {
            _state = "Move Right";
        }
    }

    if (_state == "Move Right") {
        _lateralMovement -= (float)elapsedSeconds * speed;
        _object->frame.TranslateLocal((float)elapsedSeconds * speed * right);

        if (_lateralMovement <= 0) {
            _state = "Final Rotation";
        }
    }

    if (_state == "Final Rotation") {
        float degreesToRotate = _degreesPerSecond * (float)elapsedSeconds;
        _object->frame.RotateLocal(-degreesToRotate, { 1, 0, 0 });
        _degreesRotated -= degreesToRotate;

        if (_degreesRotated <= 0) {
            _state = "Final Lower";
        }
    }

    if (_state == "Final Lower") {
        _raiseHeight -= (float)elapsedSeconds * speed;
        _object->frame.TranslateLocal((float)elapsedSeconds * speed * -flatUp);

        if (_raiseHeight <= 0.05) {
            _state = "Final Wait";
        }
    }

    if (_state == "Final Wait") {
        _waitTime -= (float)elapsedSeconds;
        if (_waitTime <= 0) {
            _waitTime = 1;
            _state = "First Raise";
            _lateralMovement = 0;
        }
    }
}