#ifndef KRIPTO_RANDOM_H
#define KRIPTO_RANDOM_H

#include <stddef.h>

typedef struct kripto_random kripto_random;

extern kripto_random *kripto_random_create(void);

extern size_t kripto_random_gen
(
	kripto_random *s,
	void *out,
	size_t len
);

extern void kripto_random_destroy(kripto_random *s);

extern int kripto_random_test(kripto_random *s);

#endif
