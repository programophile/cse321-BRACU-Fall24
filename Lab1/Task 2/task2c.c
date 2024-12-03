#include<stdio.h>
int passcheck(char *pass)
{
  int lower=0,upper=0,digit=0,special=0;
  int length=strlen(pass);
  for(int i=0;i<length;i++){
    if (pass[i]>='a' && pass[i]<='z'){
        lower=1;
    }
    else if(pass[i]>='A' && pass[i]<='Z'){
        upper=1;
    }
    else if(pass[i]>='0' && pass[i]<='9'){
        digit=1;
    }
    else if (pass[i] == '_' || pass[i] == '$' || pass[i] == '#' || pass[i] == '@'){
        special=1;
    }
    
    
  }
  int valid=1;
  if (!lower){
    printf("“Lowercase character missing”");
    valid=0;
  }
  if (!upper){
    if (valid!=1){
        printf(",");
    }
    printf("“Uppercase character missing”");
    valid=0;
  }
  if (!digit){
    if (valid!=1){
        printf(",");
    }
    printf("“Digit missing”");
    valid=0;
  }
  if (!special){
    if (valid!=1){
        printf(",");
    }
    printf("“Special character missing”");
    valid=0;
  }
  if (valid==1){
    printf("OK");
  }
  return 0;
  

}
int main(){
    char pass[100];
    printf("Enter your password: ");
    scanf("%s",pass);
    passcheck(pass);
    return 0;
}