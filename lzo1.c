#include <lzo/lzo1.h>

#define PROG_NAME       "lzo1"
#define MAX_OUT_LEN(t)  ((t) + ((t) / 16) + 64 + 3)
#define WORKMEM_SIZE    LZO1_MEM_COMPRESS
#define COMPRESS_FUNC   lzo1_compress
#define DECOMPRESS_FUNC lzo1_decompress

#include "lzo_base.c"