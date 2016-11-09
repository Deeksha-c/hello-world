/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int compare_strings(char a[], char b[])
{
   int c = 0;
 
   while (a[c] == b[c]) {
      if (a[c] == '\0' || b[c] == '\0')
         break;
      c++;
   }
 
   if (a[c] == '\0' && b[c] == '\0')
      return 0;
   else
      return -1;
}

int main(int argc, char *argv[])
{	int yes,line,ltemp=1,x,f=0;
     int sockfd, newsockfd, portno, clilen;
      FILE *q,*p;
     char buffer[256],a[256],puffer[256],temp[256],ptemp[256];
     char *l,*ptr;
     char ch;
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
while(1)
 {
	f=0;
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

     bzero(buffer,256);
     n = read(newsockfd,buffer,256);
     printf("%s\n",buffer);

     if(strcmp(buffer,"1")==0)
{
     bzero(buffer,256);
     n = read(newsockfd,buffer,256);
     if (n < 0) error("ERROR reading from socket");

     printf("Client: %s\n",buffer);
    q = fopen("up2.txt","a");
/*if (!q)
    printf( "File could not be opened to retrieve your data from it.\n" );
    else  
    printf("file created!\n");
    */
    fclose(q);

     q = fopen("up2.txt","r");
    fseek(q, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(q);
   //printf("len is %lu\n",len);
    if (len > 0)
    { 
     fseek(q,0,SEEK_SET);
     while(fgets(a,255,q)!=NULL)
     {
      //f=1;
      //printf("inside while loop\n");
      l=strtok(a,":");
      strcpy(temp,l);
      strcat(temp,"\n");
      x=compare_strings(buffer,temp);
       //printf("strncmp is %d\n",x);
      if(x==0)
      {
       printf("User exists\n");
       n = write(newsockfd,"2.User exists",13);
       f=1;
       break;
      }
      }
if(f==1)
   continue;
       n = write(newsockfd,"All good!",9);
      }
else if(len==0)
{

//printf("f is 0\n");
n = write(newsockfd, "3.New user", 10);

}
    strtok(buffer, "\n");
    strcat(buffer,":");
    bzero(puffer,256);
    n = read(newsockfd,puffer,256);
    if (n < 0) error("ERROR reading from socket");
    strcat(buffer,puffer);
    //strtok(buffer, "\n");
   p = fopen("up2.txt","a");
     fprintf(p,"%s",buffer);
      fclose(p);
     printf("1%s",buffer);
   
     n = write(newsockfd,"Added.",6);
     if (n < 0) error("ERROR writing to socket");
  
    
/*   bzero(buffer,256);
     n = read(newsockfd,buffer,256);
     printf("2%s",buffer);
     if (n < 0) error("ERROR reading from socket");

     yes = strncmp(buffer,"yes",3);
     printf("3%d\n",yes);
     while(1)
{ 
     printf("hye");
     bzero(buffer,256);
     n = read(newsockfd,buffer,256);
     //printf("%s\n",buffer);
     if (n < 0) error("ERROR reading from socket");

     if(strncmp(buffer,"end",3)==0) 
     break;

     printf("Client: %s\n",buffer);
     //printf("Server: ");
     //bzero(buffer,256);
     //fgets(buffer,255,stdin);	
     n = write(newsockfd,buffer,256);
     if (n < 0) error("ERROR writing to socket");   
     printf("Echoed back\n"); 
}
*/
close(newsockfd);
}

else if(strcmp(buffer,"2")==0)
{
      bzero(buffer,256);
     n = read(newsockfd,buffer,256);
     if (n < 0) error("ERROR reading from socket");

     printf("Client: %s\n",buffer);

     bzero(puffer,256);
    n = read(newsockfd,puffer,256);
    if (n < 0) error("ERROR reading from socket");
    q = fopen("up2.txt","r");
    line=1;
    p = fopen("replica.txt","w");
while((ptr=fgets(a,255,q))!=NULL)
     {
      l=strtok(a,":");
      strcpy(temp,l);
      strcat(temp,"\n");
      l=strtok(NULL," ");
      strcpy(ptemp,l);
      //strcat(puffer,"\n");
    //  printf("%s len %d \n%s len %d\n",temp,(int)strlen(temp),buffer, (int)strlen(buffer));
      
     // printf("%s %s\n",ptemp,puffer);
     
      x=compare_strings(buffer,temp);
      printf("strncmp is %d\n",x);
      if(x==0)
      {
       printf("User exists\n");
                //printf("%s len %d \n%s len %d\n",ptemp,(int)strlen(ptemp),puffer, (int)strlen(puffer));
       		if(compare_strings(puffer,ptemp)==0)
       		{
    		ltemp=1;
  		 fseek(q,0,SEEK_SET);
                 unsigned long len1 = (unsigned long)ftell(q);
                 printf("len is %lu\n",len1);
  		                
     		while((ch = fgetc(q)) != EOF)
		{
		if(ltemp != line)
                {
                //printf("%d %d\n",ltemp,line);
		putc(ch,p);
                }
		if(ch=='\n')
                {
                 //printf("%d %d\n",ltemp,line);
                 ltemp++;
		 //printf("%d %d\n",ltemp,line);
                }
		}
		fclose(q);
		fclose(p);
		remove("up2.txt");
		rename("replica.txt","up2.txt");
       		n = write(newsockfd,"1.Username exists.Deleted",28);
       		}
       		else
       		{ 
       		n = write(newsockfd,"2.Invalid Password",18);
       		}
       break;
      }
line++;
}
if(x == -1)
{
n = write(newsockfd,"3.User not found",16);
}
 close(newsockfd);
}

else if(strcmp(buffer,"3")==0)
{
     bzero(buffer,256);
     n = read(newsockfd,buffer,256);
     if (n < 0) error("ERROR reading from socket");

     printf("Client: %s\n",buffer);

     bzero(puffer,256);
    n = read(newsockfd,puffer,256);
    printf("password: %s\n",puffer);
    if (n < 0) error("ERROR reading from socket");
    q = fopen("up2.txt","r");
   while((ptr=fgets(a,255,q))!=NULL)
     {
      l=strtok(a,":");
      strcpy(temp,l);
      strcat(temp,"\n");
      l=strtok(NULL," ");
      strcpy(ptemp,l);
      
      x=compare_strings(buffer,temp);
     // printf("strncmp is %d\n",x);
      if(x==0)
      {
       printf("User exists\n");
                //printf("%s len %d \n%s len %d\n",ptemp,(int)strlen(ptemp),puffer, (int)strlen(puffer));
       		if(compare_strings(puffer,ptemp)==0)
       		{
       		n = write(newsockfd,"1.Authenticated",15);
       		}
       		else
       		{ 
       		n = write(newsockfd,"2.Invalid Password",18);
       		}
       break;
      }
}
if(x == -1)
{
n = write(newsockfd,"3.User not found",16);
}
fclose(q);
close(newsockfd);
} 
}   
     close(sockfd); 
     return 0; 
}

