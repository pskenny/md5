// MD5 message-digest algorithm implementation from RFC 1321
// Paul Kenny, G00326057, Software Development Year 4, Galway-Mayo Institute Of Technology

#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>

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
void nexthash( union block* M, uint32_t *H)
{
	// Placeholder
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
		nexthash(&M, &buffer);
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
