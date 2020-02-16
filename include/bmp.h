
#ifndef __BMP_H__
#define __BMP_H__

#include <stdint.h>

struct bmp_header {
  uint8_t sig[2];
  uint8_t tot_size[4];
  uint8_t unused1[4];
  uint8_t offset[4];
  uint8_t DIB[4];
  uint8_t width[4];
  uint8_t height[4];
  uint8_t planes[2];
  uint8_t bpp[2];
  uint8_t format[4];
  uint8_t im_size[4];
  uint8_t h_res[4];
  uint8_t v_res[4];
  uint8_t c_pal[4];
  uint8_t imp[4];
  uint8_t r[4];
  uint8_t g[4];
  uint8_t b[4];
  uint8_t a[4];
  uint8_t space[4];
  uint8_t unused2[36];
  uint8_t unused3[12];
  uint8_t unknown[16];
};

struct rgba {
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t a;
};

struct simple_image {
  uint32_t w, h;
  struct bmp_header bmp;
  struct rgba* d;
};

void bmp_init(struct bmp_header* b);

void simple_image_init(struct simple_image* si, uint32_t w, uint32_t h);
void simple_image_write(struct simple_image* im, char* fname);
void write_le(uint8_t* p, uint32_t val);

void test();

#endif
