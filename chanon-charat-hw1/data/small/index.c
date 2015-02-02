#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void change_alphabet(char* c);
int is_alphabet(char c);

int main(){
    FILE *ptr_file ;
    char buf[1000], subbuf[100];
    char* temp;  
    int x, i=0, j=0, c;

    ptr_file =fopen("data/file1.txt", "r");

    if (!ptr_file)
        return 1;

    //Read file
    fseek(ptr_file, 0, SEEK_END);
    size_t  len = ftell(ptr_file);
    fseek(ptr_file, 0, SEEK_SET);
    temp= (char*)malloc(sizeof(char)*len);  
    fread(temp,sizeof(char),len, ptr_file);

    printf("%s\n", temp);


    //Substring file
    for(i=0;i<=len;i++){
        j=0;

        while(is_alphabet(temp[i])){
            change_alphabet(&temp[i]);
            subbuf[j] = temp[i];
            i++;
            j++;
        }

        subbuf[j]='\0';
        if(subbuf[0]!='\0'){         
            printf("%s\n",subbuf);
        }
    }
    free(temp);
    fclose(ptr_file);
    return  0;
}

int is_alphabet(char c){

    return ((c >= 65 && c <= 90)||( c >= 97 && c <= 122));
}

void change_alphabet(char* c){
    if(*c >= 65 &&  *c <= 90){
        *c += 32;
    }
}
