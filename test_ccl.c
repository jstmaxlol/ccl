// C Color Library tests
#include <stdio.h>

// CCL
#include "ccl.h"

int main(void) {
    // Box drawing with included utility characters
    const char *msg = "the C Color Library";
    const char *COLOR = "#f82323";

    printf(" ");
    for (size_t i = 1; i < (strlen(msg) + 1); i++) {
        ccl.printf(COLOR, "%s", BLOCK);
    } printf("\n");

    ccl.printf("cfcfcf", "%s", TLANGLE);
    for (size_t i = 0; i < strlen(msg); i++) {
        ccl.printf("#cfcfcf", "%s", HORL);
    }
    ccl.printf("cfcfcf", "%s\n%s", TRANGLE, VERL);

    // message
    ccl.printf(COLOR, "%s", msg);

    ccl.printf("#cfcfcf", "%s\n%s", VERL, BLANGLE);
    for (size_t i = 0; i < strlen(msg); i++) {
        ccl.printf("cfcfcf", "%s", HORL);
    }
    ccl.printf("cfcfcf", "%s\n", BRANGLE);

    printf(" ");
    for (size_t i = 1; i < (strlen(msg) + 1); i++) {
        ccl.printf(COLOR, "%s", BLOCK);
    } printf("\n");

    return 0;
}

