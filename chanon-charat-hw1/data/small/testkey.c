#include<stdio.h>
#include"key-value.c"

int main(){
    int i;
    char* names[]={"key1","key2","key3","key4","key5"};
    char* descs[]={"value1","value2","value3","Value4","Value5"};

    inithashtab();
    for(i=0;i<5;i++)
        install(names[i],descs[i]);

printf("\n This is  a %s", lookup("key1"));

    displaytable();
    cleanup();
    return 0;
}
