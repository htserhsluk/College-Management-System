#include <stdio.h>
#include <stdlib.h>

void view_notice(){
    FILE *fp = fopen("notice_board.txt","r");
    char buffer[255];
    int c = 0;
    while (fgets(buffer,255,fp)!=NULL){
        c+=1;
        printf("%d. %s",c,buffer);
    }
    fclose(fp);
}

void create_notice(){
    FILE *fp = fopen("notice_board.txt","a");
    char buffer[255];
    getchar();
    fgets(buffer,255,stdin);
    fprintf(fp,"%s",buffer);
    fclose(fp);
}
