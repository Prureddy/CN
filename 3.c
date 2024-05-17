#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
void func(int connfd) 
{ 
 char buff[MAX]; 
 int n; 
 for (;;) { 
 bzero(buff, MAX); 
 read(connfd, buff, sizeof(buff)); 
 printf("From client: %s\t To client : ", buff); 
 bzero(buff, MAX); 
 
21CT2607 COMPUTER NETWORKS LAB 69
21CT2607 COMPUTER NETWORKS LAB 70
n = 0; 
 while ((buff[n++] = getchar()) != '\n') 
 ; 
 write(connfd, buff, sizeof(buff)); 
 if (strncmp("exit", buff, 4) == 0) { 
 printf("Server Exit...\n"); 
 break; 
 } 
 } 
} 
int main() 
{ 
 int sockfd, connfd, len; 
 struct sockaddr_in servaddr, cli; 
 sockfd = socket(AF_INET, SOCK_STREAM, 0); 
 if (sockfd == -1) { 
 printf("socket creation failed...\n"); 
 exit(0); 
 } 
 else
 printf("Socket successfully created..\n"); 
 bzero(&servaddr, sizeof(servaddr)); 
 servaddr.sin_family = AF_INET; 
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
 servaddr.sin_port = htons(PORT); 
 if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
 printf("socket bind failed...\n"); 
 exit(0); 
21CT2607 COMPUTER NETWORKS LAB 71
21CT2607 COMPUTER NETWORKS LAB 72
 } 
 else
 printf("Socket successfully binded..\n"); 
 if ((listen(sockfd, 5)) != 0) { 
 printf("Listen failed...\n"); 
 exit(0); 
 } 
 else
 printf("Server listening..\n"); 
 len = sizeof(cli); 
 connfd = accept(sockfd, (SA*)&cli, &len); 
 if (connfd < 0) { 
 printf("server accept failed...\n"); 
 exit(0); 
 } 
 else
 printf("server accept the client...\n"); 
 func(connfd); 
 close(sockfd); 
}
// TCP Client
#include <arpa/inet.h> 
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
21CT2607 COMPUTER NETWORKS LAB 73
21CT2607 COMPUTER NETWORKS LAB 74
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
 char buff[MAX];
 int n;
 for (;;) {
 bzero(buff, sizeof(buff));
 printf("Enter the string : ");
 n = 0;
 while ((buff[n++] = getchar()) != '\n')
 ;
 write(sockfd, buff, sizeof(buff));
 bzero(buff, sizeof(buff));
 read(sockfd, buff, sizeof(buff));
 printf("From Server : %s", buff);
 if ((strncmp(buff, "exit", 4)) == 0) {
 printf("Client Exit...\n");
 break;
 }
 }
}
int main()
{
 int sockfd, connfd;
 struct sockaddr_in servaddr, cli;
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
21CT2607 COMPUTER NETWORKS LAB 75
21CT2607 COMPUTER NETWORKS LAB 76
if (sockfd == -1) {
 printf("socket creation failed...\n");
 exit(0);
 }
 else
 printf("Socket successfully created..\n");
 bzero(&servaddr, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
 servaddr.sin_port = htons(PORT);
 if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
 != 0) {
 printf("connection with the server failed...\n");
 exit(0);
 }
 else
 printf("connected to the server..\n");
 func(sockfd);
 close(sockfd);
}
