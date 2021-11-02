'use strict';
// Use an arrow function to calculate calcAverage
const calcAverage = (score1, score2, score3) => (score1 + score2 + score3)/3;
// This function takes in 2 numbers as parameters
// checks which is the winner of the gymnastics
// and returns None.
function checkWinner(avgDolphins, avgKoalas){
    if (avgDolphins * 2 <= avgKoalas) console.log(`Koalas win (${avgKoalas} vs. ${avgDolphins})`);
    else if (avgKoalas * 2 <= avgDolphins)
        console.log(`Dolphins win (${avgDolphins} vs. ${avgKoalas})`);
    else console.log(`Tie`);
}

// Main code starts here
const avgDolphins1 = calcAverage(44,23,71);
const avgKoalas1 = calcAverage(65,54,49);
const avgDolphins2 = calcAverage(85,54,41);
const avgKoalas2 = calcAverage(23,34,27);
// Check winner for the two datasets
checkWinner(avgDolphins1, avgKoalas1);
checkWinner(avgDolphins2, avgKoalas2);
