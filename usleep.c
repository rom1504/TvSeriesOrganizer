#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("usage: %s <microseconds>\n",argv[0]);
		exit(1);
	}
	usleep(atoi(argv[1]));
	return 0;
	
}