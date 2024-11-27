// alternating least squares

pub struct WALS {
    m: usize,
    n: usize,
    features: usize,
    U: Vec<Vec<f64> >, // m * k
    V: Vec<Vec<f64> >, // n * k
    W: Vec<Vec<f64> > // m * n
}

impl WALS {
    pub fn new(users: usize, shows: usize, features: usize) -> Self {
        Self {
            m: users,
            n: shows,
            features,
            U: vec![vec![0.0_f64; features]; users],
            V: vec![vec![0.0_f64; features]; shows],
            W: vec![vec![0.0_f64; users]; features],
        }
    }

    fn frobinius2(M: Vec<Vec<f64> >) -> f64 {
        let mut norm: f64 = 0.0;
        for M_i in M {
            for M_ij in M_i {
                norm += M_ij * M_ij;
            }
        }

        return norm.sqrt();
    }

    pub fn initialize() {
        todo!()
    }

    pub fn train(regularization: f64, threshold: f64) {
        assert!(threshold < 1_f64);
        todo!()
    }
}
