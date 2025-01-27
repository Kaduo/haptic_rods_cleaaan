#include "raylib.h"
#include "proto/structs.pb.h"

bool Move(RodGroup *rodGroup, int movingRodId, Vector2 targetTopLeft);
Rectangle GetRodRect(Rod rod);
Vector2 GetTopLeft(Rod rod);