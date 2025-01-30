#include "structs.pb.h"
#include "input.h"
#include "signal_fsm.h"

typedef struct App {
    RodGroup rodGroup;
    int selectedRodId;
    InputProvider inputProvider;
    Vector2 selectionOffset;
    bool collided;
    bool selected;
    SignalController signalController;
    int8_t angle;
    int16_t speed;
} App;

void UpdateApp(App *me);