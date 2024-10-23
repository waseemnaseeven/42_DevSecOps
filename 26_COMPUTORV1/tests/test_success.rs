use computor::polynomial::*;

#[test]
fn polynomial3_from_subject() {
    let entry = "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0";
    let result = CommonData::polynomial_solving(&entry);
    println!("{:?}", result);
    println!("entry: {entry}");
}

#[test]
fn polynomial1_from_subject() {
    let entry = "5 * X^0 + 4 * X^1 = 4 * X^0";
    let result = CommonData::polynomial_solving(&entry);
    println!("{:?}", result);
    println!("entry: {entry}");
}

#[test]
fn polynomial2_from_subject() {
    let entry = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
    let result = CommonData::polynomial_solving(&entry);
    println!("{:?}", result);
    println!("entry: {entry}");
}

