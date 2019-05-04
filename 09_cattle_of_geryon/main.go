package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"strconv"
	"sync"
	"time"

	"flag"

	"github.com/schollz/progressbar"
)

// channel for responses and times
// func for sending requests
// func for logging all responses
// func to sum responses

type Response struct {
	code int
	time float64
}

type Element struct {
	freq int
	time float64
}

// usage: ./main 'http://google.com' 100

// func main() {
// 	fmt.Println("HI")

// 	flag.Parse()
// 	args := flag.Args()

// 	if len(args) != 2 {
// 		fmt.Println("usage: ./main 'http://example.com' num_requests")
// 		return
// 	}
// 	resp, err := http.Get(args[0])
// 	if err != nil {
// 		fmt.Println("Error requesting from", args[0])
// 		return
// 	}

// 	fmt.Println(Response{1, 100})

// 	fmt.Println(resp.StatusCode)
// 	defer resp.Body.Close()

// 	fmt.Printf("%d\n", len(args))
// 	fmt.Println(args[0])
// }

func logErr(err error) {
	fmt.Println(err) // TODO: actually log error.  Like in a file
}

func sendRequest(server string, wg *sync.WaitGroup, ch chan Response, gen chan int) {
	defer wg.Done()

	for i := <-gen; i > 0; i = <-gen {
		begin := time.Now()
		resp, err := http.Get(server)
		if err != nil {
			logErr(err)
			ch <- Response{-1, -1}
		} else {
			r := Response{resp.StatusCode, time.Since(begin).Seconds()}
			ch <- r
		}
	}
}

func logToFile(numRequests int, wg *sync.WaitGroup, ch chan Response) {
	defer wg.Done()

	bar := progressbar.New(numRequests)
	m := make(map[int]Element)

	for i := 0; i < numRequests; i++ {
		rq := <-ch

		if tmp, ok := m[rq.code]; ok {
			tmp.freq++
			tmp.time = (tmp.time + rq.time) / 2
			m[rq.code] = tmp
		} else {
			m[rq.code] = Element{1, rq.time}
		}
		bar.Add(1)
	}

	str := "code,freq,response_time\n"
	for k, v := range m {
		str += fmt.Sprintf("%d,%d,%f\n", k, v.freq, v.time)
	}

	file := "log.csv"
	ioutil.WriteFile(file, []byte(str), 0644)
}

func generator(numRequests int, gen chan int) {
	for i := numRequests; i > 0; i-- {
		gen <- i
		time.Sleep(5)
	}
	for {
		gen <- 0
	}
}

func main() {
	flag.Parse()
	args := flag.Args()
	if len(args) != 2 {
		fmt.Println("usage: ./main 'http://example.com' num_requests")
		return
	}

	numRequests, err := strconv.Atoi(args[1])
	if err != nil {
		fmt.Println(err)
		return
	}

	var wg sync.WaitGroup

	numRoutines := 4

	wg.Add(numRoutines + 1)

	ch := make(chan Response)
	gen := make(chan int)

	go generator(numRequests, gen)

	go logToFile(numRequests, &wg, ch)

	for i := 0; i < numRoutines; i++ {
		go sendRequest(args[0], &wg, ch, gen)
	}

	wg.Wait()
	fmt.Println("")
}
