#include "web_server.h"

int get_file_size(int fd)
{
	struct stat stat_struct;

	if (fstat(fd, &stat_struct) == -1) return -1;
	return (int)stat_struct.st_size;
}