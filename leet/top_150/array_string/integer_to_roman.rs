/*Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.*/

/*Symbol       Value*/
/*I             1*/
/*V             5*/
/*X             10*/
/*L             50*/
/*C             100*/
/*D             500*/
/*M             1000*/
/*For example, 2 is written as II in Roman numeral, just two one's added together.*/
/*12 is written as XII, which is simply X + II. The number 27 is written as XXVII,*/
/*which is XX + V + II.*/
/*Roman numerals are usually written largest to smallest from left to right. */
/*However, the numeral for four is not IIII. Instead, the number four is written as IV.*/
/*Because the one is before the five we subtract it making four. The same principle*/
/*applies to the number nine, which is written as IX. There are six instances where */
/*subtraction is used:*/

/*I can be placed before V (5) and X (10) to make 4 and 9. */
/*X can be placed before L (50) and C (100) to make 40 and 90. */
/*C can be placed before D (500) and M (1000) to make 400 and 900.*/
/*Given an integer, convert it to a roman numeral.*/

pub fn int_to_roman(mut num: i32) -> String {
    let mut roman = String::new();
    
    let mut multiplier = 0;
    while num > 0 {
        let last_num = num % 10;
        match multiplier {
            0 => {
                match last_num {
                    0 => {},
                    reps @ 1..=3 => roman.insert_str(0, "I".repeat(reps as usize).as_str()),
                    4 => roman.insert_str(0, "IV"),
                    5 => roman.insert(0, 'V'),
                    reps @ 6..=8 => roman.insert_str(0, ("V".to_string() + &"I".repeat(reps as usize - 5)).as_str()),
                    9 => roman.insert_str(0, "IX"),
                    _ => panic!("SASAS"),
                }
            },
            1 => {
                match last_num {
                    0 => {},
                    reps @ 1..=3 => roman.insert_str(0, "X".repeat(reps as usize).as_str()),
                    4 => roman.insert_str(0, "XL"),
                    5 => roman.insert(0, 'L'),
                    reps @ 6..=8 => roman.insert_str(0, ("L".to_string() + &"X".repeat(reps as usize - 5)).as_str()),
                    9 => roman.insert_str(0, "XC"),
                    _ => panic!("SASAS"),
                }
            },
            2 => {
               match last_num {
                    0 => {},
                    reps @ 1..=3 => roman.insert_str(0, "C".repeat(reps as usize).as_str()),
                    4 => roman.insert_str(0, "CD"),
                    5 => roman.insert(0, 'D'),
                    reps @ 6..=8 => roman.insert_str(0, ("D".to_string() + &"C".repeat(reps as usize - 5)).as_str()),
                    9 => roman.insert_str(0, "CM"),
                    _ => panic!("SASAS"),
                }
            },
            3 => {
                match last_num {
                    0 => {},
                    reps @ 1..=3 => roman.insert_str(0, "M".repeat(reps as usize).as_str()),
                    _ => panic!("SASAS"),
                }
            }
            _ => panic!("SAASAS"),
        }
        multiplier += 1;
        num = num / 10;
    }

    roman
}

fn main() {
    println!("To roman: {}", int_to_roman(12));
    println!("To roman: {}", int_to_roman(59));
    println!("To roman: {}", int_to_roman(999));
    println!("To roman: {}", int_to_roman(1945));
    println!("To roman: {}", int_to_roman(10));
}
