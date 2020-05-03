#include "web_server.h"

int send_string(int sockfd, char *buffer)
{
	int 	sent_bytes;
	int 	bytes_to_send;

	bytes_to_send = strlen(buffer);
	while (bytes_to_send > 0)
	{
		sent_bytes = send(sockfd, buffer, bytes_to_send, 0);
		if (sent_bytes == -1)
			return 0;
		bytes_to_send -= sent_bytes;
		buffer += sent_bytes;
	}
	return 1;
}