/*Program to print longest common subsequence of two sequences using Dynamic Programming.
*Author: Abanish Chaudhary
*Roll No: 184101046
*/

#include<stdio.h>
#include<string.h>

int max(int a, int b);
void findLCS(char *X, char *Y, int m, int n);

int max(int a, int b) {
	return (a > b)? a : b;
}

void findLCS(char *X, char *Y, int m, int n) {
	int L[m + 1][n + 1];
	int i, j, k;

	/*
	 * find the length of the LCS
	 */
	for(i = 0; i <= m; i++) {

		for(j = 0; j <= n; j++) {

			if(i == 0 || j == 0) {

				L[i][j] = 0;

			} else if(X[i - 1] == Y[j - 1]) {

				L[i][j] = L[i - 1][j - 1] + 1;

			} else {

				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
			}
		}
	}

	/*
	 * Print LCS
	 */
	i = m;
	j = n;
	//L[i][j] is the length of the longest common subsequence.
	k = L[i][j];

	char LCS[k+1];

	/*
	 * setting the NULL character at the end of LCS character array.
	 */
	LCS[k] = '\0';

	while(i > 0 && j > 0) {

		if(X[i - 1] == Y[j - 1]) {

			LCS[k - 1] = X[i - 1];

			k--;
			i--;
			j--;

		} else if(L[i - 1][j] > L[i][j - 1]) {

			i--;

		} else {

			j--;

		}

	}

	//print results.
	printf("Length of the LCS: %d\n", L[m][n]);
	printf("Longest Common Subsequence is: %s\n", LCS);
}

int main(void) {

	//the two sequences
	char X[] = "POTATO";
	char Y[] = "TOMATO";

	//length of the sequences
	int XLen = strlen(X);
	int YLen = strlen(Y);

	findLCS(X, Y, XLen, YLen);

	return 0;
}
