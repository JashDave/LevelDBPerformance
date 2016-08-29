package main

import (
  "os"
  "fmt"
  "net"
)

func handleClient(tid int,conn net.Conn) {
    databuf := make([]byte,64*1024)
    for {
      _,err := conn.Read(databuf)
      if(err!=nil){
        fmt.Println("Error in connection",tid);
        return
      }
    }
}

func main() {
  thread_id := 1;
  socket := os.Args[1] //Read form command line arugment eg. "10.129.28.101:8090"
  ln, err := net.Listen("tcp",socket)
  if err != nil {
    panic(err)
    return
    } else {
      fmt.Println("Server started at ",os.Args[1])
      for{
        conn, err := ln.Accept()
        if err != nil {
          continue
        }
        go handleClient(thread_id,conn)
        thread_id++
      }
    }
  }
