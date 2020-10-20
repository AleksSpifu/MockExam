#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "MockHeader.h"


int main()
{
	bool runprogram = true;
	bool allowedIn = false;
	if (login()) {
		system("cls");
		std::cout << "Password accepted!\n";
		system("pause");
		allowedIn = true;
	}
	else {
		std::cout << "Password rejected. Goodbye.";
	}

	while (runprogram && allowedIn) {
		system("cls");
		std::cout << "Welcome! Please select which task you would like to see. Press escape to exit.\n";
		std::cout << "1.\tTask 1\n2.\tTask 2\n3.\tTask 3\n4.\tTask 4(is kind of part of task 3 so it will go to task 3.\nEsc.\tExit\n";

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
	const int amountOfRolls = 2000;
	system("cls");
	std::vector <int> diceRolls;
	std::vector <int> amounts(6, 0);
	srand(time(NULL));
	for (int i = 0; i < amountOfRolls; i++) {
		diceRolls.push_back((rand() % 6) + 1);
		amounts[diceRolls[i] - 1]++;
	}
	for (int i = 0; i < amounts.size(); i++) {
		std::cout << i + 1 << ": " << amounts[i] << " times.\n";
	}
	system("pause");
}

void task2() {
	system("cls");
	srand(time(NULL));
	
	
	
	for (int i = 0; i < amountOfPlayers; i++) {
		player[i].vecIndex = i;
		player[i].name = i + 65;

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

	task2sorting();

	
}

void task2sorting() {
	playerStruct tempPlayer;

	for (int i = 0; i < amountOfPlayers; i++) {
		for (int j = 1; j < amountOfPlayers; j++) {

			if (player[j - 1].value > player[j].value) {

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
	const int boardSize = 25;
	int score = 0;
	std::vector <std::vector <char>> board(boardSize, std::vector <char>(boardSize, ' '));
	task3SetBoard(board);
	bool gameOver = false;
	bool playerWins = false;
	
	bool positionedPlayer = false;
	while (!positionedPlayer) {
		int tempR = rand() % boardSize;
		int tempC = rand() % boardSize;
		if (board[tempR][tempC] == ' ') {
			pacPlayer.row = tempR;
			pacPlayer.col = tempC;
			board[pacPlayer.row][pacPlayer.col] = pacPlayer.type;
			positionedPlayer = true;
		}
	}
	int moveDirection[2] = { 0, 0 };
	
	while (!gameOver) {
		system("cls");
		std::cout << "Use WASD to move. Esc to exit. Collect all the dots!\nScore:\t" << score << "\tTotal Score possible: " << pacmanScoreMax << "\n";
		task3printBoard(board);
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
		
		if (board[pacPlayer.row + moveDirection[0]][pacPlayer.col + moveDirection[1]] != '#') {
			if (board[pacPlayer.row + moveDirection[0]][pacPlayer.col + moveDirection[1]] == '.') {
				score += 5;
			}
			board[pacPlayer.row][pacPlayer.col] = ' ';
			pacPlayer.row += moveDirection[0];
			pacPlayer.col += moveDirection[1];
			board[pacPlayer.row][pacPlayer.col] = pacPlayer.type;
		}
		moveDirection[0] = 0;
		moveDirection[1] = 0;
		if (score == pacmanScoreMax) {
			gameOver = true;
			playerWins = true;
		}
	}
	if (playerWins) {
		std::cout << "Congrats! You got them all!\n";
	}
	else {
		std::cout << "Well you could always try again.\n";
	}
	system("pause");
}



void task3printBoard(std::vector <std::vector <char>>& board)
{
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board.size(); c++) {
			std::cout << board[r][c] << " ";
		}
		std::cout << "\n";
	}
}

void task3SetBoard(std::vector <std::vector <char>>& board)
{
	srand(time(NULL));
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
	
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].type = 'G';
		bool acceptedLocation = false;
		while (!acceptedLocation) {
			int tempR = rand() % board.size();
			int tempC = rand() % board.size();
			if (board[tempR][tempC] == ' ') {
				enemies[i].row = tempR;
				enemies[i].col = tempC;
				acceptedLocation = true;
			}
		}
	}
}

bool login()
{
	bool passwordAccepted = false;
	const int gridSize = 3;
	std::vector <std::vector <int>> displayNumbers(gridSize, std::vector <int>(gridSize, 0));
	std::vector <int> password{ 1, 4, 5, 2, 3 };
	std::vector <int> attemptedInput{ 1 };
	std::vector <int> cursor{ 0, 0 };
	int attempts = 3;

	for (int r = 0; r < displayNumbers.size(); r++) {
		for (int c = 0; c < displayNumbers[r].size(); c++) {
			displayNumbers[r][c] = (r*gridSize) + (c + 1);
		}
	}

	while (passwordAccepted == false || attempts > 0) {
		system("cls");
		if (attempts < 3) {
			std::cout << "Incorrect password! Please try again.\n";
		}
		std::cout << "Use WASD to move, and Enter to reset.\n";
		std::cout << "You have " << attempts << " attempts left.\n";
		printLogin(displayNumbers, cursor);
		int move[2] = { 0, 0 };

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
			attemptedInput.clear();
			attemptedInput.push_back(1);
			cursor[0] = 0;
			cursor[1] = 0;
			attempts--;
			break;
		default:
			break;
		}
		for (int i = 0; i < 2; i++) {
			if (cursor[i] + move[i] >= 0 && cursor[i] + move[i] <= gridSize - 1) {
				cursor[i] += move[i];
			}
		}
		if (attemptedInput[attemptedInput.size() - 1] != displayNumbers[cursor[0]][cursor[1]]) {
			attemptedInput.push_back(displayNumbers[cursor[0]][cursor[1]]);
		}

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
			else {
				attempts--;
				attemptedInput.clear();
				attemptedInput.push_back(1);
				cursor[0] = 0;
				cursor[1] = 0;
			}
		}
		if (attempts == 0) {
			return false;
			break;
		}
		
	}
	
}

void printLogin(std::vector <std::vector <int>> vec, std::vector <int> cursor) 
{
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