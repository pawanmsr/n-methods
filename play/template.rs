/* 
 * Author: Canis Lupus Loner
 * Compile and run with cargo or rustc
 */

// #![warn(unused_macros)]
// #![warn(unused_imports)]
// #![warn(unused_must_use)]
// #![allow(unused_variables)]

// Standard Library //
use std::io;
use std::fs;

use std::io::Write;

use std::cmp::{min, max};

// use std::collections::{BinaryHeap, VecDeque};
// use std::collections::{BTreeMap, BTreeSet];
// use std::collections::hash_map::HashMap;
// use std::collections::hash_set::HashSet;

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
    #[cfg(not(LOCAL))]
    let stdin: String = io::read_to_string(io::stdin().lock()).unwrap();
    #[cfg(any(LOCAL, feature = "LOCAL"))]
    let stdin: String = fs::read_to_string("input.txt").unwrap();

    #[cfg(not(LOCAL))]
    let stdout  = io::stdout().lock();
    #[cfg(any(LOCAL, feature = "LOCAL"))]
    let stdout = fs::File::create("output.txt").unwrap();
    
    let mut cin = stdin.split_whitespace();
    let mut cout = stdout;
    
    // Solution //
    // let t: usize = 1; // for single test
    let t: usize = input!(usize, cin);
    for _ in 0..t {
        // Test Case //
        writeln!(cout, "Everyone is awesome!")?;
    }

    return Ok(());
}
