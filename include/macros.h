#pragma once


//DEBUG is used to turn on debuging tools and there are some other Macros that were useful
#define WIDTH 700
#define HEIGHT 540
#define DEBUG false
#define NUMPARTS 30//number of parts to immediately add in debug mode
#define HARD snake.size%2==0


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
