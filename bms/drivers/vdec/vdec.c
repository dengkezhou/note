#include <stdint.h>
#include <config.h>
#include <initcall.h>
#include <irq.h>
#include <pads.h>
#include <vdec.h>

static bool g_inited = false;

int itcs_vdec_init(int64_t freq)
{
    if (!g_inited) {
        if (itcs_module_enable(CPU, "vdec") < 0)
            return -1;

        if (itcs_module_enable(CPU, "pp") < 0)
            return -1;
    }

    itcs_module_set_clock(CPU, "vdec", "bpll", freq, 0);

    // printf("vdec clock: %d\n", itcs_module_get_clock(CPU, "vdec"));

    g_inited = true;
    return 0;
}
