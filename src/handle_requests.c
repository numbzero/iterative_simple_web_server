#include "web_server.h"

void	handle_requests(int client_sockfd, struct sockaddr_in *client_addr)
{
	char		buffer[BUF_SIZE];
	char 		filename[255];
	char		full_path[255 + strlen(WEB_DIR)];
	int 		recv_length;
	int 		fd;
	int 		file_size;
	char		*file_content;
	time_t		t;
	struct tm 	tm;


	recv_length = recv(client_sockfd, buffer, BUF_SIZE, 0);
	if (recv_length > 0)
	{
		t = time(NULL);
		tm = *localtime(&t);
		if (parse_request(buffer, BUF_SIZE, filename, 255) == 0)
		{
			if (filename != NULL)
			{
				strcpy(full_path, WEB_DIR);
				strcat(full_path, filename);
				/* 200 OK */
				if ((access(full_path, R_OK) == 0))
				{
					send_string(client_sockfd, "HTTP/1.1 200 OK\r\n");
					if (check_image_extension(full_path))
						send_string(client_sockfd, "Content-Type: image/jpg\r\n");
					else
						send_string(client_sockfd, "Content-Type: text/html\r\n");
					send_string(client_sockfd, "Server: web_server lab_7\r\n\r\n");
					printf("[%d:%02d:%02d %02d-%02d-%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
					printf("%s%s:%d [200]: /%s%s\n", GREEN, inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port), filename, RESET);	

				}
				else
				{
					/* 404 NOT FOUND */
					if (errno == ENOENT)
					{
						send_string(client_sockfd, "HTTP/1.1 404 NOT FOUND\r\n");
						send_string(client_sockfd, "Content-Type: text/html\r\n");
						send_string(client_sockfd, "Server: web_server lab_7\r\n\r\n");
						strcpy(full_path, WEB_DIR);
						strcat(full_path, FILE_404);
						printf("[%d:%02d:%02d %02d-%02d-%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
						printf("%s%s:%d [404]: /%s%s\n", MAGENTA,inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port), filename, RESET);						
					}
					/* 500 INTERNAL SERVER ERROR */
					else 
					{
						send_string(client_sockfd, "HTTP/1.1 500 INTERNAL SERVER ERROR\r\n");
						send_string(client_sockfd, "Content-Type: text/html\r\n");
						send_string(client_sockfd, "Server: web_server lab_7\r\n\r\n");
						strcpy(full_path, WEB_DIR);
						strcat(full_path, FILE_500);
						printf("[%d:%02d:%02d %02d-%02d-%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
						printf("%s%s:%d [500]: /%s%s\n", RED, inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port), filename, RESET);						

					}
				}
			}
			/* 400 BAD REQUEST */
			else
			{
				send_string(client_sockfd, "HTTP/1.1 400 BAD REQUEST\r\n");
				send_string(client_sockfd, "Content-Type: text/html\r\n");
				send_string(client_sockfd, "Server: web_server lab_7\r\n\r\n");
				strcpy(full_path, WEB_DIR);
				strcat(full_path, FILE_400);
				printf("[%d:%02d:%02d %02d-%02d-%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
				printf("%s%s:%d [400]: /%s%s\n", MAGENTA, inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port), filename, RESET);			}

			fd = open(full_path, O_RDONLY, 0);
			if (fd == -1)
				return ;
			file_size = get_file_size(fd);
			file_content = (char *)malloc(sizeof(char) * file_size);
			read(fd, file_content, file_size);
			send(client_sockfd, file_content, file_size, 0);
			free(file_content);
		}
	}
}