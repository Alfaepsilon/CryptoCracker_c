#include <stdio.h>
#include <gmp.h>
#include "Miscellaneous.h"


short MillerRabin(mpz_t X) {
    //If evenX is even
    if (mpz_cmp_ui(X, 2) == 0) return 0;
    if (mpz_even_p(X)) {
        return 1;
    }
    short witnesses[6] = { 2, 3, 5, 7, 11, 13}; //Can try more potential MillerRabin witnesses but should be enough
    mpz_t q, modX, Xphi, a;
    mpz_inits(q, modX, Xphi, a, (mpz_ptr)NULL);
    mpz_sub_ui(q, X, 1);
    short k = 0;
    while (mpz_even_p(q) != 0) {
        mpz_div_ui(q, q, 2);
        k = k + 1;
    }

    for(short i = 0; i < (sizeof(witnesses) / sizeof(witnesses[0])); i++){
        mpz_t gcd;
        mpz_init(gcd);
        mpz_set_ui(a, witnesses[i]);
        cc_gcd(gcd, X, a);
        //If gcd is larger than 1 and not equal to X, a.k.a a divides X
        if (mpz_cmp_ui(gcd, 1) > 0 && mpz_cmp(gcd, X) != 0) {
            mpz_clears(q, modX, Xphi, gcd, a, (mpz_ptr)NULL);
            return 1;
        }
        mpz_clear(gcd);

        cc_powmod(modX, X, a, q);

        if (mpz_cmp_ui(modX, 1) == 0) {
            //mpz_clears(q, modX, Xphi, a, (mpz_ptr)NULL);
            //return 0;
            continue;
        }

        mpz_sub_ui(Xphi, X, 1); //A.k.a -1 mod X
        short flag = 0;
        for (short j = 0; j < k; j++) {
            if (mpz_cmp(modX, Xphi) == 0) {
                //mpz_clears(q, modX, Xphi, a, (mpz_ptr)NULL);
                //return 0;
                flag = 1;
                break;
            }
            //mpz_powm_ui(modX, modX, 2, X);
            mpz_t tmp;
            mpz_init_set_ui(tmp, 2);
            cc_powmod(modX, X, modX, tmp);
            mpz_clear(tmp);
        }
        if(flag == 1) continue;
        mpz_clears(q, modX, Xphi, a, (mpz_ptr)NULL);
        return 1;
    }
    return 0;
}