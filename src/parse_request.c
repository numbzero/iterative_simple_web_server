#include "web_server.h"

int parse_request(char * request_from_client, int request_size, char * string, int string_size)
{
    char * char_ptr[4], * end;

    request_from_client[request_size - 1] = '\0';
    if ((end = strstr(request_from_client, "\r\n\r\n")) == NULL)
        return (-1);
    *(end + 4) = '\0';

    char_ptr[0] = request_from_client;
    char_ptr[1] = strchr(request_from_client, ' ');
    if (char_ptr[1] == NULL)
        return (-1);
    char_ptr[2] = strchr(char_ptr[1] + 1, ' ');
    if (char_ptr[2] == NULL)
        return (-1);
    char_ptr[3] = strchr(char_ptr[2] + 1, '\r');
    if (char_ptr[3] == NULL)
        return (-1);

    * char_ptr[1] = '\0';
    * char_ptr[2] = '\0';
    * char_ptr[3] = '\0';

    if (strcmp(char_ptr[0], "GET") != 0)
        return (-1);
    if (strcmp(char_ptr[2] + 1, "HTTP/1.1") != 0)
        return (-1);
    strncpy(string, char_ptr[1] + 2, string_size);
    
    if (string[string_size - 1] != '\0')
    {
        fprintf(stderr, "[ERROR] parse_request(): string length (size = %d)\n", string_size);
        exit(3);
    }

    if (*(char_ptr[1] + 2) == '\0') strcpy(string, "index.html");
    return (0);
}