#[macro_use]
extern crate bincode;

use std::fs::File;

use bincode::{deserialize_from, Infinite};

fn deserialize_value(mut fin: &File) -> Option<i32> {
    match deserialize_from(&mut fin, Infinite) {
        Ok(value) => {
            println!("successfully deserialized from file");
            Some(value)
        }
        Err(error) => {
            println!("serialization error: {}", error);
            None
        }
    }
}

fn main() {
    match File::open("test.bin") {
        Ok(fin) => {
            match deserialize_value(&fin) {
                Some(value) => {
                    println!("deserialized value: 0x{:x}", value);
                }
                None => {
                }
            }
        }
        Err(error) => {
            println!("file create error: {}", error);
        }
    }
}

