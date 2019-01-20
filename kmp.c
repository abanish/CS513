/*
* Knuth-Morris-Pratt String Matching implementation
* Program: Given a pattern P[1..m] and a Text T[1..n], implement the Knuth-Morris-Pratt string matching algorithm to compute all valid shifts.
*
*/

#include<stdio.h>
#include<string.h>
#define MAX 100

char text[MAX]="";
char pattern[MAX]="";


int prefixFunctionCalculator(int * map){
	int patternLen = strlen(pattern);
	map[0] = 0;
	int k = 0;

	for(int q = 1; q < patternLen; q++){
		while(k > 0 && pattern[k] != pattern[q])
			k = map[k-1];
		if(pattern[k] == pattern[q])
			k = k + 1;
		map[q] = k;
	}
	return -1;
}

int KMP(){
	int textLen = strlen(text);
	int patternLen = strlen(pattern);
	int map[patternLen];
	prefixFunctionCalculator(map);
	int q = 0;
	int n = 0;

	for(int i = 0; i < textLen; i++){
		while(q > 0 && pattern[q] != text[i])
			q = map[q-1];
		if(pattern[q] == text[i])
			q = q+1;

		if(q == patternLen){
			printf("\nValid pattern found with shift %d \n", i-patternLen+1);
			q = map[q-1];
			n++;
		}
	}
    if(n==0){
        printf("\nOops! Pattern not found in the text..\n\n");
    }
    else if(n>=1){
        printf("\nTotal number of given pattern in the text are %d\n\n",n);
    }
    return -1;
}

int main(){
	printf("Enter the complete text here:\n");
	scanf("%[^\n]%*c", text);
	printf("\nEnter the pattern to be searched in above text:\n");
	scanf("%[^\n]%*c", pattern);
	KMP();
	return -1;
}
