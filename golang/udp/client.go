package main

import (
    "log"
    "net"
    "os"
)

func main() {
    conn, err := net.Dial("udp", "127.0.0.1:8080")
    if err != nil {
        log.Fatalln(err)
        os.Exit(1)
    }
    defer conn.Close()

    sendBuf := make([]byte, 1024)
    sendBuf = []byte("Ping")
    n, err := conn.Write(sendBuf)
    if err != nil {
        log.Fatalln(err)
        os.Exit(1)
    }
    log.Printf("Send data: %s", string(sendBuf[:n]))

    recvBuf := make([]byte, 1024)
    n, err = conn.Read(recvBuf)
    if err != nil {
        log.Fatalln(err)
        os.Exit(1)
    }
    log.Printf("Received data: %s", string(recvBuf[:n]))
}

