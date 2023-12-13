#include "../lib/pageserving.h"
#include "../lib/common.h"


bool handlePageRequest(char *route, int clientSocket){
    char fileURL[100];
    // generate file URL
    getFileURL(route, fileURL);
 
    // read file
    FILE *file = fopen(fileURL, "r");
    if (!file){
        const char response[] = "HTTP/1.1 404 Not Found\r\n\n";
        send(clientSocket, response, sizeof(response), 0);
        return false;
    }else{
        // generate HTTP response header
        char resHeader[SIZE];

        // get current time
        char timeBuf[100];
        getTimeString(timeBuf);

        // generate mime type from file URL
        char mimeType[32];
        getMimeType(fileURL, mimeType);
        sprintf(resHeader, "HTTP/1.1 200 OK\r\nDate: %s\r\nContent-Type: %s\r\n\n", timeBuf, mimeType);
        int headerSize = strlen(resHeader);

        printf(" %s", mimeType);

        // Calculate file size
        fseek(file, 0, SEEK_END);
        long fsize = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Allocates memory for response buffer and copies response header and file contents to it
        char *resBuffer = (char *)malloc(fsize + headerSize);
        strcpy(resBuffer, resHeader);

        // Starting position of file contents in response buffer
        char *fileBuffer = resBuffer + headerSize;
        if(fread(fileBuffer, fsize, 1, file) != static_cast<size_t>(fsize)){
            //To avoid memory leak and unused variables
        }

        send(clientSocket, resBuffer, fsize + headerSize, 0);
        free(resBuffer);
        fclose(file);
        return true;
    }
    
}

void getTimeString(char *buf)
{
    time_t now = time(0);
    struct tm tm = *gmtime(&now);
    strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
}

void getFileURL(char *route, char *fileURL){
    // if route has parameters, remove them
    char *question = strrchr(route, '?');
    if (question)
        *question = '\0';

    // if route is empty, set it to index.html
    if (route[strlen(route) - 1] == '/'){
        strcat(route, "index.html");
    }

    // get filename from route
    strcpy(fileURL, "client/public");
    strcat(fileURL, route);

    // if filename does not have an extension, set it to .html
    const char *dot = strrchr(fileURL, '.');
    if (!dot || dot == fileURL){
        strcat(fileURL, ".html");
    }
}

void getMimeType(char *file, char *mime){
    // position in string with period character
    const char *dot = strrchr(file, '.');

    // if period not found, set mime type to text/html
    if (dot == NULL)
        strcpy(mime, "text/html");

    else if (strcmp(dot, ".html") == 0)
        strcpy(mime, "text/html");

    else if (strcmp(dot, ".css") == 0)
        strcpy(mime, "text/css");

    else if (strcmp(dot, ".js") == 0)
        strcpy(mime, "application/js");

    else if (strcmp(dot, ".jpg") == 0)
        strcpy(mime, "image/jpeg");

    else if (strcmp(dot, ".png") == 0)
        strcpy(mime, "image/png");

    else if (strcmp(dot, ".gif") == 0)
        strcpy(mime, "image/gif");
    else
        strcpy(mime, "text/html");
}