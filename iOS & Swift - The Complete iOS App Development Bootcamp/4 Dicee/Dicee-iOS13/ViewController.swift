//
//  ViewController.swift
//  Dicee-iOS13
//
//  Created by Angela Yu on 11/06/2019.
//  Copyright © 2019 London App Brewery. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    // Interface builder outlet for dice 1
    @IBOutlet weak var diceImageView1: UIImageView!
    // Interface builder outlet for dice 2
    @IBOutlet weak var diceImageView2: UIImageView!
    
    // Create a variable for the left dice number
    var leftDiceNumber = 1, rightDiceNumber = 1
    // since both dices are of value 1 at the start.
    
    // Declare a constant array for dices
    let dices = [ #imageLiteral(resourceName: "DiceOne") ,#imageLiteral(resourceName: "DiceTwo"), #imageLiteral(resourceName: "DiceThree"), #imageLiteral(resourceName: "DiceFour"), #imageLiteral(resourceName: "DiceFive"), #imageLiteral(resourceName: "DiceSix")]
    
    // Notice that the code that is generated now is pretty different, it is an IBAction, not an IBOutlet.
    @IBAction func rollButtonPressed(_ sender: UIButton) {
        // Add code for the event that the user taps the roll button.
        leftDiceNumber = Int.random(in: 1...6)
        rightDiceNumber = Int.random(in: 1...6)
        diceImageView1.image = dices[leftDiceNumber-1]
        diceImageView2.image = dices[rightDiceNumber-1]
        
    }
    
}

