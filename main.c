#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *variableList[1000]; int vIndex = 0;
int integerList[1000] = { 0 }; int iIndex = 0;

char commentLine[1000]; char d[1000]; char b[1000];
void isComment(char* str) {
	bool trueComment = false;
	int j;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '{') {
			for (j = i; j < strlen(str); j++) {
				if (str[j] == '}') {
					substring(str, i + 1, j - i - 1, commentLine);
					substring(str, 0, i, d);
					substring(str, j + 1, strlen(str), b);
					strcat(d, b);
					strcpy(str, d);

					trueComment = true;

					isComment(str);
				}
			}
			if (!trueComment) {
				printf("\nError;Comment or a string constant that starts but does not terminate before the end of file.\n");
				exit(0);
			}
		}
	}
}
int substring(char *source, int from, int n, char *target) {
	int length, i;
	for (length = 0; source[length] != '\0'; length++);
	if (from > length) {
		printf("Error:Starting index is invalid.\n");
		return 1;
	}
	if ((from + n) > length) {
		n = (length - from);
	}
	for (i = 0; i < n; i++) {
		target[i] = source[from + i];
	}
	target[i] = '\0';
	return 0;
}

char* substringS(char *destination, const char *source, int beg, int n){
    while (n > 0)
    {
        *destination = *(source + beg);

        destination++;
        source++;
        n--;
    }
    *destination = '\0';
    return destination;
}

bool isKeyword(char* str) {

	if (!strcmp(str, "int") ||
		!strcmp(str, "move") || !strcmp(str, "to") || !strcmp(str, "add") ||
		!strcmp(str, "sub") || !strcmp(str, "from") ||
		!strcmp(str, "loop") || !strcmp(str, "times") ||
		!strcmp(str, "out") || !strcmp(str, "newline")) {
		return true;
	}
	return false;
}
bool isInteger(char* str) {

	int len = strlen(str);

	if (len > 100) {
        printf("\n Error: Length must be smaller then 100 digits... \n");
		return false;
	}

	for (int i = 0; i < len; i++) {
		if (i > 0) {
			if (str[i] == '-' || len == 1) {
				return false;
			}
		}
		if (!(isdigit(str[i]) || str[i] == '-')) {
			return false;
		}
	}

	return true;
}
bool isVariable(char* str) {

	int len = strlen(str);

	if (len > 20) {
        printf("\n Error: Length must be smaller then 20.. \n");
		return false;
	}

	for (int i = 0; i < len; i++) {
		if (str[0] == '_') {
            printf("\n Error: The variable can not starts with '_'.. \n");
			return false;
		}
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_')||('0'<=str[i])&&str[i]<='9')) {
		    printf("\n Error: The given word can not used with sign. Not allowed.. \n ");
			return false;
		}
	}

	return true;
}
bool isInVeriable(char* str){
    for (int i = 0; i < vIndex; i++) {
		if (!strcmp(str, variableList[i])) {
			return false;
		}
	}
	return true;
}
bool isIntegerVariable(char* str) {
    for (int i = 0; i < vIndex; i++) {
		if (!strcmp(str, variableList[i])) {
			return true;
		}
	}

	return false;
}

int main(int argc,char * argv[])
{
    char *F;
    F=malloc(300*sizeof(char));
    printf("c:\> Enter a file name => ");
    scanf("%s",F);

    strcat(F,".ba");

    FILE *fp;
    FILE *res;
	long lSize;
	char *code;

	fp=fopen(F,"rb");
	if (!fp) perror(F), printf("Error: File not found...\n"),exit(1);

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    code = calloc(1, lSize + 1);
    if (!code) fclose(fp), fputs("Error: Memory alloc fails", stderr);

    if (1 != fread(code, lSize, 1, fp)) {
        fclose(fp), free(code), fputs("Error: Entire read fails", stderr);
    }

    isComment(code);
    Parse(code);

    return 0;

}

int loopsayac=0;
int loopsayac2=0;
int blockLoop[1000][4];
char *lines[1000];
void Parse(char* code){
    int lineCount = 0;
	char *splitCode = strtok(code, "\n\r");
	while (splitCode != NULL) {
		lines[lineCount++] = splitCode;
		splitCode = strtok(NULL, "\n\r");
	}
	for(int i=0;i<lineCount;i++){
        LineParse(lines[i],i+1);
	}

	int say=loopsayac2;
	for(int i=0;i<loopsayac2;i++){
        say--;
        if(blockLoop[say][2]!=-1&&blockLoop[say][3]==-1){
            printf("\nError: Close Block is not exist after Open Block that Line '%d'\n",blockLoop[say][2]);
            return 0;
        }
        if(blockLoop[say][2]==-1&&blockLoop[say][3]!=-1){
            printf("\nError: Open Block is not exist before Close Block that Line '%d'\n",blockLoop[say][3]);
            return 0;
        }
	}
}
void LineParse(char* line,int linec){
    int outStr[3]={0,0,0};
    int sayOut=0;
    bool StrOut=false;
    int wordCount = strlen(line);
    char *word[1000];
    int lineMap[1000];
    int sayacKont=0;

    bool strChek=false;
    for(int i=0;i<wordCount;i++){
        if(line[i]==34){
            strChek=true;
            lineMap[i]=34;
            for(int j=i+1;j<wordCount;j++){
                if(line[j]==34){
                    strChek=false;
                    lineMap[j]=34;
                    i=j;
                    StrOut=true;
                    outStr[sayOut%3]++;
                    sayOut++;
                    break;
                }
                else{
                    lineMap[j]=1;
                }
            }
            if(strChek){
                printf("\nError; String Constant starts but not ends..! Line %d\n",linec);
                exit(0);
            }

        }
        else if(line[i]==32){//Bosluk
            lineMap[i]=32;
        }
        else if(line[i]==44){//virgul
            lineMap[i]=44;
        }
        else if(line[i]==46){//nokta
            lineMap[i]=46;
        }
        else if(line[i]==91){//openblock
            lineMap[i]=91;
        }
        else if(line[i]==93){//closeBlock
            lineMap[i]=93;
        }
        else if((64<line[i]&&line[i]<91)||line[i]==95||line[i]==45||(96<line[i]&&line[i]<123)||(47<line[i])&&line[i]<58){
            lineMap[i]=1;
        }
        else{
            printf("\nError; Undefined char used..! Line %d\n",linec);
            exit(0);
        }
    }
    int wordSayac=0;
    int sayac=0;
    int start=0;
    bool dogru2=true;
    for(int i=0;i<wordCount;i++){
        bool dogru=true;
        char* str=malloc(300*sizeof(char));
        if(lineMap[i]==1){
            sayac++;
        }
        if(line[i]==93){
            word[wordSayac]="]";
            wordSayac++;
            start++;
        }
        if(lineMap[i]==32&&lineMap[i-1]==1){
            substringS(str,line,start,sayac);
            word[wordSayac]=str;
            wordSayac++;
            start=start+sayac;
            sayac=0;
            dogru=false;
        }
        if(lineMap[i]==32){
            start++;
        }
        if(lineMap[i]==44&&(lineMap[i-1]==1)){
            substringS(str,line,start,sayac);
            word[wordSayac]=str;
            wordSayac++;
            start=start+sayac;
            sayac=0;
        }
        if(lineMap[i]==44){
            word[wordSayac]=",";
            wordSayac++;
            start++;
        }
        if(lineMap[i]==34&&(lineMap[i+1]==1||lineMap[i+1]==34)){
            int k=0;
            int strsayac=i+1;
            while(lineMap[strsayac]!=34){
                k++;
                strsayac++;
            }
            substringS(str,line,i+1,k);
            word[wordSayac]=str;
            wordSayac++;
            start=start+k+1;
            sayac=0;
            i=strsayac;
        }
        if(lineMap[i]==34){
            start++;
        }
        if(lineMap[i]==46&&(lineMap[i-1]==1)){
            substringS(str,line,start,sayac);
            word[wordSayac]=str;
            wordSayac++;
            start=start+sayac;
            sayac=0;
        }
        if(line[i]==46){
            word[wordSayac]=".";
            wordSayac++;
            start++;
        }

        int gec=strlen(word);
        if(i+1==wordCount&&lineMap[i]!=32&&dogru&&(i-sayac<0||lineMap[i-sayac]==32||lineMap[i-sayac]==44)){
            substringS(str,line,start,sayac);
            word[wordSayac]=str;
            wordSayac++;
            start=start+sayac;
            sayac=0;
        }
        if(lineMap[i]==91&&lineMap[i-1]==1){
            substringS(str,line,start,sayac);
            word[wordSayac]=str;
            wordSayac++;
            start=start+sayac;
            sayac=0;
        }
        if(line[i]==91){
            word[wordSayac]="[";
            wordSayac++;
            start++;
        }

    }

    word[wordSayac]="-END-";
    for(int i=0;i<wordSayac;i++){
        //int
        if(!strcmp(word[i],"int")){
            if(!strcmp(word[i+1],"-END-")){
                printf("\nError: Variable is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isKeyword(word[i+1])&&strcmp(word[i+1],"-END-")) {
                printf("\nError: The given count must not be a keyword. Variable is expected. Line '%d'..!\n",linec );
                exit(0);
            }
            else if (isVariable(word[i+1])&&strcmp(word[i+1],"-END-")&&!isIntegerVariable(word[i+1])) {
                variableList[vIndex] = word[i+1];
                integerList[iIndex] = 0;
                vIndex++;
                iIndex++;
            }
            else {
                printf("\nError: '%s' is not a variable or defined variable. Variable is expected. Line '%d'..!\n",word[i+1],linec);
                exit(0);
            }
            if(strcmp(word[i+2],".")){
                printf("\nError: End of line '.' is expected. Line '%d'..!\n",linec);
                i=i+2;
                exit(0);
            }
            else{
                i=i+2;
            }
        }
        //move
        else if(!strcmp(word[i],"move")){
            int moveInt = 0;
            if (!strcmp(word[i+1],"-END-")) {
                printf("\nError: Integer or variable are expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isKeyword(word[i+1])&&strcmp(word[i+1],"-END-")) {
                printf("\nError: The given count must not be a keyword. Integer or variable are expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isInteger(word[i+1])&&strcmp(word[i+1],"-END-")) {
                moveInt = atoi(word[i+1]);
            }
            else if (isIntegerVariable(word[i+1])&&strcmp(word[i+1],"-END-")) {
                for (int k = 0; k < vIndex; k++) {
                    if (!strcmp(variableList[k], word[i+1])) {
                        moveInt = integerList[k];
                        break;
                    }
                }
            }
            else {
                printf("\nError: '%s' is not a integer or defined variable. Integer or variable are expected. Line '%d'..!\n", word[i+1],linec);
                exit(0);
            }
            //to
            if (!strcmp(word[i+2],"-END-")) {
                printf("\nError: Keyword 'to' is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (!strcmp(word[i+2], "to")) {

            }
            else {
                printf("\nError: Keyword 'to' is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            //int or variable
            if (!strcmp(word[i+3],"-END-")) {
                printf("\nError: Variable is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isKeyword(word[i+3])&&strcmp(word[i+3],"-END-")) {
                printf("\nError: The given count must not be a keyword. Variable is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isIntegerVariable(word[i+3])&&strcmp(word[i+3],"-END-")) {
                for (int k = 0; k < vIndex; k++) {
                    if (!strcmp(variableList[k], word[i+3])) {
                        integerList[k] = moveInt;
                        break;
                    }
                }
            }
            else {
                printf("\nError: '%s' is not a variable . Variable is expected. Line '%d'..!\n", word[i+3],linec);
                exit(0);
            }
            //End of line
            if(strcmp(word[i+4],".")){
                printf("\nError: End of line '.' is expected. Line '%d'..!\n",linec);
                i=i+4;
                exit(0);
            }
            else{
                i=i+4;
            }

        }
        //add
        else if(!strcmp(word[i], "add")){
            //Integer Or Variable
            int addInt = 0;
            if (!strcmp(word[i+1],"-END-")) {
                printf("\nError:Integer or variable are expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isKeyword(word[i+1])&&strcmp(word[i+1],"-END-")) {
                printf("\nError: The given count must not be a keyword. Integer or variable are expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isInteger(word[i+1])&&strcmp(word[i+1],"-END-")) {
                addInt = atoi(word[i+1]);
            }
            else if (isIntegerVariable(word[i+1])&&strcmp(word[i+1],"-END-")) {
                for (int k = 0; k < vIndex; k++) {
                    if (!strcmp(variableList[k], word[i+1])) {
                        addInt = integerList[k];
                        break;
                    }
                }
            }
            else {
                printf("\nError: '%s' is not a integer or defined variable. Integer or variable are expected. Line '%d'..!\n", word[i+1],linec);
                exit(0);
            }
            //To
            if (!strcmp(word[i+2],"-END-")) {
                printf("\nError: Keyword 'to' is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (!strcmp(word[i+2], "to")) {

            }
            else {
                printf("\nError: Keyword 'to' is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            //variable
            if (!strcmp(word[i+3],"-END-")){
                printf("\nError: Variable is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isKeyword(word[i+3])&&strcmp(word[i+3],"-END-")) {
                printf("\nError: The given count must not be a keyword. Variable is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isIntegerVariable(word[i+3])&&strcmp(word[i+3],"-END-")) {
                for (int k = 0; k < vIndex; k++) {
                    if (!strcmp(variableList[k], word[i+3])) {
                        integerList[k] += addInt;
                        break;
                    }
                }
            }
            else {
                printf("\nError:'%s' is not a variable. Variable is expected. Line '%d'..!\n", word[i+3],linec);
                exit(0);
            }
            //End of line
            if(strcmp(word[i+4],".")){
                printf("\nError: End of line '.' is expected. Line '%d'..!\n",linec);
                i=i+4;
                exit(0);
            }
            else{
                i=i+4;
            }
        }
        //sub
        else if(!strcmp(word[i], "sub")){
            //Integer Or Variable
            int subInt = 0;
            if (!strcmp(word[i+1],"-END-")) {
                printf("\nError:Integer or variable are expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isKeyword(word[i+1])&&strcmp(word[i+1],"-END-")) {
                printf("\nError: The given count must not be a keyword. Integer or variable are expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isInteger(word[i+1])&&strcmp(word[i+1],"-END-")) {
                subInt = atoi(word[i+1]);
            }
            else if (isIntegerVariable(word[i+1])&&strcmp(word[i+1],"-END-")) {
                for (int k = 0; k < vIndex; k++) {
                    if (!strcmp(variableList[k], word[i+1])) {
                        subInt = integerList[k];
                        break;
                    }
                }
            }
            else {
                printf("\nError: '%s' is not a integer or defined variable. Integer or variable are expected. Line '%d'..!\n", word[i+1],linec);
                exit(0);
            }
            //from
            if (!strcmp(word[i+2],"-END-")) {
                printf("\nError: Keyword 'from' is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (!strcmp(word[i+2], "from")) {

            }
            else {
                printf("\nError: Keyword 'from' is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            //variable
            if (!strcmp(word[i+3],"-END-")){
                printf("\nError: Variable is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isKeyword(word[i+3])&&strcmp(word[i+3],"-END-")) {
                printf("\nError: The given count must not be a keyword. Variable is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isIntegerVariable(word[i+3])&&strcmp(word[i+3],"-END-")) {
                for (int k = 0; k < vIndex; k++) {
                    if (!strcmp(variableList[k], word[i+3])) {
                        integerList[k] -= subInt;
                        break;
                    }
                }
            }
            else {
                printf("\nError:'%s' is not a variable. Variable is expected. Line '%d'..!\n", word[i+3],linec);
                exit(0);
            }
            //End of line
            if(strcmp(word[i+4],".")){
                printf("\nError: End of line '.' is expected. Line '%d'..!\n",linec);
                i=i+4;
                exit(0);
            }
            else{
                i=i+4;
            }
        }
        //Loop
        else if (!strcmp(word[i], "loop")){
            blockLoop[loopsayac][0]=1;
            blockLoop[loopsayac][2]=-1;
            loopsayac++;
            int loopInt=0;
            if (!strcmp(word[i+1],"-END-")) {
                printf("\nError:Integer or variable are expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isKeyword(word[i+1])&&strcmp(word[i+1],"-END-")) {
                printf("\nError: The given count must not be a keyword. Integer or variable are expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (isInteger(word[i+1])&&strcmp(word[i+1],"-END-")) {
                loopInt = atoi(word[i+1]);
                if(loopInt<0){
                    printf("\nError: The given count must not be lower then 1. Integer or variable are expected. Line '%d'..!\n",linec);
                    exit(0);
                }
            }
            else if (isIntegerVariable(word[i+1])&&strcmp(word[i+1],"-END-")) {
                for (int k = 0; k < vIndex; k++) {
                    if (!strcmp(variableList[k], word[i+1])) {
                        loopInt = integerList[k];
                        break;
                    }
                }
                if(loopInt<0){
                    printf("\nError: The given count must not be lower than 1. Integer or variable are expected. Line '%d'..!\n",linec);
                    exit(0);
                }
            }
            else {
                printf("\nError: '%s' is not a integer or defined variable. Integer or variable are expected. Line '%d'..!\n", word[i+1],linec);
                exit(0);
            }
            //times
            if (!strcmp(word[i+2],"-END-")) {
                printf("\nError: Keyword 'times' is expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if (!strcmp(word[i+2], "times")) {

            }
            else {
                printf("\nError: Keyword 'times' is expected. Line '%d'..!\n",linec);
               exit(0);
            }
            blockLoop[loopsayac-1][1]=loopInt;
            //out
            if(!strcmp(word[i+3],"out")){
                blockLoop[loopsayac-1][0]=0;
                blockLoop[loopsayac-1][2]=0;
                blockLoop[loopsayac-1][1]=0;
                loopsayac--;
                if(!strcmp(word[i+4],"-END-")) {
                    printf("\nError:Integer,String,newline or variable are expected. Line '%d'..!\n",linec);
                    exit(0);
                }
                else if(isInteger(word[i+4])&&strcmp(word[i+4],"-END-")){
                    for(int l=0;l<loopInt;l++){
                        printf("%s",word[i+4]);
                    }
                }
                else if(isIntegerVariable(word[i+4])&&strcmp(word[i+4],"-END-")){
                    int cnt=0;
                    for (int k = 0; k < vIndex; k++) {
                        if (!strcmp(variableList[k], word[i+4])) {
                            cnt = integerList[k];
                            break;
                        }
                    }
                    for(int l=0;l<loopInt;l++){
                        printf("%d",cnt);
                    }
                }
                else if(!strcmp(word[i+4],"newline")){
                    for(int l=0;l<loopInt;l++){
                        printf("\n");
                    }
                }
                else if(StrOut&&strcmp(word[i+4],"-END-")){
                    for(int l=0;l<loopInt;l++){
                        printf("%s",word[i+4]);
                    }
                }
                else{
                    printf("\nError: '%s' is not a int,string,newline or variable. Countable Variable is expected. Line '%d'..!\n", word[i+4],linec);
                    exit(0);
                }
                //End of line
                if(strcmp(word[i+5],".")){
                    printf("\nError: End of line '.' is expected. Line '%d'..!\n",linec);
                    i=i+5;
                    exit(0);
                }
                else{
                    i=i+5;
                }
            }
            else if(!strcmp(word[i+3],"[")){
                blockLoop[loopsayac-1][2]=linec-1;
                blockLoop[loopsayac-1][3]=-1;
                loopsayac2++;
                i=i+4;
            }
            else if(!strcmp(word[i+3],"-END-")){
                i=i+3;
            }
            else{
                printf("\nError: Out or open block is expected. Line '%d'..!\n",linec);
                exit(0);
            }
        }
        //openblock
        else if(!strcmp(word[i],"[")){
            blockLoop[loopsayac-1][2]=linec-1;
            blockLoop[loopsayac-1][3]=-1;
            loopsayac2++;
        }
        //closeblock
        else if(!strcmp(word[i],"]")){
            blockLoop[loopsayac-1][3]=linec-1;
            for(int t=0;t<blockLoop[loopsayac-1][1]-1;t++){
                int sta=blockLoop[loopsayac-1][2];
                int end=blockLoop[loopsayac-1][3];
                for(int g=sta+1;g<end;g++){
                    LineParse(lines[g],g+1);
                }
            }
            blockLoop[loopsayac][0]=0;
            loopsayac--;
        }
        //out
        else if (!strcmp(word[i], "out")){
            if(!strcmp(word[i+1],"-END-")) {
                printf("\nError:Integer,String,newline or variable are expected. Line '%d'..!\n",linec);
                exit(0);
            }
            else if(isInteger(word[i+1])&&strcmp(word[i+1],"-END-")){
                printf("%s",word[i+1]);
            }
            else if(isIntegerVariable(word[i+1])&&strcmp(word[i+1],"-END-")){
                int cnt=0;
                for (int k = 0; k < vIndex; k++) {
                    if (!strcmp(variableList[k], word[i+1])) {
                        cnt = integerList[k];
                        break;
                    }
                }
                printf("%d",cnt);

            }
            else if(!strcmp(word[i+1],"newline")){
                printf("\n");
            }
            else if(outStr[sayacKont]>0&&strcmp(word[i+1],"-END-")){
                outStr[sayacKont]--;
                printf("%s",word[i+1]);
                sayacKont++;
            }
            else{
                printf("\nError: '%s' is not a int,string,newline or variable. Countable Variable is expected. Line '%d'..!\n", word[i+1],linec);
                exit(0);
            }
            //End or sep
            if(!strcmp(word[i+2],".")){
                i=i+2;
                sayacKont=sayacKont%3;
            }
            else if(!strcmp(word[i+2],",")){
                if(!strcmp(word[i+3],"-END-")) {
                    printf("\nError:Integer,String,newline or variable are expected. Line '%d'..!\n",linec);
                    exit(0);
                }
                else if(isInteger(word[i+3])&&strcmp(word[i+3],"-END-")){
                    printf("%s",word[i+3]);
                }
                else if(isIntegerVariable(word[i+3])&&strcmp(word[i+3],"-END-")){
                    int cnt=0;
                    for (int k = 0; k < vIndex; k++) {
                        if (!strcmp(variableList[k], word[i+3])) {
                            cnt = integerList[k];
                            break;
                        }
                    }
                    printf("%d",cnt);

                }
                else if(!strcmp(word[i+3],"newline")){
                    printf("\n");
                }
                else if(outStr[sayacKont]>0&&strcmp(word[i+3],"-END-")){
                    outStr[sayacKont]--;
                    printf("%s",word[i+3]);
                    sayacKont++;

                }
                else{
                    printf("\nError: '%s' is not a int,string,newline or variable. Countable Variable is expected. Line '%d'..!\n", word[i+3],linec);
                    exit(0);
                }
                //End or sep
                if(!strcmp(word[i+4],".")){
                    i=i+4;
                sayacKont=sayacKont%3;
                }
                else if(!strcmp(word[i+4],",")){
                    if(!strcmp(word[i+5],"-END-")) {
                        printf("\nError:Integer,String,newline or variable are expected. Line '%d'..!\n",linec);
                        exit(0);
                    }
                    else if(isInteger(word[i+5])&&strcmp(word[i+5],"-END-")){
                        printf("%s",word[i+5]);
                    }
                    else if(isIntegerVariable(word[i+5])&&strcmp(word[i+5],"-END-")){
                        int cnt=0;
                        for (int k = 0; k < vIndex; k++) {
                            if (!strcmp(variableList[k], word[i+5])) {
                                cnt = integerList[k];
                                break;
                            }
                        }
                        printf("%d",cnt);

                    }
                    else if(!strcmp(word[i+5],"newline")){
                        printf("\n");
                    }
                    else if(outStr[sayacKont]>0&&strcmp(word[i+5],"-END-")){
                        printf("%s",word[i+5]);
                        outStr[sayacKont]--;
                        sayacKont++;
                    }
                    else{
                        printf("\nError: '%s' is not a int,string,newline or variable. Countable Variable is expected. Line '%d'..!\n", word[i+5],linec);
                        exit(0);
                    }
                    if(!strcmp(word[i+6],".")){
                        i=i+6;
                        sayacKont=sayacKont%3;
                    }
                    else{
                        i=i+6;
                        printf("\nError: End of line '.' is expected. Line '%d'..!\n",linec);
                        exit(0);
                    }
                }
                else{
                    i=i+4;
                    printf("\nError: End of line '.' or Seperator ',' is expected. Line '%d'..!\n",linec);
                    exit(0);
                }
            }
            else{
                i=i+2;
                printf("\nError: End of line '.' or Seperator ',' is expected. Line '%d'..!\n",linec);
                exit(0);
            }

        }
        else{
            printf("\nError: Undefined variable used.('%s') Line '%d'..!\n",word[i],linec);
            exit(0);
        }
    }
}
