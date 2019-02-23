#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <map>

FBullCowGame::FBullCowGame() //default constructor
{
	 this->Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetMaxTries() const { 

	std::map<int32, int32> WordLengthToMaxTries { //{wordLength, maxTries}
		{3, 5}, {4, 3}, {5, 5}, {6, 5}, {7,7}
	};
	return WordLengthToMaxTries[MyHiddenWord.length()]; 

}
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }


	std::map<char, bool> LetterSeen = {};
	//TMap<char, bool> LetterSeen; 
	for (auto Letter : Word)  //for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) //if we've seeen the letter already then its repeating and not an isogram
		{
			return false; //we do not have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{

	for (auto Letter : Word)
	{
		if (!islower(Letter)) //uppercase letter found, inverted the logic
		{
			return false;
		}
		else if (isspace(Letter)) //found a whitespace, so return false
		{
			return false;
		}
		else if (Letter == '\0') // return character found \0 
		{
			return false;
		}
	}

	return true;
}

void FBullCowGame::PrintGameSummary()
{
	bool bGameWon = IsGameWon();
	if (bGameWon)
	{
		std::cout << "congratulations you won\n";
	}
	else
	{
		std::cout << "bad luck you lost\n";
	}
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	int32 GuessLength = Guess.length();

	if (!IsIsogram(Guess)) //if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess)) //if its not lowercase, so a fals return from the func would return this error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GuessLength != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
 	}
	else
	{
		return EGuessStatus::OK;
	}
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plan"; //this MUST be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;

	return;
}

//recieved a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	// loop through all letters in the Hidden Word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// letter is presnt in the hidden word
			if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				//in the same position
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else //not in the same pos
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	//check if the game has been won
	if (BullCowCount.Bulls == WordLength)
	{
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}

	return BullCowCount;
}


