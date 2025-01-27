#include "structs.pb.h"
#include "input.h"

typedef struct App {
    RodGroup rodGroup;
    int selectedRodId;
    InputProvider inputProvider;
    Vector2 selectionOffset;
    bool collided;
} App;

void UpdateApp(App *me);