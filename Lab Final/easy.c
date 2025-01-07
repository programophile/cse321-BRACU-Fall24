#include <stdio.h>

int main() {
    int start, end;
    
 
    printf("Start: ");
    scanf("%d", &start);
    
    printf("End: ");
    scanf("%d", &end);
   
    printf("Range: %d to %d\n", start, end);
    for (int i = start; i <= end; i++) {
        int is_prime = 1;
        for (int j = 2; j  <= i; j++) {
            if (i % j == 0) {
                is_prime = 0; 
                break;
            }
        }
        if ( is_prime) {
            printf("Prime: %d\n", i);
        }
    }
    
    return 0;
}
