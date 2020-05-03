#include "web_server.h"

int		check_image_extension(char *filename)
{
	if (strcmp(filename + (strlen(filename) - 4),  ".jpg") == 0) return 1;
	return 0;
}