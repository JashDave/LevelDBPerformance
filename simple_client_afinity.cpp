
#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <vector>
#include<thread>


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



#define MAX_INPUT_SIZE 1048576 //1MB

using namespace std;


void  sender_cl(string ip_addr,int port){

  uint32_t num_bytes;
  char op_code;
  int portnum;
  string ip;
  int sockfd, n;
  struct sockaddr_in server_addr;
  char inputbuf[MAX_INPUT_SIZE],*more_buf;
  char outbuf[MAX_INPUT_SIZE];


  string data="";
  for(int i=0;i<20;i++){
    data+="1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  }


  ip=ip_addr;
  portnum=port;
  /* Create client socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    fprintf(stderr, "ERROR opening socket\n");
    exit(1);
  }

  /* Fill in server address */
  bzero((char *) &server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  if(!inet_aton(ip.c_str(), &server_addr.sin_addr))
  {
    fprintf(stderr, "ERROR invalid server IP address\n");
    exit(1);
  }
  server_addr.sin_port = htons(portnum);

  /* Connect to server */
  if (connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
  {
    fprintf(stderr, "ERROR connecting\n");
    exit(1);
  }
  cout<<"Connected to server\n";

  while(1){
    if (write(sockfd,data.c_str(),data.size()) < 0){
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  if(argc<3){
    cout<<"port ip missing"<<endl;
    exit(0);
  }
  string ip=string(argv[2]);
  int port=atoi(argv[1]);

  thread threads[10000];
  //int cnt=8;

  long num_cpus = std::thread::hardware_concurrency();



  for(int i=0;i<cnt;i++){
    threads[i] = thread(sender_cl,ip,port);
    //--------------------------------------
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(i%num_cpus, &cpuset);
    int rc = pthread_setaffinity_np(threads[i].native_handle(), sizeof(cpu_set_t), &cpuset);
    if (rc != 0) {
      std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
    }
    //-------------------------------------------------------
  }
  for(int i=0;i<cnt;i++){

    if (threads[i].joinable()) {
      threads[i].join();
    }
  }
  return 0;
}
