#pragma once


//DEBUG is used to turn on debuging tools and there are some other Macros that were useful
#define WIDTH 700
#define HEIGHT 540
#define DEBUG false
#define DIFFICULTY 4
#define NUMPARTS 0//number of parts to immediately add in debug mode



void LOG()
{
	printf("check\n");
}

void LOG(int i)
{
	printf("%d\n", i);
}
void LOG(double d)
{
	printf("%f\n", d);
}
void LOG(float f)
{
	printf("%f\n", f);
}
