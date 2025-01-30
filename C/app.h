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
} App;

void UpdateApp(App *me);