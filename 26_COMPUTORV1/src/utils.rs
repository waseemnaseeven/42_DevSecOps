// src/utils.rs

use crate::polynomial2::Polynomial;

pub fn print_answers(reduced_form: &String, degree: &i32, flag: i32, poly: &Polynomial) {
    if flag < 4 {
        println!("Reduced_form: {}", reduced_form);
    }
    println!("Polynomial degree: {}", degree);
    if flag == 0 {
        print!("The solution is:\n {:.6}", poly.solution_poly1);
    } else if flag == 1 {
        println!("Discriminant is : {}", poly.discriminant);
        println!("Discriminant is strictly negative, no real solutions");
        println!("Complex solutions: \n{:.6}\n{:.6}", poly.solution_poly2.1, poly.solution_poly2.0);
    } else if flag == 2 {
        println!("Discriminant is : {}", poly.discriminant);
        println!("Discriminant equals 0 here is the unique solution: \n{:.6}", poly.solution_poly2.1);
    } else if flag == 3 {
        println!("Discriminant is : {}", poly.discriminant);
        println!("Discriminant is strictly positive, the two solutions are: \n{:.6}\n{:.6}", poly.solution_poly2.1, poly.solution_poly2.0);
    } else {
        println!("The polynomial degree is strictly greater than 2, I can't solve.");
    }
}
