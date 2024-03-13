/*Given an array of strings words and a width maxWidth, format the text such that each line has*/
/*exactly maxWidth characters and is fully (left and right) justified.*/
/*You should pack your words in a greedy approach; that is, pack as many words as you can in*/
/*each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth*/
/*characters.*/
/*Extra spaces between words should be distributed as evenly as possible. If the number of*/
/*spaces on a line does not divide evenly between words, the empty slots on the left will*/
/*be assigned more spaces than the slots on the right.*/
/*For the last line of text, it should be left-justified, and no extra space is*/
/*inserted between words.*/
/*Note:*/

/*A word is defined as a character sequence consisting of non-space characters only.*/
/*Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.*/
/*The input array words contains at least one word.*/
/*Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16*/
/*Output:*/
/*[*/
   /*"This    is    an",*/
   /*"example  of text",*/
   /*"justification.  "*/
/*]*/


pub fn full_justify(words: Vec<String>, max_width: i32) -> Vec<String> {
    let mut res:Vec<String> = Vec::new();
    let mut line: Vec<String> = Vec::new();
    let mut length = 0;
    let mut i = 0;

    while i < words.len() {
        if length + line.len() + words[i].len() > (max_width as usize) {
            // Line full
            let mut extra_space = (max_width as usize) - length;
            let spaces =  extra_space / std::cmp::max(1, line.len() - 1);
            let mut remainder =  extra_space % std::cmp::max(1, line.len() - 1);

            for j in 0..(std::cmp::max(line.len() - 1, 1)) {
                line[j] += &" ".repeat(spaces);
                if remainder != 0 {
                    line[j] += " ";
                    remainder -= 1;
                }
            }
            
            res.push(line.join(""));
            line.clear();
            length = 0;
            continue;
        }

        line.push(words[i].clone());
        length += words[i].len();
        i += 1;
    }

    let mut last_line = line.join(" ");
    let spaces = (max_width as usize) - last_line.len();
    last_line += &" ".repeat(spaces);
    res.push(last_line);

    res
}


fn main() {
    let words = Vec::from(["This".to_string(), "is".to_string(), "an".to_string(), "example".to_string(), "of".to_string(), "text".to_string(), "justification.".to_string()]); 

    println!("Justified {:?}", full_justify(words, 16));
}
