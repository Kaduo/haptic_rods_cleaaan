#include "structs.pb.h"
#include "physics.h"
#include "app.h"
#include "input.h"
#include "physics.h"
#include "raymath.h"

void UpdateApp(App *me) {
    PollInputProvider(&me->inputProvider);
    me->collided = false;
    Vector2 mousePosition = GetMousePositionFromProvider(&me->inputProvider);

    switch (me->inputProvider.inputState.leftMouseButtonState) {
        case LeftMouseButtonState_PRESSED:
            printf("hellow \n");
            for (int i=0; i<me->rodGroup.rods_count; i++) {
                if (CheckCollisionPointRec(mousePosition, GetRodRect(me->rodGroup.rods[i]))) {
                    printf("sdflsf\n");
                    me->selectedRodId = i;
                    me->selectionOffset = Vector2Subtract(GetTopLeft(me->rodGroup.rods[i]), mousePosition);
                    break;
                }
            }
            break;
        case LeftMouseButtonState_RELEASED:
            me->selectedRodId = -1;
            break;
        case LeftMouseButtonState_DOWN:
            if (me->selectedRodId != -1) {
                me->collided = Move(&me->rodGroup, me->selectedRodId, Vector2Add(mousePosition, me->selectionOffset));
            }
            break;
    }
}