package main

import "fmt"

type Id uint32
type Name string
type Surname string

func register_user(id Id, name Name, surname Surname) {
	fmt.Printf("Registering: %d %s %s", id, name, surname)
}

func main() {
	var i Id = 1
	var n Name = "Jan"
	var s Surname = "Novák"

	register_user(i, n, s)
}
