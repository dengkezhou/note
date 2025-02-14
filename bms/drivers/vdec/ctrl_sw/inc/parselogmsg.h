#include "dectypes.h"
#include "dec_log.h"
#include "vpufeature.h"

char* ParseDecPictureFormat(enum DecPictureFormat output_format);
char* ParseDecRet(enum DecRet rv);
char *ParseDWLMemType(int i);
void ParseDecInitConfig(struct DecInitConfig *cfg);
void ParseDecSequenceInfo(struct DecSequenceInfo *seq);
char* ParseDecPicAlignment(int i);
void ParseDecConfig(struct DecConfig *config);
void ParseDecInputParameters(struct DecInputParameters* param);
void ParseDecBufferInfo(struct DecBufferInfo *buf_info);
void ParseFeatureList(struct DecHwFeatures *cfg);