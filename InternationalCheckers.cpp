/**********|**********|**********|
Program: TT02.1191302326.Omar.Challaf.cpp
Course: PROGRAMMING FUNDAMENTALS 
Year: 2019/20 Trimester 2
Name: Omar Challaf
ID: 1191302326
Lecture Section: TC01
Tutorial Section: TT02
Email: 0mar@email.com
Phone: 011-3720-9584
**********|**********|**********/





#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string>
using namespace std;


void clearScreen (){
	system("cls"); //system("clear") <MacOS 
}
void mainMenue(char &choice); // print the main mene
void tipsAndRules(); // print the help menu
void printTheBoard(char positions[10][10]); // print the play board
void convert(string label, int &row, int &col); // convert the positions entered by the user into its value on the array
void move(char &from2, char &to2); // move the piece to the enterd place and transfer and the # to the piece place 
bool firstRule(int counter, char player); // block the user from playing out of his turn
bool secondRule(char fromX, char fromY, char toX, char toY); // allow only diagonally moves.
bool thirdRule(char from, char to); // block the player from playing from/to black squares or (' ')
bool fourthRule(char,int fromX, int fromY, int toX, int toY,char positions[10][10]); // block the player from jump the squares, and capture the pieces.
void gameOver(); // show the game over screen in the end of the game
void crowning(char turn, int toX, char &crown);//make the piece crowned
void saveTheGame(char positions[10][10],int); // save the game
void loadTheGame(char positions[10][10],int&);// load the game
bool crownMovingBool(int fromX,int fromY, int toX, int toY,char positions[10][10]); // move the crowned pieces
void welcome(); // greeting screen with the logo
bool checkForMove(int toX, int toY,char positions[10][10]); // check if there is more steps for the normal pieces(not crowned)
void mutliMove(int toX, int toY,char positions[10][10]); // ask if the user want to do mutltiple steps, and do it if so
bool winLose(char positions[10][10]); // check if any player win, and show the congrats screen
bool checkForMoveCrowned(int toX, int toY,char positions[10][10]); // check the muti steps for crowned pieces
void multiCrowned(int toX, int toY,char positions[10][10]); // asks the player if he wnat to perform the multistep and do it if yes

int main(){
	welcome();
	char positions[10][10] = { // the main board.
		
		{' ','b',' ','b',' ','b',' ','b',' ','b'},
		{'b',' ','b',' ','b',' ','b',' ','b',' '},
		{' ','b',' ','b',' ','b',' ','b',' ','b'},
		{'b',' ','b',' ','b',' ','b',' ','b',' '},
		{' ','#',' ','#',' ','#',' ','#',' ','#'},
		{'#',' ','#',' ','#',' ','#',' ','#',' '},
		{' ','a',' ','a',' ','a',' ','a',' ','a'},
		{'a',' ','a',' ','a',' ','a',' ','a',' '},
		{' ','a',' ','a',' ','a',' ','a',' ','a'},
		{'a',' ','a',' ','a',' ','a',' ','a',' '}
};
	char choice; // to enter a choice from the main menu
	
	string from,to; // which square to move from/to. will be passed to convert function to switch them 
					//to the values on positions array
					
	int fromRow, fromCol, toRow, toCol; // pass the values by refrence to convert function 
	
	int counter = 1;// rounds counter
	char turn; // holds whose turn is it (a,b)
	// main menu 
	 do {
		clearScreen (); // claer the screen
		mainMenue(choice); // print main menue by mainMenue function
		
		// 1st choice, Start the Game
		if (choice == '1'){
			do{
				clearScreen ();
				
				printTheBoard(positions); // pass the array to printTheBoard function so its print it
				
					cout << endl;
					cout << "Round: " << counter <<' ';
					
					if (counter % 2 != 0){ // to inform the players who's turn it is depending on the counter
						turn = 'a';
						cout << ">> Player " << turn << " turn: ";
						
					}
					else {
						turn = 'b';
						cout << ">> Player " <<  turn << " turn: ";
					}
					cin	>> from >> to;
					
					if(from == "save" && to == "game"){ // save the game when type "save game"
						saveTheGame(positions,counter);
						clearScreen();
						main(); // going back to main menu after save
					}
					else{
						convert(from, fromRow, fromCol); // convert the squares names to the cells on the array using 
						convert(to, toRow, toCol);		// ASCII table
						if (firstRule(counter,positions[fromRow][fromCol])){ // mutliMove if the player playing on his turn
							if (thirdRule(positions[fromRow][fromCol],positions[toRow][toCol]) //checking the three 
								&& secondRule (fromRow,fromCol,toRow,toCol)						// other rule, to allow 
								&& (fourthRule(turn,fromRow,fromCol,toRow,toCol,positions) 
									|| crownMovingBool(fromRow,fromCol, toRow, toCol,positions))){
										
									move(positions[fromRow][fromCol],positions[toRow][toCol]); // make the move by passing the characters 
									
									crowning(turn,toRow,positions[toRow][toCol]);				// crown the piece if it reaced the eadge
									
									if (checkForMove(toRow,toCol,positions)){ // check for more moves (not crowned pieces)
											mutliMove(toRow,toCol,positions); // if there is another move available, ask the player if he want to play it
									}
									else if (checkForMoveCrowned(toRow,toCol,positions)){ // for more moves (not crowned pieces)
										 multiCrowned(toRow,toCol,positions);// if there is another move available, ask the player if he want to play it
									}
									++counter;								// after the move done succefully, it will be counted 
							}
							
							else{ // if any of the moving rules were wrong 
								cout <<"Wrong move, Press Enter to Try again\n";
								cin.ignore();
								cin.ignore();
							}
						}
						
						else { // if The first rule has been violated (the player played out of his turn)
							cout << "Not Your Turn, Press Enter to Retry";
							cin.ignore();
							cin.ignore();
						}
					}
			} while(winLose(positions)); // keep updating the board as long as there is no winner
		}
		
		else if (choice == '2'){ // load game choice
			clearScreen ();
			loadTheGame(positions,counter); // call the load game function 
											//and pass the array and counter to it, to edit them 
		}
		
		// 2rd choice, help and rules
		else if (choice == '3'){
			clearScreen ();
			tipsAndRules(); // print help menu
		}
		
		else if (choice == '4' ){ // end the game and show game over screen
			 gameOver();
		}
		else  { // if the choice is invaild, ask the user to retry
			cout << "Invaild Input, Press Enter to Try Again";
			cin.ignore();
			cin.ignore();
		}	
	} while (choice != '4');
	 
	return 0;
}

void welcome(){ // logo and greeting 
	clearScreen();
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << right;
	cout <<setw(90)<< "<|===============================================================|>\n";
	cout << setw(91)<<"<<|    _____ _    _ ______  _____ _    ___ ______ ______   _____  |>>\n";
	cout <<setw(92)<< "<<<|   / ____| |  | |  ____ / ____| |  / / |  ____|_____ ) / ____/ |>>>\n";
	cout << setw(93)<<"<<<<|  | |    | |__| | |__  | |    | |_/ /  | |__  | |   \\\\ | (___  |>>>>\n";
	cout <<setw(94) << "<<<<<|  | |    |  __  |  __| | |    | | \\ \\  |  __| | |__ // \\___  \\ |>>>>>\n";
	cout << setw(93)<<"<<<<|  | |____| |  | | |____| |____| |  \\ \\ | |____| |  \\ \\ ____) | |>>>>\n";
	cout <<setw(92)<< "<<<|   \\_____|_|  |_|______ \\_____|_|   \\_\\|______|_|   \\_\\|_____/ |>>>\n";
	cout <<setw(91)<< "<<|                                                               |>>\n";
	cout <<setw(90)<< "<|===============================================================|>\n";
   
	cout << endl; 
	cout << endl;
	cout <<setw(65) << "Press Enter to Proceed " ;
	cin.ignore();
	
	
}

void mainMenue(char &choice){ // take the choice from the user and pass it by refrence to the main.
	
	cout <<setw(90)<< "<|===============================================================|>\n";
	cout << setw(91)<<"<<|    _____ _    _ ______  _____ _    ___ ______ ______   _____  |>>\n";
	cout <<setw(92)<< "<<<|   / ____| |  | |  ____ / ____| |  / / |  ____|_____ ) / ____/ |>>>\n";
	cout << setw(93)<<"<<<<|  | |    | |__| | |__  | |    | |_/ /  | |__  | |   \\\\ | (___  |>>>>\n";
	cout <<setw(94) << "<<<<<|  | |    |  __  |  __| | |    | | \\ \\  |  __| | |__ // \\___  \\ |>>>>>\n";
	cout << setw(93)<<"<<<<|  | |____| |  | | |____| |____| |  \\ \\ | |____| |  \\ \\ ____) | |>>>>\n";
	cout <<setw(92)<< "<<<|   \\_____|_|  |_|______ \\_____|_|   \\_\\|______|_|   \\_\\|_____/ |>>>\n";
	cout <<setw(91)<< "<<|                                                               |>>\n";
	cout <<setw(90)<< "<|===============================================================|>\n";
	cout << right <<setw(76) <<"*****************************************" << endl;
	cout << setw(76) << "*             *                  *      *" << endl;
	cout << setw(76) << "*  *    Welcome To Checkers Game!    *  *" << endl;
	cout << setw(76)  << "*        *            *                 *" << endl;
	cout  <<setw(76) <<"*****************************************" << endl;
	cout << endl;
	cout << setw(64) << "1 - Start The Game" << endl;
	cout << setw(59) << "2 - Load Game" << endl;
	cout << setw(54) << "3 - Help" << endl;
	cout << setw(54) << "4 - exit" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << ">> Please Choose a Number From The list: " ;
	cin >> choice;
}

void tipsAndRules (){ // some of the rules of the game
	char help;
	cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\t\t| The general rule is that all moves and captures are made diagonally.|\n"
				<<"\t\t\t|    All references to squares refer to the dark squares (#) only.    |\n";
	cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	do {

	
		cout << "\t\t   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
		cout << "\t\t   |                                                                               |" << endl;
	cout << "\t\t   |Please choose what do you need to know more about, or go back to the main menu:|" << endl;
		cout << "\t\t   |                                                                               |" << endl;
		cout << "\t\t   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
		cout << "\t\t\t\t\t\t1 - Starting position " << endl;
		cout << "\t\t\t\t\t\t2 - Moves and captures " << endl;
		cout << "\t\t\t\t\t\t3 - Crowning " << endl;
		cout << "\t\t\t\t\t\t4 - return " << endl;
		cin >> help;
		cout << endl;
		cout << endl;
		if (help == '1'){
			clearScreen();
			cout << "\t\t\t\tEach player has 20 pieces. In the starting position,\n"
			<< "\t\t\t\tthe pieces are placed on the first four rows closest to the players.\n"
			<< "\t\t\t\tThis leaves two central rows empty\n\n" << endl;
			for (int i = 0; i < 1000000000; ++i); // to give the player so time to read before showing the options again
			}
		
		else if (help == '2'){
			clearScreen();
			cout << "\t\t\t\tThe player with the light pieces (a) moves first. Then turns alternate." << endl;
			cout << "\t\t\t\tOrdinary pieces move one square diagonally forward to an unoccupied square.\n\n" << endl;
			for (int i = 0; i < 1000000000; ++i);
		}
		
		else if (help == '3'){ 			
			clearScreen();
			cout << "\t\t\tA piece is crowned if it stops on the far edge of the board at the end of its turn\n"
			 << "\t\t\tCrowned pieces, sometimes called kings, can move freely multiple steps in any\n" 
			<< "\t\t\tdirection and may jump over and hence capture an opponent piece some distance away \n"
			 <<"\t\t\tand choose where to stop afterwards,\n"
			  << "\t\t\tbut must still capture the maximum number of pieces possible." << endl;
			for (int i = 0; i < 1000000000; ++i);
		}
		
		
		else if (help == '4'){
		}
		else
			cout << "Invaild input. Please choose from the list" << endl;
	}while(help != '4');
}

void printTheBoard(char positions[10][10]){ // print the board and basic instruction
	cout << "Enter The Square Label You Want to Move From\n" 
					<< "Then Space, Then The Square Label You Want to Move To\n"
					<< "For Exampel \" 7b 6c\",  type \"save game\", to save it" << endl;
					
		
		for (int row = 0; row < 10; ++row){
		cout << setw(45) << right <<"|---+---+---+---+---+---+---+---+---+---|\n";
		if (row < 9)
		cout << row+1 << "  ";
		else 
			cout << row+1 << " ";
		for (int col = 0; col < 10; ++col){
			cout << "| " << left <<setw(2)<< positions[row][col] ;
		}
		cout << "|";
		cout << endl;
		
		
	}
	cout << "   |---+---+---+---+---+---+---+---+---+---|" << endl;
	cout << "     a   b   c   d   e   f   g   h   i   j"  << endl;
}

void move(char &from2, char &to2){ // move the pieces using temporary variable
	char temp;
	temp = from2;
	from2 = to2;
	to2 = temp;
}

void convert(string label, int &row, int &col){ // to convert from the squares on the board to
										// the real cells on the arry;
	//if the choice was the 10th row.
	if (label[1] == '0'){						
		row = label[0] + label[1] -'X';
		col = label[2] - 'a' ;
	}
	// anything else but 10th.
	else {
		row = label[0] - '1'; 					   
		col = label[1] - 'a';
	}
}

bool firstRule (int counter, char player){ // to stop the player from playing on the others turn
	if (counter % 2 != 0 && (player == 'b'|| player == 'B'))
		return false;
	
	else if (counter % 2 == 0 && (player == 'a' || player == 'A'))
		return false;
	
	else 
		return true;
	
	
}

bool secondRule (char fromX, char fromY, char toX, char toY){ // to stop the user from playing in horizontal
															//or vertical lines, even if its ok for role 1
	if (fromX == toX || fromY == toY)
		return false;
	else 
		return true;
	
}


bool thirdRule(char from, char to){ // to stop the user from moving in from/ to blank (or 'light') spaces 
									// which are not part of the playing area.
									//and stop the player from moving to his own places. 
	if (from == ' ' || from == '#')
		return false;
	else if (to != '#')
		return false;
	else 
		return true;
}

bool fourthRule (char turn,int fromX, int fromY, int toX, int toY,char positions[10][10]){ // make a range for the player, cant move two empty squares.
																							//and allow the player to eat the piece 1 square away from him if the square after it is empty
	if ((fromX - toX == 1 || fromX - toX == -1) && (fromY - toY == 1 || fromY - toY == -1))
		return true;
	
	else if ((fromX - toX == 2) && (fromY - toY == 2)){
		if(((turn == 'a') && ((positions[toX + 1][toY + 1] == 'b') || (positions[toX + 1][toY + 1] == 'B'))) || 
		((turn == 'b') && ((positions[toX + 1][toY + 1] == 'a') || (positions[toX + 1][toY + 1] == 'A')))){
			positions[toX + 1][toY + 1] = '#';
			return true;
			}
			
		else
		return false;
	}
	
	else if ((fromX - toX == -2) && (fromY - toY == -2)){
		if(((turn == 'a') && ((positions[toX - 1][toY - 1] == 'b') || (positions[toX - 1][toY - 1] == 'B'))) || 
			((turn == 'b') && ((positions[toX - 1][toY - 1] == 'a') || (positions[toX - 1][toY - 1] == 'A')))){
				positions[toX - 1][toY - 1] = '#';
				return true;
				}
			
		else
		return false;
	}
	
	else if ((fromX - toX == -2) && (fromY - toY == 2)){
		if(((turn == 'a') && ((positions[toX - 1][toY + 1] == 'b') || (positions[toX - 1][toY + 1] == 'B'))) || 
			((turn == 'b') && ((positions[toX - 1][toY + 1] == 'a') || (positions[toX - 1][toY + 1] == 'A')))){
				positions[toX - 1][toY + 1] = '#';
				return true;
				}
		else
		return false;
	}
	
	else if ((fromX - toX == 2) && (fromY - toY == -2)){
		if(((turn == 'a') && ((positions[toX + 1][toY - 1] == 'b') || (positions[toX + 1][toY - 1] == 'B'))) || 
			((turn == 'b') && ((positions[toX + 1][toY - 1] == 'a') || (positions[toX + 1][toY - 1] == 'A')))){
			positions[toX + 1][toY - 1] = '#';
			return true;
			}
			
		else
		return false;
	}
	
	else
		return false;
}
void gameOver(){ // game over screen 
	clearScreen();
	cout << right;
	cout << endl;
	cout << endl;
	cout << '\a';
cout << setw(110) <<  "<|====================================================================================================================|>\n";
cout /*<< setw(111)*/<< "                   _______    ____       ____     ____      ______     _______  ___     _________  ______ 	   \n";
cout<< setw(111) << "    / ______|  / /\\ \\     / /\\ \\   / /\\ \\    |  ____|   / _____ \\ | |     | |  ____||_____ )		  \n";
cout << setw(111)<< "   | |        / /  \\ \\   / /  \\ \\ / /  \\ \\   | |___    / /     \\ \\| |     | | |___  | |   \\\\	  	\n";
cout<< setw(108)<<  "   | |    __ / /____\\ \\ / /    \\ / /    \\ \\  |  ___|   | |     | || \\     / |  ___| | |__ // \n";
cout << setw(109)<< "   | |____| || |    | |/ /      / /\\     \\ \\ | |____   \\ \\_____/ / \\ \\___/ /| |____ | |  \\ \\  \n";
cout << setw(111)<< "    \\_____|_||_|    |_/_/      /_/\\ \\     \\_\\|______|   \\_______/   \\_____/ |______||_|   \\_\\			\n";
cout << setw(110)<< "                                                                                              \n";
cout << setw(110) <<  "<|====================================================================================================================|>\n";
	for (int i = 0; i < 100000000; ++i);
	cout << right << setw(70) << "+-----------------------+\n" ;
	cout << setw(70) << "|   *           *       |\n" ;
	cout << setw(70) << "|      Thanks For    *  |\n" ;
	cout << setw(70) << "|     * Playing    *    |\n" ;
	cout << setw(70) << "| Hope you Enjoyed it * |\n" ;
	cout << setw(70) << "|*        *             |\n" ;
	cout << setw(70) << "+-----------------------+\n" ;
	exit(0);
	
}

void crowning(char piece, int toX, char &crown){ // crowning the piece when reach the edge
	if ((piece == 'a') && (toX == 0))
		crown = 'A';
	else if((piece == 'b') && (toX == 9))
		crown = 'B';
	
}
void saveTheGame(char positions[10][10] ,int counter){ // pass the board and counter to a file to save it
	ofstream saveGame;
	saveGame.open("Load.txt");
	saveGame << counter;
	for(int x = 0; x < 10; ++x){
		for(int y = 0; y < 10; ++y)
			saveGame << positions[x][y];
	saveGame << endl;
	}
	saveGame.close();
	
}

void loadTheGame(char positions[10][10],int &counter){ // load the array and counter from the file to the actual ones in the game.
	ifstream loadGame;
	loadGame.open("load.txt");
	loadGame >> counter;
	for(int x = 0; x < 10; ++x){
		for(int y = 0; y < 10; ++y){
			if (positions[x][y]!= ' ') // to avoid skipping the spaces.
			loadGame >> positions[x][y];
		}
			
	}
	loadGame.close();
}

bool crownMovingBool(int fromX,int fromY, int toX, int toY,char positions[10][10]){ // to allow the crowned pieces to go away, under certain conditions
	bool notIntheway = true; // variable to check if there is an (a) in the way of A, or b in the way of B, if so, the move is not vaild
	if (positions[fromX][fromY] == 'A'){
		 if((toX > fromX) && (toY > fromY)){ // check the way of moving
			for (int i = 0; i < (toY - fromY) ;++i){ // loop to check if there is a in the way of A and the same for B
				if(positions[toX - i][toY - i] == 'a' || positions[toX - i][toY - i] == 'A'){ // if there is, the variable will turn to false and will not allow the move to happen.
					notIntheway = false;
				}
			}
			if((positions[toX - 1][toY - 1] =='b' || positions[toX - 1][toY - 1] =='B') && notIntheway){
				positions[toX - 1][toY - 1] = '#';
				return true;
			}
			else
				return false;
		}
		
		else if ((toX > fromX) && (toY < fromY)){
			for (int i = 0; i < (fromY - toY); ++i){
				if(positions[toX - i][toY + i] == 'a' || positions[toX - i][toY + i] == 'A'){
					notIntheway = false;
				}
			}
			if((positions[toX - 1][toY + 1] =='b' || positions[toX - 1][toY + 1] =='B' ) && notIntheway){
				positions[toX - 1][toY + 1] = '#';
				return true;
			}
			else
				return false;
		}
		else if ((toX < fromX) && (toY < fromY)){
			for (int i = 0; i < (fromY - toY) ;++i){
				if(positions[toX + i][toY + i] == 'a' || positions[toX + i][toY + i] == 'A'){
					notIntheway = false;
				}
			}
			if((positions[toX + 1][toY + 1] =='b' || positions[toX + 1][toY + 1] =='B' ) && notIntheway){
				positions[toX + 1][toY + 1] = '#';
				return true;
			}
			else
				return false;
		}
	
		else if ((toX < fromX) && (toY > fromY)){
			for (int i = 0; i < (toY - fromY); ++i){
				if(positions[fromX + i][fromY - i] == 'a' || positions[fromX + i][fromY - i] == 'A'){
					notIntheway = false;
				}
			}
			if((positions[toX + 1][toY - 1] =='b' || positions[toX + 1][toY - 1] =='B' ) && notIntheway){
				positions[toX + 1][toY - 1] = '#';
				return true;
			}
			else
				return false;
		}
		else 
			return false;
	}
	
	else if (positions[fromX][fromY] == 'B'){
		if((toX > fromX) && (toY > fromY)){
			for (int i = 0; i < (toY - fromY) ;++i){
				if(positions[toX - i][toY - i] == 'b' || positions[toX - i][toY - i] == 'B'){
					notIntheway = false;
				}
			}
			if((positions[toX - 1][toY - 1] =='a' || positions[toX - 1][toY - 1] =='A'  ) &&notIntheway){
				positions[toX - 1][toY - 1] = '#';
				return true;
			}
			else
				return false;
		
		}
		else if ((toX > fromX) && (toY < fromY)){
			for (int i = 0; i < (fromY - toY); ++i){
				if(positions[toX - i][toY + i] == 'b' || positions[toX - i][toY + i] == 'B'){
					notIntheway = false;
				}
			}
			if((positions[toX - 1][toY + 1] =='a' || positions[toX - 1][toY + 1] =='A' )&&notIntheway){
				positions[toX - 1][toY + 1] = '#';
				return true;
			}
			else
				return false;
		}
		else if ((toX < fromX) && (toY < fromY)){
			for (int i = 0; i < (fromY - toY) ;++i){
				if(positions[toX + i][toY + i] == 'b' || positions[toX + i][toY + i] == 'B'){
					notIntheway = false;
				}
			}
			if((positions[toX + 1][toY + 1] =='a' || positions[toX + 1][toY + 1] =='A' )&&notIntheway){
				positions[toX + 1][toY + 1] = '#';
				return true;
			}
			else
				return false;
		}
	
		else if ((toX < fromX) && (toY > fromY)){
			for (int i = 0; i < (toY - fromY); ++i){
				if(positions[fromX + i][fromY - i] == 'b' || positions[fromX + i][fromY - i] == 'B'){
					notIntheway = false;
				}
			}
			if((positions[toX + 1][toY - 1] =='a' || positions[toX + 1][toY - 1] =='A' )&&notIntheway){
				positions[toX + 1][toY - 1] = '#';
				return true;
			}
			else
				return false;
		}
	}
	else
		return false;
	
}

bool checkForMove(int toX, int toY,char positions[10][10]){ // check if there is another move available for not crowned pieces
	if (positions[toX][toY] == 'a'){
		if((positions[toX + 1][toY + 1] == 'b' || positions[toX + 1][toY + 1] == 'B')
		&& positions[toX + 2][toY + 2] == '#'){
			return true;
		}
		
		else if((positions[toX - 1][toY + 1] == 'b'|| positions[toX - 1][toY + 1] == 'B') 
				&& positions[toX - 2][toY + 2] == '#'){
			return true;
		}
		
		else if((positions[toX + 1][toY - 1] == 'b'|| positions[toX + 1][toY - 1] == 'B')
				&& positions[toX + 2][toY - 2] == '#'){
			return true;
		}
		
		else if((positions[toX - 1][toY - 1] == 'b' || positions[toX - 1][toY - 1] == 'B')
				&& positions[toX - 2][toY - 2] == '#'){
			return true;
		}
		else 
			return false;
	}
	else if (positions[toX][toY] == 'b'){
		if((positions[toX + 1][toY + 1] == 'a' || positions[toX + 1][toY + 1] == 'A')
				&& positions[toX + 2][toY + 2] == '#'){
			return true;
		}
			
		else if((positions[toX - 1][toY + 1] == 'a' || positions[toX - 1][toY + 1] == 'A') 
				&& positions[toX - 2][toY + 2] == '#'){
			return true;
		
		}
		else if((positions[toX + 1][toY - 1] == 'a' || positions[toX + 1][toY - 1] == 'A') 
				&& positions[toX + 2][toY - 2] == '#'){
			return true;
		}
		
		else if((positions[toX - 1][toY - 1] == 'a'|| positions[toX - 1][toY - 1] == 'A')
				&& positions[toX - 2][toY - 2] == '#'){
			return true;
		}
		else 
			return false;
	}
	 else 
		 return false;
}

void mutliMove(int toX, int toY,char positions[10][10]){ // make the multi step if the player want so
	int multiX; // variables to resend them to checkForMove function and check for further moves
	int multiY;
	char take; // to hold the user"s choice, move or no

	clearScreen();
	printTheBoard(positions);
	cout << endl;
	cout << " >> Another move is available, Press y to take it, or anything else to skip it: ";
	cin >> take;
	if (take == 'y'){
		if (positions[toX][toY] == 'a'){ // search for the meant move 
			if((positions[toX + 1][toY + 1] == 'b' || positions[toX + 1][toY + 1] == 'B')
				&& positions[toX + 2][toY + 2] == '#'){
				positions[toX + 1][toY + 1] = '#'; // capture the piece
				move(positions[toX][toY],positions[toX + 2][toY + 2]); // move the players piece to the new place
				multiX = toX + 2; // new variables to resend them to checkForMove function and check for more moves
				multiY = toY + 2;
			}
			else if((positions[toX - 1][toY + 1] == 'b'|| positions[toX - 1][toY + 1] == 'B') 
				&& positions[toX - 2][toY + 2] == '#'){
				positions[toX - 1][toY + 1] = '#';
				move(positions[toX][toY],positions[toX - 2][toY + 2]);
				multiX = toX - 2;
				multiY = toY + 2;
			}
			
			else if((positions[toX + 1][toY - 1] == 'b'|| positions[toX + 1][toY - 1] == 'B')
				&& positions[toX + 2][toY - 2] == '#'){
				positions[toX + 1][toY - 1] = '#';
				move(positions[toX][toY],positions[toX + 2][toY - 2]);
				multiX = toX + 2;
				multiY = toY - 2;
			}
			else if((positions[toX - 1][toY - 1] == 'b' || positions[toX - 1][toY - 1] == 'B')
				&& positions[toX - 2][toY - 2] == '#'){
				positions[toX - 1][toY - 1] = '#';
				move(positions[toX][toY],positions[toX - 2][toY - 2]);
				multiX = toX - 2;
				multiY = toY - 2;
			}
		}
		else if (positions[toX][toY] == 'b'){
			if((positions[toX + 1][toY + 1] == 'a' || positions[toX + 1][toY + 1] == 'A')
				&& positions[toX + 2][toY + 2] == '#'){
				positions[toX + 1][toY + 1] = '#';
				move(positions[toX][toY],positions[toX + 2][toY + 2]);
				multiX = toX + 2;
				multiY = toY + 2;
			}
				
			else if((positions[toX - 1][toY + 1] == 'a' || positions[toX - 1][toY + 1] == 'A') 
				&& positions[toX - 2][toY + 2] == '#'){
				positions[toX - 1][toY + 1] = '#';
				move(positions[toX][toY],positions[toX - 2][toY + 2]);
				multiX = toX - 2;
				multiY = toY + 2;
			
			}
			else if((positions[toX + 1][toY - 1] == 'a' || positions[toX + 1][toY - 1] == 'A') 
				&& positions[toX + 2][toY - 2] == '#'){
				positions[toX + 1][toY - 1] = '#';
				move(positions[toX][toY],positions[toX + 2][toY - 2]);
				multiX = toX + 2;
				multiY = toY - 2;
			}
			
			else if((positions[toX - 1][toY - 1] == 'a'|| positions[toX - 1][toY - 1] == 'A')
				&& positions[toX - 2][toY - 2] == '#'){
				positions[toX - 1][toY - 1] = '#';
				move(positions[toX][toY],positions[toX - 2][toY - 2]);
				multiX = toX - 2;
				multiY = toY - 2;
			}
		}
		// resend the new variables to checkForMove, if there was another move, mutliMove function will be recalled  
		if (checkForMove(multiX,multiY,positions)){
				mutliMove(multiX,multiY,positions);
			}
	}
}



bool checkForMoveCrowned(int toX, int toY,char positions[10][10]){ // check for multistep for crowned pieces 
	if (positions[toX][toY] == 'A'){ 
		for (int x = 1; x < 10; ++x){ // loop to check if there is a piece to capture in all 4 directions.
				if((positions[toX + x][toY + x] == 'b' || positions[toX + x][toY + x] == 'B')
						&& positions[toX + x + 1][toY + x + 1] == '#'){
							return true;
						}
						
				else if ((positions[toX - x][toY - x] == 'b' || positions[toX - x][toY - x] == 'B')
						&& positions[toX - (x + 1)][toY - (x + 1)] == '#'){
							return true;
						}
				else if ((positions[toX - x][toY + x] == 'b' || positions[toX - x][toY + x] == 'B')
						&& positions[toX - (x + 1)][toY + (x + 1)] == '#'){
							return true;
						}
				else if ((positions[toX + x][toY - x] == 'b' || positions[toX + x][toY - x] == 'B')
						&& positions[toX + (x + 1)][toY - (x + 1)] == '#'){
							return true;
						}
				else 
					return false;
		}
	}
		
	else if (positions[toX][toY] == 'B'){
		for (int x = 1; x < 10; ++x){
				if((positions[toX + x][toY + x] == 'a' || positions[toX + x][toY + x] == 'A')
						&& positions[toX + x + 1][toY + x + 1] == '#'){
							return true;
						}
						
				else if ((positions[toX - x][toY - x] == 'a' || positions[toX - x][toY - x] == 'A')
						&& positions[toX - (x + 1)][toY - (x + 1)] == '#'){
							return true;
						}
				else if ((positions[toX - x][toY + x] == 'a' || positions[toX - x][toY + x] == 'A')
						&& positions[toX - (x + 1)][toY + (x + 1)] == '#'){
							return true;
						}
				else if ((positions[toX + x][toY - x] == 'a' || positions[toX + x][toY - x] == 'A')
						&& positions[toX + (x + 1)][toY - (x + 1)] == '#'){
							return true;
						}
				else 
					return false;
		}
	}
	else 
	 return false;
}
	




void multiCrowned(int toX, int toY,char positions[10][10]){
	char take;
	int specialX = 0 ; // new variable to use them in recalling the checkForMoveCrowned function again.
	int specialY = 0;
	int dontSkipMeX = toX;
	int dontSkipMeY = toY;
	
	clearScreen();
	printTheBoard(positions);
	
	cout << endl;
	cout << "Another move is available, Press y to take it, or anything else to skip it: ";
	cin >> take;
	if (take == 'y'){
		if (positions[toX][toY] == 'A'){
			for (int x = 1; x < 10; ++x){ // loop to check which direction and which piece is meant to be captured
					if((positions[toX + x][toY + x] == 'b' || positions[toX + x][toY + x] == 'B')
						&& positions[toX + x + 1][toY + x + 1] == '#'){
							
						positions[toX + x][toY + x] = '#';
						move(positions[toX][toY],positions[toX + x + 1][toY + x + 1]);
						specialX = toX + x + 1;
						specialY = toY + x + 1;
						break; // break out of the loop once it finds the meant piece, to avoid double multisteps without user permission if they both were available in the same time.
					}
					else if ((positions[toX - x][toY - x] == 'b' || positions[toX - x][toY - x] == 'B')
							&& positions[toX - (x + 1)][toY - (x + 1)] == '#'){
							positions[toX - x][toY - x] = '#';
							move(positions[toX][toY],positions[toX - (x + 1)][toY - (x + 1)]);
							specialX = toX - (x + 1);
							specialY = toY - (x + 1);
							break;
						}
					else if ((positions[toX - x][toY + x] == 'b' || positions[toX - x][toY + x] == 'B')
							&& positions[toX - (x + 1)][toY + (x + 1)] == '#'){
							positions[toX - x][toY + x] = '#';
							move(positions[toX][toY],positions[toX - (x + 1)][toY + (x + 1)]);
							specialX = toX - (x + 1);
							specialY = toY + (x + 1);
							break;
						}
					else if ((positions[toX + x][toY - x] == 'b' || positions[toX + x][toY - x] == 'B')
							&& positions[toX + (x + 1)][toY - (x + 1)] == '#'){
							positions[toX + x][toY - x] = '#';
							move(positions[toX][toY],positions[toX + (x + 1)][toY - (x + 1)]);
							specialX = toX + (x + 1);
							specialY = toY - (x + 1);
							break;
						}
			}
		}
		else if (positions[toX][toY] == 'B'){
			for (int x = 1; x < 10; ++x){
					if((positions[toX + x][toY + x] == 'a' || positions[toX + x][toY + x] == 'A')
						&& positions[toX + x + 1][toY + x + 1] == '#'){
						positions[toX + x][toY + x] = '#';
						move(positions[toX][toY],positions[toX + x + 1][toY + x + 1]);
						specialX = toX + x + 1;
						specialY = toY + x + 1;
						break;
					}
					else if ((positions[toX - x][toY - x] == 'a' || positions[toX - x][toY - x] == 'A')
							&& positions[toX - (x + 1)][toY - (x + 1)] == '#'){
							positions[toX - x][toY - x] = '#';
							move(positions[toX][toY],positions[toX - (x + 1)][toY - (x + 1)]);
							specialX = toX - (x + 1);
							specialY = toY - (x + 1);
							break;
						}
					else if ((positions[toX - x][toY + x] == 'a' || positions[toX - x][toY + x] == 'A')
							&& positions[toX - (x + 1)][toY + (x + 1)] == '#'){
							positions[toX - x][toY + x] = '#';
							move(positions[toX][toY],positions[toX - (x + 1)][toY + (x + 1)]);
							specialX = toX - (x + 1);
							specialY = toY + (x + 1);
							break;
						}
					else if ((positions[toX + x][toY - x] == 'a' || positions[toX + x][toY - x] == 'A')
							&& positions[toX + (x + 1)][toY - (x + 1)] == '#'){
							positions[toX + x][toY - x] = '#';
							move(positions[toX][toY],positions[toX + (x + 1)][toY - (x + 1)]);
							specialX = toX + (x + 1);
							specialY = toY - (x + 1);
							break;
						}
			}
		}
		// recall the checkForMoveCrowned to check for more steps using the new variables.
		if (checkForMoveCrowned(specialX,specialY,positions)){
				multiCrowned(specialX,specialY,positions);
		}
}

}

bool winLose(char positions[10][10]){ // searching for the characters to check if one of them is finished
	bool founda = false; // bool variables initialized to false, will change if and only if there is a (a,b) characters
	bool foundb = false;
	for (int x = 0; x < 10; ++x){
		for (int y = 0; y < 10; ++y){
			if(positions[x][y] == 'a' || positions[x][y] == 'A'){
				founda = true;
			}
			else if (positions[x][y] == 'b' || positions[x][y] == 'B'){
				foundb = true;
		}
	}
	
	}
	if (founda == false){ // if the variable still false after the checking loop,
							//it will announce the winner based on the loop, and will return false to the main function to stop the loop and end the game.
		clearScreen();
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "\t\t\t\t\t+============================+" << endl;
		cout << "\t\t\t\t\t|                            |" << endl;
		cout << "\t\t\t\t\t|       Player b Won !       |" << endl;
		cout << "\t\t\t\t\t|                            |" << endl;
		cout << "\t\t\t\t\t|      CONGRATULATIONS!!     |" << endl;
		cout << "\t\t\t\t\t|              &	     |" << endl;
		cout << "\t\t\t\t\t|     Hard Luck Player a :)  |" << endl;
		cout << "\t\t\t\t\t+============================+" << endl;
			for (int i = 0; i < 1000000000; ++i);
			gameOver();
		return founda;
	
	}
	else if(foundb == false){
		clearScreen();
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "\t\t\t\t\t+============================+" << endl;
		cout << "\t\t\t\t\t|                            |" << endl;
		cout << "\t\t\t\t\t|       Player a Won !       |" << endl;
		cout << "\t\t\t\t\t|                            |" << endl;
		cout << "\t\t\t\t\t|      CONGRATULATIONS!!     |" << endl;
		cout << "\t\t\t\t\t|              &	     |" << endl;
		cout << "\t\t\t\t\t|     Hard Luck Player b :)  |" << endl;
		cout << "\t\t\t\t\t+============================+" << endl;
		for (int i = 0; i < 6000000000; ++i);
		 gameOver();
	}
	else
		return true;
}