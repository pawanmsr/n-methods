/* 
 * Author: Canis Lupus Loner
 * Compile and Run with cargo
 */

// #![warn(unused_macros)]
// #![allow(unused_variables)]

// Imports and Inclusion //
use std::io;

// Macro //
macro_rules! input {
    ($t: ty, $s: expr) => {
        $s.next().unwrap().parse::<$t>().unwrap()
    };

    (String, $s: expr) => {
        $s.next().unwrap().to_string()
    };

    ($t: ty, $n : expr, $s: expr) => {
        (0..$n)
            .map(|_| $s.next().unwrap().parse::<$t>().unwrap())
            .collect::<Vec<$t>>()
    };
}

// External //


// Global //


// Functions //


fn main() -> io::Result<()> {
    let stdin: String = io::read_to_string(io::stdin()).unwrap();
    let mut s: std::str::SplitWhitespace<'_> = stdin.split_whitespace();
    
    // let t: usize = 1; // for single test
    let t: usize = input!(usize, s);
    for _ in 0..t {
        // Solution //
        println!("Everyone is awesome!");
    }

    Ok(())
}
