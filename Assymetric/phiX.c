#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include "RSA.h"

uint64_t phiX(mpz_t X) {
	uint64_t a = 0;
	mpz_t i;
	mpz_init_set_ui(i, 2);
	while (mpz_cmp(X, i) > 0) {
		if (!MillerRabin(i)) {
			a = a + 1;
		}
		mpz_add_ui(i, i, 1);
	}
	mpz_clear(i);
	return a;
}