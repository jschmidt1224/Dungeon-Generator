
#ifndef __ROOM_H__
#define __ROOM_H__

#include "dungeon.h"

struct room {
  int x, y;
  int w, h;
};

struct room_parameters {
  struct room min, max;
};

void room_random(struct room* r, struct room_parameters p);
int room_check_dungeon(struct room* r, struct dungeon* d);

#endif