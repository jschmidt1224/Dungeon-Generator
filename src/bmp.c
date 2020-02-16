
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

void bmp_init(struct bmp_header* b) {
  memset(b, 0, sizeof(struct bmp_header));
  b->sig[0] = 0x42;
  b->sig[1] = 0x4D;
  b->offset[0] = 0x8A;
  b->DIB[0] = 0x7C;
  b->planes[0] = 0x01;
  b->bpp[0] = 0x20;
  b->format[0] = 0x03;
  b->h_res[0] = 0x13;
  b->h_res[1] = 0x0B;
  b->v_res[0] = 0x13;
  b->v_res[1] = 0x0B;
  b->r[2] = 0xFF;
  b->g[1] = 0xFF;
  b->b[0] = 0xFF;
  b->a[3] = 0xFF;
  b->space[0] = 0x42;
  b->space[1] = 0x47;
  b->space[2] = 0x52;
  b->space[3] = 0x73;
}

void simple_image_init(struct simple_image* si, uint32_t w, uint32_t h) {
  si->w = w;
  si->h = h;
  si->d = (struct rgba*)malloc(sizeof(struct rgba) * w * h);
  memset(si->d, 0, sizeof(struct rgba) * w * h);
  bmp_init(&si->bmp);
  uint32_t image_size = w * h * 4;
  uint32_t total_size = image_size + 0x8A;
  write_le(&si->bmp.width[0], w);
  write_le(&si->bmp.height[0], h);
  write_le(&si->bmp.tot_size[0], total_size);
  write_le(&si->bmp.im_size[0], image_size);
}

void write_le(uint8_t* p, uint32_t val) {
  *p++ = (uint8_t)(val & 0x000000FF);
  *p++ = (uint8_t)((val & 0x0000FF00) >> 8);
  *p++ = (uint8_t)((val & 0x00FF0000) >> 16);
  *p++ = (uint8_t)((val & 0xFF000000) >> 24);
}

void simple_image_write(struct simple_image* im, char* fname) {
  FILE* ptr;
  ptr = fopen(fname, "wb");
  fwrite(&im->bmp, sizeof(struct bmp_header), 1, ptr);
  fwrite(im->d, sizeof(struct rgba), im->w * im->h, ptr);
  fclose(ptr);
}

void test() {
  printf("Hello\n");
  struct simple_image im;
  simple_image_init(&im, 2, 2);
  im.d[0] = (struct rgba){.r = 0xFF, .g = 0x00, .b = 0x00, .a = 0xFF};
  im.d[1] = (struct rgba){.r = 0x00, .g = 0xFF, .b = 0x00, .a = 0xFF};
  im.d[2] = (struct rgba){.r = 0x00, .g = 0x00, .b = 0xFF, .a = 0xFF};
  im.d[3] = (struct rgba){.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF};
  FILE* ptr;
  ptr = fopen("test.bmp", "wb");
  fwrite(&im.bmp, sizeof(struct bmp_header), 1, ptr);
  fwrite(im.d, sizeof(struct rgba), im.w * im.h, ptr);
  fclose(ptr);
}