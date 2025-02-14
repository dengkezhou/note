#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <lpddr4.h>
#include <uart.h>
#include "../lpddr4_common.h"

extern void rambuster(int port, int is_lpddr4x, uint32_t search_value, uint32_t replace_value);

static int isxdigit(int c) {
    if (c >= '0' && c <= '9') {
        return 1;
    }
    if (c >= 'a' && c <= 'f') {
        return 1;
    }
    if (c >= 'A' && c <= 'F') {
        return 1;
    }
    return 0;
}

static int atoi(char *str) {
  uint32_t result = 0;
    int i = 0;
    if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X')) {
        i += 2;
    }
    while (isxdigit(str[i])) {
        char ch = str[i];
        uint32_t value;
        if (ch >= '0' && ch <= '9') {
            value = ch - '0';
        } else if (ch >= 'a' && ch <= 'f') {
            value = 10 + (ch - 'a');
        } else if (ch >= 'A' && ch <= 'F') {
            value = 10 + (ch - 'A');
        } else {
            break;  
        }
        result = (result << 4) | value;
        i++;
    }

    return result;
}

int lpddr4_rambuster(int port, int is_lpddr4x) {
    char buf_line[256];
    uint32_t search_value = 0;
    uint32_t replace_value = 0;

    printf("Please enter the register address (hex):\n");
    readline_into_buffer("search_value:", buf_line);
    search_value = atoi(buf_line);    
    printf("-----search_value = %x\n", search_value);

    printf("Please enter the value to replace (in hexadecimal):\n");
    readline_into_buffer("replace_value:", buf_line);
    replace_value = atoi(buf_line);    
    printf("-----replace_value = %x\n", replace_value);

    rambuster(port, is_lpddr4x, search_value, replace_value);

    return 0;
}