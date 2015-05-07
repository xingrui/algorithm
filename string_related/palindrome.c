/*
 ============================================================================
 Name        : palindrome.cpp
 Author      : 
 Version     : insert str1 to str2 to make palindrome
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int judge(const char* str1, const char *str2);
int innerJudge(const char* str1, const char *str2);
int judgeSameIndex(const char *str, int nLen);

void extendKMPNext(const char*pattern, int* next, int length);
// T is Pattern String, contain pattern to search
// S is Base String, contain search string.
int extendkmp(const char* S, int lenS, const char* T, int lenT, int* extend);

void printArray(const char* name, int* array, int length);

int isPalindrome(const char* S, int lenS);
void Manacher(int*rad, char*str, int n);

int main(void) {
	//testNext();
	//judge("abab", "abcdabcdabdcbadcba");
	int matchIndex;
	//matchIndex = judge("ababab", "abababababa");
	matchIndex = judge("ad", "abdabba");
	printf("Insert Index = %d\n", matchIndex);
	return EXIT_SUCCESS;
}

void testNext() {
	const char* pattern="ababababababab";
	int len = strlen(pattern);
	int next[100];
	next[0]=0;
	extendKMPNext(pattern, next, len);
	printArray("next array:", next, len);
}

int isPalindrome(const char* S, int lenS) {
	int i= 0;
	while (i < lenS >> 1) {
		if (S[i] != S[lenS-1-i])
			return 0;
		++i;
	}
	return 1;
}

void Manacher(int*rad, char*str, int n) {
	printf("Manacher : %s\n", str);
	int i;
	int mx = 0;
	int id;
	for (i = 1; i < n; ++i) {
		if (mx>i) {
			rad[i]=rad[2*id-i]<mx-i ? rad[2*id-i] : mx-i;
		}

		else
			rad[i] = 1;
		for (; str[i+rad[i]]==str[i-rad[i]]; rad[i]++)
			;
		if (rad[i]+i>mx) {
			mx=rad[i]+i;
			id=i;
		}
	}
}
void revert(char* str, int len) {
	int i = 0;
	while (i < len >> 1) {
		char c = str[i];
		str[i] = str[len - 1 -i];
		str[len-1-i]=c;
		++i;
	}
}
int judge(const char* IStr, const char *BStr) {
	int nMatchIndex = innerJudge(IStr, BStr);
	if (nMatchIndex == -1) {
		char* IDup = strdup(IStr);
		char* BDup = strdup(BStr);
		revert(IDup, strlen(IStr));
		revert(BDup, strlen(BStr));
		nMatchIndex = innerJudge(IDup, BDup);
		if (nMatchIndex != -1)
			nMatchIndex = strlen(BStr) - nMatchIndex;
	}
	return nMatchIndex;
}
int innerJudge(const char* IStr, const char *BStr) {
	int nLenB = strlen(BStr);
	int nSameIndex = judgeSameIndex(BStr, nLenB);
	printf("same index = %d\n", nSameIndex);
	int nLenI = strlen(IStr);
	//judge the left index.
	int* extend = malloc(nSameIndex * sizeof(int)+ 1);
	extendkmp(BStr, nSameIndex, IStr, nLenI, extend);
	extend[nSameIndex] = 0;
	//cat double str1
	char* DBIStr = malloc(2*nLenI + 1);
	memcpy(DBIStr, IStr, nLenI);
	memcpy(DBIStr+nLenI, IStr, nLenI);
	DBIStr[2*nLenI]='\0';
	puts(DBIStr);
	//diff string
	int nLenRe = nLenB - 2 * nSameIndex;
	printf("Diff Length:%d\n", nLenRe);
	char* BReS = malloc(nLenRe+1);
	memcpy(BReS, BStr + nSameIndex, nLenRe);
	BReS[nLenRe] = '\0';
	revert(BReS, nLenRe);
	puts(BReS);
	//find the diff string length
	int* extend2 = malloc(2 *nLenI * sizeof(int));
	extendkmp(DBIStr, 2*nLenI, BReS , nLenRe, extend2);
	//get the fit condition index
	puts("fit condition index:");
	int i;
	int min = nLenI > nLenRe ? nLenRe : nLenI;
	int matchIndex = -1;

	if (nLenRe >= nLenI) {
		if (!isPalindrome(BStr + nSameIndex, nLenRe - nLenI))
			return -1;
		for (i = 0; i <= nSameIndex; ++i) {
			if (extend[i] + i >= nSameIndex)
				if (nSameIndex-i <= 2*nLenI && extend2[nSameIndex - i] >= min) {
					printf("%d ", i);
					matchIndex = i;
					break;
				}
		}
	} else {
		int nn=2*nLenI;
		int n=2*nn+2;
		char* str = malloc(n + 1);
		int * rad = malloc(n*sizeof(int));
		str[0]='$';
		for (i=0; i<=nn; ++i) {
			str[2*i+1]='#';
			str[2*i+2]=DBIStr[i];
		}
		Manacher(rad, str, n);
		printArray("rad", rad, n);
		int nLenSum = nLenI + nLenRe;
		int nLenSub = nLenI - nLenRe;
		printf("nLenI = %d, nLenRe = %d\n", nLenI, nLenRe);
		for (i = 0; i <= nSameIndex; ++i) {
			if (extend[i] + i >= nSameIndex)
				if (nSameIndex-i <= 2*nLenI&& extend2[nSameIndex - i] >= min) {
					if (rad[2*(nSameIndex - i)+nLenSum+1] > nLenSub) {
						matchIndex = i;
					}
				}
		}
	}

	//judge the right index.
	return matchIndex;
}
int judgeSameIndex(const char *str, int nLen) {
	int i = 0;
	while (i < nLen >> 1) {
		if (str[i] != str[nLen - 1 - i])
			break;
		++i;
	}
	return i;
}

void printArray(const char* name, int* array, int length) {
	int i;
	puts(name);
	for (i = 0; i < length; ++i)
		printf("%d ", array[i]);
	puts("");
}

void extendKMPNext(const char*pattern, int* next, int length) {
	int matchedIndex = 0;
	int index;
	while (matchedIndex + 1< length && pattern[matchedIndex]
			== pattern[matchedIndex+1])
		++matchedIndex;
	next[0] = 0;
	next[1] = matchedIndex;
	int sumMaxIndex = 1;
	int maxSearchLength;
	for (index = 2; index < length; ++index) {
		maxSearchLength = sumMaxIndex + next[sumMaxIndex];
		if (next[index-sumMaxIndex] + index < maxSearchLength)
			next[index]=next[index-sumMaxIndex];
		else {
			matchedIndex = (0>maxSearchLength-index) ? 0 : maxSearchLength
					-index;
			while (index+matchedIndex<length&&pattern[matchedIndex]
					==pattern[index+matchedIndex])
				++matchedIndex;
			next[index] = matchedIndex;
			sumMaxIndex = index;
		}
	}
}

int extendkmp(const char* S, int lenS, const char* T, int lenT, int* extend) {
	int i = 0;
	printf("S: ");
	for (i = 0; i < lenS; ++i)
		putchar(S[i]);
	printf("\nT: ");
	for (i = 0; i < lenT; ++i)
		putchar(T[i]);
	puts("");
	int* next = malloc(lenT * sizeof(int));
	int index;
	extendKMPNext(T, next, lenT);

	int matchedIndex = 0;
	int minLen = lenS < lenT ? lenS : lenT;
	while (matchedIndex < minLen && T[matchedIndex] == S[matchedIndex])
		++matchedIndex;
	extend[0] = matchedIndex;
	int sumMaxIndex = 0;
	int maxSearchLength;
	for (index = 1; index < lenS; ++index) {
		maxSearchLength = sumMaxIndex + extend[sumMaxIndex];
		if (next[index - sumMaxIndex] + index < maxSearchLength)
			extend[index] = next[index - sumMaxIndex];
		else {
			matchedIndex = (0 > maxSearchLength - index) ? 0 : maxSearchLength
					- index;
			while (index + matchedIndex<lenS && matchedIndex < lenT
					&& T[matchedIndex]==S[index+matchedIndex])
				++matchedIndex;
			extend[index] = matchedIndex;
			sumMaxIndex = index;
		}
	}
	printArray("next array:", next, lenT);
	printArray("extend array:", extend, lenS);
	return 0;
}
#define M 20000050
char str1[M], str[2*M];//start from index 1
int rad[M], nn, n;

int testManacher() {
	int i, ans;
	while (scanf("%s", str1)!=EOF) {
		nn=strlen(str1);
		n=2*nn+2;
		str[0]='$';
		for (i=0; i<=nn; ++i) {
			str[2*i+1]='#';
			str[2*i+2]=str1[i];
		}
		Manacher(rad, str, n);
		ans = 1;
		for (i=0; i<n; ++i)
			ans=rad[i]>ans ? rad[i] : ans;
		printf("%d\n", ans-1);
		fflush(stdout);
	}
	return 0;

}
