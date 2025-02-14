#pragma once

struct vdec {
    const void *dec_inst;
    const void *dwl_inst;
};

#define VDEC_DEFAULT_FREQ 594000000

extern int itcs_vdec_init(int64_t freq);
