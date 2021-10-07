#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char * deci_to_hexa (int deci) {
    char tmp[20], * hexa;
    int r, i = 0, j;

    do {
        r = deci % 16;
        
        if (r < 10)
            tmp[i++] =  r + '0';
        else
            tmp[i++] = r - 10 + 'A';
        
        deci /= 16;
    } while (deci > 0);

    hexa = (char *) calloc(i + 1, sizeof(char));
    if (hexa != NULL) {
        j = 0;

        while (i >= 0)
            hexa[j++] = tmp[--i];
        hexa[j] = '\0';
    }

    return hexa;
}

void test () {
    int i, deci;
    char * hexa; 
    
    srand(time(NULL));

    for (i = 0; i < 30; ++i) {
        deci = rand() % 1000;
        hexa = deci_to_hexa(deci);
        printf("%-3d : %s\n", deci, hexa);
        free(hexa);
    }
}

int main (void) {
    test();
} 
