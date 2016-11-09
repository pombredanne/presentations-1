fn main() {
    let is_odd  = |x: i32| x & 1 == 1;
    //let is_even = |x: i32| !is_odd(x);
    let square  = |x: i32| x*x;
    for x in 0..10 {
        println!("{}*{}={}, {} is {} number", x, x, square(x), x, if is_odd(x) {"odd"} else {"even"})
    }
}

