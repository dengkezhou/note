
#include <common.h>
#include <malloc.h>
#include <serial.h>
#include <version.h>
#include <asm/io.h>

extern __uint64_t __init_f_start;
extern __uint64_t __init_f_end;

void __initcall(void) {
  int len    = &__init_f_end - &__init_f_start;
  void **__f = (void **)&__init_f_start;
  void (*__the_f)(void);

  //	printf("initcall: len:%d, section:%p\n", len, __f);
  for (; len > 0; len--) {
    __the_f = *__f++;
    //		printf("initcall: exec@%p\n", __the_f);
    __the_f();
  }
}

int main(void) {
  init_core();

  /* init malloc */
  init_malloc();

  printf("\n\n");
  printf("WSS: " BMS_COMMIT_ID "\n");
  printf("WSS: " BMS_COMPILE_INFO "\n\n");

  /* call init functions */
  __initcall();

  /* enter shell */
  printf("\n\n");

  main_loop();
  /* BUG if executation pass main_loop */
  for (;;)
    ;
}
