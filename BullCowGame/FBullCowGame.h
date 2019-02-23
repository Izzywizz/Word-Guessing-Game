/*
The game logic (no view code or direct user interaction). The game is a simple guess the word game based on Mastermind
*/
#pragma once
#include <string>

//type alias/ make the syntax Unreal friendly
using FString = std::string;
using int32 = int;

// all values init to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

//enums

enum class EGuessStatus
{
	Invalid_Status,
	OK, 
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	//constructor
	FBullCowGame();
	//~FBullCowGame(); //deconstructor like in swift

	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	void PrintGameSummary();
	EGuessStatus CheckGuessValidity(FString Guess) const;
	void Reset();
	FBullCowCount SubmitValidGuess(FString);


// Please try and ignore this and cous on the interface above ^^
private:
	// see constructor for init
	bool bGameWon;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};