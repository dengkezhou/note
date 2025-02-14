int console_puts(const char *str) { return 0; }

int console_getc(void) { return 0; }

int console_putc(const char c) {
  //   printUartPutchar(c);
  return c;
}

int console_tstc(void) { return 0; }

void init_core(void) {}