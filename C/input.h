#ifndef INPUT_INCLUDE
#define INPUT_INCLUDE

#include "stdio.h"
#include "raylib.h"
#include "structs.pb.h"

// typedef enum MouseStateLabel
// {
//   RELEASED,
//   PRESSED,
//   DOWN,
//   UP,
// } MouseStateLabel;

// typedef struct MouseState {
//     MouseStateLabel label;
//     Vector2 position;
// } MouseState;

typedef struct InputProvider {
    InputHistory *inputHistory;
    int historyId;
    InputState inputState;
    InputState oldInputState;
} InputProvider;

void PollInputProvider(InputProvider *me);
Vector2 GetMousePositionFromProvider(const InputProvider *inputProvider);
float GetMouseSpeedFromProvider(const InputProvider *me);
float GetMouseAngleFromProvider(const InputProvider *me);

#endif