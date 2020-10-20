#include <iostream>
#include <vector>
#include <string>
#include <conio.h> //for _getch
#include <stdlib.h> //for random number
#include <stdio.h> //for NULL for random seed
#include <time.h> //for random seed
#include "MockHeader.h"


int main()
{
	bool runprogram = true;
	bool allowedIn = false;
	if (login()) { //Have to login to see the rest of the program
		system("cls");
		std::cout << "Password accepted!\n";
		system("pause");
		allowedIn = true;
	}
	else {
		std::cout << "Password rejected. Goodbye.";
	}

	//I don't have time to comment everything here but it's a pretty straight forward menu.
	while (runprogram && allowedIn) {
		system("cls");
		std::cout << "Welcome! Please select which task you would like to see. Press escape to exit.\n";
		std::cout << "1.\tTask 1\n2.\tTask 2\n3.\tTask 3\n4.\tTask 4(is kind of part of task 3 so it will go to task 3).\nEsc.\tExit\n";

		switch (_getch())
		{
		case 27:
			runprogram = false;
			break;
		case '1':
			task1();
			break;
		case '2':
			task2();
			break;
		case '3':
			task3();
			break;
		case '4':
			task3();
			break;
		default:
			bool acceptedInput = false;
			
			while (!acceptedInput) {
				system("cls");
				std::cout << "Wrong input. Do you want to try again?(Y/N)\n";
				switch (tolower(_getch()))
				{
				case 'y':
					acceptedInput = true;
					break;
				case 'n':
					acceptedInput = true;
					runprogram = false;
				default:
					break;
				}
			}
			
			break;
		}
	}
}

void task1() {
	//This is also pretty self explanatory.
	const int amountOfRolls = 2000;
	system("cls");
	std::vector <int> diceRolls;
	std::vector <int> amounts(6, 0);
	srand(time(NULL));
	for (int i = 0; i < amountOfRolls; i++) {
		diceRolls.push_back((rand() % 6) + 1);
		amounts[diceRolls[i] - 1]++;
	}
	std::cout << "The dice was rolled " << amountOfRolls << " times, and this was how many times I got the different numbers:\n";
	for (int i = 0; i < amounts.size(); i++) {
		std::cout << i + 1 << ": " << amounts[i] << " times.\n";
	}
	system("pause");
}

void task2() {

	system("cls");
	srand(time(NULL));
	//first give everyone a name and number
	for (int i = 0; i < amountOfPlayers; i++) {
		player[i].vecIndex = i;
		player[i].name = i + 65;

		//Then give everyone a random number, but never the same number.
		bool acceptedNumber = false;
		while (!acceptedNumber) {
			int numberHolder = (rand() % 20) + 1;
			for (int j = 0; j < amountOfPlayers; j++) {
				if (numberHolder == player[j].value) {
					numberHolder = 0;
				}
				
			}
			if (numberHolder != 0) {
				player[i].value = numberHolder;
				acceptedNumber = true;
			}
		}
		
	}

	//then print it out.
	std::cout << "Number\tName\tValue\tHealthbar\n";
	std::cout << "----------------------------------------\n";
	for (int i = 0; i < amountOfPlayers; i++) {
		std::cout << player[i].vecIndex << "\t" << player[i].name << "\t" << player[i].value << "\t";
		for (int j = 0; j < player[i].value; j++) {
			std::cout << player[i].healthBar;
		}
		std::cout << "\n";
	}
	std::cout << "\nNow watch the sorting work it's magic!\n";
	system("pause");

	//Then go into the sorting
	task2sorting();

	
}

void task2sorting() {
	playerStruct tempPlayer;

	//This basically moves through everything the same amount of times as there are players, and if one is smaller than the other, swap their places. then it goes again. and again.
	//If i was writing for an old computer or trying to optimize i could probably do that, but this works and i have no idea how to do that.
	for (int i = 0; i < amountOfPlayers; i++) {
		for (int j = 1; j < amountOfPlayers; j++) {

			if (player[j - 1].value < player[j].value) {

				tempPlayer.name = player[j].name;
				tempPlayer.vecIndex = player[j].vecIndex;
				tempPlayer.value = player[j].value;

				player[j].name = player[j - 1].name;
				player[j].vecIndex = player[j - 1].vecIndex;
				player[j].value = player[j - 1].value;

				player[j - 1].name = tempPlayer.name;
				player[j - 1].vecIndex = tempPlayer.vecIndex;
				player[j - 1].value = tempPlayer.value;
			}

		}
	}
	//Then it prints everything out again allowing you to compare all the numbers and names and stuff to check that it's working properly.
	std::cout << "\nNumber\tName\tValue\tHealthbar\n";
	std::cout << "----------------------------------------\n";
	for (int i = 0; i < amountOfPlayers; i++) {
		std::cout << player[i].vecIndex << "\t" << player[i].name << "\t" << player[i].value << "\t";
		for (int j = 0; j < player[i].value; j++) {
			std::cout << player[i].healthBar;
		}
		std::cout << "\n";
	}
	system("pause");
}

void task3() {
	srand(time(NULL));

	//Here you can change the board size if you want. I make walls and stuff based on the size, but it's not really made for much smaller than 15, at that point the walls go next to eachother and 
	//there is no space for the player to collect the dots.
	const int boardSize = 25;
	int score = 0;
	bool positionedPlayer = false;
	int moveDirection[2] = { 0, 0 };
	std::vector <std::vector <char>> board(boardSize, std::vector <char>(boardSize, ' '));

	//Prepare the board
	task3SetBoard(board);

	//this puts the player in a random position, assuming it's not a wall
	while (!positionedPlayer) {
		int tempR = rand() % boardSize;
		int tempC = rand() % boardSize;
		if (board[tempR][tempC] == ' ') {
			pacPlayer.row = tempR;
			pacPlayer.col = tempC;

			positionedPlayer = true;
		}
	}

	//Then get the dots and enemies in place
	task4(board);

	//Then start the gameloop
	bool gameOver = false;
	bool playerWins = false;
	
	while (!gameOver) {
		system("cls");
		std::cout << "Use WASD to move. Esc to exit. Collect all the dots!\nScore:\t" << score << "\tTotal Score possible: " << pacmanScoreMax << "\n";

		//Print the board and all the peices.
		//The peices are not actually stored on the board, but if there is a peice on the tiles it will print the peice instead of a space.
		task3printBoard(board);

		//This changes moveDirections X or Y "axis" and just adds it onto the row or coloumn depending on what was pressed.
		switch (tolower(_getch()))
		{
		case 'w':
			
			moveDirection[0] = -1;
			break;
		case 's':

			
			moveDirection[0] = 1;
			break;
		case 'a':
			
			moveDirection[1] = -1;
			break;
		case 'd':
			
			moveDirection[1] = 1;
			break;
		case 27:
			gameOver = true;
			break;
		default:
			break;
		}
		
		//after a quick failsafe to make sure it's not into a wall
		if (board[pacPlayer.row + moveDirection[0]][pacPlayer.col + moveDirection[1]] != '#') {
			pacPlayer.row += moveDirection[0];
			pacPlayer.col += moveDirection[1];
		}

		//if you are no a dot, move it out of the way and get points for it
		for (int i = 0; i < dots.size(); i++) {
			if (pacPlayer.row == dots[i].row && pacPlayer.col == dots[i].col) {
				
				dots[i].row = boardSize * 2;
				dots[i].col = boardSize * 2;
				score += 5;
			}
		}
		
		//then reset the direction of movement.
		moveDirection[0] = 0;
		moveDirection[1] = 0;

		//if you get all the dots, it'll let you win even if an enemy could theoretically win.
		if (score == pacmanScoreMax) {
			gameOver = true;
			playerWins = true;
		}
		else {
			task4enemiesMove(board);
		}

		//Checks if your position is the same as an enemy position, if so, lose.
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].row == pacPlayer.row && enemies[i].col == pacPlayer.col) {
				gameOver = true;
				break;
			}
		}
		turn++;
	}

	//outside of the loop, just print the final state of the board and either congratulate or encourage for replays.
	system("cls");
	std::cout << "Use WASD to move. Esc to exit. Collect all the dots!\nScore:\t" << score << "\tTotal Score possible: " << pacmanScoreMax << "\n";
	task3printBoard(board);
	if (playerWins) {
		std::cout << "Congrats! You got them all!\n";
	}
	else {
		std::cout << "Well you could always try again.\n";
	}
	system("pause");
}

void task4enemiesMove(std::vector <std::vector <char>>& board) {
	//Same thing with the move direction here as with the player.
	int moveDirection[2] = { 0, 0 };

	//for every enemy, it will calculate the distance in the X and Y axis from the player, decide which is bigger, and tries to move that.
	//it will not work if it is about to move into another enemy, or if it will hit a wall. Also, it never actually actively kills the player,
	//it just stays in the way, and the player has to run into them. They do tend to block up stuff though so its pretty fair. 
	//They only move every 2nd player move. Otherwise it's impossible to win. this can be tuned up or down in the header file.
	for (int i = 0; i < enemies.size(); i++) {
		int diffRow = enemies[i].row - pacPlayer.row;
		int diffCol = enemies[i].col - pacPlayer.col;
		if (diffRow < 0) {
			moveDirection[0] = 1;
			diffRow *= -1;
		}
		else {
			moveDirection[0] = -1;
		}
		if (diffCol < 0) {
			moveDirection[1] = 1;
			diffCol *= -1;
		}
		else {
			moveDirection[1] = -1;
		}
		if (turn % pacmanEnemiesPlayEvery == 0) {
			bool illegalRow = false;
			bool illegalCol = false;
			for (int j = 0; j < enemies.size(); j++) {
				if (enemies[i].row + moveDirection[0] == enemies[j].row) {
					illegalRow = true;
				}
				else if (enemies[i].col + moveDirection[1] == enemies[j].col) {
					illegalCol = true;
				}
			}
			if (diffRow > diffCol) {
				if (board[enemies[i].row + moveDirection[0]][enemies[i].col] == ' ' && !illegalRow) {
					enemies[i].row += moveDirection[0];
				}
				else if (board[enemies[i].row][enemies[i].col + moveDirection[1]] == ' ' && !illegalCol) {
					enemies[i].col += moveDirection[1];
				}
			}
			if (diffRow < diffCol) {
				if (board[enemies[i].row][enemies[i].col + moveDirection[1]] == ' ' && !illegalCol) {
					enemies[i].col += moveDirection[1];
				}
				else if (board[enemies[i].row + moveDirection[0]][enemies[i].col] == ' ' && !illegalRow) {
					enemies[i].row += moveDirection[0];
				}

			}
		}
		
	}
}

void task3printBoard(std::vector <std::vector <char>>& board)
{

	//This is pretty straight forward. Print everything, if the players position is the same as the tile currently selected, print E. This is always the first priority.
	//Then it will try to print an enemy, if the positions are the same. This is the second priority. After that come the dots. I did it this way so that the
	//enemies don't wipe out the dots by walking over them, like they do if i just change the board itself. 
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board.size(); c++) {
			bool spaceOccupied = false;
			if (r == pacPlayer.row && c == pacPlayer.col) {
				std::cout << pacPlayer.type << " ";
				spaceOccupied = true;
			}
			for (int i = 0; i < numberOfEnemies; i++) {
				if (r == enemies[i].row && c == enemies[i].col && !spaceOccupied) {
					std::cout << enemies[i].type << i;
					spaceOccupied = true;
				}
			}
			for (int i = 0; i < dots.size(); i++) {
				if (r == dots[i].row && c == dots[i].col && !spaceOccupied) {
					std::cout << dots[i].type << " ";
					spaceOccupied = true;
				}
			}
			if (!spaceOccupied) {
				std::cout << board[r][c] << " ";
			}
		}
		std::cout << "\n";
	}
}

void task3SetBoard(std::vector <std::vector <char>>& board)
{

	//this will create walls and random peices of wall around the level. It's kind of modular as i divided by the size of the board, but this is what i was talking about
	//when i wrote that less than 15 is pretty unplayable. I didn't have time to fidget more with this though, so i'm just gonna say don't play on less than 15. otherwise its good.
	srand(time(NULL));

	//all of these are created the same all the time.
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board.size(); c++) {
			if (r == 0 || r == (board.size() - 1) || c == 0 || c == (board.size() - 1)) {
				board[r][c] = '#';
			}
			if (r == (board.size() / 6) && c > (board.size() - (board.size() / 3))) {
				board[r][c] = '#';
			}
			if (r == (board.size() / 5) && c < (board.size() / 3)) {
				board[r][c] = '#';
			}
			if (c == (board.size() / 2 - 1) && r >= (board.size() / 5) && r <= (board.size() / 2)) {
				board[r][c] = '#';
			}
			if (c == (board.size() / 2 - 1) && r >= ((board.size() / 4) * 3)) {
				board[r][c] = '#';
			}
			if (c == (board.size() / 4 - 1) && r >= (board.size() / 3)) {
				board[r][c] = '#';
			}
			if (c == ((board.size() / 4) * 3) && r >= (board.size() / 3)) {
				board[r][c] = '#';
			}
		}
	}
	//then scatter some peices randomly around. There's a 20% chance on every tile that it'll make a wall, and it also checks around it to make sure it doesn't block anything.
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board.size(); c++) {

			if ((rand() % 10) < 2) {
				if (r != 0 && r != (board.size() - 1) && c != 0 && c != (board.size() - 1)) {
					int counter = 0;
					for (int row = -1; row < 2; row++) {
						for (int col = -1; col < 2; col++) {
							if (board[r + row][c + col] != ' ') {
								counter++;
							}
						}
					}
					if (counter == 0) {
						board[r][c] = '#';
					}
				}
			}
		}
	}

	
}

void task4(std::vector <std::vector <char>>& board) {
	srand(time(NULL));
	
	//this sets up 5 enemies and 15 dots randomly across empty spaces. it makes sure not to spawn enemies on top of the player so you'll lose instantly.
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].type = 'G';
		bool acceptedLocation = false;
		while (!acceptedLocation) {
			int tempR = rand() % board.size();
			int tempC = rand() % board.size();
			if (board[tempR][tempC] == ' ' && tempR != pacPlayer.row && tempC != pacPlayer.col) {
				enemies[i].row = tempR;
				enemies[i].col = tempC;
				acceptedLocation = true;
			}
		}
	}

	for (int i = 0; i < dots.size(); i++) {
		dots[i].type = '.';
		bool acceptedLocation = false;
		while (!acceptedLocation) {
			int tempR = rand() % board.size();
			int tempC = rand() % board.size();
			if (board[tempR][tempC] == ' ') {
				dots[i].row = tempR;
				dots[i].col = tempC;
				acceptedLocation = true;
			}
		}
	}
}

bool login()
{
	//here it's possible to change the gridSize to get as many possibilities as you want. You have to change the password for that to work though, 
	//as the numbers might not be next to eachother anymore. However doing that just requires changing the vector itself, and everything works regardless of how long it is. 
	bool passwordAccepted = false;
	const int gridSize = 3;
	std::vector <std::vector <int>> displayNumbers(gridSize, std::vector <int>(gridSize, 0));
	std::vector <int> password{ 1, 4, 5, 2, 3 };
	std::vector <int> attemptedInput{ 1 };
	std::vector <int> cursor{ 0, 0 };
	int attempts = 3;

	//This will populate the vector with however many spaces there are from 1 all the way to the final number.
	for (int r = 0; r < displayNumbers.size(); r++) {
		for (int c = 0; c < displayNumbers[r].size(); c++) {
			displayNumbers[r][c] = (r*gridSize) + (c + 1);
		}
	}

	//runs until either password accepted or you run out of attempts.
	while (passwordAccepted == false && attempts > 0) {
		system("cls");

		//if one attempt is already spent, shame the user for forgetting the password.
		if (attempts < 3) {
			std::cout << "Incorrect password! Please try again.\n";
		}
		std::cout << "Use WASD to move, and Enter to reset.\n";
		std::cout << "You have " << attempts << " attempts left.\n";
		printLogin(displayNumbers, cursor);
		int move[2] = { 0, 0 };

		//i use a similar moveDirection thing here, making the switch statement much smaller.
		switch (tolower(_getch()))
		{
		case 'w':
			move[0] = -1;
			move[1] = 0;
			break;
		case 'a':
			move[0] = 0;
			move[1] = -1;
			break;
		case 's':
			move[0] = 1;
			move[1] = 0;
			break;
		case 'd':
			move[0] = 0;
			move[1] = 1;
			break;
		case '\r':
			//if they hit enter, let them waste an attempt but try again.
			attemptedInput.clear();
			attemptedInput.push_back(1);
			cursor[0] = 0;
			cursor[1] = 0;
			attempts--;
			break;
		default:
			break;
		}

		//Then it's just a matter of moving the cursor the correct way, based on the move array.
		for (int i = 0; i < 2; i++) {
			if (cursor[i] + move[i] >= 0 && cursor[i] + move[i] <= gridSize - 1) {
				cursor[i] += move[i];
			}
		}

		//every move, just have a failsafe that it will never add the same number twice, as that's not possible. then push_back the number you land on in an attempt vector which
		//will be compared with the actual password later.
		if (attemptedInput[attemptedInput.size() - 1] != displayNumbers[cursor[0]][cursor[1]]) {
			attemptedInput.push_back(displayNumbers[cursor[0]][cursor[1]]);
		}

		//If they are the same size, it's the moment of truth. It'll go through every position, and if all of them are the same, access granted.
		if (attemptedInput.size() == password.size()) {
			int counter = 0;
			for (int i = 0; i < attemptedInput.size(); i++) {
				if (attemptedInput[i] == password[i]) {
					counter++;
				}
			}
			if (counter == password.size()) {
				passwordAccepted = true;
				return true;
				break;
			}

			//if not then reset everything and try again.
			else {
				attempts--;
				attemptedInput.clear();
				attemptedInput.push_back(1);
				cursor[0] = 0;
				cursor[1] = 0;
			}
		}

		//if you run out of attempts, get kicked out of the program.
		if (attempts == 0) {
			return false;
		}
		
	}
	
}

void printLogin(std::vector <std::vector <int>> vec, std::vector <int> cursor) 
{

	//this just prints the login screen, nothing important. 
	//Here i also don't actually change the board, but rather print the cursor instead of the number, so as to not change the value on the screen.
	const int x = 0;
	const int y = 1;
	for (int r = 0; r < vec.size(); r++) {
		for (int c = 0; c < vec[r].size(); c++) {
			std::cout << " | ";
			if (cursor[x] == r && cursor[y] == c) {
				std::cout << "* ";
			}
			else {
				std::cout << vec[r][c];
				if (vec[r][c] < 10) {
					std::cout << " ";
				}
			}
		}
		std::cout << " | \n";
	}
}