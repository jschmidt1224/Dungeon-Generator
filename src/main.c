
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"
#include "dungeon.h"
#include "room.h"

int main() {
  srand(time(NULL));
  printf("Hello Level!\n");
  struct dungeon dngn;
  dungeon_init(&dngn, 150, 20);
  struct room r;
  struct room_parameters p = {{1, 1, 3, 3},
                              {dngn.w - 5, dngn.h - 3, 10, 10}};
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
    } while (dungeon_place_room(&dngn, &r, count + 48));
    attempts += i;
    count++;
    if (attempts > 10000 * goal && !j) {
      p.max.w = p.max.w / 2;
      p.max.h = p.max.h / 2;
      j = 1;
    }
    if (count >= goal || attempts >= 100000 * goal)
      break;
  }
  printf("Count: %d\nAttempts: %d\n", count, attempts);
  dungeon_print(&dngn);
  return 0;
}
