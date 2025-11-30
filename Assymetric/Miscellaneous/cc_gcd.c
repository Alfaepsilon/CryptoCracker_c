#include <gmp.h>

void cc_gcd(mpz_t result, mpz_t N, mpz_t a) {
	mpz_t A, b;
	mpz_init_set(A, N);
	mpz_init_set(b, a);
	while (mpz_cmp(A, b) != 0) {
		if (mpz_cmp(A, b) > 0) {
			mpz_sub(A, A, b);
		}
		else {
			mpz_sub(b, b, A);
		}
	}
	mpz_set(result, A);
	mpz_clears(A, b, (mpz_ptr)NULL);
}