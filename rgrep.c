#include <stdio.h>
#include <string.h>
#define MAXSIZE 4096

int matches_leading(char*, char*, int);

//This function will be very similar to the matches_leading
int backSlashCheck(char* partial_line, char* pattern, int patternIndex){
	int i = patternIndex;
	//If you reach this point and your pattern++ which is passed through the function
	//is a '\000' then it reached the end and return 1
	if(pattern[i] == '\000'){
		return 1;
	}
	//Checks for the case if the next character is '\'
	if(pattern[i] == '\\'){
		if(partial_line[0] == '\\'){
			return matches_leading(++partial_line, pattern, i = i + 2);
		}
	}
	//Checks for the case where the . is after the '\'
	else if(pattern[i] == '.'){
		if(partial_line[0] == '.'){
			return matches_leading(++partial_line, pattern, ++i);
		}
	}
	//Checks for the case where the ? is after the '\'
	else if(pattern[i] == '?'){
		if(partial_line[0] != '?'){
			return matches_leading(partial_line, pattern, i);
		}
		return matches_leading(partial_line, pattern, ++i) || matches_leading(++partial_line, pattern, i);
	}
	//Checks for the case where the + is after the '\'
	else if(pattern[patternIndex] == '+'){
		if(partial_line[0] == '+'){
			return matches_leading(++partial_line, pattern, ++i);
		}
	}
	//This case is when the thing after the '\' is not a wildcard
	else if(pattern[i] == partial_line[0]){
		return matches_leading(++partial_line, pattern, ++i);
	}
	return 0;
}
//WIll try to implment a recurssive search pattern
int matches_leading(char *partial_line, char *pattern, int patternIndex) {
	//If you reached the end of the pattern and did not return 0 then the
	//pattern passed
	int i = patternIndex;

	if(pattern[i] == '\000'){
		return 1;
	}

	char next = pattern[i + 1];

	if(pattern[i] == '\\'){
		return backSlashCheck(partial_line, pattern, ++i);
	}

	else if(pattern[i] == '.'){
		//This is for the case where it will return any length of char .+
		if(next == '+'){
			int next2 = pattern[i+2];
			int lineCount = 0;
			while(partial_line[lineCount] != next2){
				++partial_line;
			}
			return matches_leading(partial_line, pattern, i=i+2);
		}
		//Since the dot will almost always pass then I will move on to the next thing in pattern.
		return matches_leading(++partial_line, pattern, ++i);
	}
	//Check if the next characters is one of the wild cards that rely on the
	// previous character
	if(next == '+'){
		//For the plus if you check the prev character which is i
		//if the character does not match then the plus will not work
		if(pattern[i] != partial_line[0]){
			return 0;
		}

		//Since the conditon ^ passed then + condition was passed so move on
		//Move the pattern cursor two to the right to skip the letter and
		//the +
		return matches_leading(++partial_line, pattern, i) || matches_leading(partial_line, pattern, i = i + 2);
	}
	//Like the + where it checks the next character for the wildcard
	else if(next == '?'){
		//This is the condition where the char before ? does not exist so it moves
		//on
		if(pattern[i] != partial_line[0]){
			return matches_leading(partial_line, pattern, i = i + 2);
		}
		//When it includes things before and after the question mark
		//This means the pattern and partial_line are the same so we need
		//To check after the ?
		return matches_leading(partial_line, pattern, i = i + 2) || matches_leading(++partial_line, pattern, i);

	}
	//This means that none of the wildcard got called and that we are checking
	//if the characters match
	else{
		if(pattern[i] == partial_line[0]){
			return matches_leading(++partial_line, pattern, ++i);
		}
		else{
			return 0;
		}
	}
	return 0;
}

int rgrep_matches(char *line, char *pattern) {
	int i = 0;
	int size = strlen(line);
	while(i <=  size || i <= strlen(pattern)){
		if(matches_leading(line, pattern, 0) == 1){
			return 1;
		}
		else{
			++line;
			++i;
		}
	}

	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
		return 2;
	}

	char buf[MAXSIZE];

	while (!feof(stdin) && !ferror(stdin)) {
		if (!fgets(buf, sizeof(buf), stdin)) {
			break;
		}
		if (rgrep_matches(buf, argv[1])) {
			fputs(buf, stdout);
			fflush(stdout);
		}
	}

	if (ferror(stdin)) {
		perror(argv[0]);
		return 1;
	}
	return 0;
}
