package main

import (
	"time"
	"os"
	"io"

	"github.com/spiegel-im-spiegel/logf"
)

func main() {
	logfilename := "./logs/LOG_" + time.Now().String() + ".log"
	logfile, err := os.OpenFile(logfilename, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0666)
	if err != nil {
		panic("cannnot open logfile:" + err.Error())
	}
	defer logfile.Close()
	log := logf.New(
		logf.WithFlags(logf.LstdFlags|logf.Lshortfile),
		logf.WithPrefix("[Sample] "),
		logf.WithWriter(io.MultiWriter(logfile, os.Stdout)),
		logf.WithMinLevel(logf.INFO),
	)

	log.Debug("Debugging")   // this will not print
	log.Print("Information") // this will not print
	log.Warn("Warning")      // this will
	log.Error("Erroring")    // and so will this
}
