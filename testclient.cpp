#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

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

    int portNum;

    int res;
    struct sockaddr_in addrOfServ;
    struct hostent *server;

    char msgStream[256];
        if (argc < 1) 
    {
        cout << "ERROR: Please enter name and port number" << endl;
        exit(1);
    }
     if (argc < 2) 
    {
        cout << "ERROR: Please enter hostname" << endl;  //hostname is 2nd argument
        exit(1);
    }
    if(argc < 3)
    {
        cout << "ERROR:Please provide host number"<< endl;
        exit(1);
    }

    portNum = atoi(argv[2]);
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        cout << "ERROR: couldnt initialize server" << endl;
        exit(1);
    }
        socketSet = socket(AF_INET, SOCK_STREAM, 0);

    if (socketSet <0)
    {
        cout<< "ERROR: Bad Connection, cant connect" << endl;
        exit(1);
    }
        bzero((char*) &addrOfServ, sizeof(addrOfServ));
        addrOfServ.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&addrOfServ.sin_addr.s_addr, server->h_length);
        addrOfServ.sin_port = htons(portNum);
        if(connect(socketSet, (struct sockaddr *) &addrOfServ, sizeof(addrOfServ))<0)
        {
            cout<< "BAD CONNECTION: cant connect to server" << endl;
            exit(1);
        }
        cout << "please enter message vmro" << endl;
        while(true)
        {
		bzero(msgStream, 256);
		fgets(msgStream,255,stdin);
		res = write(socketSet,msgStream,strlen(msgStream));
		if (res<0)
		{
		    cout<< "Error: cant write to player2" <<endl;
		    exit(1);
		}
		bzero(msgStream,256);
		/*res = read(socketSet,msgStream,255);
		if(res <0);
		{
		    cout<< "ERROR: cant read from socket"<< endl;
		    exit(1);
		}
		cout << msgStream << endl; */
		bool quit = false;
		
		if (strcmp(msgStream, "QUIT")== 0)
		{
		quit = true;
		}
		
		if(quit)
		{
		close(socketSet);
		break;
		}
        }
        return 0;
        
        }
