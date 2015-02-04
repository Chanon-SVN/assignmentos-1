#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<glib.h>

void change_alphabet(char* c);
int is_alphabet(char c);

int main(){
    FILE *ptr_file ;
    char buf[1000], subbuf[100];
    char* temp;  
    int x, i=0, j=0, c, countterm=0;

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


    //Create hash
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
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
            //Keep in hash table
            gchar* key = g_strdup(subbuf);
            g_hash_table_insert(hash, key, "DocA");
            printf("The %p was inserted in hash table.\n", key);
        }
    }
    printf("%d\n", g_hash_table_size(hash));


    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, hash);
    while (g_hash_table_iter_next (&iter, &key, &value))
    {
printf("key = %s, value= %s\n", key, value);
    }

    g_hash_table_destroy(hash);
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
