const cost = Number(prompt());
const tip = (cost < 50 || cost > 300)?  0.2 : 0.15;

// Get output string
console.log(`The bill was ${cost}, the tip was ${tip*cost}, and the total value is ${cost + tip*cost}`);
