#pragma once
//Just declaring a bunch 
bool login();
void printLogin(std::vector <std::vector <int>> vec, std::vector <int> cursor);
void task1();
void task2();
void task2sorting();
void task3();
void task3SetBoard(std::vector <std::vector <char>>& board);
void task3printBoard(std::vector <std::vector <char>>& board);
void task4(std::vector <std::vector <char>>& board);
void task4enemiesMove(std::vector <std::vector <char>>& board);

//Playerstruct for task 2
struct playerStruct
{
	int vecIndex;
	char name;
	int value;
	char healthBar = '*';
};
const int amountOfPlayers = 20;
std::vector <playerStruct> player(amountOfPlayers);

//Pacman struct for the player, enemies and the dots.
struct pacmanPlayers
{
	int row = 0;
	int col = 0;
	char type = 'E';
};

//Turn is used for telling the AI if it can move or not.
int turn = 0;
int pacmanEnemiesPlayEvery = 2; //pacman enemies play every 2 turns

//The rest is pretty self explanatory.
pacmanPlayers pacPlayer;
const int numberOfDots = 15;
std::vector <pacmanPlayers> dots(numberOfDots);
const int numberOfEnemies = 5;
std::vector <pacmanPlayers> enemies(numberOfEnemies);
int pacmanScoreMax = numberOfDots * 5;
