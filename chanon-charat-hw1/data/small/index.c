#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
FILE *ptr_file ;
char buf[1000], subbuf[100];
char* temp;  
int x, i=0, j=0, c;

        ptr_file =fopen("data/file1.txt", "r");

        if (!ptr_file)
            return 1;

            //Read file
/*             do
            {
                
               c = fgetc(ptr_file);
                if( feof(ptr_file) )
                 {              
                     break ;
                 }
                printf("%c", c) ;
             }while(1);

           while (fgetc(ptr_file)!=EOF){
            printf("%s\n",fgetc(ptr_file));
           }
            fclose(ptr_file);*/

            //Readfile2
             fseek(ptr_file, 0, SEEK_END);
            size_t  len = ftell(ptr_file);
            fseek(ptr_file, 0, SEEK_SET);
            temp= (char*)malloc(sizeof(char)*len);  
            fread(temp,sizeof(char),len, ptr_file);

            printf("%s\n", temp);
           //Substring file
          /* while(buf[i]!='\0'||buf[i]!='.'){
               j=0;
               while(buf[i]!=' '||buf[i]!='.'){
                subbuf[j] = buf[i];
                i++;j++;
               }
               subbuf[j]='\0';
               i++;
               printf("%s\n",subbuf);
           }*/
            free(temp);
            fclose(ptr_file);
        return  0;
}
