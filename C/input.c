#include "raylib.h"
#include "app.h"
#include "stdio.h"
#include "input.h"
#include "raymath.h"
#include "structs.pb.h"

Vector2 FromMousePosition(MousePosition mousePosition) {
    return (Vector2){mousePosition.x, mousePosition.y};
}

MousePosition FromVector2(Vector2 mousePosVector) {
    return (MousePosition){.has_x=true, .x=mousePosVector.x, .has_y=true, .y=mousePosVector.y};
}

void PollInputProvider(InputProvider *me) {
    InputState *myState = &me->inputState;
    me->oldInputState = me->inputState;
    if (me->inputHistory == NULL) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            myState->leftMouseButtonState = LeftMouseButtonState_RELEASED;
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            myState->leftMouseButtonState = LeftMouseButtonState_PRESSED;
        } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            myState->leftMouseButtonState = LeftMouseButtonState_DOWN;
        } else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
            myState->leftMouseButtonState = LeftMouseButtonState_UP;
        }
        if (myState->leftMouseButtonState == LeftMouseButtonState_PRESSED || myState->leftMouseButtonState == LeftMouseButtonState_DOWN) {
            myState->mousePosition = FromVector2(GetMousePosition());
        }
        myState->frameTime = GetFrameTime();
    } else {
        // TODO : Read from InputHistory
    }
}

Vector2 GetMouseDeltaFromProvider(const InputProvider *me) {
    return Vector2Subtract(FromMousePosition(me->inputState.mousePosition), FromMousePosition(me->oldInputState.mousePosition));
}

float GetMouseSpeedFromProvider(const InputProvider *me) {
    if (me->inputState.frameTime > 0) {
        return  Vector2Distance(FromMousePosition(me->inputState.mousePosition), FromMousePosition(me->oldInputState.mousePosition))/me->inputState.frameTime;
    } else {
        return 0;
    }
}

float GetMouseAngleFromProvider(const InputProvider *me) {
    return Vector2Angle((Vector2){1, 0}, GetMouseDeltaFromProvider(me));
}


void AddInputStateToHistory(InputState inputState, InputHistory *inputHistory) {
    inputHistory->inputStates[inputHistory->inputStates_count] = inputState;
    inputHistory->inputStates_count += 1;
}

Vector2 GetMousePositionFromProvider(const InputProvider *inputProvider) {
    return FromMousePosition(inputProvider->inputState.mousePosition);
}

// void HandleInput(App *app) {
//     if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
//         app->
//     }
// }