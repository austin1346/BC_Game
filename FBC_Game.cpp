#include "FBC_Game.h"

using int32 = int;

FBC_Game::FBC_Game() {
	Reset();
}

void FBC_Game::Reset() {
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	return;
}

int32 FBC_Game::GetMaxTries() const {
	return MyMaxTries;
}

int32 FBC_Game::GetCurrentTry() const {
	return MyCurrentTry;
}

int32 FBC_Game::GetHiddenWordLength() const {
	return MyHiddenWord.length();
}

bool FBC_Game::IsGameWon() const {
	return false;
}

EGuessStatus FBC_Game::CheckGuessValidity(FString Guess) const {
	if (false) {
		return EGuessStatus::Not_Isogram; //if the guess is not an isogram
	}
	else if (false) {
		return EGuessStatus::Not_Lowercase; //if the guess is not all lowercase
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length; //if the guess length is wrong
	}
	else {
		return EGuessStatus::OK;
	}
}

//Receives a VALID guess, incrememnts turn, and returns count
FBullCowCount FBC_Game::SubmitGuess(FString Guess) {
	//increment turn number
	MyCurrentTry++;

	//setup a return variable
	FBullCowCount BullCowCount;

	//loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();

	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	return BullCowCount;
}
