 #include "input.h"
 #include "physics.h"


typedef struct SelectionInfo {
    int selectedRodId;
    Vector2 selectionOffset;
} SelectionInfo;

// Returns -1 if no rod has been selected.
// int GetSelectedRodId(const RodGroup *rodGroup, const InputProvider *inputProvider) {
//     int selectedRodId = -1;
//         for (int i=0; i<rodGroup->rods_count; i++) {
//             if (CheckCollisionPointRec(GetMousePositionFromProvider(inputProvider), GetRodRect(rodGroup->rods[i]))) {
//                 selectedRodId = i;
//                 me->selected = true;
//                 me->selectionOffset = Vector2Subtract(GetTopLeft(me->rodGroup.rods[i]), mousePosition);
//                 break;
//             }
//         }
// }