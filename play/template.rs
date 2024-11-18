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


fn main() -> io::Result<()> {
    let stdin: String = io::read_to_string(io::stdin()).unwrap();
    let mut s: std::str::SplitWhitespace<'_> = stdin.split_whitespace();
    
    let mut t: usize = 1;
    // comment the line below for single test case
    t = s.next().unwrap().parse::<usize>().unwrap();
    
    for _ in 0..t {
        // solution //
    }

    Ok(())
}
