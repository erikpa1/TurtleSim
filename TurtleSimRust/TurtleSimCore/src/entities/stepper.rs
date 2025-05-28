pub struct Stepper {
    pub Now: i64,
    pub End: i64,
}

impl Stepper {
    pub fn new() -> Self {
        Self { Now: 0, End: 100 }
    }
}
