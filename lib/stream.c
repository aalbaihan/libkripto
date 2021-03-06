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

#include <assert.h>
#include <stdint.h>

#include <kripto/stream.h>
#include <kripto/desc/stream.h>

struct kripto_stream
{
	const kripto_stream_desc *desc;
	unsigned int multof;
};

kripto_stream *kripto_stream_create
(
	const kripto_stream_desc *desc,
	unsigned int rounds,
	const void *key,
	unsigned int key_len,
	const void *iv,
	unsigned int iv_len
)
{
	assert(desc);
	assert(desc->create);

	assert(key);
	assert(key_len);
	assert(key_len <= kripto_stream_maxkey(desc));
	assert(iv_len <= kripto_stream_maxiv(desc));
	if(iv_len) assert(iv);

	return desc->create(desc, rounds, key, key_len, iv, iv_len);
}

kripto_stream *kripto_stream_recreate
(
	kripto_stream *s,
	unsigned int rounds,
	const void *key,
	unsigned int key_len,
	const void *iv,
	unsigned int iv_len
)
{
	assert(s);
	assert(s->desc);
	assert(s->desc->recreate);

	assert(key);
	assert(key_len);
	assert(key_len <= kripto_stream_maxkey(s->desc));
	assert(iv_len <= kripto_stream_maxiv(s->desc));
	if(iv_len) assert(iv);

	return s->desc->recreate(s, rounds, key, key_len, iv, iv_len);
}

void kripto_stream_encrypt
(
	kripto_stream *s,
	const void *pt,
	void *ct,
	size_t len
)
{
	assert(s);
	assert(s->desc);
	assert(s->desc->encrypt);
	assert(len % kripto_stream_multof(s) == 0);

	s->desc->encrypt(s, pt, ct, len);
}

void kripto_stream_decrypt
(
	kripto_stream *s,
	const void *ct,
	void *pt,
	size_t len
)
{
	assert(s);
	assert(s->desc);
	assert(s->desc->decrypt);
	assert(len % kripto_stream_multof(s) == 0);

	s->desc->decrypt(s, ct, pt, len);
}

void kripto_stream_prng
(
	kripto_stream *s,
	void *out,
	size_t len
)
{
	assert(s);
	assert(s->desc);
	assert(s->desc->prng);

	s->desc->prng(s, out, len);
}

void kripto_stream_destroy(kripto_stream *s)
{
	assert(s);
	assert(s->desc);
	assert(s->desc->destroy);

	s->desc->destroy(s);
}

unsigned int kripto_stream_multof(const kripto_stream *s)
{
	assert(s);
	assert(s->multof);

	return s->multof;
}

const kripto_stream_desc *kripto_stream_getdesc(const kripto_stream *s)
{
	assert(s);
	assert(s->desc);

	return s->desc;
}

unsigned int kripto_stream_maxkey(const kripto_stream_desc *desc)
{
	assert(desc);
	assert(desc->maxkey);

	return desc->maxkey;
}

unsigned int kripto_stream_maxiv(const kripto_stream_desc *desc)
{
	assert(desc);

	return desc->maxiv;
}
