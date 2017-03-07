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
    int sockfd, new_fd;  /* Écouter sur sock_fd, nouvelle connection sur new_fd */
    int error;
    struct sockaddr_in my_addr;    /* Informations d'adresse */
    struct sockaddr_in their_addr; /* Informations d'adresse du client */
    struct sockaddr_in sin;

    int sin_size;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0); /* Contrôle d'erreur! */
    
    my_addr.sin_family = AF_INET;         /* host byte order */
    my_addr.sin_port = htons(MYPORT);     /* short, network byte order */
    my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-remplissage avec mon IP */
    bzero(&(my_addr.sin_zero), 8);        /* zero pour le reste de struct */
    
    /* ne pas oublier les contrôles d'erreur pour ces appels: */
    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
    
    if ((error = bind(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr))) < 0) {
        perror("error bind socket");
        exit(error);
    }
    listen(sockfd,5);
    
    sin_size = sizeof(struct sockaddr_in);
    new_fd = accept(sockfd, &their_addr, &sin_size);

}
