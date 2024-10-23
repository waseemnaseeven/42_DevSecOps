// src/polynomial2.rs

#[derive(Debug)]
pub struct Polynomial {
    pub a: f64,
    pub b: f64,
    pub c: f64,
    pub discriminant: f64,
    pub solution_poly1: f64,
    pub solution_poly2: (f64, f64),
}

impl Default for Polynomial {
    fn default() -> Self {
        Self {
            a: 0.0,
            b: 0.0,
            c: 0.0,
            discriminant: 0.0,
            solution_poly1: 0.0,
            solution_poly2: (0.0, 0.0),
        }
    }
}

fn my_sqrt(x: f64) -> f64 {
    // Initial guess for the square root
    let mut guess = x / 2.0;

    // The precision you desire
    let epsilon = 1e-10;

    // Loop until the guess is close enough to the actual square root
    while (guess * guess - x).abs() > epsilon {
        guess = (guess + x / guess) / 2.0;
    }

    guess
}

pub fn solution2(discriminant: f64, data: &mut Polynomial) {
    let sqrt_discriminant = my_sqrt(discriminant.abs());
    // Solve the quadratic equation : ((-b -+ sqrt) / 2*a)
    data.solution_poly2.0 = (-data.b + sqrt_discriminant) / (2.0 * data.a);
    data.solution_poly2.1 = (-data.b - sqrt_discriminant) / (2.0 * data.a);
}

pub fn get_discriminant(data: &mut Polynomial) {

    data.discriminant = data.b * data.b - 4.0 * data.a * data.c;

}