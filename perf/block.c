/*
 * Copyright (C) 2013 Gregor Pintar <grpintar@gmail.com>
 *
 * Permission is granted to deal in this work without any restriction,
 * including unlimited rights to use, publicly perform, publish,
 * reproduce, relicence, modify, merge, and/or distribute in any form,
 * for any purpose, with or without fee, and by any means.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind,
 * to the utmost extent permitted by applicable law. In no event
 * shall a licensor, author or contributor be held liable for any
 * issues arising in any way out of dealing in the work.
 */

/* gcc -Wall -Wextra -std=c99 -pedantic perf/block.c -Iinclude lib/libkripto.a -O2 */

#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <kripto/block/anubis.h>
#include <kripto/block/aria.h>
#include <kripto/block/blowfish.h>
#include <kripto/block/camellia.h>
#include <kripto/block/des.h>
#include <kripto/block/gost.h>
#include <kripto/block/noekeon.h>
#include <kripto/block/rc5.h>
#include <kripto/block/rc6.h>
#include <kripto/block/rijndael128.h>
#include <kripto/block/rijndael256.h>
#include <kripto/block/safer.h>
#include <kripto/block/safer_sk.h>
#include <kripto/block/seed.h>
#include <kripto/block/serpent.h>
#include <kripto/block/simon32.h>
#include <kripto/block/simon64.h>
#include <kripto/block/simon128.h>
#include <kripto/block/skipjack.h>
#include <kripto/block/speck32.h>
#include <kripto/block/speck64.h>
#include <kripto/block/speck128.h>
#include <kripto/block/threefish256.h>
#include <kripto/block/threefish512.h>
#include <kripto/block/threefish1024.h>
#include <kripto/block/twofish.h>
#include <kripto/block/xtea.h>

#ifndef CPU
#define CPU 2000
#endif

#ifndef ITER
#define ITER 1000000
#endif

#ifndef KEYSTEP
#define KEYSTEP 1
#endif

#define MAXBLOCK 255
#define MAXKEY 32

static void die(const char *str)
{
	perror(str);
	exit(-1);
}

int main(void)
{
	kripto_block *s;
	unsigned int i;
	unsigned int n;
	unsigned int cipher;
	unsigned int maxkey;
	uint8_t t[MAXBLOCK];
	const uint8_t k[MAXKEY] =
	{
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
	};
	clock_t c;
	const kripto_block_desc *ciphers[27] =
	{
		kripto_block_anubis,
		kripto_block_aria,
		kripto_block_blowfish,
		kripto_block_camellia,
		kripto_block_des,
		kripto_block_gost,
		kripto_block_noekeon,
		kripto_block_rc5,
		kripto_block_rc6,
		kripto_block_rijndael128,
		kripto_block_rijndael256,
		kripto_block_safer,
		kripto_block_safer_sk,
		kripto_block_seed,
		kripto_block_serpent,
		kripto_block_simon32,
		kripto_block_simon64,
		kripto_block_simon128,
		kripto_block_skipjack,
		kripto_block_speck32,
		kripto_block_speck64,
		kripto_block_speck128,
		kripto_block_threefish256,
		kripto_block_threefish512,
		kripto_block_threefish1024,
		kripto_block_twofish,
		kripto_block_xtea
	};

	memset(t, 0, MAXBLOCK);

	for(cipher = 0; cipher < 27; cipher++)
	{
		if(!ciphers[cipher]) continue;

		maxkey = kripto_block_maxkey(ciphers[cipher]);
		if(maxkey > MAXKEY) maxkey = MAXKEY;

		for(n = KEYSTEP; n <= maxkey; n += KEYSTEP)
		{
			s = kripto_block_create(ciphers[cipher], 0, k, n);
			if(!s) die("kripto_block_create()");

			/* setup */
			c = clock();
			for(i = 0; i < ITER; i++)
			{
				s = kripto_block_recreate(s, 0, k, n);
				if(!s) die("kripto_block_recreate()");
			}
			c = clock() - c;

			printf("%s %u-bit setup: %.1f cycles\n",
				kripto_block_name(ciphers[cipher]), n * 8,
				(float)c / (float)ITER * CPU);

			/* encrypt */
			c = clock();
			for(i = 0; i < ITER; i++)
				kripto_block_encrypt(s, t, t);
			c = clock() - c;

			printf("%s %u-bit encrypt: %.1fcb, %.1fMB/s\n",
				kripto_block_name(ciphers[cipher]), n * 8,
				(float)c / (float)(ITER * kripto_block_size(ciphers[cipher])) * CPU,
				(float)(ITER * kripto_block_size(ciphers[cipher])) / ((float)c / (float)CLOCKS_PER_SEC) / 1000000.0);

			/* decrypt */
			c = clock();
			for(i = 0; i < ITER; i++)
				kripto_block_decrypt(s, t, t);
			c = clock() - c;

			printf("%s %u-bit decrypt: %.1fcb, %.1fMB/s\n",
				kripto_block_name(ciphers[cipher]), n * 8,
				(float)c / (float)(ITER * kripto_block_size(ciphers[cipher])) * CPU,
				(float)(ITER * kripto_block_size(ciphers[cipher])) / ((float)c / (float)CLOCKS_PER_SEC) / 1000000.0);

			kripto_block_destroy(s);

			putchar('\n');
		}
	}

	return 0;
}