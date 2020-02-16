
#include <string.h>

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

int dungeon_place_room(struct dungeon* d, struct room rc, int c) {
  if (!room_check_dungeon(&rc, d)) {
    struct room* r = malloc(sizeof(struct room));
    memcpy(r, &rc, sizeof(struct room));
    int x, y;
    for (x = r->x; x < r->x + r->w; x++) {
      for (y = r->y; y < r->y + r->h; y++) {
        d->world[x][y] = c;
        list_insert_begin(&d->list_rooms, (void*)r);
      }
    }
    return 0;
  } else {
    return 1;
  }
}

#define CELLSIZE 24
const struct rgba RED = RGBA(178, 53, 53, 0xFF);
const struct rgba BLUE = RGBA(0x00, 0x00, 0xFF, 0xFF);
const struct rgba WHITE = RGBA(171, 178, 191, 0xFF);
const struct rgba BLACK = RGBA(33, 37, 43, 0xFF);

void im_write_cell(struct simple_image* im, int x, int y, struct rgba color) {
  int i, j;
  for (i = CELLSIZE * x; i < CELLSIZE * (x + 1); i++) {
    for (j = CELLSIZE * y; j < CELLSIZE * (y + 1); j++) {
      if (i % CELLSIZE <= 0 || j % CELLSIZE <= 0) {
        im->d[i + im->w * j] = WHITE;
      } else {
        im->d[i + im->w * j] = color;
      }
    }
  }
}

struct simple_image* dungeon_to_im(struct dungeon* d) {
  struct simple_image* si = malloc(sizeof(struct simple_image));
  simple_image_init(si, d->w * CELLSIZE, d->h * CELLSIZE);
  int x, y;
  for (x = 0; x < d->w; x++) {
    for (y = 0; y < d->h; y++) {
      if (d->world[x][y]) {
        im_write_cell(si, x, y, RED);
      } else {
        im_write_cell(si, x, y, BLACK);
      }
    }
  }
  return si;
}