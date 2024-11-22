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
        assert(ret == outlen);
    }
    assert(inlen == 0);
#else
    while ((ret = read(0, &outlen, sizeof(outlen))) > 0) {
        for (int nr = 0; nr != outlen; nr += ret) {
            ret = read(0, outbuf+nr, outlen-nr);
            assert(ret > 0);
        }
        ret = DECOMPRESS_FUNC(outbuf, outlen, inbuf, &inlen, NULL);
        assert(ret == LZO_E_OK);
        ret = write(1, inbuf, inlen);
        assert(ret == inlen);
    }
    assert(ret == 0);
#endif
}
