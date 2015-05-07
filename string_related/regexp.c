/*
 ============================================================================
 Name        : regexp.cpp
 Author      : xingrui
 Version     : A Small Regular Matcher
 Copyright   : GPL
 Description : A Matcher To Test Whethe The Input Match The Regular
 ============================================================================
 */
 
int matchhere(char* regexp, char*text);
int matchstar(char c, char* regexp, char*text);

int match(char* regexp, char*text) {
	if (regexp[0] == '^')
		return matchhere(regexp + 1, text);
	do {
		if (matchhere(regexp, text))
			return 1;
	} while (*text++ != '\0');
	return 0;
}

int matchhere(char*regexp, char*text) {
	if (regexp[0] == '\0')
		return 1;
	if (regexp[0] == '$'&& regexp[1] == '\0')
		return *text == '\0';
	if (regexp[1] == '*')
		return matchstar(text[0], regexp + 2, text);
	if (*text!= '\0'&& (regexp[0] == '.'|| regexp[0] == *text))
		return matchhere(regexp+1, text+1);
	return 0;
}

int matchstar(char c, char*regexp, char*text) {
	do {
		if (matchhere(regexp, text))
			return 1;
	} while (*text != '\0'&& (*text++ == c || c=='.'));
	return 0;
}
