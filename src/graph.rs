use std::collections::HashMap;
use std::hash::Hasher

pub struct UnionFind {
}

pub struct Graph {
    n: usize,
    directed: bool,
    weighted: bool,
    adjacency_list: Vec<HashMap<usize, i64>>,
}

impl Graph {
    pub fn new(n: usize, directed: bool, weighted: bool) -> Self {
        Self {
            n: n + 1,
            directed,
            weighted,
            adjacency_list: vec![HashMap::<usize, i64>::new(); n + 1],
        }
    }

    pub fn add_edge(&mut self, u: usize, v: usize) {
        self.add_weighted_edge(u, v, 1);
    }

    pub fn add_weighted_edge(&mut self, u: usize, v: usize, w: i64) {
        assert!(u < self.n);
        assert!(v < self.n);
        
        self.adjacency_list[u].insert(v, w);
        if self.directed {
            return ;
        }
        self.adjacency_list[v].insert(u, w);
    }

    fn mst() {
    }
}
