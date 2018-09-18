package main

import (
//	"io"
	"log"
	"os"
//	"time"

	"github.com/hashicorp/logutils"
)

func main() {
/*
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
*/
	filter := &logutils.LevelFilter{
		Levels:   []logutils.LogLevel{"DEBUG", "WARN", "ERROR"},
		MinLevel: logutils.LogLevel("WARN"),
		Writer:   os.Stderr,
	}
	log.SetOutput(filter)

	log.Print("[DEBUG] Debugging")         // this will not print
	log.Print("[WARN] Warning")            // this will
	log.Print("[ERROR] Erroring")          // and so will this
	log.Print("Message I haven't updated") // and so will this
}
