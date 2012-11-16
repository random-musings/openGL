Student :2997420
Name: Janie Jacobucci
Assignment: TMA3 4x4 tic tac toe
Email:  jdjacobucci@gmail.com

The heuristics in this program are the following
1) Does there exist a move that can end the game ?
	the program examines the game board and determines if four in row
	can be made by either player.
2) Are there two game Pieces (Xs or Os) beside each other and do they have an open
	slot on either end of them? 
	if so then put your piece at one of the ends
3) are any of the interior spaces open?
	put game pieces on the interior spaces first to cut off as many losing moves as possible
4) are any of the corners open?
	

The program does the following when determining the best move.
1) apply moves suggested by the function firstMove()
	to the game board until there is a draw or a winner.
2) the program then examines other potential moves comparing the score against the moves
	made in step  1. this is where the alphabeta pruning tree is applied.
	the maxSearchLevel is 3. The program will examine other moves  but 
	the program is only allowed to go three levels deep on the game board.
	This ensures we can provide an answer in real time.

It is not possible for a human to win because the heuristics ensure that 
	* the computer will make all winning moves when they are available.
	* the computer will block all opponent winning moves when they are available.
	* the computer will ensure that any opponent game pieces that are side by side will be blocked
	by the computers game piece.
	* if the user chooses to play on the outside spaces the computer will put its pieces 
	on the interior spaces of the tic-tac-toe board. Ignoring the user until they force the computer 
	to block a winnig move.
	* the computer will take interior spaces away from the opponent.
	* the computer will take the corners away from the opponent.