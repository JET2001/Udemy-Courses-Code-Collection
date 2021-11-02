'use strict';
const Mark =
{
    name: `Mark Miller`,
    mass: 78,
    height: 1.69,
    calcBMI: function(){
        this.BMI = this.mass/this.height**2;
        return this.BMI;
    }
}
const John =
{
    name: `John Smith`,
    mass: 92,
    height: 1.95,
    calcBMI: function(){
        this.BMI = this.mass/this.height**2;
        return this.BMI;
    }
}
if (John.calcBMI() !== Mark.calcBMI())
console.log((John.BMI > Mark.BMI)?`John's BMI ${John.BMI} is higher than Mark's ${Mark.BMI}`: `Mark's BMI ${Mark.BMI} is higher than John's ${John.BMI}`);
else console.log(`Their BMIs are equal`);

// Mark's BMI 27.309968138370508 is higher than John's 24.194608809993426
