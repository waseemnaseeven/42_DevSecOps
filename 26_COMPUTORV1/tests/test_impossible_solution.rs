use computor::parsing::*;

// Absence of solutions

#[test]
fn no_solution_contradictory() {
    let entry = "0 * X^0 + 0 * X^1 = 1 * X^0";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "No solution possible");
}

#[test]
fn no_solution_zero_left() {
    let entry = "0 * X^2 + 0 * X^1 + 0 * X^0 = 5 * X^0";
    let result = parsing_entry(&entry);
    assert!(result.is_err());
    assert_eq!(result.unwrap_err(), "No solution possible");
}

