    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/wait.h>

    #include <future>

    #define MYPORT 3490    /* the port users will be connecting to */

    #define BACKLOG 10     /* how many pending connections queue will hold */
    using namespace std;
    void resend(int new_fd, int new_fd2)
    {
        char bufer[256];
        while(1) {/* this is the child process */
            recv(new_fd, bufer, 256, 0);
            send(new_fd2, bufer, 256, 0);
        }
    }
    int main()
    {
        char bufer[256];
        int sockfd, new_fd, new_fd2;  /* listen on sock_fd, new connection on new_fd */
        struct sockaddr_in my_addr;    /* my address information */
        struct sockaddr_in their_addr; /* connector's address information */
        int sin_size;

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }

        my_addr.sin_family = AF_INET;         /* host byte order */
        my_addr.sin_port = htons(MYPORT);     /* short, network byte order */
        my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
        bzero(&(my_addr.sin_zero), 8);        /* zero the rest of the struct */

        if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) \
                                                                      == -1) {
            perror("bind");
            exit(1);
        }

        if (listen(sockfd, BACKLOG) == -1) {
            perror("listen");
            exit(1);
        }

          /* main accept() loop */
            sin_size = sizeof(struct sockaddr_in);
            if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, \
                                                          (socklen_t*)&sin_size)) == -1) {
                perror("accept");

            }
            if ((new_fd2 = accept(sockfd, (struct sockaddr *)&their_addr, \
                                                          (socklen_t*)&sin_size)) == -1) {
                perror("accept");

            }
            printf("server: got connection from %s\n");
                        //sinet_ntoa(their_addr.sin_addr));
            auto ft1=async(resend,new_fd2,new_fd);
            auto ft2=async(resend, new_fd, new_fd2);
            //printf("%s",bufer);
            /*close(new_fd);
            exit(0);

            close(new_fd);  /* parent doesn't need this */
            ft1.wait();
            ft2.wait();
            //while(waitpid(-1,NULL,WNOHANG) > 0); /* clean up child processes */

    }

