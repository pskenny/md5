// MD5 message-digest algorithm implementation from RFC 1321
// Paul Kenny, G00326057, Software Development Year 4, Galway-Mayo Institute Of Technology

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

// Initial buffer values from Section 3.3
uint32_t buffer[] = {
	0x01234567,
	0x89abcdef,
	0xfedcba98,
	0x76543210
};

uint32_t F(uint32_t x, uint32_t y, uint32_t z)
{
	// Section 3.4
	return x & y | ~x & z;
}

uint32_t G(uint32_t x, uint32_t y, uint32_t z)
{
	// Section 3.4
	return x & z | y & ~z;
}

uint32_t H(uint32_t x, uint32_t y, uint32_t z)
{
	// Section 3.4
	return x ^ y ^ z;
}

uint32_t I(uint32_t x, uint32_t y, uint32_t z)
{
	// Section 3.4
	return y ^ (x | ~z);
}

int main(int argc, char argv[])
{
	// Check has an argument
	if (argc == 2)
	{
		printf("Error: expected filename as argument.\n");
		return EXIT_FAILURE;
	}

	// Open file as read-only with no newline translation
	// "rb" means read-only, binary
	FILE* file = fopen(argv[1], "rb");

	if (!file)
	{
		printf("Error: file could not be opened: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	

	return 0;
}
