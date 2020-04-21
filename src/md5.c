// MD5 message-digest algorithm implementation from RFC 1321
// Paul Kenny, G00326057, Software Development Year 4, Galway-Mayo Institute Of Technology

#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<string.h>

// Initial buffer values from Section 3.3
uint32_t buffer[] = {
	0x01234567,
	0x89abcdef,
	0xfedcba98,
	0x76543210
};

// block of data to process
union block
{
    uint64_t sixtyFour[8];
    uint32_t thirtyTwo[16];
    uint8_t eight[64];
};

// Precomputed table from https://en.wikipedia.org/wiki/MD5#Pseudocode
uint32_t T[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

enum flag {READ, PAD0, PAD1, FINISH};

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

// Return the number of 0 bytes to output
uint8_t nozerobytes(uint8_t noBits)
{
    // ULL means unsigned long long, making sure numbers are treated as 64 bit
    // Amount of bits left for padding
    uint8_t result = 512ULL - (noBits % 512ULL);

    // check if there's enough room to do padding
    if (result < 65) // 65 = 1 bit (required in spec) + 64 bits ()
    {
        // Add 512 to make more space
        result += 512;
    }

    // Why? See video timestamp 34:10, 45:00
    // 72 = 8 bits (1000 0000) + 64 bits (length of file)
    result -= 72;

    return (result / 8ULL);
}

uint32_t* generateT()
{
	// From Section 3.4
	// This step uses a 64-element table T[1 ... 64] constructed from the
	// sine function. Let T[i] denote the i-th element of the table, which
	// is equal to the integer part of 4294967296 times abs(sin(i)), where i
	// is in radians. The elements of the table are given in the appendix.

	return NULL;
}

// Read next 512 bit block from file (infile)
// M - 512 bit block to store data
// infile - file to read
// nobits - number of bits currently read from infile
// status - represents state
int nextblock(union block* M, FILE* infile, uint64_t* nobits, 
	enum flag* status)
{
	// Following function incomplete, fragmented. Needs to determine appropriate action based on flag.
	uint8_t i;

	// Read 1 byte (into )
	for(*nobits = 0, i = 0; fread(&M.eight[i], 1, 1, infile) == 1; *nobits += 8)
	{
		// Print out byte just read
		printf("%02" PRIx8, M.eight[i]);
	}

	// Print bits 1000 0000 (see Section )
	printf("%02" PRIx8, 0x80);

	for(uint64_t i = nozerobytes(*nobits); i > 0; --i)
	{
		// Print remaining 0's (minus 64, see nozerobytes documentation )
		printf("%02" PRIx8, 0x00);
	}

	printf("%016" PRIx64, *nobits);
}

// Perform hash calculation on block using initial/previous hash values
// See Section 3.4
void nexthash(union block* M)
{
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

	// Current padded message block
	union block M;
	uint64_t nobits = 0;
	enum flag status = READ;

	// Read next 512 bit block from file, then calculate hash
	while(nextblock(&M, file, nobits, status))
	{
		// Calculate the next hash value
		nexthash(&M);
	}

	// Close file
	fclose(file);

	// Output hash
	for(int i = 0; i < 4; i++)
	{
		printf("%02" PRIX32, H[i]);
	}
	printf("\n");

	return 0;
}
