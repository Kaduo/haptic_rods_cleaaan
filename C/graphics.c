#include <raylib.h>
#include "proto/structs.pb.h"
#include "stdio.h"

Rectangle FromProtoRectangle(_Rectangle rect) {
    return (Rectangle){rect.x, rect.y, rect.width, rect.height};
}

Color FromProtoColor(_Color color) {
    return (Color){color.r, color.g, color.b, color.a};
}

void DrawRod(Rod rod) {
    DrawRectangleRec(FromProtoRectangle(rod.rect), FromProtoColor(rod.color));
}

void DrawRodGroup(RodGroup *rodGroup) {
    for (int i = 0; i<rodGroup->rods_count; i++) {
        DrawRod(rodGroup->rods[i]);
    }
}