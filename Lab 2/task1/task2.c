#include <stdio.h>

int main() {
    int num1, num2, i, j, sum;
    
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    
    for(i = num1; i < num2; i++) {
        sum = 0;
        for(j = 1; j < i; j++) {
            if (i % j == 0){
                sum += j;
            }
        }
        //condition
        if (sum == i) {
            printf("%d\n", sum);
        }
        
    }
    return 0;
}
