#include <stdio.h>

// Function to Check Email address
int is_updated_email(char* email) {
    int at_index = -1; // Index of '@' in the email
    int i = 0;
    

    // Find the index of '@'
    while (email[i] != '\0') {
        if (email[i] == '@') {
            at_index = i;
            break;
        }
        i++;
    }
    if (at_index == -1) {
        return 2;

    }
     char* correct_domain = "sheba.xyz";
    i = at_index + 1; 
    int j = 0;
    while (correct_domain[j] != '\0') {
        if (email[i] != correct_domain[j]) {
            return 0;
            
        }
        i++;
        j++;
    }
    


    return 1;
}

int main() {
    char email[100];
    printf("Enter your email address: ");
    scanf("%s", email);

    if (is_updated_email(email)==1) {
        printf("Email address is okay.\n");
    } else if (is_updated_email(email) == 0) {
        printf("Email address is outdated.\n");
        
    }
    else if (is_updated_email(email) == 2)
    {
        printf("Invalid email address.\n");
    }
    

    return 0;
}