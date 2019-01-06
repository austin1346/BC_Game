/*
This is the console executable that makes use of the BC Class
This acts as the view in a MVC pattern, and is responsible for all
user interaction for game logic see the FBC_Game class.
*/

#include <iostream>
#include <string>
#include "FBC_Game.h"

using FText = std::string;
using int32 = int;

void print_intro();
void play_game();
FText GetValidGuess();
bool ask_to_play_again();

//Instantiate a new game
FBC_Game BCGame;

//Entry point
int main() {
	bool bPlayAgain = false;

	do {
		print_intro();
		play_game();
		bPlayAgain = ask_to_play_again();
	} while (bPlayAgain);

	return 0; //exit
}

//Display intro text
void print_intro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;

	return;
}

//Play game
void play_game() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//Loop number of turns
	for (int32 i = 1; i <= MaxTries; i++) { //TODO change from FOR to WHILE loop once we are validating tries
		FText Guess = GetValidGuess();

		//Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls <<
			"\nCows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}

	//TODO; summarise game
	return;
}

//Loop continually until the user gives a valid guess
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		FText Guess = "";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word" << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letter." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters." << std::endl;
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //Keep looping until we get no errors
}

bool ask_to_play_again() {
	std::cout << "Do you want to play again? (y/n)";

	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
