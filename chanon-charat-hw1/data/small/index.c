#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<glib.h>
#include<dirent.h>

void change_alphabet(char* c);
int is_alphabet(char c);
int listdir(char *dir); 
int size_array(gpointer *includes[]);

int main(){
    FILE *ptr_file ;
    char buf[1000], subbuf[100];
    char* temp;  
    int x, i=0, j=0, c, countterm=0;


    //Create hash
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    //Directory Manipulation
    int file_count = 0;
    DIR * dirp;
    struct dirent * entry;
    int filenum = listdir("data");
    GArray *garray;
    GString *s;
    //   printf("File count = %d\n", filenum);
    int filenumber = 1;
    for(filenumber = 1; filenumber<=1;filenumber++){

        gchar path[100] = "data/file";
        char strtemp[10];
        snprintf(strtemp, 10,"%d", filenumber);
        strcat(path, strtemp);
        strcat(path, ".txt");
        printf("File = %s\n", path);
        ptr_file =fopen(path, "r");

        if (!ptr_file)
            return 1;

        //Read file
        fseek(ptr_file, 0, SEEK_END);
        size_t  len = ftell(ptr_file);
        fseek(ptr_file, 0, SEEK_SET);
        temp= (char*)malloc(sizeof(char)*(len+1));  
        fread(temp,sizeof(char),len, ptr_file);

        // printf("%s\n", temp);


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
                //Keep in hash table
                gchar* key = g_strdup(subbuf);

                s = g_string_new(path);
                //If hash exist.
                if(g_hash_table_contains(hash, key)){
                    garray = (GArray*)g_hash_table_lookup(hash, key); // Copy old value to GArray.
                    g_print("Hello %s \n", s->str);
                    g_print("eiei = %s\n", g_array_index(garray, GString*, 0)->str);
                    g_array_append_val(garray, s);
                    g_hash_table_insert(hash,key, garray);
                }else{
                    // Hash doesn't exist.


                    //Create new array and insert path in array. 
                    garray = g_array_new(FALSE, TRUE, sizeof(GString*));
                    g_array_append_val(garray, s);
                    g_print("string = %s\n", g_array_index(garray, GString*, 1)->str);
                    g_hash_table_insert(hash, key, garray);
                    //  printf("%d\n", g_array_get_element_size (garray));
                    int y;
                    for(y =0; y<=1;y++){
                        GString* a;
                        a= g_string_new("0");
                        if(g_string_equal((GString*)(g_array_index(garray, GString*, y))->str, a)){
                            printf("HI\n");
                            g_print("string = %s\n", g_array_index(garray, GString*, y)->str);}
                    }
                }// END ELSE
            }
        }
        //printf("%d\n", g_hash_table_size(hash));


        GHashTableIter iter;
        gpointer key, value;

        g_hash_table_iter_init (&iter, hash);
        while (g_hash_table_iter_next (&iter, &key, &value))
        {
            // gchar* teampchar = value;
            //   g_print("key = %s, value= %s\n", key, g_array_index(&value, gchar*, 0) );
        }
        free(temp);

        fclose(ptr_file);
    }// CLOSE FOR LOOP

    g_hash_table_destroy(hash);
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


int listdir(char *dir) {
    struct dirent *dp;
    DIR *fd;
    int count=0;

    if ((fd = opendir(dir)) == NULL) {
        fprintf(stderr, "listdir: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(fd)) != NULL) {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
            continue;    /* skip self and parent */
        //         printf("%s/%s\n", dir, dp->d_name);
        count++;
    }
    closedir(fd);
    return count;
}

int size_array(gpointer *includes[]) {
    size_t count = 0;
    while (includes[count]){
        count++;
    }

    return count;
}


