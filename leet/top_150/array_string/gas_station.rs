/*There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].*/
/*You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its*/
/*next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.*/
/*Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the*/
/*circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique*/

pub fn can_complete_circuit(gas: Vec<i32>, cost: Vec<i32>) -> i32 {
    for i in 0..gas.len() {
        if gas[i] >= cost[i] {
            let mut current_gas = gas[i] - cost[i];
            for j in 1..gas.len() {
                current_gas += gas[(i+j) % gas.len()] - cost[(i+j) % cost.len()];
                if current_gas < 0 {
                    break;
                }
            }
            if current_gas >= 0 {
                return i as i32;
            }
        }
    }

    return -1;
}


// So greedy
pub fn can_complete_circuit_2(gas: Vec<i32>, cost: Vec<i32>) -> i32 {
    if gas.iter().sum::<i32>() < cost.iter().sum::<i32>() {
        return -1;
    }

    let mut total: i32 = 0;
    let mut start: i32 = 0;
    for i in 0..gas.len() {
        total += gas[i] - cost[i];
        if total < -0 {
            start = i as i32 + 1;
            total = 0;
        }
    }

    return start;
}


fn main() {
    let gas = Vec::from([1,2,3,4,5]);
    let cost = Vec::from([3,4,5,1,2]);

/*    let gas = Vec::from([2,3,4]);*/
    /*let cost = Vec::from([3,4,3]);*/

/*    let gas = Vec::from([2]);*/
    /*let cost = Vec::from([2]);*/


    println!("Result {:?}", can_complete_circuit_2(gas, cost));
}
