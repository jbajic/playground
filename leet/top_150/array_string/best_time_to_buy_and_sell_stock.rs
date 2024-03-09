/*You are given an array prices where prices[i] is the price of a given stock on the ith day.*/
/*You want to maximize your profit by choosing a single day to buy one stock and choosing*/
/*a different day in the future to sell that stock.*/
/*Return the maximum profit you can achieve from this transaction. */
/*If you cannot achieve any profit, return 0.*/

pub fn max_profit(prices: Vec<i32>) -> i32 {
    let mut min = prices[0];
    let mut profit = 0;

    for price in prices {
        min = std::cmp::min(min, price);
        if (price - min) > profit {
            profit = price - min;
        }
    }

    profit
}

fn main() {
    //let prices = Vec::from([7,1,5,3,6,4]);
    let prices = Vec::from([1,2]);

    println!("Max profit is {}", max_profit(prices));
}
