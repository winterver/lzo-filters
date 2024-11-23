/**
 * Copyright (c) 2024 winterver
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * File              : lzo1.c
 * Author            : winterver
 * Date              : 2024.11.22
 * Last Modified Date: 2024.11.23
 * Last Modified By  : winterver
 */

#include <lzo/lzo1.h>

#define PROG_NAME       "lzo1"
#define MAX_OUT_LEN(t)  ((t) + ((t) / 16) + 64 + 3)
#define WORKMEM_SIZE    LZO1_MEM_COMPRESS
#define COMPRESS_FUNC   lzo1_compress
#define DECOMPRESS_FUNC lzo1_decompress

#include "lzo_base.c"
