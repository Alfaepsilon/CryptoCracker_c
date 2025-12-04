#include <gmp.h>

void cc_powmod(mpz_t result, mpz_t base, mpz_t exponent, mpz_t modulo) {
	mpz_t b, e;
	mpz_init_set(b, base);
	mpz_init_set(e, exponent);
	mpz_set_ui(result, 1);
	while (mpz_sgn(e) > 0) {
		if (!mpz_even_p(e)) {
			mpz_mul(result, result, b);
			mpz_mod(result, result, modulo);
		}
		mpz_mul(b, b, b);
		mpz_mod(b, b, modulo);
		mpz_div_ui(e, e, 2);
	}
	mpz_clears(b, e, (mpz_ptr)NULL);
}