#include <lzo/lzo1a.h>

#define PROG_NAME       "lzo1a_99"
#define MAX_OUT_LEN(t)  ((t) + ((t) / 16) + 64 + 3)
#define WORKMEM_SIZE    LZO1A_99_MEM_COMPRESS
#define COMPRESS_FUNC   lzo1a_99_compress
#define DECOMPRESS_FUNC lzo1a_decompress

#include "lzo_base.c"
