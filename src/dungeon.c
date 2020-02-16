
#include "dungeon.h"
#include "room.h"
#include "bmp.h"

void dungeon_init(struct dungeon* d, int w, int h) {
  d->w = w;
  d->h = h;
  d->world = (int**)malloc(w * sizeof(int*));
  int i;
  for (i = 0; i < w; i++) {
    d->world[i] = (int*)malloc(h * sizeof(int));
  }
  dungeon_clear(d);
}

void dungeon_clear(struct dungeon* d) {
  int x, y;
  for (y = 0; y < d->h; y++) {
    for (x = 0; x < d->w; x++) {
      d->world[x][y] = 0;
    }
  }
}

void dungeon_print(struct dungeon* d) {
  int x, y;
  for (y = 0; y < d->h; y++) {
    for (x = 0; x < d->w; x++) {
      printf("%c", d->world[x][y] + 32);
    }
    printf("\n");
  }
}

int dungeon_place_room(struct dungeon* d, struct room* r, int c) {
  if (!room_check_dungeon(r, d)) {
    int x, y;
    for (x = r->x; x < r->x + r->w; x++) {
      for (y = r->y; y < r->y + r->h; y++) {
        d->world[x][y] = c;
      }
    }
    return 0;
  } else {
    return 1;
  }
}

struct simple_image* dungeon_to_im(struct dungeon* d) {
  struct simple_image* si = malloc(sizeof(struct simple_image));
  simple_image_init(si, d->w * 8, d->h * 8);
  int x, y;
  for (x = 0; x < d->w; x++) {
    for (y = 0; y < d->h; y++) {
      int i, j;
      for (i = 8 * x; i < 8 * (x + 1); i++) {
        for (j = 8 * y; j < 8 * (y + 1); j++) {
          si->d[i + (d->w * 8) * j] = (struct rgba){.r = 0xFF * d->world[x][y], .g = 0xFF, .b = 0xFF, .a = 0xFF};
        }
      }
    }
  }
  return si;
}