fn div(x: i32, y: i32) -> Result<i32, &'static str> {
    if y != 0 {
        Ok(x/y)
    } else {
        Err("Divide by zero!")
    }
}

fn print_div_result(result: Result<i32, &'static str>) {
    match result {
        Ok(value)  => println!("value: {}", value),
        Err(error) => println!("error: {}", error)
    }
}

fn inc(x: i32) -> i32 {
    x+1
}

fn main() {
    let z0 = div(0, 1);
    print_div_result(z0);
    print_div_result(z0.map(inc));

    let z1 = div(2, 1);
    print_div_result(z1);
    print_div_result(z1.map(inc));

    let z2 = div(2, 0);
    print_div_result(z2);
    print_div_result(z2.map(inc));
}

