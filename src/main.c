
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"
#include "dungeon.h"
#include "room.h"
#include "bmp.h"

int main() {
  srand(time(NULL));
  printf("Hello Level!\n");
  struct dungeon dngn;
  dungeon_init(&dngn, 15, 15);
  struct room r;
  struct room_parameters p = {{1, 1, 3, 3},
                              {dngn.w - 5, dngn.h - 3, 5, 5}};
  int attempts = 0, count = 0;
  int goal = 100, i = 0, j = 0;
  while (1) {
    i = 0;
    do {
      i++;
      room_random(&r, p);
      if (i > 1000) {
        count--;
        break;
      }
    } while (dungeon_place_room(&dngn, &r, count + 1));
    attempts += i;
    count++;
    if (attempts > 1000 * goal && !j) {
      p.max.w = p.min.w + 1;
      p.max.h = p.min.h + 1;
      p.min.h--;
      p.min.w--;
      printf("Count: %d\nAttempts: %d\n", count, attempts);
      j = 1;
    }
    if (count >= goal || attempts >= 100000 * goal)
      break;
  }
  printf("Count: %d\nAttempts: %d\n", count, attempts);
  struct simple_image* im = dungeon_to_im(&dngn);
  simple_image_write(im, "map.bmp");
  test();
  return 0;
}
