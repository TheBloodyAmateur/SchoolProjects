/*
	Author: Botan Celik
	Date: 21.02.2021
	Project: Openssl
	File: main.c

	This program encrypts and decrypts the message "Schoene Crypto Welt".

    GCC: gcc main.c -o main -lcrypto

    GitHub: https://github.com/TheBloodyAmateur/SchoolProjects/aes128
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

void hexToDez(const char *message, const void* data, int len)
{
	printf("%s : ",message);
	const unsigned char * p = (const unsigned char*)data;
	int i = 0;

	for (; i<len; ++i)
        //Print out the first two digits/characters
		printf("%02X ", *p++);

	printf("\n");
}

int main()
{
    //Key, IV and message for the encryption
    static unsigned char key[15] = {0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42};
    static unsigned char iv[15] = {0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42};
    const unsigned char message[] = "Schoene Crypto Welt";

    unsigned char encryptionOutput[sizeof(message)];
	unsigned char decryptionOutput[sizeof(message)];

    AES_KEY enc_key, dec_key;
    //Encryption function: the 128 bit key is set, then the acutal encryption process begins ...
	AES_set_encrypt_key(key, 128, &enc_key);
	AES_cbc_encrypt(message, encryptionOutput, sizeof(message), &enc_key, iv, AES_ENCRYPT);

    //... same process for the decryption process
    AES_set_decrypt_key(key, 128, &dec_key);
    AES_cbc_encrypt(encryptionOutput, decryptionOutput, sizeof(message), &dec_key, iv, AES_DECRYPT);

    //Output of all parameters
    printf("\n%s\n", message);

    printf("========================================\n");

    //Because the program would display a number of random characters the variables must be formated
    hexToDez("\nOriginal message", message, sizeof(message));

	hexToDez("\nEncrypted message",encryptionOutput, sizeof(encryptionOutput));

	hexToDez("\nDecrypted message",decryptionOutput, sizeof(decryptionOutput));

	printf("\n");

	return 0;
}
