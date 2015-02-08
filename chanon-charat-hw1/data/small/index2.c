#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<glib.h>
#include<dirent.h>

int list_file_in_dir(char *dir);
char* readfile(FILE *ptr_file, char *temp);
int is_alphabet(char c);
void change_alphabet(char* c);

int main(){
	FILE *ptr_file;
	int count_of_file = list_file_in_dir("data");
	printf("count file = %d\n", count_of_file);
	
	char* word = malloc(1000);
	char dir[12] = "data/";
	char filename[15] = "file";

	int filenumber = 1;
	
	for(filenumber=1;filenumber<=3000;filenumber++){
	char path[30]="";
        strcat(path, dir);
	strcat(path, filename);
	char temp_filenumber[15];
	snprintf(temp_filenumber, 10,"%d", filenumber);
	strcat(path, temp_filenumber);
        strcat(path, ".txt");
        printf("File => %s\n", path);

	//OPEN FILE
        ptr_file =fopen(path, "r");
	
	//READFILE
	if (!ptr_file)
          return 1;
	char* temp;	
	fseek(ptr_file, 0, SEEK_END);
        size_t  len = ftell(ptr_file);
        fseek(ptr_file, 0, SEEK_SET);
        temp= (char*)malloc(sizeof(char)*(len));  
        fread(temp,sizeof(char),len, ptr_file);	
	
	//printf("%s\n", temp);
	//END READFILE
	
	int i,j;
	 for(i=0;i<=len;i++){
            j=0;

            while(is_alphabet(temp[i])){
                change_alphabet(&temp[i]);
                word[j] = temp[i];
                i++;
                j++;
		
            }
	
	word[j]='\0';
	if(word[0]!='\0'){ 
	printf("%s\n", word);
	}

	}
	free(temp);
	fclose(ptr_file);

	} // END FOR LOOP FILE
return 0;
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
             printf("%s/%s\n", dir, dp->d_name);
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
