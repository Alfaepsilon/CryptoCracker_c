#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>
#include "RSA.h"

int main(){
    mpz_t X;
    mpz_init(X);
    char* Xs = "1000000";
    mpz_set_str(X, Xs, 10);
    uint64_t prime = phiX(X);
    printf("%d", prime);
    mpz_clear(X);
    return 0;
}