package main

import (
    "encoding/json"
    "fmt"
    "io/ioutil"
)

type Config struct {
    Server ServerConfig `json:"server"`
    Db     DbConfig     `json:"db"`
}

type ServerConfig struct {
    Host  string        `json:"host"`
    Port  string        `json:"port"`
    Slave []SlaveServer `json:"slave"`
}

type DbConfig struct {
    User string `json:"user"`
    Pass string `json:"pass"`
}

type SlaveServer struct {
    Weight int    `json:"weight"`
    Ip     string `json:"ip"`
}

func main() {
    file, err := ioutil.ReadFile("config.json")
    if err != nil {
        panic(err)
    }
    var config Config
    json.Unmarshal(file, &config)
    fmt.Printf("Host is :%s\n", config.Server.Host)
    fmt.Printf("Port is :%s\n", config.Server.Port)
    for k, v := range config.Server.Slave {
        fmt.Printf("Slave %d\n", k)
        fmt.Printf("  weight is %d\n", v.Weight)
        fmt.Printf("  ip is %s\n", v.Ip)
    }
    fmt.Printf("DB Username is :%s\n", config.Db.User)
    fmt.Printf("DB Password is :%s\n", config.Db.Pass)
}
