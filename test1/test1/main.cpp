#include <stdio.h>
#include <string.h>

typedef struct {
	long long s1[2][100];
}AA;

void main()
{
	AA aa;
	printf("%d\n", sizeof(AA));
	memset((&aa), 0xff, sizeof(aa));
	printf("%lld", aa.s1[1][98]);

	getchar();
}