#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0};
    char passwd[1024]={0}; 
    char result[1000];
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    valread = read(new_socket,buffer,1024); 
    valread = read(new_socket,passwd,1024);
    printf("Username:%s\n",buffer); 
    printf("Password:%s\n",passwd);
FILE *fp;
char aun[20],apw[20];
char *sd="Authenticated Successfully";
fp = fopen("user_pass.txt","r+");
if(fp==0)
{printf("can not open file");
}
while(fscanf(fp,"%s %s",aun,apw)!=EOF)
if(strcmp(aun,buffer)==0&&strcmp(apw,passwd)==0)
{
char * ins="instructor";
if(strcmp(ins,aun)==0){
    char arr[100000];
    arr[0]='\0';
    FILE *fp3;
    fp3 = fopen("student_marks.txt","r+");
    char temp2[10000];
    while(fgets(temp2, 10000, (FILE*)fp3)!=NULL){
        strcat(arr,temp2);
        temp2[0]='\0';
        
    }
    int sos=strlen(arr);
    arr[sos]='\0';
    printf("%s\n",arr);
        
     send(new_socket , arr , strlen(arr) , 0 );
     exit(0);
} 
send(new_socket,sd ,strlen(sd),0);
FILE *fp2;
fp2 = fopen("student_marks.txt","r+");
if(fp2==0)
{printf("can not open file");
exit(0);
}
char curuser[20];
size_t len = 0;
while(fgets(curuser, 20, (FILE*)fp2)!=NULL)
{  
printf("User:%s\n",curuser);
int i;
    for(i=0;i<20;i++)
    if(curuser[i]=='\n')
    {curuser[i]='\0';
    break;
    }
    if(strcmp(curuser,aun)==0)
    { //printf("Yaha aa gye");
        fgets(result, 1000, (FILE*)fp2); 
        send(new_socket , result , strlen(result) , 0 );
        printf("%s",result);
        exit(0);
    }
    fgets(result, 1000, (FILE*)fp2);

    printf("%s",result);
}
}
    send(new_socket , hello , strlen(hello) , 0 ); 
    //printf("Hello message sent\n"); 
    return 0; 
}