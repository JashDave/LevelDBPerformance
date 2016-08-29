#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>

#include<thread>
using namespace std;

void *task1(void *);


        int connFd[1000];
int main(int argc, char* argv[])
{

    long num_cpus = std::thread::hardware_concurrency();
    int pId, portNo, listenFd;
    socklen_t len; //store size of the address
    bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;

    pthread_t threadA[1000];

    if (argc < 2)
    {
        cerr << "Syntam : ./server <port>" << endl;
        return 0;
    }

    portNo = atoi(argv[1]);

    if((portNo > 65535) || (portNo < 2000))
    {
        cerr << "Please enter a port number between 2000 - 65535" << endl;
        return 0;
    }



    //create socket
    listenFd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }

    bzero((char*) &svrAdd, sizeof(svrAdd));

    svrAdd.sin_family = AF_INET;
    //svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);

    if(!inet_aton(argv[2], &svrAdd.sin_addr))
    {
      fprintf(stderr, "ERROR invalid server IP address\n");
      exit(1);
    }
    //bind socket
    if(bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        cerr << "Cannot bind" << endl;
        return 0;
    }

    listen(listenFd, 5);

    len = sizeof(clntAdd);

    int noThread = 0;

    while (noThread < 1000)
    {
        cout << "Listening" << endl;


        //this is where client connects. svr will hang in this mode until client conn
        connFd[noThread] = accept(listenFd, (struct sockaddr *)&clntAdd, &len);

        if (connFd[noThread] < 0)
        {
            cerr << "Cannot accept connection" << endl;
            return 0;
        }
        else
        {
            cout << "Connection successful" << endl;
        }

        pthread_create(&threadA[noThread], NULL, task1, &connFd[noThread]);

        //--------------------------------------
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(noThread%num_cpus, &cpuset);
        int rc = pthread_setaffinity_np(threadA[noThread], sizeof(cpu_set_t), &cpuset);
        if (rc != 0) {
          std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
        }
        //-------------------------------------------------------
        noThread++;
    }

    for(int i = 0; i < 3; i++)
    {
        pthread_join(threadA[i], NULL);
    }


}

void *task1 (void *data)
{
    int connFd = *(int*)data;
    cout << "Thread No: " << pthread_self() << endl;
    char test[(int)1e3 +1 ];
    while(1)
    {
        if(read(connFd, test, (int)1e3) < 0){
          break;
        }
    }
    cout << "\nClosing thread and conn" << endl;
    close(connFd);
}
