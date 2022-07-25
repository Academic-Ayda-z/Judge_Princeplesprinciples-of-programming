#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXCHAR 1000

/**
 *
 * @param fPtr1 is a file pointer to a file in out folder in testCase folder.
 * @param fPtr2 is a file pointer to a file which is generated by generator function.
 * @return this function returns 1 or 0 which means the input file pointers are equal or not.
 */
int compareFile(FILE * fPtr1, FILE * fPtr2){
    char ch1, ch2;

    ch1 = fgetc(fPtr1);
    ch2 = fgetc(fPtr2);

    while (ch1 != EOF && ch2 != EOF) {
        ch1 = fgetc(fPtr1);
        ch2 = fgetc(fPtr2);
        if (ch1 != ch2)
            return 0;
    }
    if (ch1 == EOF && ch2 == EOF)
        return 1;
    else
        return 0;
}

/**
 *
 * @param testCase is the name of testCase dir and contains in and out.
 * @param outPutCode is the name of folder that generate function has generated.
 * @param num is the number of the test cases  -it has been check at the begging-
 * @return this function will return a none negative number as the number of accepted test cases
 */
int judge(char*testCase,char*outPutCode,int num) {

    FILE* myFile;
    FILE *outFile;;
    char command[MAXCHAR];
    char path[MAXCHAR];
    char codeOutFilePath[MAXCHAR];
    char testOutFilePath[MAXCHAR];
    FILE *resultFile=fopen("finalResult.txt","w");
    int result=0;

    sprintf(command,"cd >path.txt");
    system(command);

    FILE * pathname=fopen("path.txt","r");
    fscanf(pathname,"%s",path);
    fclose(pathname);
    system("del path.txt");

    strcpy(codeOutFilePath,path);
    strcat(codeOutFilePath,"\\");
    strcat(codeOutFilePath,outPutCode);

    strcpy(testOutFilePath,path);
    strcat(testOutFilePath,"\\");
    strcat(testOutFilePath,testCase);
    strcat(testOutFilePath,"\\out");

    for (int i=1 ; i<=num ; i++) {

        char name[MAXCHAR]="\\output";
        char j[20];
        itoa(i,j,10);
        strcat(name,j);
        strcat(name,".txt");

        strcpy(path,codeOutFilePath);
        strcat(path,name);
        myFile=fopen(path,"r");

        strcpy(path,testOutFilePath);
        strcat(path,name);
        outFile=fopen(path,"r");

        if(outFile==NULL || myFile==NULL)
            return -1;

        if(compareFile(myFile,outFile)) {

            fprintf(resultFile, " accepted \n");
            result++;
        }
        else
            fprintf(resultFile," wrongAnswer \n");

        fclose(myFile);
        fclose(outFile);
    }
        fclose(resultFile);

    return result;
}