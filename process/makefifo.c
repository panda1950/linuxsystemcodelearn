#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


int main()
{

	int fd;
	fd = mkfifo("myfifo",0777);
	if(fd < 0)
	{
		perror("create myfifo failed\n");
		return -1;
	}
	printf("create myfifo success\n");
	return 0;
}




