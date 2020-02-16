
#include "dungeon.h"
#include "room.h"

void room_random(struct room* r, struct room_parameters p) {
  r->x = p.min.x + rand() % (p.max.x - p.min.x);
  r->y = p.min.y + rand() % (p.max.y - p.min.y);
  r->w = p.min.w + rand() % (p.max.w - p.min.w);
  r->h = p.min.h + rand() % (p.max.h - p.min.h);
}

int room_check_dungeon(struct room* r, struct dungeon* d) {
  int x, y;
  if (r->x + r->w >= d->w || r->y + r->h >= d->h) {
    return 1;
  } else if (r->x < 1 || r->y < 1) {
    return 1;
  }
  for (x = r->x - 1; x <= r->x + r->w; x++) {
    for (y = r->y - 1; y <= r->y + r->h; y++) {
      if (d->world[x][y]) {
        return 1;
      }
    }
  }
  return 0;
}