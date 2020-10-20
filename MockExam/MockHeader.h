#pragma once

bool login();
void printLogin(std::vector <std::vector <int>> vec, std::vector <int> cursor);
void task1();
void task2();
void task2sorting();
void task3();
void task3SetBoard(std::vector <std::vector <char>>& board);
void task3printBoard(std::vector <std::vector <char>>& board);
void task4(std::vector <std::vector <char>>& board);

struct playerStruct
{
	int vecIndex;
	char name;
	int value;
	char healthBar = '*';
};
const int amountOfPlayers = 20;
std::vector <playerStruct> player(amountOfPlayers);
struct pacmanPlayers
{
	int row = 0;
	int col = 0;
	char type = 'E';
};
pacmanPlayers pacPlayer;
pacmanPlayers dots; 
const int numberOfEnemies = 5;
std::vector <pacmanPlayers> enemies(numberOfEnemies);
int pacmanScoreMax = 0;
