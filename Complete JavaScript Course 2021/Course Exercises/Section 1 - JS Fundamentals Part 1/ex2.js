// c style syntax
function round(value, precision)
{
    const multiplier = Math.pow(10, precision);
    return Math.round(value * multiplier)/multiplier;
}
const markWeight = 95, markHeight = 1.88, johnWeight = 85, johnHeight = 1.76;
const markBMI =  round(markWeight/(markHeight)**2, 1), johnBMI = round( johnWeight/(johnHeight)**2,1);
const markHigherBMI = markBMI > johnBMI;
if(markHigherBMI)
    console.log(`Mark's BMI (${markBMI}) is higher than John's (${johnBMI})!`);
else
    console.log(`John's BMI (${johnBMI}) is higher than Mark's (${markBMI})!`);
