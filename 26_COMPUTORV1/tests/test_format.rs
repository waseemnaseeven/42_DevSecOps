// tests/test_format.rs

use computor::parsing::*;

// Test Format n * X^p only between '-' or '+'

#[test]
fn no_coeff() {
    let entry = "5 * 1 + 4 * 4 = 5";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn no_coeff_only_left() {
    let entry = "5 * 1 + 4 * 4 = 5 * X^0";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn no_coeff_only_right() {
    let entry = "5 * X^2 + 4 * X^1 = 5";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn no_left_side() {
    let entry = " = 1 * X^0";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn no_numbers() {
    let entry = "b * X^0 + t * X^1 - t * X^2 = p * X^0";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn only_numbers() {
    let entry = "1 + 3 + 8 - 8 = 1";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn only_operands() {
    let entry = "*-+=*";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn brain_test() {
    let entry = "eqghgqeugqe876eqh4h4te6hw=hwh";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn no_spaces() {
    let entry = "5*X^15*X^0=1*X^1";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn invalid_right_side_term() {
    let entry = "5 * X^2 - 3 * X^1 + 7 * X^0 = 5 * X";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn no_right_side() {
    let entry = "5 * X^0 + 4 * X^1 - 9.3 * X^0 =";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}

#[test]
fn right_side_with_letters() {
    let entry = "5 * X^0 + 4 * X^1 - 9.3 * X^0 = hoi";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Not the right format");
}
