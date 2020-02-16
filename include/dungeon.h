
#ifndef __DUNGEON_H__
#define __DUNGEON_H__

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct dungeon {
  int w, h;
  int** world;
  struct list list_rooms;
};

void dungeon_init(struct dungeon* d, int w, int h);
void dungeon_clear(struct dungeon* d);
void dungeon_print(struct dungeon* d);
struct room;
int dungeon_place_room(struct dungeon* d, struct room* r, int c);

#endif