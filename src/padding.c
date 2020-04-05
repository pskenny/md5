// Paul Kenny, G00326057, Software Development Year 4, Galway-Mayo Institute Of Technology
// From video lecture from Dr Ian McLoughlin, Theory Of Algorithms

#include <stdio.h>
#include <inttypes.h>

// block of data to process
union block
{
    uint64_t sixtyFour[8];
    uint32_t thirtyTwo[16];
    uint8_t eight[64];
};

// Return the number of 0 bytes to output
uint8_t noZeroBytes(uint8_t noBits)
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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error, no file");
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb");
    if (!infile)
    {
        printf("Can't open file %s", argv[1]);
        return 1;
    }

    // placeholder for current byte read
    uint8_t b;
    // number of bits in file
    uint8_t noBits;

    for (noBits = 0; fread(&b, 1, 1, infile) == 1; noBits += 8)
    {
        // print 2 hexidecimal numbers representing b, padded with up to 2 0's
        printf("%02" PRIu8 " ", b);
    }

    printf("%02" PRIx8, 0x80); // 0x80 is 1000 0000, as in spec

    // print out number of 0 bytes needed
    for (int i = noZeroBytes(noBits); i > 0; i--)
    {
        printf("%02" PRIx8 " ", 0x00);
    }

    // print number of bits (in the file) in hex, padded with up to 16 0's
    printf("%016" PRIx64 "\n", noBits);

    printf("\n");

    fclose(infile);

    return 0;
}
