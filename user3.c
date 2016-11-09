#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int ch;
int sockfd, portno, n, nsockfd;
struct sockaddr_in serv_addr;
struct hostent *server;
int val;
char buffer[256],pw[10];

void error(char *msg)
{
    perror(msg);
    exit(0);
}

void adduser(int pno)
{ 
int yes;
printf("Enter option.\n 1. Local\n 2.Remote\n");
scanf("%d",&ch);
if(ch==1)
    {
    server = gethostbyname("127.0.0.1");
    }
else {
      server = gethostbyname("10.250.242.36");
      //server = gethostbyname("10.154.20.143");
     }

    printf("%s\n", server->h_name);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(pno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

 printf("Hello you are connected\n");
     bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,"1",1);
     if (n < 0) 
         error("ERROR writing to socket");
   printf("Enter Username : ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,256);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server: %s\n",buffer);
    if(strncmp(buffer,"2",1)==0)
    {
    printf("user exists\n");
    return;
    }
printf("Enter password : ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
printf("Retypr password\n");
    bzero(pw,10);
    fgets(pw,9,stdin);
    
if(strcmp(buffer,pw)==0)
{
printf("Password match\n");
n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
}
	else 
	{
	printf("Invalid password. Enter again\n");
	}
    bzero(buffer,256);
    n = read(sockfd,buffer,256);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server: %s\n",buffer);

/*    bzero(buffer,256);
    fgets(buffer,255,stdin);
    if(strncmp(buffer,"yes",3)==0);
{
while(1)
{
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    if(strncmp(buffer,"end",3)==0) 
    break;
    bzero(buffer,256);
    n = read(sockfd,buffer,256);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server: %s\n",buffer);
}
}*/

return;
}


void deluser(int pno)
{
printf("Enter option.\n 1. Local\n 2.Remote\n");
scanf("%d",&ch);
if(ch==1)
    {
    server = gethostbyname("127.0.0.1");
    }
else {
      server = gethostbyname("10.250.242.36");
     }

printf("%s\n", server->h_name);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(pno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

  printf("Hello you are connected\n");
     bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,"2",1);
     if (n < 0) 
         error("ERROR writing to socket");
printf("Enter Username : ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    printf("%s\n",buffer);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
printf("Enter password : ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,256);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server: %s\n",buffer);
    if(strncmp(buffer,"1",1)==0)
    {
    printf("Succesfull\n");
    }
    else if(strncmp(buffer,"2",1)==0)
    {
    printf("Enter username and password again\n");
    }
    else
    printf("Try remote login\n");
return;
}


void loginr(int prno)
{
    nsockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (nsockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("10.250.242.36");
    

    printf("%s\n", server->h_name);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(prno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

 printf("Hello you are connected\n");
     //bzero(buffer,256);
    //fgets(buffer,255,stdin);
    n = write(nsockfd,"3",1);
     if (n < 0) 
         error("ERROR writing to socket");
printf("Enter Username : ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    printf("%s\n",buffer);
    n = write(nsockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
printf("Enter password : ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(nsockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(nsockfd,buffer,256);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server: %s\n",buffer);
    if(strncmp(buffer,"1",1)==0)
    {
    printf("Succesfull login\n");
    }
    else if(strncmp(buffer,"2",1)==0)
    {
    printf("Enter username and password again\n");
    }
    else
	{
	printf("Not in remote as well\n");
        close(nsockfd);
	}
return;
}



void login(int pno)
{

    server = gethostbyname("127.0.0.1");
    

    printf("%s\n", server->h_name);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(pno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

 printf("Hello you are connected\n");
     //bzero(buffer,256);
    //fgets(buffer,255,stdin);
    n = write(sockfd,"3",1);
     if (n < 0) 
         error("ERROR writing to socket");
printf("Enter Username : ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    printf("%s\n",buffer);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
printf("Enter password : ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,256);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server: %s\n",buffer);
    if(strncmp(buffer,"1",1)==0)
    {
    printf("Succesfull login\n");
    }
    else if(strncmp(buffer,"2",1)==0)
    {
    printf("Enter username and password again\n");
    }
    else
	{
	printf("Try remote login\n");
        close(sockfd);
        loginr(pno);
	}
return;
}




int main(int argc, char *argv[])
{	
    //int yes;
    if (argc < 2) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    printf("Welcome! Enter your choice.\n 1.New user\n 2.Delete user account\n 3.Login\n ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
     val=atoi(buffer);
if(val == 1)
{
adduser(portno);
}
else if(val == 2)
{
deluser(portno);
}
else 
{
login(portno);
}
    close(sockfd);
    return 0;
}


