/*Write a function to find the longest common prefix string amongst an array of
* strings.*/
/*If there is no common prefix, return an empty string "".*/

pub fn longest_common_prefix(strs: Vec<String>) -> String {
    let min_len = strs.iter().map(|v| v.len()).min().unwrap_or(0);
    let mut len = 0;

    for i in 0..min_len {
        let c = strs[0].chars().nth(i).unwrap();
        if strs.iter().all(|x| x.chars().nth(i).unwrap() == c) {
            len += 1;
        } else {
            break;
        }
    }

    strs[0][0..len].to_string()        
}

fn main() {
    let strs = Vec::from(["flower".to_string(),"flow".to_string(),"flight".to_string()]);

    println!("Longest pref {}", longest_common_prefix(strs));
}
