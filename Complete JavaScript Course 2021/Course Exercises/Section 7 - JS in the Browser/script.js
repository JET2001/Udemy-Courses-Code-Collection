'use strict';
/////////////// Lecture 85: Project #3: PIG GAME Introduction
// Global variables
const score0El = document.querySelector('#score--0'); // total score elem
const score1El = document.getElementById('score--1'); // total score elem
const diceEl = document.querySelector('.dice'); // dice elem
const btnNewEl = document.querySelector('.btn--new'); // New game button
const btnRollEl = document.querySelector('.btn--roll'); // Roll dice button
const btnHoldEl = document.querySelector('.btn--hold'); // Hold score button
const current0El = document.getElementById('current--0'); // currentScore0 elem
const current1El = document.getElementById('current--1'); // currentScore1 elem
const player0El = document.querySelector('.player--0'); // player1 Elem
const player1El = document.querySelector('.player--1'); // player2 Elem
// some variables for game support
let playing, activePlayer, currentScore, scores, winner;

// Start the game.
init();

// Support for rolling the dice
btnRollEl.addEventListener(`click`, function () {
  if (playing) {
    // Generate random dice rolls
    const dice = Math.trunc(Math.random() * 6) + 1;
    // Display the dice
    diceEl.classList.remove(`hidden`);
    // Manipulate the source attribute of the <a> tag from our JS.
    diceEl.src = `dice-${dice}.png`;
    // If its a 1, switch player, if not add to the current score.
    if (dice !== 1) {
      // Add to the current score
      currentScore += dice;
      document.getElementById(
        `current--${activePlayer}`
      ).textContent = currentScore;
    } else {
      changePlayer();
    }
  }
});

// Support for holding the score
btnHoldEl.addEventListener('click', function () {
  if (playing) {
    // Add current score to score of active player:
    scores[activePlayer] += currentScore;
    document.getElementById(`score--${activePlayer}`).textContent =
      scores[activePlayer];
    // Check if current score is at least 100,
    if (scores[activePlayer] >= 20) {
      playing = false;
      winner = activePlayer;
      // Finish the Game
      document
        .querySelector(`.player--${activePlayer}`)
        .classList.add('player--winner');
      document
        .querySelector(`.player--${activePlayer}`)
        .classList.remove(`player--active`);
      diceEl.classList.add(`hidden`); // makes the dice disappear upon winning the game.
    } else {
      // If not , switch to the next player.
      changePlayer();
    }
  }
});

// Functionality for Initialising game variables
const init = function () {
  // Set scores to 0
  score0El.textContent = score1El.textContent = 0;
  // Create a hidden class for dice, and add it at the beginning.
  if (!diceEl.classList.contains('hidden')) diceEl.classList.add(`hidden`);
  switch (winner) {
    case 0:
      player0El.classList.remove(`player--winner`);
      break;
    case 1:
      player1El.classList.remove(`player--winner`);
      break;
    default:
      break; // do nothing
  }
  //Reassign the value winner.
  winner = 2; // flag for winner to not be initialised.
  playing = true;
  activePlayer = 0;
  currentScore = 0;
  scores = new Array(0, 0);
  // Set the first player to be active again.
  if (!player0El.classList.contains(`player--active`))
    player0El.classList.add(`player--active`);
  if (player1El.classList.contains(`player--active`))
    player1El.classList.remove(`player--active`);
};

// Changeplayer functionality - to be reused at two different points of the code.
function changePlayer() {
  document.getElementById(`current--${activePlayer}`).textContent = 0;
  currentScore = 0;
  activePlayer = 1 - activePlayer; // Reassign the activePlayer
  // the toggle() method in classList, if the class isn't there it will add it.
  // if the class is there, it will remove it.
  player0El.classList.toggle(`player--active`);
  player1El.classList.toggle(`player--active`);
}
//////////// CODING CHALLENGE #2: Lecture 85: Resetting the Game
btnNewEl.addEventListener('click', init);
