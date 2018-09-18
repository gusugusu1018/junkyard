package main

import (
	"os"
)

func main() {
    file, err := os.Create(`./test.txt`)
    if err != nil {
		panic("cannnot open file:" + err.Error())
    }
    defer file.Close()

    output := "testmessage"
    file.Write(([]byte)(output))
}
