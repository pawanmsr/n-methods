use std::collections::HashSet;

// unweighted graph
pub struct Graph {
    n: usize,
    directed: bool,
    adjacency_list: Vec<HashSet<usize> >,
}

impl Graph {
    pub fn new(nodes: usize) -> Self {
        Self {
            n: nodes + 1,
            directed: false,
            adjacency_list: vec![HashSet::<usize>::new(); nodes + 1],
        }
    }

    pub fn add_edge(&mut self, u: usize, v: usize) {
        assert!(u < self.n);
        assert!(v < self.n);
        self.adjacency_list[u].insert(v);
        if self.directed {
            return ;
        }
        self.adjacency_list[v].insert(u);
    }

    fn mst() {
    }
}
