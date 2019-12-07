# AtariBreakoutxAkira

![alt text](https://github.com/dianapaula19/IntroductionToRobotics/blob/master/MatrixGame/kanedaImage.jpg)
### "31 YEARS AFTER WORLD WAR III. AD 2019 NEO TOKYO"

An explosion caused a bunch of rocks to block the entrance of a Neo Tokyo tunnel. Clear the path for Kaneda to pass
and then guide his way through the tunnel making sure he doesn't hit any of the obstacles.  

## Rules

1. You have a predefined number of minutes to clear the path based on the level of difficulty you chose. Not clearing the path in that interval of time means you lose the game. Your score for this part of the game will be calculated based on how long it took you to finish the game. 
2. After you clear the path, you must guide Kaneda through the tunnel and make sure he doesn't hit any obstacles. There will be some items to collect along the way. You must collect at least one item to win the game. Your score for this part of the game is equal to the number of items collected multiplied by 5.
3. Your final score is the sum of the scores you obtained in the first two parts of the game.

### Levels of Difficulty

1. Easy - You have 5 minutes to clear the path
2. Medium - You have 4 minutes to clear the path
3. Hard - You have 3 minutes to clear the path

## Requirements 

### Hardware

1. 8x8 LED matrix
2. LCD
3. Joystick :joystick:
4. MAX7219 Driver
5. Active Buzzer
6. 2 Pushbuttons

### Game Specifications

- The score is the sum of the scores obtained in the first two parts of the game
- There are three levels of difficulty
- There are two requirements for finishing the game: clearing the path in the predefined amount of time and collecting at least one item along the way
- [Kaneda's theme song](https://www.youtube.com/watch?v=hpDvtIt6Lsc) will play during the second part of the game, I hope. 

### LCD Display
The LCD will display 4 options:

1. **Start**, when this option is chosen, the game will start. The only things that will remain on the screen will be the score and the amount of time the user has left to clear the path.
2. **HighScore**, the high score will be displayed when this option is chosen.
3. **Setup**, there are two settings available: 
   - setting the level of difficulty
   - setting the speed of Kaneda's motorcycle
4. **Info**, when this option is chosen, the credits will be displayed
