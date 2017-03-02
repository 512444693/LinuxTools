package main

import (
	"net/http"
	"time"
)

var last, now uint64

func main() {
	ifIncrease := make(chan bool)
	go printSpeed()
	go increaseTimes(ifIncrease)

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Write([]byte("ok"))
		ifIncrease <- true
	})
	http.ListenAndServe(":8081", nil)
}

func increaseTimes(ifIncrease chan bool) {
	for {
		<-ifIncrease
		now++
		//print("get increase")
	}
}

func printSpeed() {
	for {
		num := now - last
		last = now

		if num > 0 {
			println(num, " p/s,", now, " sum")
		}
		time.Sleep(time.Second * 1)
	}
}
