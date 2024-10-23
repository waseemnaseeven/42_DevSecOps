// src/main.rs

use std::{
    env,
    error::Error,
};

use computor::polynomial::CommonData;

fn main() -> Result<(), Box<dyn Error>> {
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 { return Err(Box::from("Need one argument")) }

    let entry: &str = &args[1];
    CommonData::polynomial_solving(&entry);
    Ok(())
}
