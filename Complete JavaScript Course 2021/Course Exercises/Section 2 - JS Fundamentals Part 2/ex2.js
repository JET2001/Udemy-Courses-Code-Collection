'use strict';
// Function calc tip
// Takes a bill (number) as input
// Calculates the tip
// Returns the value of the tip (number) as output
const calcTip = function(bill){
    if (bill < 50 || bill > 300) return 0.2*bill;
    return 0.15*bill;
}
const bills = new Array(125, 555, 44), tips = [calcTip(bills[0]), calcTip(bills[1]), calcTip(bills[2])], total = [bills[0]+tips[0], bills[1]+tips[1], bills[2] + tips[2]];

console.log(`Bills:`, bills);
console.log(`Tips:`, tips);
console.log(`Total:`, total);
