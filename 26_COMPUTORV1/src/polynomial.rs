// src/polynomial.rs

use crate::utils::*;
use crate::parsing::*;
use crate::polynomial2::{
    Polynomial,
    get_discriminant,
    solution2
};

#[derive(Debug, Clone)]
pub struct CommonData {
    pub reduced_form: String,
    pub degree: i32,

}

impl CommonData {
    pub fn new() -> Self {
        Self {
            reduced_form: String::new(),
            degree: 0,
        }
    }

    pub fn polynomial_solving(entry: &str) {
        let mut poly2: Polynomial = Polynomial::default();
        let good_entry: Result<CommonData, &str> = parsing_entry(entry);
        match good_entry {
            Ok(common_data) => {
                get_real_numbers(&common_data.reduced_form, &mut poly2);
                if common_data.degree == 1 {
                    Self::solution1(&mut poly2);
                    print_answers(&common_data.reduced_form, &common_data.degree, 0, &poly2);
                } else if common_data.degree == 2 {
                    get_discriminant(&mut poly2);
                    if poly2.discriminant < 0.0 {
                        solution2(poly2.discriminant, &mut poly2);
                        print_answers(&common_data.reduced_form, &common_data.degree, 1, &poly2);
                    } else if poly2.discriminant == 0.0 {
                        solution2(poly2.discriminant, &mut poly2);
                        print_answers(&common_data.reduced_form, &common_data.degree, 2, &poly2);
                    } else {
                        solution2(poly2.discriminant, &mut poly2);
                        print_answers(&common_data.reduced_form, &common_data.degree, 3, &poly2);
                    }
                } else {
                    print_answers(&common_data.reduced_form, &common_data.degree, 2147483647, &poly2);
                }
            }
            Err(error) => {
                println!("{error}")}
        }
    }

    fn solution1(poly2: &mut Polynomial) {
        let a = poly2.b;
        let b = poly2.c;

        // Solve the equation: ax + b = 0
        poly2.solution_poly1 = -b / a;

    }
}
