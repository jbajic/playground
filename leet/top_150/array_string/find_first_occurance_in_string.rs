/*Given two strings needle and haystack, */
/*return the index of the first occurrence of needle in haystack, or -1 if*/
/*needle is not part of haystack.*/

pub fn str_str(haystack: String, needle: String) -> i32 {
    if needle.len() > haystack.len() {
        return -1;
    }
    for (i, c) in haystack.chars().enumerate() {
        if c == needle.chars().nth(0).unwrap() {
            let mut j = 1;
            let mut found = true;
            while j < needle.len() {
                if (i+j) >= haystack.len() {
                    found = false;
                    break;
                }
                if haystack.chars().nth(i + j).unwrap() != needle.chars().nth(j).unwrap() {
                    found = false;
                    break;
                }
                j += 1;
            }
            if found {
                return i as i32;
            }
        } 
    }
    
    -1
}


fn main() {
    println!("Index at {}", str_str("sadbutsad".to_string(), "sad".to_string()));
    println!("Index at {}", str_str("leetcode".to_string(), "leeto".to_string()));
    println!("Index at {}", str_str("sasjfdsleijdsl".to_string(), "lei".to_string()));
    println!("Index at {}", str_str("mississippi".to_string(), "issipi".to_string()));
}
