#include <common.h>
#include "image.c"

#define IMAGE_START_ADDR 0x20
#define IMAGE_DEST_ADDR  0x10000000

struct bms_image_head_s {
  uint64_t main_data_size;
  uint64_t image_start_addr;
  uintptr_t image_dest_addr;
  uint64_t nand_page_size;
};

struct bms_image_s {
  uint32_t image_length;
  uint8_t *image_ptr;
};

struct bms_image_head_s bms_image_head;
struct bms_image_s bms_image;

int bms_image_init() {
  bms_image.image_ptr    = bms_image_arr;
  bms_image.image_length = BMS_IMAGE_LENGTH; // sizeof(bms_image_arr);

  bms_image_head.main_data_size   = bms_image.image_length;
  bms_image_head.image_start_addr = IMAGE_START_ADDR;
  bms_image_head.image_dest_addr  = IMAGE_DEST_ADDR;
  bms_image_head.nand_page_size   = 0x00;
  return 0;
}