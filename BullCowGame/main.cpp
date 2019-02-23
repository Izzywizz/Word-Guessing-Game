/* This is the console executable, that makes use of BullVow class
This acts as the view in aMVC pattern, and is responsible for all user
interaction. For game logic see the FBUllCowGame class
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//just an alias not a type change, to make syntax Unreal frientldy
using FText = std::string;
using int32 = int;
// FText and FString are unreal type but we are going to be using a type alias to simulate it
// String is mutable, good for chaging text and Ftext good for user interaction


// forward declartion/ prototype bc outside of class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; //instatiate a new game/ Global/ we use across plays

// the entry point for our application
int main()
{
	bool bPlayAgain{ false };
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; //exit application
}

// METHODS

// Introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


//plays a single game till completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// LOOP asking for guesses while the game 
	// 	is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		// submit valud guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	BCGame.PrintGameSummary();

	return;
}

//loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess("");
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout <<  ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		//guess validity
		switch (Status)
		{
		case EGuessStatus::OK:
			return Guess;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase letters\n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until you get a valid input

	return Guess;
}
	

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/ n) with the same hidden word: ";
	FText Response{ "" };
	std::getline(std::cin, Response);

	std::cout << std::boolalpha; // print bools as true or false	
	return (Response[0] == 'y' || Response[0] == 'Y');

}

