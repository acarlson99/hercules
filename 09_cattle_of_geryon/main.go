package main

import (
	"fmt";
	"net/http";
	"flag";
)

// channel for responses
// channel for iterating through requests
// func for sending requests
// func for logging all responses
// func to sum responses

func main() {
	fmt.Println("HI")
	resp, err := http.Get("https://google.com")
	if err != nil {
		return
	}

	flag.Parse()
	args := flag.Args()

	fmt.Println(resp.StatusCode)
	defer resp.Body.Close()

	fmt.Printf("%d\n", len(args))
	fmt.Println(args[0])
}
