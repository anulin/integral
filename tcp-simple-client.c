    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <netdb.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <sys/socket.h>

    #define PORT 3490    /* the port client will be connecting to */

    #define MAXDATASIZE 100 /* max number of bytes we can get at once */
    using namespace std;
    void sssend(int sockfd){
        char u[MAXDATASIZE];
        while(1){
            scanf("%s", u);
            send(sockfd,u,256,0);
        }
    }
    void rrecv(int sockfd){
        char u[MAXDATASIZE];
        while(1){
            recv(sockfd,u,256,0)
            printf("%s", u);
        }
    }
    int main(int argc, char *argv[])
    {
        future<void> ft1, ft2;
        int sockfd, numbytes;
        char buf[MAXDATASIZE], u[MAXDATASIZE];
        struct hostent *he;
        struct sockaddr_in their_addr; /* connector's address information */

        if (argc < 2) {
            fprintf(stderr,"usage: client hostname\n");
            exit(1);
        }

        if ((he=gethostbyname(argv[1])) == NULL) {  /* get the host info */
            herror("gethostbyname");
            exit(1);
        }

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }

        their_addr.sin_family = AF_INET;      /* host byte order */
        their_addr.sin_port = htons(PORT);    /* short, network byte order */
        their_addr.sin_addr = *((struct in_addr *)he->h_addr);
        bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

        if (connect(sockfd, (struct sockaddr *)&their_addr, \
                                              sizeof(struct sockaddr)) == -1) {
            perror("connect");
            exit(1);
        }

        if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
            perror("recv");
            exit(1);
        }

          buf[numbytes] = '\0';
        auto ft1= async(sssend, sockfd);
        auto ft2= async(rrecv, sockfd);
        printf("Received: %s",buf);
        ft1.wait();
        ft2.wait();


        return 0;
    }


