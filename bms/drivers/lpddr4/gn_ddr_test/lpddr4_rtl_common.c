#include "../lpddr4_common.h"
#include "lpddr4_cfg.h"

float clk_max(float ns,float nclk){
    float max;
    max= ns > nclk ? ns : nclk;
    return max;
}

float clk_min(float ns,float nclk){
    float min;
    min= ns < nclk ? ns : nclk;
    return min;
}