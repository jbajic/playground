/*The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like*/
/*this: (you may want to display this pattern in a fixed font for better legibility)*/
/*P   A   H   N*/
/*A P L S I I G*/
/*Y   I   R*/
/*And then read line by line: "PAHNAPLSIIGYIR"*/
/*Write the code that will take a string and make this conversion given a number of rows:*/
/*string convert(string s, int numRows);*/

/*PAYPALISHIRING, num_rows = 3*/
/*0: P (0), A(4), H(8), N(12) => diff: num_rows + 1*/
/*1: A (1), P(3), L(5), S(7), I(9), G(11) => diff: 2*/
/*2: Y(2), I(6), R(10) => diff: num_rows + 1*/

/*PAYPALISHIRING, num_rows = 4 */
/*Explanation:*/
/*P     I    N*/
/*A   L S  I G*/ /* A = i = 1 , L =  1 + (4 - 1 - 1) + (4 - 1 - 1) = 5 */
/*Y A   H R*/ /* Y = i = 2 , A = 2 + (4 - 2 - 1) + (4 - 1 - 2) = 4  */
/*P     I*/
// One zigzag has num_rows + num_rows -2 elements
// First and last row repeat on freq = index + (2*num_rows - 2)
// Middle ones repeat on freq = index + (2*num_rows - 2), 
// and freq = row_index + (num_rows - row_index - 1) + (num_rows - 1 - i))

/*0: P(0), I(6), N(12) => diff = (num_rows-1)*2 */
/*1: A(1), L(5), S(7), I(11), G(13) */
/*2: Y(2), A(4), H(8), R(10) */
/*3 P(3), I(9) diff = (num_rows-1)*2 */


pub fn convert(s: String, num_rows: i32) -> String {
    let mut zig_zagged = String::new();
    if num_rows == 1 {
        return s;
    }
    for i in 0..num_rows {
        if i == 0 {
            let mut indexed = i;
            while (indexed as usize) < s.len() {
                zig_zagged.push(s.chars().nth(indexed as usize).unwrap());
                indexed += 2*num_rows - 2; 
            }
        } else if i == num_rows - 1 {
            let mut indexed = i;
            while (indexed as usize) < s.len() {
                zig_zagged.push(s.chars().nth(indexed as usize).unwrap());
                indexed += 2*num_rows - 2; 
            }
        } else {
            let mut indexed = i;
            while (indexed as usize) < s.len() {
                zig_zagged.push(s.chars().nth(indexed as usize).unwrap());
                // and freq = row_index + (num_rows - row_index - 1) + (num_rows - 1 - i))
                let other = indexed + (num_rows - i - 1) + (num_rows - 1 - i);
                if (other as usize) < s.len() {
                    zig_zagged.push(s.chars().nth(other as usize).unwrap());
                }

                indexed += 2*num_rows - 2; 
            }

        }
    }

    zig_zagged
}


fn main() {
    let s = "PAYPALISHIRING".to_string();
    let numRows = 3;

    let s = "PAYPALISHIRING".to_string();
    let numRows = 4;

/*    let s = "A".to_string();*/
    /*let numRows = 1;*/

    let s = "AB".to_string();
    let numRows = 1;


    println!("ZigZagged converted: {}", convert(s, numRows));
}
