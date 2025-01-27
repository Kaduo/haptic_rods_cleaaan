#include "proto/structs.pb.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

typedef enum CollisionType
{
  NO_STRICT_COLLISION,
  FROM_LEFT,
  FROM_RIGHT,
  FROM_ABOVE,
  FROM_BELOW,
} CollisionType;


typedef struct Bound
{
  float value;
  CollisionType collisionType;
} Bound;

enum RelativeYPosition
{
  STRICTLY_ABOVE = 0x01,
  STRICTLY_BELOW = 0x02,
  JUST_ABOVE = 0x04,
  JUST_BELOW = 0x08,
  Y_ALIGNED = 0x10
};

enum RelativeXPosition
{
  STRICTLY_LEFT = 0x01,
  STRICTLY_RIGHT = 0x02,
  JUST_LEFT = 0x04,
  JUST_RIGHT = 0x08,
  X_ALIGNED = 0x10
};

Vector2 GetTopLeft(Rod rod)
{
  return (Vector2){rod.rect.x, rod.rect.y};
}

Vector2 GetBottomRight(Rod rod)
{
  return (Vector2){rod.rect.x + rod.rect.width, rod.rect.y + rod.rect.height};
}

Vector2 GetBottomLeft(Rod rod)
{
  return (Vector2){rod.rect.x, rod.rect.y + rod.rect.height};
}

Vector2 GetTopRight(Rod rod)
{
  return (Vector2){rod.rect.x + rod.rect.width, rod.rect.y};
}

float GetTop(Rod rod)
{
  return rod.rect.y;
}

void SetTop(Rod *rod, float top)
{
  rod->rect.y = top;
}

float GetBottom(Rod rod)
{
  return rod.rect.y + rod.rect.height;
}

void SetBottom(Rod *rod, float bottom)
{
  rod->rect.y = bottom - rod->rect.height;
}

float GetLeft(Rod rod)
{
  return rod.rect.x;
}

void SetLeft(Rod *rod, float left)
{
  rod->rect.x = left;
}

float GetRight(Rod rod)
{
  return rod.rect.x + rod.rect.width;
}

void SetRight(Rod *rod, float right)
{
  rod->rect.x = right - rod->rect.width;
}

void SetTopLeft(Rod *rod, Vector2 newPos)
{
  rod->rect.x = newPos.x;
  rod->rect.y = newPos.y;
}


enum RelativeYPosition RelativeYPosition(Rod rod1, Rod rod2)
{
  if (GetBottom(rod1) < GetTop(rod2))
  {
    return STRICTLY_ABOVE;
  }
  else if (GetBottom(rod1) == GetTop(rod2))
  {
    return JUST_ABOVE;
  }
  else if (GetTop(rod1) > GetBottom(rod2))
  {
    return STRICTLY_BELOW;
  }
  else if (GetTop(rod1) == GetBottom(rod2))
  {
    return JUST_BELOW;
  }
  else
  {
    return Y_ALIGNED;
  }
}

enum RelativeXPosition RelativeXPosition(Rod rod1, Rod rod2)
{
  if (GetRight(rod1) < GetLeft(rod2))
  {
    return STRICTLY_LEFT;
  }
  else if (GetRight(rod1) == GetLeft(rod2))
  {
    return JUST_LEFT;
  }
  else if (GetLeft(rod1) > GetRight(rod2))
  {
    return STRICTLY_RIGHT;
  }
  else if (GetLeft(rod1) == GetRight(rod2))
  {
    return JUST_RIGHT;
  }
  else
  {
    return X_ALIGNED;
  }
}

bool StrictlyCollide(Rod rod1, Rod rod2)
{
  return (RelativeXPosition(rod1, rod2) == X_ALIGNED) && (RelativeYPosition(rod1, rod2) == Y_ALIGNED);
}

bool SoftlyCollide(Rod rod1, Rod rod2)
{
  return (RelativeXPosition(rod1, rod2) & (X_ALIGNED | JUST_RIGHT | JUST_LEFT)) && (RelativeYPosition(rod1, rod2) & (Y_ALIGNED | JUST_ABOVE | JUST_BELOW));
}

CollisionType CheckStrictCollision(Rod rod_before, Rod rod_after, Rod other_rod)
{
  if (!StrictlyCollide(rod_after, other_rod))
  {
    return NO_STRICT_COLLISION;
  }

  switch (RelativeYPosition(rod_before, other_rod))
  {
  case JUST_ABOVE: case STRICTLY_ABOVE:
    return FROM_ABOVE;
  case JUST_BELOW: case STRICTLY_BELOW:
    return FROM_BELOW;
  default:
    break;
  }

  switch (RelativeXPosition(rod_before, other_rod))
  {
  case JUST_LEFT: case STRICTLY_LEFT:
    return FROM_LEFT;
  case JUST_RIGHT: case STRICTLY_RIGHT:
    return FROM_RIGHT;
  default:
    fprintf(stderr, "THIS HSHOLDN4T AHPPEN!\n");
    return NO_STRICT_COLLISION;
  }
}

Bound newBound(Rod boundingRod, CollisionType collisionType)
{
  float value;
  switch (collisionType)
  {
  case FROM_ABOVE:
    value = GetTop(boundingRod);
    break;
  case FROM_BELOW:
    value = GetBottom(boundingRod);
    break;

  case FROM_RIGHT:
    value = GetRight(boundingRod);
    break;

  case FROM_LEFT:
    value = GetLeft(boundingRod);
    break;

  default:
    fprintf(stderr, "SHOULDN'T HAPPEN!!\n ONLY CALL THIS FUNCTION WHEN THERE IS A COLLISION !\n");
    abort();
  }
  return (Bound){value, collisionType};
}

Rod SpeculativeMove(Rod rod, Vector2 targetTopLeft)
{
  Rod clone = rod;
  SetTopLeft(&clone, targetTopLeft);
  return clone;
}

#define BOUNDS_MAX_COUNT 22

typedef struct Bounds {
  int nbBounds;
  Bound bounds[BOUNDS_MAX_COUNT];
} Bounds;

typedef struct XYBounds {
  Bounds xBounds;
  Bounds yBounds;
} XYBounds;

void AddBound(Bounds *bounds, Bound bound) {
  bounds->bounds[bounds->nbBounds] = bound;
}

void AddYBound(XYBounds *xyBounds, Bound bound) {
  AddBound(&xyBounds->yBounds, bound);
}

void AddXBound(XYBounds *xyBounds, Bound bound) {
  AddBound(&xyBounds->xBounds, bound);
}

XYBounds GetCollisionBounds(const RodGroup *rodGroup, int movingRodId, Rod targetRod) {

  Rod movingRod = rodGroup->rods[movingRodId];

  XYBounds xyBounds = {0};
  for (int i = 0; i < rodGroup->rods_count; i++)
  {

    if (i == movingRodId) {
      continue;
    }
    Rod otherRod = rodGroup->rods[i];
    CollisionType collisionType = CheckStrictCollision(movingRod, targetRod, otherRod);

    if (collisionType != NO_STRICT_COLLISION)
    {
      if (collisionType == FROM_ABOVE || collisionType == FROM_BELOW)
      {
        AddYBound(&xyBounds, newBound(otherRod, collisionType));
      }
      else
      {
        AddXBound(&xyBounds, newBound(otherRod, collisionType));
      }
    }
  }
  AddYBound(&xyBounds, (Bound){.value =  GetBottom(targetRod), FROM_ABOVE});
  AddXBound(&xyBounds, (Bound){.value =  GetRight(targetRod), FROM_LEFT});
  AddYBound(&xyBounds,(Bound){.value =  GetBottom(movingRod), FROM_ABOVE});
  AddXBound(&xyBounds,(Bound){.value =  GetRight(movingRod), FROM_LEFT});

  return xyBounds;
}

// Returns true if there was a collision
bool Move(RodGroup *rodGroup, int movingRodId, Vector2 targetTopLeft)
{
  Rod movingRod = rodGroup->rods[movingRodId];
  Rod targetRod = SpeculativeMove(movingRod, targetTopLeft);

  XYBounds xyBounds = GetCollisionBounds(rodGroup, movingRodId, targetRod);

  if (xyBounds.xBounds.nbBounds <= 1 && xyBounds.yBounds.nbBounds <= 1)
  {
    return false;
  }

  Rod candidateRod = rodGroup->rods[movingRodId];
  Rod bestRod = candidateRod;
  float bestDist = Vector2DistanceSqr(GetTopLeft(targetRod), GetTopLeft(candidateRod));
  for (int ix = 0; ix < xyBounds.xBounds.nbBounds; ix++)
  {
    for (int iy = 0; iy < xyBounds.yBounds.nbBounds; iy++)
    {
      Bound yBound = xyBounds.yBounds.bounds[iy];
      Bound xBound = xyBounds.yBounds.bounds[ix];
      if (yBound.collisionType == FROM_ABOVE)
      {
        SetBottom(&candidateRod, yBound.value);
      }
      else
      {
        SetTop(&candidateRod, yBound.value);
      }

      if (xBound.collisionType == FROM_LEFT)
      {
        SetRight(&candidateRod, xBound.value);
      }
      else
      {
        SetLeft(&candidateRod, xBound.value);
      }

      float candidateDist = Vector2DistanceSqr(GetTopLeft(targetRod), GetTopLeft(candidateRod));

      if (candidateDist < bestDist)
      {
        bool noCollision = true;
        for (int i = 0; i < rodGroup->rods_count; i++)
        {
          if (i != movingRodId) {
            Rod otherRod = rodGroup->rods[i];
            if (StrictlyCollide(otherRod, candidateRod))
            {
              noCollision = false;
              break;
            }
          }
        }
        if (noCollision)
        {
          bestDist = candidateDist;
          bestRod = candidateRod;
        }
      }
    }
  }
  SetTopLeft(&rodGroup->rods[movingRodId], GetTopLeft(bestRod));
  return true;
}


