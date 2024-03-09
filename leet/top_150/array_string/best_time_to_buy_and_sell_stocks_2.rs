/*You are given an integer array prices where prices[i] is the price of a given stock*/
/*on the ith day.*/
/*On each day, you may decide to buy and/or sell the stock. You can only hold at most one*/
/*share of the stock at any time. However, you can buy it then immediately sell it on*/
/*the same day.*/
/*Find and return the maximum profit you can achieve.*/

pub fn max_profit(prices: Vec<i32>) -> i32 {
    let mut changes = Vec::new();
    for window in prices.as_slice().windows(2) {
       changes.push(window[1] - window[0]);
    }
    changes.iter().filter(|x| *x > &0).sum() 
}

fn main() {
    let prices = Vec::from([7,1,5,3,6,4]);

    println!("Max profit is {}", max_profit(prices));
}
