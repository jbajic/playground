/*Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.*/
/*Symbol       Value*/
/*I             1*/
/*V             5*/
/*X             10*/
/*L             50*/
/*C             100*/
/*D             500*/
/*M             1000*/
/*For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII,*/
/*which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.*/
/*Roman numerals are usually written largest to smallest from left to right. However, the numeral for four*/
/*is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract*/
/*it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:*/

/*I can be placed before V (5) and X (10) to make 4 and 9. */
/*X can be placed before L (50) and C (100) to make 40 and 90. */
/*C can be placed before D (500) and M (1000) to make 400 and 900.*/
/*Given a roman numeral, convert it to an integer.*/

pub fn roman_to_int(s: String) -> i32 {
    let mut num = 0;

    let mut i = 0;
    while i < s.len() {
        let ith = s.chars().nth(i).unwrap();
        let ithhh = s.chars().nth(i+1);
        let current_num = match ith {
            'I' => {
                if i < s.len() - 1 && ithhh.unwrap() == 'V' {
                    i += 1;
                    4
                } else if i < s.len() - 1 && ithhh.unwrap() == 'X' {
                    i += 1;
                    9
                } else {
                    1
                }
            },
            'V' => 5,
            'X' => {
                if i < s.len() - 1 && ithhh.unwrap() == 'C' {
                    i += 1;
                    90
                } else if i < s.len() - 1 && ithhh.unwrap() == 'L' {
                    i += 1;
                    40
                } else {
                    10
                }
            },
            'L' => 50,
            'C' => {
                if i < s.len() - 1 && ithhh.unwrap() == 'M' {
                    i += 1;
                    900
                } else if i < s.len() - 1 && ithhh.unwrap() == 'D' {
                    i += 1;
                    400
                } else {
                    100
                }
            },
            'D' => 500,
            'M' => 1000,
            _ => panic!("Not recognizable"),
        };
        num += current_num;
        println!("num {} at {}", num, ith);
        i += 1;
    }

    num
}

fn main() {
    let roman = "III".to_string();
    let roman = "MCMXCIV".to_string();
    let roman = "MCDLXXVI".to_string();
    
    println!("Value of roman is {}", roman_to_int(roman));
}
