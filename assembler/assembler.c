#include "stdio.h"
#include "stdlib.h"
#include "reader.h"

int main(int argc, char const *argv[]) {
    int x;
    for(x = 1; x<argc; x++) {
        //*char[] file = readFile(argv[x]);
        printf("%s: %s", argv[x], readFile(argv[x]) == 0
               ? "Success\n------------------------------------------------------------\n\n"
               : "Fail\n------------------------------------------------------------\n\n");
    }
}
