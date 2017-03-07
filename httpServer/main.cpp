//
//  main.cpp
//  httpServer
//
//  Created by jerome on 02/03/2017.
//  Copyright © 2017 jerome. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define DEST_IP   "132.241.5.10"
#define DEST_PORT 23
#define MYPORT 3490

// définition des structures

//struct in_addr {
//    unsigned long s_addr;  // load with inet_aton()
//};
//
//struct sockaddr_in {
//    short            sin_family;   // e.g. AF_INET
//    unsigned short   sin_port;     // e.g. htons(3490)
//    struct in_addr   sin_addr;     // see struct in_addr, below
//    char             sin_zero[8];  // zero this if you want to
//};



int main (int argc, char *argv[]) {
    int sockfd, new_fd;
    pid_t pid = 0;
    socklen_t clientLength;  /* Écouter sur sock_fd, nouvelle connection sur new_fd */
    int error;
    struct sockaddr_in server_addr;    /* Informations d'adresse */
    struct sockaddr_in client_addr; /* Informations d'adresse du client */
    struct sockaddr_in sin;

    int sin_size;
    memset(&server_addr, 0, sizeof(server_addr)); //zero out the sockaddr

    
    sockfd = socket(AF_INET, SOCK_STREAM, 0); /* Contrôle d'erreur! */
    
    server_addr.sin_family = AF_INET;         /* défini le type d'adresse avec lesquelle notre socket va communiquer */
    server_addr.sin_port = htons(MYPORT);     /* short, network byte order */
    server_addr.sin_addr.s_addr = INADDR_ANY; /* accepte n'importe quelle type d'adresse : pour localhost uniquement :  inet_addr("127.0.0.1");*/
    bzero(&(server_addr.sin_zero), 8);        /* zero pour le reste de struct */
    
    
    /* ne pas oublier les contrôles d'erreur pour ces appels: */
//    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    
    if ((error = bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr))) < 0) {
        perror("error bind socket");
        exit(error);
    } else {
        std::cout << "socket binded \n";
    }
    
    listen(sockfd,5);
    clientLength = sizeof(client_addr);

    sin_size = sizeof(struct sockaddr_in);
    while ((new_fd = accept(sockfd, (struct sockaddr *) &client_addr, &clientLength)) >= 0)
    {
        //...process new connection...
        pid = fork();
        if (pid < 0) {
            perror("ERROR on fork");
        }
        if (pid == 0)  {
            close(sockfd);
            // handle incomming requests
          //  error = hr->handleRequest(new_fd);
            if (error < 0) {
                perror("ERROR on handleRequest");
                exit(error);
            }
            else { std::cout << "hanlde request success \n"; }
            exit(0);
        }
        else close(new_fd);
        
        // close connection
        close(new_fd);
    }
}

