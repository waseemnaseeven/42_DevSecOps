// src/parsing.rs

use crate::{polynomial::CommonData, polynomial2::Polynomial};

pub fn parsing_entry(entry: &str) -> Result<CommonData, &str> {
    if entry.is_empty() {
        return Err("Empty string");
    }

    let mut common_data = CommonData::new();

    let side: Vec<&str> = entry.split('=').collect();
    if side.len() != 2 {
        return Err("Need at least one '='");
    }
    
    let right_format = is_right_format(side[1].trim());
    let left_format = is_right_format(side[0].trim());
    if !left_format || !right_format {
        return Err("Not the right format");
    }

    let left_constant = is_constant(side[0]);
    let right_constant = is_constant(side[1]);

    let left_side_result = parse_side_value(side[0]);
    let right_side_result = parse_side_value(side[1]);
    
    if left_constant && right_constant {
        if left_side_result != right_side_result {
            return Err("No solution possible")
        }
    }
    if left_side_result == 0.0 && right_side_result != 0.0 {
        return Err("No solution possible");
    } else if left_side_result == right_side_result {
        return Err("Identity equation, infinite solutions")
    }

    let left_side = get_commondata(&mut common_data, side[0]);
    if !left_side {
        return Err("Error on the left side of the polynomial");
    }
    let right_side = get_commondata(&mut common_data, side[1]);
    if !right_side {
        return Err("Error on the right side of the polynomial");
    }

    let token_left: Vec<&str> = side[0].split_whitespace().collect();
    let token_right: Vec<&str> = side[1].split_whitespace().collect();

    get_reduced_form(&mut common_data, side[0], side[1], token_left, token_right);

    Ok(common_data)
}

fn is_constant(side: &str) -> bool {
    let token: Vec<&str> = side.split_whitespace().collect();
    let mut is_constant = true;
    for item in token {
        let trimmed = item.trim();
        if trimmed.starts_with("X^") && trimmed != "X^0" {
            is_constant = false;
            break;
        }
    }
    is_constant
}

// Fonction pour obtenir la valeur numérique d'un côté de l'équation
fn parse_side_value(side: &str) -> f64 {
    let token: Vec<&str> = side.split_whitespace().collect();
    let mut value = 0.0;

    #[allow(unused_assignments)]
    let mut current_coefficient = 1.0;
    let mut is_negative = false;

    #[allow(unused_assignments)]
    for item in token {
        let trimmed = item.trim();

        if trimmed.is_empty() {
            continue;
        } else if trimmed == "+" {
            is_negative = false;
        } else if trimmed == "-" {
            is_negative = true;
        } else if let Ok(coeff) = trimmed.parse::<f64>() {
            current_coefficient = if is_negative { -coeff } else { coeff };
            value += current_coefficient;
            current_coefficient = 1.0;
        }
    }
    value
}

fn is_right_format(side: &str) -> bool {
    let token: Vec<_> = side.split(|c| c == '+' || c == '-').collect();

    for i in &token {
        let trimmed = i.trim();
        let token_of_trimmed: Vec<&str> = trimmed.split_whitespace().collect();

        // Chaque terme doit être de la forme `coefficient * X^puissance`
        if token_of_trimmed.len() != 3 {
            return false;
        }

        let mut iter = token_of_trimmed.iter();
        if let (Some(num), Some(star), Some(exponent)) = (iter.next(), iter.next(), iter.next()) {
            if num.parse::<f64>().is_ok()
                && *star == "*"
                && exponent.starts_with("X^")
                && exponent[2..].parse::<u32>().is_ok()
            {
                continue;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    true
}


fn get_reduced_form(
    common_data: &mut CommonData,
    left: &str,
    right: &str,
    _token_left: Vec<&str>,
    _token_right: Vec<&str>,
) {
    let mut a = 0.0;
    let mut b = 0.0;
    let mut c = 0.0;

    // Fonction pour regrouper les termes similaires pour chaque côté de l'équation
    let left_tokens: Vec<&str> = left.split_whitespace().collect();
    let right_tokens: Vec<&str> = right.split_whitespace().collect();

    let mut current_coefficient = 1.0;
    let mut is_negative = false;

    // Regroupement des termes de la partie gauche
    for token in left_tokens {
        let trimmed = token.trim();

        if trimmed == "+" {
            is_negative = false;
        } else if trimmed == "-" {
            is_negative = true;
        } else if let Ok(coeff) = trimmed.parse::<f64>() {
            current_coefficient = if is_negative { -coeff } else { coeff };
        } else if trimmed.starts_with("X^") {
            let exponent = trimmed[2..].parse::<i32>().unwrap_or(0);
            match exponent {
                2 => a += current_coefficient,
                1 => b += current_coefficient,
                0 => c += current_coefficient,
                _ => {}
            }
            current_coefficient = 1.0;
            is_negative = false;
        }
    }

    // Regroupement des termes de la partie droite (les soustraire de la gauche)
    is_negative = false;
    for token in right_tokens {
        let trimmed = token.trim();

        if trimmed == "+" {
            is_negative = false;
        } else if trimmed == "-" {
            is_negative = true;
        } else if let Ok(coeff) = trimmed.parse::<f64>() {
            current_coefficient = if is_negative { -coeff } else { coeff };
        } else if trimmed.starts_with("X^") {
            let exponent = trimmed[2..].parse::<i32>().unwrap_or(0);
            match exponent {
                2 => a -= current_coefficient,
                1 => b -= current_coefficient,
                0 => c -= current_coefficient,
                _ => {}
            }
            current_coefficient = 1.0; // Réinitialisation
            is_negative = false; // Réinitialisation du signe
        }
    }

    // Création de la forme réduite
    let mut reduced_form = String::new();
    if a != 0.0 {
        reduced_form.push_str(&format!("{} * X^2 ", a));
    }
    if b != 0.0 {
        if b > 0.0 && !reduced_form.is_empty() {
            reduced_form.push_str("+ ");
        }
        reduced_form.push_str(&format!("{} * X^1 ", b));
    }
    if c != 0.0 {
        if c > 0.0 && !reduced_form.is_empty() {
            reduced_form.push_str("+ ");
        }
        reduced_form.push_str(&format!("{} * X^0 ", c));
    }

    if reduced_form.is_empty() {
        reduced_form.push_str("0 ");
    }

    reduced_form.push_str("= 0");
    common_data.reduced_form = reduced_form;
}

fn get_commondata(
    common_data: &mut CommonData,
    side: &str
) -> bool {
    if side.is_empty() {
        return false;
    }

    let token: Vec<&str> = side.split(' ').collect();

    if token.is_empty() {
        return false;
    }

    for item in &token {
        let trimmed = item.trim();

        if trimmed.is_empty() {
            continue;
        } else if trimmed.parse::<f64>().is_ok() {
            continue;
        }

        match trimmed {
            "*" | "-" | "+" => continue,
            "X^0" | "X^1" | "X^2" => {
                find_error(common_data, trimmed);
                continue;
            }
            _ => {
                let error = find_error(common_data, trimmed);
                if error == true {
                    continue;
                } else {
                    return false;
                }
            }
        }
    }
    true
}

fn find_error(common_data: &mut CommonData, trimmed: &str) -> bool {
    let bytes: Vec<_> = trimmed.bytes().collect();
    let chars: Vec<char> = trimmed.chars().collect();

    #[allow(unused_assignments)]
    let mut max_degree: i32 = 0;
    for (i, c) in chars.iter().enumerate() {
        if *c == 'X' && chars[i + 1] == '^' && chars[i + 2].is_digit(10) {
            let ss = &bytes[2..bytes.len()];
            let integer_str = String::from_utf8_lossy(ss); // Convert byte slice to lossy string
            max_degree = integer_str.parse().unwrap_or_default();
            if common_data.degree < max_degree {
                common_data.degree = max_degree;
            }
            return true;
        } else {
            return false;
        }
    }
    false
}

pub fn get_real_numbers(reduced_form: &String, data: &mut Polynomial) {
    let token: Vec<_> = reduced_form.split_whitespace().collect();
    let mut current_coefficient = 1.0;
    let mut is_negative = false;

    for i in token.iter() {
        let trimmed = i.trim();
        // println!("Processing: {:?}", trimmed);

        match trimmed {
            "X^2" => {
                // Si on trouve "X^2", on affecte le coefficient courant à `a`
                data.a = if is_negative {
                    -current_coefficient
                } else {
                    current_coefficient
                };
                current_coefficient = 1.0; // Réinitialisation
                is_negative = false; // Réinitialisation du signe
            }
            "X^1" => {
                data.b = if is_negative {
                    -current_coefficient
                } else {
                    current_coefficient
                };
                current_coefficient = 1.0; 
                is_negative = false;
            }
            "X^0" => {
                data.c = if is_negative {
                    -current_coefficient
                } else {
                    current_coefficient
                };
                current_coefficient = 1.0;
                is_negative = false;
            }
            "-" => {
                // Si c'est un signe moins, on met à jour le flag
                is_negative = true;
            }
            "+" => {
                is_negative = false;
            }
            _ => {
                // Si c'est un nb
                if let Ok(coeff) = trimmed.parse::<f64>() {
                    current_coefficient = coeff;
                }
            }
        }
    }
}