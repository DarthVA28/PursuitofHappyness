#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

void raiseError(char* errMsg) //error flag message
{
    cout << "ERROR:" << endl;
    perror(errMsg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int socketSet;
    int newSocket;
    int portNum;
    socklen_t clientSize;
    int res;
    char buffer[256];
    struct sockaddr_in addrOfServ, addrOfClient;

    if (argc < 1) 
    {
        cout << "ERROR: Please enter name and port number" << endl;
        exit(1);
    }
     if (argc < 2) 
    {
        cout << "ERROR: Please enter port number" << endl;  //port num is 2nd argument
        exit(1);
    }

    socketSet = socket(AF_INET, SOCK_STREAM ,0) ; //make connection via internet/local host
    if (socketSet <0)
    {
        cout<< "ERROR: Bad Connection, cant connect" << endl;
        exit(1);
    }

    bzero((char*) &addrOfServ, sizeof(addrOfServ));
    portNum = atoi(argv[1]); // convert portNum given to usable form


    addrOfServ.sin_family = AF_INET;
    addrOfServ.sin_port = htons(portNum);
    addrOfServ.sin_addr.s_addr =INADDR_ANY;

    if(bind(socketSet,(struct sockaddr*) &addrOfServ, sizeof(addrOfServ))< 0)
    {
        cout << "ERROR: Cannot bind" << endl;
        exit(1);
    }

    listen(socketSet,7);
    
   
    clientSize  = sizeof(addrOfClient);
    newSocket = accept(socketSet,(struct sockaddr*) &addrOfClient, &clientSize);
    if (newSocket <0)
    {
        cout << "BAD CONNECTION ERROR: cant connect to server" << endl;
    
    }

    while(true)
    {       bzero(buffer,256);
    	    res = read(newSocket, buffer, 255);
	    if(res <0)
	    {
		cout<< " ERROR : cant read from buffer" << endl;
		exit(1);
	    }
	    cout << "here is the message : \n" << buffer << endl;
	    //res = write(newSocket, "I got your message",18);
	    if (res<0)
	    {
		cout << "Error: cant write to client"<< endl;
		exit(1);
	    }
	    if(strcmp(buffer,"QUIT") ==0)
	    {
	    	close(socketSet);
	    	close(newSocket);
	    	break;
            }
	    
    }
    return 0;
    



}
