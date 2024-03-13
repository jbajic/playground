/*A phrase is a palindrome if, after converting all uppercase letters into lowercase letters*/
/*and removing all non-alphanumeric characters, it reads the same forward and backward.*/
/*Alphanumeric characters include letters and numbers.*/
/*Given a string s, return true if it is a palindrome, or false otherwise.*/


pub fn is_palindrome(s: String) -> bool {
    let chars:Vec<_> = s.chars().collect();
    let mut left = 0;
    let mut right = s.len() - 1;
    while left < right {
        while !chars[left].is_alphanumeric() {
            left += 1;
            if left == s.len() {
                return true;
            }
        }
        while !chars[right].is_alphanumeric() {
            right -= 1;
            if right == 0 {
                return true;
            }
        }
        if chars[left].to_ascii_lowercase() != chars[right].to_ascii_lowercase() {
            return false;
        }
        left += 1;
        if right.checked_sub(1).is_none() {
            break
        }
        right -= 1;
    }
    
    true
}

fn main() {
    println!("Is palindrome: {:?}", is_palindrome("A man, a plan, a canal: Panama".to_string()));
    println!("Is palindrome: {:?}", is_palindrome("a.".to_string()));
    println!("Is palindrome: {:?}", is_palindrome(",.".to_string()));
    println!("Is palindrome: {:?}", is_palindrome("0P".to_string()));
}
