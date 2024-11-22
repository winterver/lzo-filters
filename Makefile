CC = gcc
CFLAGS = -O3 -llzo2

TARGETS = lzo1x_1 lzo1x_999

all: $(TARGETS)

%: %.c
	$(CC) $< -o $@ $(CFLAGS) -DCOMPRESSOR=1
	$(CC) $< -o $@d $(CFLAGS) -DCOMPRESSOR=0

clean:
	rm -rf $(foreach t,$(TARGETS),$(t) $(t)d) > /dev/null
