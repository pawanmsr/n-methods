/* 
 * Author:
 * Compile and Run with cargo
 */

// Imports and Inclusion //
use std::io;

// Macro //


// External //


// Global //


// Functions //


fn main() {
    let mut s = String::new();
    
    let mut t: usize = 1;
    // comment lines below for single test case
    io::stdin().read_line(&mut s).unwrap();
    t = s.trim().parse::<usize>().unwrap();
    s.clear();
    
    for _ in 0..t {
        // solution //
    }
}
