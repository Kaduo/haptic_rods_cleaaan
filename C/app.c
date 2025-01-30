#include "structs.pb.h"
#include "physics.h"
#include "app.h"
#include "input.h"
#include "physics.h"
#include "raymath.h"
#include "signals.h"

void UpdateApp(App *me) {
    PollInputProvider(&me->inputProvider);
    me->collided = false;
    Vector2 mousePosition = GetMousePositionFromProvider(&me->inputProvider);

    // TODO CLEAN ME UP
    switch (me->inputProvider.inputState.leftMouseButtonState) {
        case LeftMouseButtonState_PRESSED:
            for (int i=0; i<me->rodGroup.rods_count; i++) {
                if (CheckCollisionPointRec(mousePosition, GetRodRect(me->rodGroup.rods[i]))) {
                    me->selectedRodId = i;
                    me->selected = true;
                    me->selectionOffset = Vector2Subtract(GetTopLeft(me->rodGroup.rods[i]), mousePosition);
                    break;
                }
            }
            break;
        case LeftMouseButtonState_RELEASED:
            me->selected = false;
            break;
        case LeftMouseButtonState_DOWN:
            if (me->selected) {
                me->collided = Move(&me->rodGroup, me->selectedRodId, Vector2Add(mousePosition, me->selectionOffset));
            }
            break;
    }
    // SetDirection(me->signalController.fd, GetMouseAngleFromProvider(&me->inputProvider)*255/(2*314), GetMouseSpeedFromProvider(&me->inputProvider));
    if (me->selected && me->selectedRodId == 0) {
        me->angle += 10;
    }
    SetDirection(me->signalController.fd, me->angle, 0);
    UpdateSignalController(&me->signalController, me->selected, me->collided, &me->rodGroup.rods[me->selectedRodId]);
}