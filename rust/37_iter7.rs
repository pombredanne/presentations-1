fn main() {
    // iterator (povsimnete si, ze je nemenny)
    let iter1 = 1..11;
    let iter2 = iter1.rev();

    // pruchod sekvenci se ziskanim indexu a hodnoty kazdeho prvku
    for (index,item) in iter2.enumerate() {
	println!("item[{}] = {}", index, item);
    }
}

