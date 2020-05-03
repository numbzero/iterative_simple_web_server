#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define PORT 		8080
#define WEB_DIR 	"../assets/siteWeb/"

#define FILE_400	"file400.html"
#define FILE_404	"file404.html"
#define FILE_500	"file500.html"

#define	RED			"\033[31m"
#define GREEN		"\033[32m"
#define MAGENTA		"\033[35m"
#define	RESET 		"\033[0m"

#define BUF_SIZE	1000

int 	parse_request(char * request_from_client, int request_size, char * string, int string_size);
void	handle_requests(int client_sockfd, struct sockaddr_in *client_addr);
int 	send_string(int sockfd, char *buffer);
int 	get_file_size(int fd);
int		check_image_extension(char *filename);

#endif