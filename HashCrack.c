#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <string.h>
#include "Algos.h"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Usage: %s <Hash> <Algo> <File>", argv[0]);
		return 2;
	}

	FILE* fp = NULL;
	errno_t err;

	err = fopen_s(&fp, argv[3], "r");
	if (err != 0) {
		printf("Could not open: %s", argv[3]);
		return 1;
	}

	if (fp) {
		char line[256];
		int wasFound = 0;
		while (fgets(line, sizeof(line), fp)) {
			size_t ln = strlen(line) - 1;
			if (line[ln] == '\n') {
				line[ln] = '\0';
			}

			char* buffer = malloc((SHA256_DIGEST_LENGTH * 2 + 1) * sizeof(char)); // 65 * sizeof(char)
			char* tmp_buf;

			if (strcmp(argv[2], "sha256") == 0) {
				computeSHA256(line, buffer);
			}
			else if (strcmp(argv[2], "sha512") == 0) {
				tmp_buf = realloc(buffer, (SHA512_DIGEST_LENGTH * 2 + 1) * sizeof(char)); // 129 * sizeof(char)
				if (tmp_buf == NULL) {
					printf("Realloc failed.");
					return 1;
				}
				buffer = tmp_buf;
				computeSHA512(line, buffer);
			}
			else {
				printf("Invalid algorithm.");
				return 1;
			}
				
			printf("%s:%s\n", line, buffer);
			
			if (strcmp(argv[1], buffer) == 0) {
				printf("Match found ^.");
				wasFound = 1;
				break;
			}
		}

		if (wasFound == 0) {
			printf("No match found.");
		}

		err = fclose(fp);
		if (err != 0) {
			printf("Could not close: %s", argv[3]);
		}
	}

	return 0;
}