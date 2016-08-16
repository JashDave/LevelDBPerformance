//CSV file formate
//http://www.computerhope.com/issues/ch001356.htm

#include <iostream>
#include "TestUtils.h"
#include "../../KVStore.h"

#define conn_str "127.1.1.1:8090" //To be passed during make test CONN="conn string"
//#define iter 10000

#define ll long long
#define ull unsigned long long

using namespace std;
using namespace kvstore;


void singleRead(ull datasize,ull iter,string filename,string tb_name=""){
    ll i;
    Measure m;
    KVStore<ll,string> kvs;
    KVData<string> kd;
    kvs.bind(conn_str,"table_single_rw"+tb_name);
    for(i=0;i<iter;i++){
      m.start();
      kd = kvs.get(i);
      m.end();
      if(kd.ierr<0){
        cout<<"Error in single read "<<datasize<<"B at i="<<i<<" : "<<kd.serr<<endl;
      }
    }
    string desc = "Single Read,KeyType:long long,KeySize:64bits,ValueType:string,ValueSize:"+to_string(datasize)+"Bytes";
    m.print(desc);
    m.saveToFile(desc,filename);
}


void singleWrite(ull datasize,ull iter,string filename,string tb_name=""){
    ll i;
    string data="";
    for(i=0;i<datasize;i++){
      data+=char('a'+i%26);
    }
    //cout<<data;
    Measure m;
    KVStore<ll,string> kvs;
    KVData<string> kd;
    kvs.bind(conn_str,"table_single_rw"+tb_name);
    for(i=0;i<iter;i++){
      m.start();
      kd = kvs.put(i,data);
      m.end();
      if(kd.ierr<0){
        cout<<"Error in single write "<<datasize<<"B at i="<<i<<" : "<<kd.serr<<endl;
      }
    }
    string desc="Single Write,KeyType:long long,KeySize:64bits,ValueType:string,ValueSize:"+to_string(datasize)+"Bytes";
    m.print(desc);
    m.saveToFile(desc,filename);
}


int main(int argc,char *argv[]) {
  //cout<<currentDateTime()<<endl;

  ull K = 1e3;
  ull M = 1e6;
  string folder = "SameMachine_LabPC_2/";
  singleWrite(10,100000,folder+"SingleWrite_10B_100000.csv");
  singleRead (10,100000,folder+"SingleRead_10B_100000.csv");

  singleWrite(K,100000,folder+"SingleWrite_1KB_100000.csv");
  singleRead (K,100000,folder+"SingleRead_1KB_100000.csv");

  singleWrite(2*K,100000,folder+"SingleWrite_2KB_100000.csv");
  singleRead (2*K,100000,folder+"SingleRead_2KB_100000.csv");

  singleWrite(100*K,1000,folder+"SingleWrite_100KB_1000.csv");
  singleRead (100*K,1000,folder+"SingleRead_100KB_1000.csv");

  singleWrite(1*M,1000,folder+"SingleWrite_1MB_1000.csv");
  singleRead (1*M,1000,folder+"SingleRead_1MB_1000.csv");

  return 0;
}
