// tests/test_equal_sign.rs

use computor::parsing::*;

// Equal Sign '='

#[test]
fn no_equal_sign() {
    let entry = "5 * X^2";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Need at least one '='");
}

#[test]
fn more_than_one_equal_sign() {
    let entry = "5 * X^2 = 5 * X^0 = 1 * X^1";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Need at least one '='");
}

#[test]
fn only_space() {
    let entry = "     ";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Need at least one '='");
}

#[test]
fn letters() {
    let entry = "iugqhiugqb";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Need at least one '='");
}