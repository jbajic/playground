/*Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper,*/
/*return the researcher's h-index.*/
/*According to the definition of h-index on Wikipedia: The h-index is defined as the maximum value of h such that the given */
/*researcher has published at least h papers that have each been cited at least h times.*/

pub fn h_index_2(citations: Vec<i32>) -> i32 {
    let mut sorted = citations.clone();
    sorted.sort();
    sorted.reverse();
    for (i, citation) in sorted.iter().enumerate() {
        if i >= (*citation as usize) {
            return i as i32;
        }
    }

    0 as i32
}


pub fn h_index(citations: Vec<i32>) -> i32 {
    let mut published_papers = citations.iter().filter(|x| *x > &0).count();

    while published_papers > 0 {
        let mut satisfy_predicate = 0;
        for citation in citations.iter() {
            if (*citation as usize) >= published_papers {
                satisfy_predicate += 1;
            } 
        }

        println!("Satisfied {}", satisfy_predicate);
        if satisfy_predicate >= published_papers {
            return published_papers as i32;
        }

        published_papers -= 1;
    }

   0 
}


fn main() {
    //let citations = Vec::from([3,0,6,1,5]);
    let citations = Vec::from([1,3,1]);

    println!("H index: {}", h_index_2(citations));
}
