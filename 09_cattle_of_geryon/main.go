package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
	"strconv"
	"sync"
	"time"

	"flag"

	"github.com/schollz/progressbar"
)

type Response struct {
	code int
	time float64
}

type Element struct {
	freq int
	time float64
}

type Error struct {
	err       error
	timestamp string
}

func sendRequest(server string, wg *sync.WaitGroup, ch chan Response, gen chan int, errchan chan Error) {
	defer wg.Done()

	for i := <-gen; i > 0; i = <-gen {
		begin := time.Now()
		resp, err := http.Get(server)
		if err != nil {
			errchan <- Error{err, time.Now().Format("20060102150405")}
			ch <- Response{-1, time.Since(begin).Seconds()}
		} else {
			r := Response{resp.StatusCode, time.Since(begin).Seconds()}
			ch <- r
		}
	}
}

func logToFile(numRequests int, wg *sync.WaitGroup, ch chan Response) {
	defer wg.Done()

	bar := progressbar.New(numRequests)
	bar.RenderBlank()
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

	str := "code,freq,num_requests,avg_response_time\n"
	for k, v := range m {
		str += fmt.Sprintf("%d,%d,%d,%f\n", k, v.freq, numRequests, v.time)
	}

	file := "log.csv"
	ioutil.WriteFile(file, []byte(str), 0644)
}

func generator(numRequests int, gen chan int) {
	for i := numRequests; i > 0; i-- {
		gen <- i
	}
	for {
		gen <- 0
	}
}

func logErrs(errchan chan Error, wg *sync.WaitGroup) {
	defer wg.Done()

	f, err := os.OpenFile("error.log", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Unable to open error file:", err)
		return
	}

	defer f.Close()

	for e := <-errchan; ; e = <-errchan {
		if err != nil {
			fmt.Println("Error writing to err.log:", err)
			continue
		}
		if _, err := f.Write([]byte(fmt.Sprintf("%s %s\n", time.Now().Format("20060102150405"), e.err))); err != nil {
			fmt.Println("Error writing to err.log:", err)
		}
	}
}

func main() {
	flag.Parse()
	args := flag.Args()
	if len(args) != 2 {
		fmt.Println("usage: ./main 'http://example.com' num_requests")
		os.Exit(1)
	}

	numRequests, err := strconv.Atoi(args[1])
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	var wg sync.WaitGroup

	numRoutines := 4

	wg.Add(numRoutines + 1)

	ch := make(chan Response)
	gen := make(chan int)
	errchan := make(chan Error)

	go generator(numRequests, gen)

	go logToFile(numRequests, &wg, ch)
	go logErrs(errchan, &wg)

	for i := 0; i < numRoutines; i++ {
		go sendRequest(args[0], &wg, ch, gen, errchan)
	}

	wg.Wait()
	fmt.Println("")
}
