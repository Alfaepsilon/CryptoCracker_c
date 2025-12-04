#include <stdio.h>
#include <gmp.h>
#include "Miscellaneous.h"
#include <stdint.h>
#include <stdbool.h>


bool MillerRabin(mpz_t X) {
    short witnesses[6] = { 2, 3, 5, 7, 11, 13 }; //Can try more potential MillerRabin witnesses but should be enough
    for(short l = 0; l < (sizeof(witnesses) / sizeof(witnesses[0])); l++){
        if(mpz_cmp_ui(X, witnesses[l]) == 0) return false;
    }

    //If evenX is even
    if (mpz_even_p(X)) {
        return true;
    }

    mpz_t q, modX, Xphi, a, gcd, tmp;
    mpz_inits(q, modX, Xphi, a, gcd, tmp, (mpz_ptr)NULL);
    mpz_sub_ui(q, X, 1);
    mpz_sub_ui(Xphi, X, 1); //A.k.a -1 mod X
    mpz_set_ui(tmp, 2);
    bool composite = false;
    uint64_t k = 0;
    while (mpz_even_p(q)) {
        mpz_div_ui(q, q, 2);
        k = k + 1;
    }

    for(short i = 0; i < (sizeof(witnesses) / sizeof(witnesses[0])); i++){
        if(mpz_cmp_ui(X, witnesses[i]) < 0) break;
        mpz_set_ui(a, witnesses[i]);
        cc_gcd(gcd, X, a);

        //If gcd is larger than 1 and not equal to X, a.k.a a divides X
        if (mpz_cmp_ui(gcd, 1) > 0 && mpz_cmp(gcd, X) != 0) {
            mpz_clears(q, modX, Xphi, gcd, a, tmp, (mpz_ptr)NULL);
            return true;
        }

        cc_powmod(modX, a, q, X);

        if (mpz_cmp_ui(modX, 1) == 0) continue;
        if (mpz_cmp(modX, Xphi) == 0) continue;
        short flag = 0;
        for (short j = 0; j < k; j++) {
            cc_powmod(modX, modX, tmp, X);
            if (mpz_cmp(modX, Xphi) == 0) {
                flag = 1;
                break;
            }
        }
        if(flag == 1) continue;
        mpz_clears(q, modX, Xphi, gcd, a, tmp, (mpz_ptr)NULL);
        return true;
    }
    mpz_clears(q, modX, Xphi, gcd, a, tmp, (mpz_ptr)NULL);
    return false;
}