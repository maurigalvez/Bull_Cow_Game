// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
//#include "Math/UnrealMathUtility.h" - Need to be included if not already done so

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();   
    FBullCowCount Count;
    this->m_Isograms = GetValidWords(HiddenWords);
    InitGame();   
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{      
    // check if game is over
    if (this->m_IsGameOver)
    {
        //restart game
        ClearScreen();
        InitGame();
        return;
    }
    // pass player input
    this->ProcessGuess(Input);   
}

// ------
// INITIALIZE GAME
// ------
void UBullCowCartridge::InitGame()
{
   // in Unreal every time you use a string you need to use TEXT macro
   // Set hidden word
   this->m_HiddenWord = this->m_Isograms[FMath::RandRange(0, m_Isograms.Num()-1)];
   // set player lives
   this->m_PlayerLives = this->m_HiddenWord.Len();
   // init game over
   this->m_IsGameOver = false;
   // ----
   // Game Message
   // ----
   PrintLine(TEXT("Welcome to Bull Cows!"));
   PrintLine(TEXT("Guess the %i letter word!"), this->m_HiddenWord.Len());    // TODO: replace magic number
   PrintLine(TEXT("You have %i Lives"), this->m_PlayerLives);
   PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
   // -----
   // Guess
   // ------
   PrintLine(TEXT("Character 1 of the hidden word is: %c"), this->m_HiddenWord[0]);
   PrintLine(TEXT("The 4th character of HW is: %c"), this->m_HiddenWord[3]);
}

// ----
// Process End Game
// ----
void UBullCowCartridge::EndGame()
{
    this->m_IsGameOver = true;
    PrintLine(TEXT("Press enter to start again!"));
}

// -----
// Process guess from player
// -----
void UBullCowCartridge::ProcessGuess(const FString& guess)
{
    // check player guess
    if (guess == this->m_HiddenWord)
    {
        PrintLine(TEXT("You are correct! You win!"));
        EndGame();
        return;
    }

    // check if length is different
    if (guess.Len() != this->m_HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i characters long!"), this->m_HiddenWord.Len());
        return;
    }
    // check if word is isogram
    if (!this->IsIsogram(guess))
    {
        PrintLine(TEXT("No repeating letters!"));
        return;
    }   

    this->m_PlayerLives--;

    // check player lives
    if (this->m_PlayerLives == 0)
    {
        PrintLine(TEXT("You ded!"));
        PrintLine(TEXT("The hidden word was %s!"), *this->m_HiddenWord);
        EndGame();
        return;
    }

    PrintLine(TEXT("Try again! You have % i lives left"), this->m_PlayerLives);
    // show player bulls and cows
    FBullCowCount count = this->GetBullCows(guess);
    PrintLine(TEXT("You have %i Bulls and %i Cows"), count.Bulls, count.Cows);
}

// ------
// Check whether given word is an isogram
// ------
bool UBullCowCartridge::IsIsogram(const FString& word) const
{
    // iterate through word
    for (int32 index = 0; index < word.Len(); index++)
    {
        for (int32 comparison = index + 1; comparison < word.Len(); comparison++)
        {
            if (word[index] == word[comparison])
                return false;
        }
    }
    return true;
}

// -----
// Return a list of valid words
// ------
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& wordList) const
{
    TArray<FString> validWords;
    // iterate through every word in passed word list
    for (FString word : wordList)
    {
        // word needs to be between 4 to 8 characters
        // AND make sure word is isogram
        if (word.Len() >= 4 && word.Len() <= 10 && IsIsogram(word))
        {            
            validWords.Emplace(word);
        }
    }
    return validWords;
}

// -----
// Get the bull and cow count depending on players' guess
// -----
FBullCowCount UBullCowCartridge::GetBullCows(const FString& guess) const
{
    FBullCowCount count;
    // if the index guess is same as index hidden, increase bull count
    // if not a bull was it a cow? if yes increase cow count
    for (int32 charIndex = 0; charIndex < guess.Len(); charIndex++)
    {
        // check if character is the same
        if (guess[charIndex] == this->m_HiddenWord[charIndex])
        {
            count.Bulls++;
            continue;
        }

        // otherwise check if it's a cow
        for (int32 hiddenIndex = 0; hiddenIndex < this->m_HiddenWord.Len(); hiddenIndex++)
        {
            if (guess[charIndex] == this->m_HiddenWord[hiddenIndex])
            {
                count.Cows++;
                break;
            }
        }
    }
    return count;
}
