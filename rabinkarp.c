/*
* Rabin Karp String Matching implementation
* Program: Given a pattern P[1..m] and a Text T[1..n], implement the Rabin-Karp string matching algorithm to compute all valid shifts.
*
*/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int rabinKarp(const char *text, const char *pattern)
{
    int i,j;
    int n =0;

    int text_len = strlen(text);
    int pattern_len = strlen(pattern);

    if(text_len == 0 || pattern_len == 0){
        printf("\n\nEither text or pattern or both are empty\n\n");
        printf("exiting...\n\n");
        exit(1);
    }
    if (text_len < pattern_len){
        printf("\n\nPattern length is smaller than text size..\n\n");
        printf("exiting...\n\n");
        exit(1);
    }

    long d = 10;
    long q = 13;
    int k,s;

    long h=1;

    h = (long)pow(d,pattern_len-1)%q;

    int h_pattern = 0;
    int h_tmp = 0;

    //preprocessing the hash values for pattern and first substring of text
    for(int i = 0; i < pattern_len; i++){
		h_pattern = (d*h_pattern + pattern[i])%q;
		h_tmp = (d*h_tmp + text[i])%q;
	}


    for (i = 0; i<=(text_len-pattern_len); i++)
    {
        if(h_tmp == h_pattern)
        {
            for(j=0; j<pattern_len; j++)
            {
                if(pattern[j] != text[i+j])
                {
                    break;
                }
            }
            //substring is same as the pattern
            if(j == pattern_len){
                n++;
                printf("\nPattern found. Valid shift at : %d\n",i);
            }
        }
        //computing rolling hash values from the previous hash value
        if(i < text_len-pattern_len){
			h_tmp = (d*(h_tmp - text[i]*h) + text[h_tmp+pattern_len])%q;
			if(h_tmp < 0)
				h_tmp = h_tmp + q;
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
    char text[10000], pattern[100];
    char temp;
    memset(text, 0, 10000);
    memset(pattern, 0, 100);
    printf("Enter the complete text here:\n");
    scanf("%[^\n]",text);
    printf("\nEnter the pattern to be searched in above text:\n");
    scanf("%c",&temp);
    scanf("%[^\n]",pattern);
    rabinKarp(text, pattern);
    return 0;
}
