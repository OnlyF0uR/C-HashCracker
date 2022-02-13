#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>

void computeSHA256(char* line, char buffer[65]) {
	unsigned char digest[SHA256_DIGEST_LENGTH];
	SHA256(line, strlen(line), digest);

	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) { // Or sizeof(digest)
		sprintf_s(&buffer[i * 2], 3, "%02x", (unsigned int)digest[i]);
	}
}

void computeSHA512(char* line, char buffer[129]) {
	unsigned char digest[SHA512_DIGEST_LENGTH];
	SHA512(line, strlen(line), digest);

	for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) { // Or sizeof(digest)
		sprintf_s(&buffer[i * 2], 3, "%02x", (unsigned int)digest[i]);
	}
}