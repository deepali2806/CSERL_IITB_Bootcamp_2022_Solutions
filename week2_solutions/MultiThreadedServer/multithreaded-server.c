/* run using ./server <port> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>

#include <pthread.h>

#define CLIENT_NUMBER 50

void error(char *msg) {
  perror(msg);
  exit(1);
}

void *client_handler(void *arg) {
   int clientfd = *((int *) arg);
   printf("\nClient FD Number %d : ", clientfd);
   char buffer[256];

   // ...thread processing...

   if (clientfd < 0)
          error("ERROR on accept");

        /* read message from client */
         while(1) {
          bzero(buffer, 256);
          int n = read(clientfd, buffer, 255);
          if (n < 0)
            error("ERROR reading from socket");
          if (n == 0)
            break;
          fflush(stdout);

          printf("Here is the message: %s", buffer);

          /* send reply to client */
          fflush(stdout);

          n = write(clientfd, buffer, n);
          if (n < 0)
            error("ERROR writing to socket");
        }
        
 }



int main(int argc, char *argv[]) {

    int thread_arg = 0;
//    pthread_t thread_id[CLIENT_NUMBER];
    pthread_t thread_id;


    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    if (argc < 2) {
      fprintf(stderr, "ERROR, no port provided\n");
      exit(1);
    }

    /* create socket */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
      error("ERROR opening socket");

    /* fill in port number to listen on. IP address can be anything (INADDR_ANY)
    */

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* bind socket to this port number on this machine */

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      error("ERROR on binding");

    /* listen for incoming connection requests Max 10 connections we are taking*/

    listen(sockfd, 10);
    clilen = sizeof(cli_addr);
    int i = 0;
    while (1){

    /* accept a new request, create a newsockfd */
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

        pthread_create(&thread_id, NULL, client_handler, &newsockfd);
        // i++;
        // for (int j = 0; j < i && i < 10; j++)
        // {
        //       pthread_join(thread_id[j], NULL);
        // }
        // i=0;           
    }
    

    return 0;
}
