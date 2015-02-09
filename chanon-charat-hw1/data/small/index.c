#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<glib.h>
#include<dirent.h>
#include<ctype.h>
#include<sys/stat.h>
int list_file_in_dir(char *dir);
char* readfile(FILE *ptr_file, char *temp);
int is_alphabet(char c);
void change_alphabet(char* c);
int comparison_fn_t (const void *a, const void *b);
gint compare_items (gpointer a, gpointer b);

    int main(){
    FILE *ptr_file;
    int count_of_file = list_file_in_dir("data");
  //  printf("count file = %d\n", count_of_file);

    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    GPtrArray* garray;
    char word[1000];
    char* temp;
    char dir[12] = "data/";
    char filename[15] = "file";

    int filenumber = 1;
    struct stat st;
    for(filenumber=1;filenumber<=1;filenumber++){
        char path[30]="";
        strcat(path, dir);
        strcat(path, filename);
        char temp_filenumber[15];
        char* file_name = temp_filenumber;
        snprintf(temp_filenumber, 10,"%d", filenumber);
        strcat(path, temp_filenumber);
        strcat(path, ".txt");
//        printf("File => %s\n", path);
        char* fnum;
        sprintf(fnum, "%d", filenumber);

        //OPEN FILE
        ptr_file =fopen(path, "r");

        //READFILE
        if (!ptr_file)
            return 1;
        stat(path,&st);
      //  printf("%d\n",st.st_size);

        //fseek(ptr_file, 0, SEEK_END);
        //        size_t  len = ftell(ptr_file);
        //        fseek(ptr_file, 0, SEEK_SET);
        temp = malloc(st.st_size);
        fread(temp,sizeof(char),st.st_size, ptr_file);	

        //	printf("%s\n", temp);
        //END READFILE

        int i,j;
        for(i=0;i<=st.st_size;i++){
            j=0;
            while(isalpha(temp[i])){
                word[j] = tolower(temp[i]);
                i++;
                j++;		
            }

            word[j]='\0';
            if(word[0]!='\0'){
              //  printf("%s\n", word);

                gchar* key = g_strdup(word);
                //s = g_string_new(path);

                //IF HASH EXIST...
                if(g_hash_table_contains(hash, key)){
                    garray = g_hash_table_lookup(hash, key); // Copy old value to GArray.
                  //  g_print("Hello %s \n", s->str);
                  //  g_print("eiei = %s\n", g_array_index(garray, GString*, 0)->str);
                    if(g_strcmp0(path, garray->pdata[(garray->len)-1])){
                    g_ptr_array_add(garray, g_strdup(file_name));
                    g_hash_table_insert(hash,key, garray);
                    }
            //        if(!g_strcmp0(key,"translations"))
           //         g_print("key = %s %s %s\n",key,garray->pdata[0],garray->pdata[1]);
                }else{
                    //IF HASH DOESN'T EXIST
                    garray = g_ptr_array_new();
                    g_ptr_array_add(garray, g_strdup(file_name));
                    g_hash_table_insert(hash, key, garray);
           //         g_print("key = %s %s \n",key,garray->pdata[0]);
                }
            }// END IF IN WORD
        }// END FOR IN FILE
        free(temp);
        fclose(ptr_file);

    } // END FOR LOOP FILE

   


//    FILE *f = fopen("output", "w");
//    if (f == NULL)
//    {
//            printf("Error opening file!\n");
//                exit(1);
//    }

    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hash);
    
    GPtrArray* sort_hash = g_ptr_array_new();
    while (g_hash_table_iter_next (&iter, &key, &value))
    {
        //ADD IN Q_SORT
        g_ptr_array_add(sort_hash, g_strdup(key));
        
      //  garray = (GPtrArray*)value;
      //  int count_array=0;

        //PRINT VALUE IN EACH KEY.
      //  while(count_array < garray->len){
  //       fprintf(f,"-- value= %s\n",  garray->pdata[count_array]);
      //  count_array++;
      //  }
    }
        g_ptr_array_sort(sort_hash, (GCompareFunc)compare_items);
        printf("%d\n", sort_hash->len);

        int count_hash_array=0;
        while(count_hash_array < sort_hash->len){
       g_print("%s:",  sort_hash->pdata[count_hash_array]);
        int count_value=0;
        GPtrArray* hash_value = g_hash_table_lookup(hash, sort_hash->pdata[count_hash_array]);
        g_print("%d:", hash_value->len);
        for(count_value=0; count_value < hash_value->len; count_value++){
            g_print("%s" ,hash_value->pdata[count_value]);
            if(count_value < hash_value->len-1){
            g_print(",");
            }
        }
        g_print("\n");
        count_hash_array++;
        }
        
//    fclose(f);


  //  printf("FINISHED");
    return 0;
}

gint compare_items (gpointer a, gpointer b) {
   //   char* alpha = *(char **) a;
   //     char* beta = *(char **) b;
          return strcmp (* (char * const *) a, * (char * const *) b);
}

int list_file_in_dir(char *dir) {
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
    //    printf("%s/%s\n", dir, dp->d_name);
        count++;
    }
    closedir(fd);
    return count;
}


int is_alphabet(char c){

    return ((c >= 65 && c <= 90)||( c >= 97 && c <= 122));
}

void change_alphabet(char* c){
    if(*c >= 65 &&  *c <= 90){
        *c += 32;
    }
}
