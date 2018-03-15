#include <stdio.h>
#include <string.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  // Implement if desire
	// int i = 0;
	//
	// while(i < strlen(pattern)){
	//
	// 	if(pattern[i] == '.'){
	// 		char start = pattern[i-1];
	//
	// 		int j = i;
	//
	// 		while(pattern[j] == '.'){
	// 			j++;
	// 		}
	//
	//
	// 		char end = pattern[i + j - 1];
	// 		char end1 = pattern[i+j];
	//
	//
	// 		if((partial_line[0] == start && partial_line[j] == end)){
	//
	// 			return 1;
	// 		}
	//
	// 		else if(start == '\000' && end1 != '\000'){
	//
	// 			if(partial_line[j] == end1)
	// 				return 1;
	// 		}
	// 		else if(start != '\000' && end == '\000'){
	//
	// 			if(partial_line[0] == start)
	// 				return 1;
	// 		}
	// 		else if(start == '\000' && end1 == '\000'){
	// 			if(strlen(partial_line) >= j){
	// 				return 1;
	// 			}
	// 		}
	// 	}
	//
	// 	char preceding;
	//
	// 	if(pattern[i] == '+'){
	// 		preceding = pattern[i-1];
	//
	// 		int j;
	// 		for(j = 0; j <= strlen(partial_line); j++){
	//
	// 			if(preceding == '.'){
	// 				preceding = '\000';
	// 			}
	// 			if (partial_line[j] == preceding) {
	// 				return 1;
	//
	// 			}
	// 		}
	// 	}
	//
	// 	i++;
	// }
	int k = 0;
	char escaped;
	while (k < strlen(pattern)) {
		if(pattern[k] == '\\'){
				escaped = pattern[k+1]
				int j;
				for(j = 0; j <= strlen(partial_line); j++){
					if (partial_line[j] == escaped) {
						return 1;
					}

		}
	}

	return 0;
}

/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by M     AXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
	int i = 0;
	for(i = strlen(line); i > strlen(pattern); i--){
		if(matches_leading(line, pattern) == 1){
			return 1;
		}
		else{
			line++;
		}
	}

	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
		return 2;
	}

    /* we're not going to worry about long lines */
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
