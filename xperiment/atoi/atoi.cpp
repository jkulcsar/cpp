#include "string.h"

int atoi_impl(const char* str)
{
	
	if(!str)
		return 0;
	
	while(*str == ' ' || *str == '\t')
		str++;

	int ret = 0;
	bool neg = (*str == '-');
	if(neg || *str == '+')
		str++;

	while(*str && *str >= '0' && *str <= '9')
	{
		ret = ret * 10 + *str - '0';
		str++;
	}

	return (neg ? -ret : ret);
}

char *strrev_impl(char *str) {
	char *p1, *p2;

	if (!str || !*str)
		return str;

	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return str;
}


char* itoa_impl(int n, char* str)
{
	static char digits[] = "0123456789"; /*abcdefghijklmnopqrstuvwxyz";*/
	int i=0, sign;

	if((sign = n) < 0)
		n = -n;

	do
	{
		str[i++] = '0' + (n % 10);
	}
	while( (n = n / 10) > 0);

	if(sign < 0)
		str[i++] = '-';

	str[i] = '\0';
	
	return strrev_impl(str);
}

int main(int argc, char** argv)
{
	const char* number = "12345";
	int value = atoi_impl(number);

	int n = 56789;
	char buffer[10];
	itoa_impl(n, buffer);

	return 0;
}