#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    lzo_byte inbuf[8192];
    lzo_byte outbuf[MAX_OUT_LEN(sizeof(inbuf))];
    lzo_byte wrkmem[WRKMEM_SIZE];
    lzo_uint inlen, outlen;

#ifndef COMPRESSOR
# error "-DCOMPRESSOR=1 for compressor, 0 for decompressor"
#endif

    if (argc != 1) {
#if COMPRESSOR
        dprintf(2, "usage: cat file | " ALGO_NAME " > file." ALGO_NAME "\n");
        dprintf(2, "I take no argument. Please feed me data through stdin.\n");
        dprintf(2, "Then I will emit compressed data to stdout.\n");
#else
        dprintf(2, "usage: cat file." ALGO_NAME " | " ALGO_NAME "d > file\n");
        dprintf(2, "I take no argument. Please feed me data through stdin.\n");
        dprintf(2, "Then I will emit decompressed data to stdout.\n");
#endif
        return -1;
    }

    assert(lzo_init() == LZO_E_OK);

    int ret;
#if COMPRESSOR
    while ((inlen = read(0, inbuf, sizeof(inbuf))) > 0) {
        ret = COMPRESS_FUNC(inbuf, inlen, outbuf, &outlen, wrkmem);
        assert(ret == LZO_E_OK);
        ret = write(1, &outlen, sizeof(outlen));
        assert(ret == sizeof(outlen));
        ret = write(1, outbuf, outlen);
        assert(ret == outlen);
    }
    assert(inlen == 0);
#else
    while ((ret = read(0, &outlen, sizeof(outlen))) > 0) {
        int nr = 0;
        while (nr != outlen) {
            ret = read(0, outbuf+nr, outlen-nr);
            assert(ret > 0);
            nr += ret;
        }
        ret = DECOMPRESS_FUNC(outbuf, outlen, inbuf, &inlen, NULL);
        assert(ret == LZO_E_OK);
        ret = write(1, inbuf, inlen);
        assert(ret == inlen);
    }
    assert(ret == 0);
#endif
}
