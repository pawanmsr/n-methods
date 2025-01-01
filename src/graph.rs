use std::collections::HashMap;
use std::mem::swap;

pub struct UnionFind {
    n: usize,
    parent: Vec<i64>,
}

impl UnionFind {
    pub fn new(n: usize) -> Self {
        Self {
            n,
            parent: vec![-1; n],
        }
    }

    pub fn find(&self, x: usize) -> usize {
        assert!(x < self.n);
        
        let mut x: i64 = x as i64;
        while self.parent[x as usize] > 0 {
            x = self.parent[x as usize];
        }

        return x as usize;
    }

    pub fn size(&self, x: usize) -> usize {
        let x: usize = self.find(x);
        return (-self.parent[x]) as usize;
    }

    pub fn unite(&mut self, x: usize, y: usize) -> usize {
        let mut x: usize = self.find(x);
        let mut y: usize = self.find(y);

        if x == y {
            return x;
        }

        let size_of_x: usize = self.size(x);
        let size_of_y: usize = self.size(y);

        let component_size: usize = size_of_x + size_of_y;
        if size_of_x > size_of_y {
            swap(&mut x, &mut y);
        }

        self.parent[x] = y as i64;
        self.parent[y] = -(component_size as i64);

        return y;
    }

    pub fn united(&self, x: usize, y: usize) -> bool {
        return self.find(x) == self.find(y);
    }
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
            n,
            directed,
            weighted,
            adjacency_list: vec![HashMap::<usize, i64>::new(); n],
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

    pub fn get_edges(&self) -> Vec<(usize, usize, i64)> {
        let mut edges: Vec<(usize, usize, i64)> = Vec::new();
        for u in 0..self.n {
            for (v, w) in &self.adjacency_list[u] {
                if ! self.directed && u > *v {
                    continue;
                }

                edges.push((u, *v, *w));
            }
        }

        return edges;
    }

    pub fn mst(&self) -> Vec<(usize, usize, i64)> {
        let mut mst: Vec<(usize, usize, i64)> = Vec::new();
        let mut uf: UnionFind = UnionFind::new(self.n);
        let mut edges: Vec<(usize, usize, i64)> = self.get_edges();
        edges.sort_by_key(|(_, _, w)| *w);

        for (u, v, w) in edges {
            if uf.united(u, v) {
                continue;
            }

            mst.push((u, v, w));
            uf.unite(u, v);
        }
        
        return mst;
    }
}
