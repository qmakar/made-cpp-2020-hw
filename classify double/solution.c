#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    return number == 0;
}

bool checkForPlusDenormal (uint64_t number) {
    return number > 0 && \
    number < 0x0010000000000000;
}

bool checkForPlusNormal (uint64_t number) {
    return number >= 0x0010000000000000 && \
    number < 0x7FF0000000000000;
}

bool checkForPlusInf (uint64_t number) {
    return number == 0x7FF0000000000000;
}

bool checkForSignalingNan (uint64_t number) {
    return number > 0x7FF0000000000000 && \
    number < 0x7FF8000000000000 ||
    number > 0xFFF0000000000000 && \
    number < 0xFFF8000000000000
    ;
}

bool checkForQuietNan (uint64_t number) {
    return number >= 0x7FF8000000000000 && \
    number < 0x8000000000000000 ||
    number >= 0xFFF8000000000000 && \
    number <= 0xFFFFFFFFFFFFFFFF
    ;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForMinusDenormal (uint64_t number) {
    return number > 0x8000000000000000 && \
    number < 0x8010000000000000;
}

bool checkForMinusNormal (uint64_t number) {
    return number >= 0x8010000000000000 && \
    number < 0xFFF0000000000000;
}

bool checkForMinusInf (uint64_t number) {
    return number == 0xFFF0000000000000;
}




void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n"); //0
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n"); //-0
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n"); //1.0 / 0;
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n"); //-1.0 / 0;
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n"); // 1     .. 1.7976931348623157E+308
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n"); // -1
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n"); // 4.940656e-324 .. 2.225074e-308
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n"); // -4.940656e-324 .. -2.225074e-308
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n"); // std::numeric_limits<double>::signaling_NaN();
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n"); // 0.0 / 0     sqrt(-2) INF-INF   INF/INF   0*INF
    }

    else {
        printf("Error.\n");
    }
} 



//int main(){
//    uint64_t r = 0x7FF000000000000F;
//
//    double a = *((double *)(&r));
//    double b;// = 4.940656e-324;
//    printf("%e\n", a);
//    classify(b);
//}

