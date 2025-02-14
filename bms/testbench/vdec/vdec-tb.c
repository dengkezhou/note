#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <getopt.h>

#include <vdec.h>

#define INPUT_STREAM_ADDR  (0x150000000)
#define STREAM_BUFFER_SIZE (1U << 30)
#define STREAM_FILE_SIZE   (8391) // stream_48x48_min.h264

#define OUTPUT_BUFFER_ADDR  (0x140000000)
#define OUTPUT_BUFFER_SIZE  (1U << 20)
#define OUTPUT_BUFFER_NUMS  (1)


#define EXIT_IF_CALLOC_FAIL(struct_name, name) \
  struct struct_name *name = calloc(1, sizeof(*name)); \
  if (!name) \
    goto exit;


extern int h264_test(int case_index, int frame);
extern int h265_test(int case_index, int frame);
extern int jpeg_test(int case_index, int frame);
extern int pp_test(int case_index, int frame);
extern int int_test(int case_index, int frame);
extern int jpeg_perf_test(int case_index, int frame);
extern int h264_perf_test(int case_index, int frame);
extern int h265_perf_test(int case_index, int frame);
extern void vdec_test_all(void);
extern int uni_self_test(void);
extern volatile unsigned long VC9000D_BASE;

static int atoi(char *s) {
  int i;
  int n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

static struct option long_options[] = {
    {"h264",  no_argument,       0, 'a'},
    {"h265",  no_argument,       0, 'h'},
    {"jpeg",  no_argument,       0, 'j'},
    {"pp",    no_argument,       0, 'p'},
    {"int",   no_argument,       0, 'i'},
    {"perf",  no_argument,       0, 'e'},
    {"unit",  no_argument,       0, 'u'},
    {"pp2",   no_argument,       0, 'c'},
    {"all",   no_argument,       0, 'b'},
    {"local", required_argument, 0, 'l'},
    {"frame", required_argument, 0, 'f'},
    {0, 0, 0, 0}
};

TESTBENCH_INIT_HELPER(vdec) {
  int c, ret, option_index;
  int case_index = 0, frame = 0;
  char f_h264 = 0, f_h265 = 0, f_jpeg = 0, f_pp = 0, f_int = 0, f_perf = 0, f_uni = 0;
  
  ret = itcs_vdec_init(VDEC_DEFAULT_FREQ);
  if (ret < 0)
    goto exit;

  while((c = getopt_long(argc, argv, "bl:f:ahjpieuc", long_options, &option_index)) != -1) {
    switch (c) {
    case 'l':
      case_index = atoi(optarg);
      break;
    case 'f':
      frame = atoi(optarg);
      break;
    case 'a':
      f_h264 = 1;
      break;
    case 'h':
      f_h265 = 1;
      break;
    case 'j':
      f_jpeg = 1;
      break;
    case 'p':
      f_pp = 1;
      break;
    case 'i':
      f_int = 1;
      break;
    case 'e':
      f_perf = 1;
      break;
    case 'u':
      f_uni = 1;
      break;
    case 'c':
      VC9000D_BASE = 0xc6100000;
      break;
    case 'b':
      vdec_test_all();
      break;
    default:
      break;
    }
  }

  if (f_perf) {
    if (f_h264)
      h264_perf_test(case_index, frame);
    if (f_h265)
      h265_perf_test(case_index, frame);
    if (f_jpeg)
      jpeg_perf_test(case_index, frame);
    if (f_uni)
      uni_self_test();
  } else {
    if (f_h264)
      h264_test(case_index, frame);
    if (f_h265)
      h265_test(case_index, frame);
    if (f_jpeg)
      jpeg_test(case_index, frame);
    if (f_pp)
      pp_test(case_index, frame);
    if (f_int)
      int_test(case_index, frame);
  }

  ret = 0;
exit:
  optind = 1;
  return ret;
}
