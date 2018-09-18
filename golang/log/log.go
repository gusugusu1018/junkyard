package main

import (
	"time"
	"log"
	"os"
	"io"
)

func main() {
	logfilename := "LOG_" + time.Now().String() + ".log"
	logfile, err := os.OpenFile(logfilename, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0666)
	if err != nil {
		panic("cannnot open logfile:" + err.Error())
	}
	defer logfile.Close()
	log.SetFlags(log.LstdFlags | log.Lmicroseconds | log.Lshortfile)
	log.SetOutput(io.MultiWriter(logfile, os.Stdout))
	log.SetPrefix("[Hello] ")
	log.Println("Hello World")
}
