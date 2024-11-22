#include <lzo/lzo1x.h>

#define ALGO_NAME       "lzo1x_999"
#define MAX_OUT_LEN(t)  ((t) + ((t) / 16) + 64 + 3)
#define WRKMEM_SIZE     LZO1X_999_MEM_COMPRESS
#define COMPRESS_FUNC   lzo1x_999_compress
#define DECOMPRESS_FUNC lzo1x_decompress

#include "lzo_base.c"