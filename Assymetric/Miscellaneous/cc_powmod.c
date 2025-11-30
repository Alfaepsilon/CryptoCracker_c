#include <gmp.h>

void cc_powmod(mpz_t result, mpz_t modulo, mpz_t base, mpz_t exponent) {
	mpz_t a;
	mpz_init_set(a, base);
	mpz_set_ui(result, 1);
	while (mpz_sgn(exponent) > 0) {
		if (!mpz_even_p(exponent)) {
			mpz_mul(result, result, a);
			mpz_mod(result, result, modulo);
		}
		mpz_mul(a, a, a);
		mpz_mod(a, a, modulo);
		mpz_div_ui(exponent, exponent, 2);
	}
	mpz_clear(a);
}