use computor::parsing::*;

// Infinite solutions

#[test]
fn infinite_solutions_identity() {
    let entry = "42 * X^0 = 42 * X^0";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Identity equation, infinite solutions");
}

#[test]
fn infinite_solutions_same_constants() {
    let entry = "5 * X^0 = 5 * X^0";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Identity equation, infinite solutions");
}

#[test]
fn infinite_solutions_polynomial_terms() {
    let entry = "3 * X^2 + 2 * X^1 - 5 * X^0 = 3 * X^2 + 2 * X^1 - 5 * X^0";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Identity equation, infinite solutions");
}

#[test]
fn infinite_solutions_all_terms_cancel() {
    let entry = "4 * X^2 - 4 * X^2 + 7 * X^1 - 7 * X^1 + 10 * X^0 - 10 * X^0 = 0 * X^0";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "Identity equation, infinite solutions");
}



