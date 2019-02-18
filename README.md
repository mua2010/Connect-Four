# Connect-Four
Note: The game state is displayed after each move.
This connect four game starts by prompting the user if they want to go first or not. Depending on the input ‘Y’- yes or ‘N’ - no, the game begins. Who ever goes first is player X and the one playing after is player O.
The main handling of the game is done in the main and several helper methods are made like charToIndex() , AIturn() , isBoardfull() etc which make the game easier to implement. The game is played in a while loop which ends when the board is full or it terminates when either the AI or the player has won. A boolean variable turn is used to switch between the player and the AI after every turn. 

checkHorontal(), checkVertical() and checkDiagonal() functions are used to find consective match of 4.

AIcheckHorontal(), AIcheckVertical() and AIcheckDiagonal()are functions which are used to defend and also attack when the AI sees 3 consecutive matches of any type X or O. AIturn() uses these functions to make a move for AI by returning an int and if there is not a possible defense or attack move it is assigned a random value.

LINK TO VIDEO (Sample Gameplay):
https://youtu.be/flAVIe7dErA
