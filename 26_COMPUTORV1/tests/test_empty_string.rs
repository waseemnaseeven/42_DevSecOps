// tests/test_empty_string.rs

use computor::parsing::*;

// Empty Entry

#[test]
fn is_empty() {
    let entry = "";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Empty string");
}

