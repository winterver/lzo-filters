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
 * File              : lzo_base.c
 * Author            : winterver
 * Date              : 2024.11.22
 * Last Modified Date: 2024.11.23
 * Last Modified By  : winterver
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    lzo_byte inbuf[8192];
    lzo_byte outbuf[MAX_OUT_LEN(sizeof(inbuf))];
    lzo_byte workmem[WORKMEM_SIZE];
    lzo_uint inlen, outlen;

    (void)argv;
    (void)workmem;
#ifndef COMPRESSOR
# error "-DCOMPRESSOR=1 for compressor, 0 for decompressor"
#endif

    if (argc != 1) {
#if COMPRESSOR
        fprintf(stderr, "usage: cat file | %s > file.%s\n", PROG_NAME, PROG_NAME);
        fprintf(stderr, "I take no arguments. Please feed me data through stdin.\n");
        fprintf(stderr, "Then I will emit compressed data to stdout.\n");
#else
        fprintf(stderr, "usage: cat file.%s | un%s > file\n", PROG_NAME, PROG_NAME);
        fprintf(stderr, "I take no arguments. Please feed me data through stdin.\n");
        fprintf(stderr, "Then I will emit decompressed data to stdout.\n");
#endif
        return -1;
    }

    assert(lzo_init() == LZO_E_OK);

    int ret;
#if COMPRESSOR
    while ((inlen = read(0, inbuf, sizeof(inbuf))) > 0) {
        ret = COMPRESS_FUNC(inbuf, inlen, outbuf, &outlen, workmem);
        assert(ret == LZO_E_OK);
        ret = write(1, &outlen, sizeof(outlen));
        assert(ret == sizeof(outlen));
        ret = write(1, outbuf, outlen);
        assert(ret == (int)outlen);
    }
    assert(inlen == 0);
#else
    while ((ret = read(0, &outlen, sizeof(outlen))) > 0) {
        for (lzo_uint nr = 0; nr != outlen; nr += ret) {
            ret = read(0, outbuf+nr, outlen-nr);
            assert(ret > 0);
        }
        ret = DECOMPRESS_FUNC(outbuf, outlen, inbuf, &inlen, NULL);
        assert(ret == LZO_E_OK);
        ret = write(1, inbuf, inlen);
        assert(ret == (int)inlen);
    }
    assert(ret == 0);
#endif
}
