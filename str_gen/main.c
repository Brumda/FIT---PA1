#include <stdio.h>
#include <stdlib.h>

int main(){
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    printf("10\n");

    for (int i=0;i<10000;i++){
        printf("+ ");
        for (int j=0;j<30;j++){
            int key = rand() % (int)(sizeof(charset) -1);
            printf("%c",charset[key]) ;
        }
        printf("\n");
    }
    printf("#\n?\n");
    return 0;
}