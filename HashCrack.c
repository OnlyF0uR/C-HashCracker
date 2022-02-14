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

		char* buffer = NULL;
		char* tmp_buf;
		while (fgets(line, sizeof(line), fp)) {
			size_t ln = strlen(line) - 1;
			if (line[ln] == '\n') {
				line[ln] = '\0';
			}

			if (strcmp(argv[2], "sha256") == 0) {
				buffer = malloc((SHA256_DIGEST_LENGTH * 2 + 1) * sizeof(char)); // 65 * sizeof(char)
				computeSHA256(line, buffer);
			}
			else if (strcmp(argv[2], "sha512") == 0) {
				buffer = malloc((SHA512_DIGEST_LENGTH * 2 + 1) * sizeof(char)); // 129 * sizeof(char)
				computeSHA512(line, buffer);
			}
			else {
				printf("Invalid algorithm.");
				return 1;
			}
				
			printf("%s:%s\n", line, buffer);
			
			if (strcmp(argv[1], buffer) == 0) {
				printf("Match found ^.");
				return 0;
			}
		}

		free(buffer);
		printf("No match found.");

		err = fclose(fp);
		if (err != 0) {
			printf("Could not close: %s", argv[3]);
		}
	}

	return 0;
}