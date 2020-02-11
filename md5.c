// MD5 message-digest algorithm implementation from RFC 1321
// Paul Kenny, G00326057, Software Development Year 4, Galway-Mayo Institute Of Technology

#include<stdio.h>
#include<stdint.h>

// Initial buffer values from Section 
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
	return 0;
}
