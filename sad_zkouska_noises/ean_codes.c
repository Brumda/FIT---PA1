#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct code{
    char* code;
    int count;
}CODE;
int isLegit(char* buffer){
   int i = 0; //i will help cycling through the string and also tell me how many digits does the input have
    while(buffer[i] != '\0'){
        if(!(isdigit(buffer[i]))){ //If the input is not a number, we return 0
            return 0;
        }
        i++;
    }
    if(i < 5 || i > 100){ //If the code is either too short or too long
        return 0;
    }
    return 1;
}
void addToArr(CODE* storage,CODE newCode,int index){ //This is a function only because I could not figure out how to
    storage[index] = newCode;                        //add elements to an array passed as a double pointer
}
void addToArray(char* code,CODE** storage,int* count,int* constant){
    int added = 0; //bool value of whether a code was added to the array already or not
    for(int i = 0;i < (*count); i++){
       if(strcmp(((*storage)[i]).code,code) == 0){ //If the code is already in the array, we only increment its count
           ((*storage)[i]).count++;
           added = 1; //To know that we already added this code
       }
    }
    if(added == 0){ //If we havent added it yet (=it is an original code)
        if(*count >= *constant){ //Realloc if needed
            (*constant) *= 2;
            *storage = (CODE*) realloc (*storage,sizeof(CODE)*(*constant));
        }
        CODE newCode = {code,1};
        addToArr(*storage,newCode,*count); //We add the new code
        (*count)++;
    }
}
int takeFromStorage(char* code, CODE* storage, int count){
    for(int i = 0;i < count;i++){
        if(strcmp(storage[i].code,code) == 0 && storage[i].count > 0){ //If the code is in the storage AND the count is not 0
            storage[i].count--;                                        //we decrement the count by 1
            return 1;
        }
    }
    return 0; //If the code is not in the storage at all
}
void freeArr(CODE* arr, int count){
    for(int l = 0;l < count;l++){ //free all the codes strings
        free(arr[l].code);
    }
    free(arr); //free the array itself
}
int main (void){
    char* buffer = NULL; //User input
    size_t size = 0;
    size_t chars = 0; //Number of chars read by getline
    int constant = 10; //Constant for reallocing my arrays when needed
    int count = 0; //Amount of elements in storage
    CODE* storage = (CODE*) malloc (sizeof(*storage)*constant);
    printf("Sklad:\n");
    while(true){
        buffer = NULL;
        chars = getline(&buffer,&size,stdin); //Read the user input
        if(chars == 1){ //If it is \n , we move on the inventory
            break;
        }
        if(chars == EOF){ //EOF is not a valid input
            printf("Nespravny vstup.\n");
            free(buffer);
            freeArr(storage,count);
            return 0;
        }
        buffer[chars-1] = '\0'; //Getline puts \n to the end, so here I change that
        if(!(isLegit(buffer))){ //Some more input validation
            printf("Nespravny vstup.\n");
            free(buffer);
            freeArr(storage,count);
            return 0;
        }
        char* newCode = strdup(buffer);  //Here I copy the string from the buffer to an independent string
        addToArray(newCode,&storage,&count,&constant); //Add to storage
        free(buffer); //Not sure if this is needed after every cycle, but it doesnt break anything so why not
    }
    printf("Inventura:\n");
    CODE* missingCodes = (CODE*) malloc (sizeof(CODE)*constant); //This array will store the codes that are not in storage
    int invCount = 0; //Amount of elements in the missingCodes array
    while(true){
        buffer = NULL;
        chars = getline(&buffer,&size,stdin);
        if(chars == EOF){ //If the input is EOF, we move on to print the missing codes
            break;
            free(buffer);
            return 0;
        }
        buffer[chars-1] = '\0'; //This again
        if(!(isLegit(buffer))){ //The same input validation
            printf("Nespravny vstup.\n");
            freeArr(missingCodes,invCount);
            free(buffer);
            return 0;
        }
        char* invCode = strdup(buffer);
        if(!(takeFromStorage(invCode,storage,count))){ //If we could not find this code in the storage, we consider it a missing code
            addToArray(invCode,&missingCodes,&invCount,&constant); //So we add it to the missingCodes array
        }
        free(buffer);
    }
    printf("Chybi:\n");
    for(int l = 0;l < invCount;l++){ //Print all the missing codes
        printf("%s: %d x\n",missingCodes[l].code,missingCodes[l].count);
        free(missingCodes[l].code); //And free them while we are at it
    }
    free(missingCodes);
}