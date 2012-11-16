/*
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
*/
// tic_tac_toe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h";


//number of slots on the tic tac toe
vector<vector<int> > game;
typedef vector<vector<int> > Game;

typedef pair<int,int> Move;
typedef pair<int,Move> Outcome;

const int rows = 4;
const int cols = 4;
const int maxSearchLevel=3;

// **********************
// ***** Game Pieces ****
// **********************
typedef enum playerType{COMPUTER=-1,HUMAN=1};
typedef enum gameState{NEW=0,IN_PLAY,OVER};
typedef enum gamePiece{O=-1,OPEN,X};

gameState  gameStatus=NEW;  //default - this is used to determine 
							//whether keyboard events should be recognized


//game board
GLfloat slotWidth = 20;
GLfloat slotHeight= 20;
GLfloat lineSize =2;
Color colorX(1,1,1);
Color colorO(1,1,1);
Color lineColor(1,1,1);
string msgLine1;
string msgLine2;


const GLfloat BannerSpace = 3;				//space for text that say "current balls sunk"
const GLfloat resetButtonStart=10;			//position of reset button
int windowHandle;
int W;
int H;
int worldX=rows*slotWidth;
int worldY=100;
const int magfactor=8;


// ************************
// ****** Game Settings ***
// ************************
GLint nbrPlayers=2;
gamePiece player1GamePiece=X; //is player1 an X or O - default X
gamePiece player2GamePiece=O; //is player2 an X or O - default O
bool player1Turn = true; //who goes first - default player1
playerType player1Type=HUMAN; //indicate if player is human or computer
playerType player2Type=HUMAN; //indicate if player is human or computer

//function headers for drawing X or O
void drawX(Point location);
void drawO(Point location);
void drawGamePiece(Move mv,gamePiece playPiece);
Point getPointFromSlot(Move mv);
Move getSlotFromPoint(Point boardPt);
void recordAnswers(GLint scriptQues, GLint scriptAnswer);
void startupScript();
void initStartupScript();
void recordWin(gamePiece player);
void makeComputerMove();
void displayBoard( Game&);
Move noMovesLeft( rows, 0 );
Move findOffensiveMove(Game &game,int player);
Move findDefensiveMove(Game &game,int player);
Outcome minimax( int player, Game game, vector<int> alphaBeta ,int currLevel);





// **********************************
// ********** ScoreBoard ************
// **********************************
Point sbCorner(0,worldY-3,0);
GLfloat sbHeight =20;
GLfloat sbWidth = worldX;
int startupScriptState=0;
char msg_ChooseNumberPlayers[]="Choose number of players: Press 1 or 2 now.";
char msg_ChooseOrderOfTurn[]="Which player to should go first? Press 1 or 2 now.";
char msg_ChoosePlayer1GamePiece[]="Player 1 choose your play piece. Press X or O now";
char msg_ChoosePlayer2GamePiece[]="Player 2 choose your play piece. Press X or O now";
char msg_Player1Won[]="Player 1 WON!";
char msg_Player2Won[]="Player 2 WON!";
char msg_GameEndsDraw[]="Game ends in draw.";
char err_InvalidMove[]="Invalid Move";
char msg_Player1Turn[]="Player 1 make your move";
char msg_Player2Turn[]="Player 2 make your move";
ScoreBoard *sb;



void initGame()
{
	game.resize(rows);
	for( int i = 0; i < rows; i++ )  {
		game[i].resize(cols);
		for( int j = 0; j < cols; j++ ) // for each row
			game[i][j] = OPEN;
	}
}


// returns the first move of a game, which is lastMove
Move firstMove( Game& game,int player )
{

	//find or block a winning move
	for(int i=0;i<rows;i++)
	{
		int colSum=0;
		int rowSum=0;
		int blankSpaceRow=-1;
		int blankSpaceCol=-1;

		for(int j =0; j<cols;j++)
		{
			if(game[i][j]==0)
				blankSpaceRow=j;
			if(game[j][i]==0)
				blankSpaceCol=j;
			rowSum +=game[i][j];
			colSum +=game[j][i];
		}
		
		if (blankSpaceRow>=0 && (abs(rowSum)==3))
			return Move(i,blankSpaceRow);		//there is a blank space and all other game pieces on the row  are X's or O's 
		if (blankSpaceCol>=0 && (abs(colSum)==3))
			return Move(blankSpaceCol,i);		//there is a blank space and all other game pieces on the column  are X's or O's 
	}//if we get through this for loop there are no winning/saving moves


	//find an offensive move - this means find a group of two game pieces that have an empty space on either end
	Move mv = findOffensiveMove(game,player);

	//find an defensive move - if no suitable offensive move can be made then try to block the user from putting three in a row
	mv = mv == noMovesLeft?findDefensiveMove(game,player):mv;


	//play the interior spaces first
	if (mv ==noMovesLeft)
	{
		//play interior square
		for(int i=1;i<rows-1;i++)
			for(int j=1;j<rows-1;j++)
				if (game[i][j]==0)
					return Move(i,j);

	//play the corners next
		if(game[0][0]==0)			return Move(0,0);
		if(game[0][rows-1]==0)		return Move(0,rows-1);
		if(game[cols-1][0]==0)		return Move(cols-1,0);
		if(game[cols-1][rows-1]==0)	return Move(cols-1,rows-1);

	//play all other slots
		for(int i=0;i<cols;i++)
		{
			for(int j=0;j<rows;j++)
			{
				if (game[i][j]==0)
				{
					return Move(i,j);
				}
			}
		}
	}
	return mv;
}


void incr( Move &m )
{
	m.second++;
	if ( m.second == cols )  {
		m.first++;
		m.second=0;
	}
}


//if two in a row exist and there is 
//slots open at each end then play 
//on the end of the open slot
Move findOffensiveMove(Game &game,int player)
{
	Move tmpM=noMovesLeft;


	//horizontal check row1
	if(game[1][1]==game[1][2] &&
		game[1][1]==player &&
		(game[1][0]==0 || game[1][0]==player) &&
		(game[1][3]==0 || game[1][3]==player) )
	{
		tmpM.first= 1;
		tmpM.second=game[1][0]==player?3:0; //put move in open slot
	}

	//horizontal Check row 2
	if(game[2][1]==game[2][2] &&
		game[2][1]==player &&
		(game[2][0]==0 || game[2][0]==player) &&
		(game[2][3]==0 || game[2][3]==player) )
	{
		tmpM.first= 2;
		tmpM.second=game[2][0]==player?3:0; //put move in open slot
	}

	//vertical check col 1
	if(game[1][1]==game[2][1] &&
		game[1][1]==player &&
		(game[0][1]==0 || game[0][1]==player) &&
		(game[3][1]==0 || game[3][1]==player) )
	{
		tmpM.first= game[0][1]==player?3:0;
		tmpM.second=1; //put move in open slot
	}

	//vertical check col 2
	if(game[1][2]==game[2][2] &&
		game[1][2]==player &&
		(game[0][2]==0 || game[0][2]==player) &&
		(game[3][2]==0 || game[3][2]==player) )
	{
		tmpM.first= game[0][2]==player?3:0;
		tmpM.second=2; //put move in open slot
	}

	//diagonal check right down
	if(game[1][1]==game[2][2] &&
		game[1][1]==player &&
		(game[0][0]==0 || game[0][0]==player) &&
		(game[3][3]==0 || game[3][3]==player) )
	{
		tmpM.first= game[0][0]==player?3:0;
		tmpM.second=game[0][0]==player?3:0; //put move in open slot
	}


	//diagonal check right down
	if(game[1][2]==game[2][1] &&
		game[1][2]==player &&
		(game[3][0]==0 || game[3][0]==player) &&
		(game[0][3]==0 || game[0][3]==player) )
	{
		tmpM.first= game[3][0]==player?0:3;
		tmpM.second=game[3][0]==player?3:0; //put move in open slot
	}

	return tmpM;
}

//if corner has been played
//then play on the interior corner to take diagonal options
Move findDefensiveMove(Game &game,int player)
{
	//use the offensive moves to mount a defense
	Move tmpM=findOffensiveMove(game,-player);
	return tmpM;
}


Move nextMove( Game& game, Move m,int player)
{

	int stt = m.second+1;
	//find the next open slot to put a game piece into
	for(int i=m.first;i<cols;i++)
		for(int j=stt;j<rows;j++)
			if (game[i][j]==0)
				return Move(i,j);

	return noMovesLeft;
}


//determine if someone won the game
bool win( Game &game, int player ) // player is 1 or -1
{
	for( int i = 0; i < rows; i++ ) 
	{	
		int rowSum= game[0][i]+ game[1][i]+ game[2][i]+ game[3][i];
		int colSum= game[i][0]+ game[i][1]+ game[i][2]+ game[i][3];
		if ((rowSum== player*rows)||
			(colSum==player*cols))
			return true;
	}	
	int diagSum = game[0][0]+ game[1][1]+ game[2][2]+ game[3][3];
	if (diagSum  ==player*rows)
		return true;

	diagSum = game[0][3]+ game[1][2]+ game[2][1]+ game[3][0];
	if (diagSum  ==player*rows)
		return true;

	return false;
}


//determine if the game ended in a draw
bool done( Game &game )
{

	if(win(game,1) || win(game,-1))
		return true;
	//stalemate (moves available but no possible win)
	for( int i = 0; i < rows; i++ ) 
	{	
		int rowSum= abs(game[0][i]+ game[1][i]+ game[2][i]+ game[3][i]);
		int rowAbs= abs(game[0][i])+ abs(game[1][i])  + abs(game[2][i]) + abs(game[3][i]);
		int colSum= abs(game[i][0]+ game[i][1]+ game[i][2]+ game[i][3]);
		int colAbs= abs(game[i][0])+ abs(game[i][1])  + abs(game[i][2]) + abs(game[i][3]);

		//if both players have played in the row or col then win is not possible and rowSum != rowAbs
		if (rowAbs==rowSum || colAbs==colSum)
			return false;
	}

	//check diagonal stalemate
	int diagSum = abs(game[0][0]+ game[1][1]+ game[2][2]+ game[3][3]);
	int diagAbs = abs(game[0][0])+ abs(game[1][1])  + abs(game[1][2]) + abs(game[1][3]);
	if(diagSum == rows)
			return true;
	if( diagSum==diagAbs)
			return false;

	//check diagonal stalemate
	diagSum = abs(game[0][3]+ game[1][2]+ game[2][1]+ game[3][0]);
	diagAbs = abs(game[0][3])+ abs(game[1][2])  + abs(game[2][1]) + abs(game[3][0]);
	if(diagSum == rows)
			return true;
	if( diagSum==diagAbs)
			return false;		

	return true;
}


//apply the move to the game board
int tryMove( int player, Move move, Game game, vector<int> alphaBeta,int currLevel )
{
	int bestScore;
	if (move==noMovesLeft)
		return 0;
	game[move.first][move.second] = player;

	if ( win( game, player ) )  
		bestScore = player;
	else 
	if ( done( game ) ) 
		bestScore = 0;
	else //we have reached the maximum level to search through
	if (currLevel==maxSearchLevel)
		bestScore = 0;
	else
		bestScore = minimax( -player, game, alphaBeta,currLevel ).first;		

	return bestScore;
}

bool debug = true;
Outcome minimax( int player, Game game, vector<int> alphaBeta,int currLevel ) // notice that this is a call by value, so array gets copied!!!!
{

	//char c = 13;
	//if ( ! (minimaxCalls % 1000000 ) )
	//	cout << "minimax Calls = " << minimaxCalls/1000000 << " 000000" << c;
//	minimaxCalls++;

	int index = 1 - ((player*2)+2)/4;

	Move move = firstMove( game,player );
	Outcome Best( tryMove( player, move, game, alphaBeta,currLevel ), move ); // get a starting value on the first branch

	for ( move = nextMove( game, move ,player); move != noMovesLeft; move=nextMove( game, move ,player) )	{ 
//		If I am a max, being simulated by a min, who can already get
//      a score of beta, and the outcome from above is worse (for my parent), I might as well quit at this point.
//		Why? The grandparent will be totally uninterested in anything this node has to offer because it can pick
//		the previous node.
		
		alphaBeta[index] = player*__max( player*alphaBeta[index], player*Best.first );
		if ( alphaBeta[0] > alphaBeta[1] )  
		{
			Best.first = alphaBeta[index];
			break;
		}

		//add a check but ensure that we track the levels 
		int currentScore = tryMove( player, move, game, alphaBeta ,currLevel+1);
		if ( currentScore * player > Best.first * player ) 
		{ 
			Best = Outcome(currentScore, move);
		}
	}
	return Best;
}



//exception thrown if gameboard is not indexed correctly
 class IndexOutOfBounds : public std::exception 
    { 

    public: 
		//Constructor allows user to specify a message
        IndexOutOfBounds(const std::string errmsg) 
            : m_what(string(errmsg) )
        { } 
		
		//Constructor
		IndexOutOfBounds()
		{
		  m_what ="Index is Out Of Bounds";
		}
		
		//Destructor
		~IndexOutOfBounds() throw() {} 
		 virtual const char* what() const throw()
		 {
			return m_what.c_str();
		 }
		 private: 
			std::string m_what;
    };




void displayBoard(Game &board)
{
	//drawLines
	for(int colLine=1;colLine<rows;colLine++)
	{
		glColor3f(lineColor.red,lineColor.green,lineColor.blue);
		//draw the column Line
		glBegin(GL_LINES);
			glVertex2f(colLine*slotWidth,0);
			glVertex2f(colLine*slotWidth,rows*slotWidth);
		glEnd();

		//draw Row
		glBegin(GL_LINES);
			glVertex2f(0,colLine*slotHeight);
			glVertex2f(rows*slotHeight,colLine*slotHeight);
		glEnd();
	}

	//draw moves on board
	for(int col=0;col<cols;col++)
		for(int row=0;row<rows;row++)
			drawGamePiece(Move(col,row),(gamePiece)game[col][row]);
}


void drawGamePiece(Move mv,gamePiece playPiece)
{
	if (playPiece==OPEN)
		return;
	if (playPiece==X)
		drawX(getPointFromSlot(mv));
	else
		drawO(getPointFromSlot(mv));
}


void drawX(Point location)
{
		glColor3f(colorX.red,colorX.green,colorX.blue);
		glRasterPos2f(location.x,location.y);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
}

void drawO(Point location)
{
		glColor3f(colorO.red,colorO.green,colorO.blue);
		glRasterPos2f(location.x,location.y);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
}



 



void 
reshape(int w, int h)
{
	
	W = w;
    H = h;
	GLfloat scaleX(1), scaleY(1);
	if ( W * worldY > H * worldX )  // the window is too wide
		scaleX = (W * worldY)/(H * worldX );
	else
		scaleY = (H * worldX )/(W * worldY);

    glViewport(0, 0, w/scaleX, h/scaleY);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//       left,right, bottom, top
    glOrtho(0.0f, worldX, 0.0f, worldY, -5.0f, 5.0f);
    glMatrixMode(GL_MODELVIEW);
    W = w;
    H = h;	
}

void
display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	displayBoard(game);
	sb->display();
	glFlush();
	glutSwapBuffers();
}



//Handle keyboard input
void keyboard( unsigned char key, int x, int y )
{

    switch( key )  {
        case '1':
			if 	(startupScriptState ==1)
				return;
			if (gameStatus !=NEW)
				return;
			recordAnswers(startupScriptState, 1);
			startupScript();
            break;
        case '2':
			if 	(startupScriptState ==1)
				return;
			if (gameStatus !=NEW)
				return;
			recordAnswers(startupScriptState, 2);
			startupScript();
            break;
		case 'x':
		case 'X':
			if 	(startupScriptState !=1)
				return;
			if (gameStatus !=NEW)
				return;
			recordAnswers(startupScriptState, X);
			startupScript();
            break;
		case '0':
		case 'o':
		case 'O':
			if 	(startupScriptState !=1)
				return;
			if (gameStatus !=NEW)
				return;
			recordAnswers(startupScriptState, O);
			startupScript();
			break;
	}
	glutPostRedisplay();
}

Move getSlotFromPoint(Point boardPt)
{
	GLfloat colNbr = floor((boardPt.x ) /slotWidth);
	GLfloat rowNbr = floor((boardPt.y ) /slotHeight);
	return Move(colNbr,rowNbr);
}

Point getPointFromSlot(Move mv)
{

	GLfloat x = mv.first*slotWidth;
			x = x + lineSize*mv.first/magfactor;
	GLfloat y = mv.second*slotHeight;
			y = y + lineSize*mv.second/magfactor;
	return Point(x,  //X
				y, //Y
				0); //Z
}



void makeMove( Move  mv,gamePiece playerPiece)
{
	if (gameStatus!=IN_PLAY)
		return;

	if (mv.first>=cols || mv.first<0
	|| mv.second>=rows || mv.second<0)
	{
	  sb->setMessage(err_InvalidMove);
	  return;
	}
  if (game[mv.first][mv.second]!=OPEN)
  {
	  sb->setMessage(err_InvalidMove);
	  return;
  }
  //make move
	game[mv.first][mv.second]=playerPiece;

	//record win
	if (win(game,playerPiece))
		recordWin(playerPiece);
	if(done(game))
	{
		gameStatus=OVER;
		sb->setMessage(msg_GameEndsDraw);
	}

  player1Turn=!player1Turn;
  if (player1Turn)
	  sb->setMessage(msg_Player1Turn);
  else
	  sb->setMessage(msg_Player2Turn);
}


void recordWin(gamePiece  player)
{
	//change game Status
	gameStatus = OVER;

	//indicate winner
	if (player==player1GamePiece)
		sb->setMessage(msg_Player1Won);
	else
		sb->setMessage(msg_Player2Won);

	//animate winning line

}


//convert mouse Coordinates to real coordinates
void screenToWorld( int sX, int sY, GLfloat& wX, GLfloat& wY )
{
	wX = sX / (1.0*W) * worldX;
	wY = ( H - sY ) / (1.0*H) * worldY;
}


//Handle mouse input
void mouse(int mouseButton, int buttonState, int x, int y)
{
	GLfloat mouseX,mouseY;
	screenToWorld(x,y,mouseX,mouseY);
	Point mousePt(mouseX,mouseY,0);

	if(sb->getResetButton().pointInButton(mousePt) &&
		buttonState == GLUT_DOWN)  //did user click on reset button
	{
		sb->getResetButton().setButtonIsPressed(true);		
		return;
	}
	if(sb->getResetButton().pointInButton(mousePt) &&
		sb->getResetButton().isButtonPressed() &&
		buttonState == GLUT_UP)  //did user click on reset button
	{
		initGame();
		initStartupScript();
		return;
	}
	sb->getResetButton().setButtonIsPressed(false);		

	if (gameStatus!= IN_PLAY)
		return;
	if( mouseButton == GLUT_LEFT_BUTTON  &&
		buttonState == GLUT_DOWN)
	{
		gamePiece tmp = player1Turn?player1GamePiece:player2GamePiece;
		Move m= getSlotFromPoint(mousePt);
		makeMove(m ,tmp);
	}
	glutPostRedisplay();
}

void idle()
{
	if ((player1Type==COMPUTER && 
		player1Turn==true
		)||
		(player2Type==COMPUTER && 
		player1Turn==false
		))
	{
		makeComputerMove();
	}
	if (win(game,player1GamePiece))
		recordWin(player1GamePiece);
	else if (win(game,player2GamePiece))
		recordWin(player2GamePiece);
	else if(done(game))
	{
		gameStatus=OVER;
		sb->setMessage(msg_GameEndsDraw);
	}


}

void	setGameDetails()
{	
	stringstream ss(stringstream::in | stringstream::out);
	string pType = player1Type ==HUMAN?"HUMAN":"COMPUTER"; 
	string pPiece = player1GamePiece ==X?"X":"O"; 
	msgLine1 = "Player 1 ("+pPiece+"): "+pType;
	sb->setMessage2((char*) msgLine1.c_str());


	pType = player2Type ==HUMAN?"HUMAN":"COMPUTER"; 
	pPiece = player2GamePiece ==X?"X":"O"; 
	msgLine2 = "Player 2 ("+pPiece+"): "+pType;
	sb->setMessage3((char*) msgLine2.c_str());
	sb->setMessage("");

  if (player1Turn)
	  sb->setMessage(msg_Player1Turn);
  else
	sb->setMessage(msg_Player2Turn);

}


void startupScript()
{

	switch(startupScriptState)
	{
	case 0: sb->setMessage(msg_ChooseNumberPlayers); break;
	case 1: sb->setMessage(msg_ChoosePlayer1GamePiece); break;
	case 2: sb->setMessage(msg_ChooseOrderOfTurn); break;
	default: 
		setGameDetails();
		gameStatus=IN_PLAY; 
		break;
	}
}

void recordAnswers(GLint scriptQues, GLint scriptAnswer)
{
	switch(scriptQues)
	{
		case 0: //user answers - choose number of players
			player1Type = HUMAN;
			player2Type = scriptAnswer ==2?HUMAN:COMPUTER;
			startupScriptState++;
			break;
		case 1: //1 player1 chooses Xs or Os
			player1GamePiece = (gamePiece)scriptAnswer;
			player2GamePiece = (gamePiece)scriptAnswer==X?O:X;
			startupScriptState++;
			break;
		case 2: //Choose who goes first
			player1Turn= scriptAnswer==1?true:false;
			startupScriptState++;
			break;
	}
}


void initStartupScript()
{
	startupScriptState=0;
	gameStatus=NEW;
	sb->setMessage(msg_ChooseNumberPlayers);
	sb->setMessage2("");
	sb->setMessage3("");
	initGame();
	glutPostRedisplay();
}

void initializeGraphics()
{
	glDisable(GL_TEXTURE_2D);
	glClearColor(0.3,0.3,0.3,0.0);
    W = int( worldX * magfactor ); H = int( worldY * magfactor );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    int windowHandle = glutCreateWindow("4x4 Tic Tac Toe");
    glutSetWindow(windowHandle);
    glutPositionWindow ( 100, 100 );
    glutReshapeWindow( W, H );
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);	

	//initialize Score Board
	sb = new ScoreBoard(sbCorner, sbHeight, sbWidth,msg_ChooseNumberPlayers);
	sb->getResetButton().setStyle(Color(0.5,0.0,0.5),Color(1.0,1.0,1.0),GLUT_BITMAP_TIMES_ROMAN_24);
	sb->getResetButton().setDimensions(Point(worldX-resetButtonStart,worldY-BannerSpace,0),BannerSpace,resetButtonStart );

	//initialize Game Board
	initGame();
	startupScript();
}







void makeComputerMove()
{
	GLint currMaxPts=0; //array of maximum points associated with a move
	GLint newMaxPts=0; //array of maximum points associated with a move
	GLint currMaxSlot=-1;

	//make the move
	gamePiece player= player1Turn==true?player1GamePiece:player2GamePiece;
	vector<int> alphaBeta(2);
	alphaBeta[0] = -2; alphaBeta[1] = 2;
	Outcome best = minimax( (int)player, game, alphaBeta,0 );
	makeMove(Move(best.second.first,best.second.second),player);	
}

void cleanup()
{
	delete sb;
}


int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	initializeGraphics();
	glutMainLoop();
	cleanup();
	return 0;
}

