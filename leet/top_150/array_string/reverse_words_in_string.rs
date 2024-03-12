/*Given an input string s, reverse the order of the words.*/
/*A word is defined as a sequence of non-space characters. The words in s will be separated*/
/*by at least one space.*/
/*Return a string of the words in reverse order concatenated by a single space.*/
/*Note that s may contain leading or trailing spaces or multiple spaces between two words.*/
/*The returned string should only have a single space separating the words. Do not include*/
/*any extra spaces.*/
/*Follow-up: If the string data type is mutable in your language, can you solve it*/
/*in-place with O(1) extra space?*/

// O(1) space complexity
// Reverse whole string, then reverse word by word
// have to shift whole array for extra spaces
pub fn reverse_words_2(mut s: String) -> String {
    
}


pub fn reverse_words(s: String) -> String {
    let mut words = Vec::new();

    let mut word = String::new();
    for c in s.chars() {
        if c == ' ' && word.len() > 0 {
            words.insert(0, word.clone());
            word.clear();
        } else if c != ' ' {
            word.push(c);
        }
    }
    if word.len() > 0 {
        words.insert(0, word);
    }
    
    words.join(" ")
}


fn main() {
    let s = "the sky is blue".to_string();
    let s = "  hello   world  ".to_string();

    println!("Reversed words: {}", reverse_words(s));
}
