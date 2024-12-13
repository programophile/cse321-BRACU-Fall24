#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int i, len;
    int flag = 1; 
	
    printf("Enter a string: ");
    scanf("%s", str);

    len = strlen(str);
	
	// Check Palindrome
	
    char *ptr1 = str; 
    char *ptr2 = str + len - 1; 

    for (i = 0; i < len / 2; i++) {
        if (*ptr1 != *ptr2) { 
            flag = 0;
            break;
        }
        ptr1++; 
        ptr2--;
    }
    if (flag) {
        printf("Palindrome\n");
    } else {
        printf("Not Palindrome\n");
    }

    return 0;
}
