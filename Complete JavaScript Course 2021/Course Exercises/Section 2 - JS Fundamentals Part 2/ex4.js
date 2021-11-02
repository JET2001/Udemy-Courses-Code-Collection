'use strict';
// Function calc tip
// Takes a bill (number) as input
// Calculates the tip
// Returns the value of the tip (number) as output
const calcTip = function(bill, tips, total){
    let tip = (bill < 50 || bill > 300)? 0.2*bill: 0.15*bill;
    tips.push(tip);
    total.push(tip + bill);
}
// Function calcAverage
const calcAverage = function(arr) {
        let sum = 0;
        for (let i = 0; i < arr.length; i++)
            sum += arr[i];
        return sum/arr.length;
}

// Main Code
const bills = [22, 295, 176, 440, 37, 105, 10, 1100, 86, 52];
const tips = new Array(), total = new Array();

for (let i = 0; i < bills.length; i++)
    calcTip(bills[i], tips, total);

console.log(bills, tips, total);

console.log(calcAverage(total));
