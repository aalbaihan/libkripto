/*
 * Written in 2013 by Gregor Pintar <grpintar@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated
 * all copyright and related and neighboring rights to this software
 * to the public domain worldwide.
 * 
 * This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication.
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <stdint.h>
#include <stdio.h>

#include <kripto/block/rijndael256.h>

int main(void)
{
	kripto_block *s;
	unsigned int i;
	unsigned int n;
	uint8_t t[32];
	const uint8_t k[32] =
	{
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
	};
	const uint8_t pt[32] =
	{
		0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
	};
	const uint8_t ct[32][32] =
	{
		{
			0xC3, 0xC6, 0xC6, 0x4F, 0x0E, 0x8F, 0x18, 0xCC,
			0xE1, 0xC9, 0x9A, 0x57, 0x51, 0x5A, 0xFF, 0x82,
			0x14, 0x6E, 0x18, 0x7E, 0xC0, 0x7C, 0x54, 0x37,
			0x42, 0x0F, 0x3D, 0xD7, 0x9B, 0x8B, 0x54, 0x9E
		},
		{
			0x7C, 0xDE, 0xA5, 0x17, 0xB0, 0x78, 0x26, 0xF3,
			0xC3, 0x8D, 0xE6, 0x89, 0x0B, 0x25, 0x7F, 0x7B,
			0x3F, 0x7F, 0x8D, 0xE8, 0x4D, 0xD4, 0x13, 0x09,
			0x80, 0xB3, 0xA7, 0x69, 0xE9, 0xC0, 0xF7, 0xBE
		},
		{
			0x05, 0x85, 0x34, 0x8C, 0x03, 0xC0, 0xA9, 0xBA,
			0xA3, 0x95, 0x54, 0x2F, 0x1A, 0x75, 0x26, 0xEF,
			0x41, 0xB0, 0xFB, 0xA9, 0xEB, 0xB9, 0x46, 0x5F,
			0x54, 0x2C, 0x99, 0x1A, 0xFD, 0xAB, 0xE7, 0x59
		},
		{
			0xEE, 0x54, 0x90, 0x11, 0x42, 0x64, 0x12, 0xF2,
			0xDC, 0x72, 0xD0, 0xCD, 0x8A, 0x59, 0xA1, 0x03,
			0x19, 0x2F, 0x78, 0x8B, 0xFC, 0xB5, 0x05, 0x99,
			0xB5, 0x9B, 0xD6, 0x0E, 0x4F, 0x7C, 0x87, 0xD1
		},
		{
			0x06, 0xF1, 0x56, 0xF4, 0x91, 0x5D, 0x6B, 0x5F,
			0x08, 0xB1, 0xC0, 0xF8, 0xBB, 0x91, 0xE8, 0x1F,
			0xE5, 0x09, 0x3D, 0x43, 0x48, 0x2D, 0x62, 0x9E,
			0xEE, 0xA3, 0x66, 0x1D, 0x10, 0xC1, 0x85, 0x24
		},
		{
			0x32, 0x3F, 0xAD, 0x15, 0x79, 0x27, 0x6A, 0x6C,
			0x55, 0xED, 0x71, 0x62, 0x68, 0x20, 0x03, 0xD2,
			0x36, 0xF9, 0x35, 0x0C, 0x1F, 0x6D, 0xFD, 0x26,
			0xE1, 0xD7, 0xC2, 0xAD, 0x0E, 0xAB, 0x15, 0x4F
		},
		{
			0x33, 0xC2, 0x9A, 0xC7, 0x32, 0xF5, 0x51, 0x9B,
			0x98, 0x2A, 0x41, 0xFB, 0x61, 0xFA, 0xBE, 0x62,
			0xD5, 0xA6, 0x82, 0xFF, 0x1F, 0x09, 0xD7, 0x98,
			0x5D, 0x3B, 0x38, 0x44, 0x06, 0x43, 0x17, 0xD3
		},
		{
			0x8B, 0xAC, 0x6D, 0xF7, 0x4C, 0x79, 0x28, 0x78,
			0x08, 0x4B, 0x2C, 0x97, 0xBF, 0x9E, 0x71, 0x47,
			0x17, 0xBE, 0xEB, 0xB9, 0xFA, 0xCC, 0x04, 0x4B,
			0x47, 0xA8, 0x1A, 0xC0, 0xE6, 0xD6, 0xA1, 0x7D
		},
		{
			0xCB, 0x99, 0x8C, 0x9D, 0x0F, 0x3D, 0x75, 0xF1,
			0x0D, 0xFD, 0x7B, 0x2B, 0xEF, 0xFA, 0x3E, 0x1B,
			0xCB, 0x24, 0x1D, 0xBC, 0xFF, 0x2D, 0x1E, 0x09,
			0x48, 0x84, 0x0C, 0x87, 0x3D, 0x95, 0xDD, 0xA0
		},
		{
			0x6B, 0xA1, 0xC2, 0x2C, 0x4F, 0xCB, 0xB6, 0x2F,
			0x22, 0x8F, 0x03, 0x19, 0xA0, 0x6B, 0xF1, 0x00,
			0x17, 0xAC, 0x42, 0x86, 0x01, 0x07, 0x0C, 0xB9,
			0xD4, 0xB8, 0x51, 0xB2, 0x86, 0xD6, 0xDD, 0x77
		},
		{
			0xD9, 0x62, 0x37, 0xC1, 0x00, 0x60, 0x43, 0x33,
			0xF2, 0x7B, 0xE3, 0xC5, 0xF1, 0x79, 0xFE, 0x2B,
			0xDC, 0xA0, 0x14, 0x16, 0x0F, 0x43, 0x5F, 0xE1,
			0xF4, 0x57, 0x5D, 0x0D, 0xBF, 0xEA, 0xC4, 0x97
		},
		{
			0xB6, 0xD7, 0xCB, 0x95, 0x3E, 0x8D, 0xFA, 0x21,
			0xCB, 0xD0, 0xBD, 0xAE, 0x34, 0x91, 0xF7, 0x2D,
			0x4A, 0x95, 0x23, 0xE7, 0xE5, 0xBD, 0x50, 0x01,
			0x61, 0x28, 0x78, 0xC2, 0x53, 0xCE, 0xCB, 0x76
		},
		{
			0x5E, 0xFA, 0x11, 0x70, 0x1B, 0x42, 0xD3, 0x40,
			0x50, 0x8B, 0xB4, 0xED, 0xAE, 0xC1, 0x40, 0xFC,
			0x37, 0x7F, 0x7C, 0xA5, 0x03, 0x03, 0x33, 0x6D,
			0xD5, 0x3F, 0xD5, 0x6F, 0x9A, 0x43, 0xC7, 0xA4
		},
		{
			0x31, 0x4E, 0x40, 0x3C, 0xAB, 0xF0, 0x6B, 0x75,
			0x0C, 0x58, 0x9A, 0xDF, 0x35, 0xCA, 0xF0, 0x4B,
			0xFA, 0x1B, 0x9B, 0x1A, 0x6E, 0x86, 0x26, 0x37,
			0x4F, 0xE4, 0x97, 0x8F, 0x04, 0xA4, 0x8B, 0x47
		},
		{
			0x4F, 0x27, 0xDC, 0x36, 0xD8, 0xDD, 0x12, 0x13,
			0x09, 0x09, 0x50, 0x02, 0xA0, 0x66, 0xFB, 0xD4,
			0x3E, 0xE0, 0x99, 0xF8, 0x73, 0x99, 0xD7, 0x8A,
			0x13, 0x23, 0x09, 0x12, 0xA2, 0x8A, 0x02, 0xFB
		},
		{
			0x79, 0xAA, 0xA6, 0x1B, 0xA7, 0x64, 0x56, 0x47,
			0xCC, 0x4C, 0x74, 0xA6, 0x28, 0xDF, 0x3B, 0xF6,
			0xFB, 0x11, 0x43, 0x53, 0xA3, 0x37, 0xA5, 0x4F,
			0xB5, 0x92, 0xA2, 0x83, 0x6B, 0x39, 0x0E, 0xD1
		},
		{
			0xB4, 0x2C, 0x15, 0x7F, 0x22, 0x49, 0x19, 0x5D,
			0xB5, 0x67, 0xB6, 0xDA, 0x5D, 0xDD, 0xD4, 0x62,
			0xF5, 0x0B, 0x1D, 0xA9, 0x14, 0x3D, 0x80, 0xA8,
			0x23, 0xDF, 0xFF, 0xA3, 0xB5, 0xBB, 0x9E, 0x06
		},
		{
			0x41, 0x0B, 0x25, 0x66, 0x2B, 0xF8, 0x11, 0xEA,
			0xF4, 0xF4, 0xD9, 0xBB, 0x31, 0x89, 0xB0, 0x2C,
			0x6D, 0xAC, 0x30, 0x54, 0x88, 0x70, 0x77, 0x9D,
			0xDA, 0xFD, 0x11, 0x88, 0x5B, 0xFA, 0xE9, 0x50
		},
		{
			0x0C, 0x7C, 0xE8, 0x42, 0xF1, 0xCD, 0xF5, 0xAC,
			0x6E, 0x8A, 0x2D, 0x0A, 0x8E, 0x75, 0xE1, 0x00,
			0xD9, 0xAD, 0x28, 0xB1, 0x78, 0x0F, 0x2D, 0x20,
			0x02, 0x3E, 0xB6, 0x92, 0x59, 0x07, 0xEE, 0x6E
		},
		{
			0xAE, 0xC0, 0xFD, 0xBB, 0x93, 0x4E, 0x50, 0x00,
			0x25, 0x94, 0x57, 0x46, 0x67, 0xE9, 0x3E, 0x0D,
			0x17, 0xEE, 0x3D, 0x59, 0x2A, 0xA3, 0xA9, 0xE1,
			0x62, 0xB4, 0x08, 0xF8, 0xF9, 0x4C, 0xB4, 0xFE
		},
		{
			0x19, 0x51, 0x08, 0xE7, 0x4A, 0xC2, 0x9D, 0xE3,
			0xE1, 0x7D, 0x72, 0x7C, 0x7B, 0x4B, 0x89, 0xD3,
			0xD6, 0x51, 0x11, 0xC9, 0x2A, 0xF9, 0xA1, 0x1E,
			0x71, 0x87, 0xC3, 0xA9, 0x80, 0x52, 0xD5, 0x6A
		},
		{
			0x11, 0x29, 0x7D, 0x1B, 0x4D, 0x32, 0x16, 0xC5,
			0xC7, 0xD9, 0xCD, 0xAD, 0xCE, 0x0E, 0x6C, 0xA9,
			0xCD, 0x4E, 0x0A, 0x31, 0x45, 0x20, 0x65, 0xC0,
			0xCC, 0xD0, 0x05, 0xD5, 0x03, 0xD3, 0x52, 0xD4
		},
		{
			0x15, 0x56, 0x2A, 0x48, 0x67, 0xA0, 0x82, 0xB3,
			0x6A, 0x41, 0xC2, 0x73, 0x99, 0x81, 0xB3, 0x33,
			0xC6, 0xE3, 0xC3, 0xDA, 0x00, 0x85, 0xCE, 0x29,
			0x71, 0x13, 0xEA, 0xB9, 0x48, 0x12, 0xCF, 0x5A
		},
		{
			0xAF, 0xD4, 0x48, 0xE3, 0x7A, 0xD2, 0x62, 0x80,
			0x3A, 0x97, 0xBB, 0xFE, 0x10, 0xBB, 0x0B, 0x48,
			0x6A, 0xC7, 0x7A, 0x16, 0xD5, 0x1F, 0x89, 0xE1,
			0xE9, 0xA5, 0x13, 0xAC, 0x01, 0xBF, 0xB9, 0x33
		},
		{
			0x6E, 0x31, 0x41, 0xF6, 0xF0, 0x5D, 0x4C, 0x5D,
			0xEB, 0x90, 0x7A, 0x80, 0x0B, 0x17, 0x91, 0x4F,
			0xBB, 0x53, 0x40, 0x9E, 0xC3, 0x56, 0x6D, 0xF6,
			0x13, 0xB1, 0x41, 0x8F, 0xC0, 0xAF, 0x55, 0x17
		},
		{
			0x99, 0x1A, 0xA5, 0xB3, 0x17, 0x8B, 0x0A, 0x47,
			0x11, 0x35, 0x45, 0x06, 0xA4, 0x87, 0x44, 0xF1,
			0x63, 0x49, 0x4F, 0xE3, 0xD3, 0x03, 0xC7, 0x36,
			0xD2, 0x90, 0xB6, 0x68, 0xE4, 0x22, 0x68, 0x3A
		},
		{
			0xA9, 0x51, 0x74, 0x96, 0x79, 0xF5, 0x4D, 0xB3,
			0x63, 0x5C, 0x3E, 0xD1, 0x37, 0x8E, 0x50, 0x0D,
			0x47, 0x53, 0xF5, 0xC2, 0x8B, 0x87, 0xC4, 0xB8,
			0xF9, 0xF9, 0xF1, 0x32, 0xEA, 0x18, 0xC9, 0x59
		},
		{
			0x52, 0xE4, 0xDD, 0x82, 0x19, 0x48, 0x66, 0x72,
			0xAB, 0x31, 0x82, 0x0D, 0x0B, 0x2B, 0x14, 0xA7,
			0x95, 0x76, 0xFD, 0x36, 0xA4, 0xE8, 0x68, 0xB2,
			0x3A, 0x28, 0x17, 0x7C, 0xAF, 0xB9, 0x00, 0xE9
		},
		{
			0x49, 0x31, 0xCC, 0x3C, 0xD2, 0x65, 0x1F, 0x2E,
			0x6B, 0xC8, 0xD5, 0xCB, 0x8A, 0xBD, 0x54, 0x98,
			0x8C, 0xEA, 0xD5, 0xB9, 0x4A, 0xE8, 0x5D, 0x62,
			0x4F, 0xDE, 0xC2, 0xB6, 0x5E, 0x2F, 0xE3, 0x92
		},
		{
			0x3A, 0xD6, 0x7A, 0xEE, 0xFF, 0x30, 0xCD, 0x6D,
			0x79, 0xF2, 0xAE, 0x57, 0x33, 0xF0, 0x10, 0xD5,
			0x41, 0xC6, 0x68, 0xB4, 0x8B, 0x6A, 0x90, 0xAE,
			0x94, 0xAC, 0x20, 0x0E, 0x17, 0x2B, 0xA6, 0x59
		},
		{
			0x92, 0xB2, 0xDA, 0x3A, 0x4E, 0x0C, 0x3E, 0x5A,
			0x79, 0xBE, 0x87, 0x49, 0x20, 0x2C, 0x5C, 0x20,
			0x5D, 0xDA, 0xF3, 0x72, 0xFB, 0x14, 0x45, 0x70,
			0x78, 0x85, 0x9D, 0xAE, 0x4D, 0x9D, 0x33, 0xC3
		},
		{
			0xFC, 0x93, 0xDA, 0x01, 0x11, 0x0B, 0xDB, 0x84,
			0x7F, 0xF2, 0x7F, 0xC5, 0x28, 0x40, 0xC0, 0x64,
			0x78, 0x84, 0xA6, 0x44, 0xE7, 0x04, 0x00, 0x66,
			0x19, 0xC4, 0x8F, 0x30, 0x08, 0x27, 0x9A, 0x85
		}
	};

	puts("kripto_block_rijndael256");

	for(n = 1; n <= 32; n++)
	{
		s = kripto_block_create(kripto_block_rijndael256, 0, k, n);
		if(!s) puts("error");

		kripto_block_encrypt(s, pt, t);
		for(i = 0; i < 32; i++) if(t[i] != ct[n - 1][i])
		{
			printf("%u-bit key encrypt: FAIL\n", n * 8);
			break;
		}
		if(i == 32) printf("%u-bit key encrypt: OK\n", n * 8);

		kripto_block_decrypt(s, ct[n - 1], t);
		for(i = 0; i < 32; i++) if(t[i] != pt[i])
		{
			printf("%u-bit key decrypt: FAIL\n", n * 8);
			break;
		}
		if(i == 32) printf("%u-bit key decrypt: OK\n", n * 8);

		kripto_block_destroy(s);
	}

	return 0;
}
