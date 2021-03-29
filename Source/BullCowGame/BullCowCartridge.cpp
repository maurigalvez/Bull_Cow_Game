// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame();   
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{   
    ClearScreen(); 
    // check if game is over
    if (this->m_IsGameOver)
    {
        //restart game
        ClearScreen();
        InitGame();
        return;
    }

    this->ProcessGuess(Input);   
}

// ------
// INITIALIZE GAME
// ------
void UBullCowCartridge::InitGame()
{
   // in Unreal every time you use a string you need to use TEXT macro
   // Set hidden word
   this->m_HiddenWord = TEXT("loco");
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
void UBullCowCartridge::ProcessGuess(FString guess)
{
    // check player guess
    if (guess == this->m_HiddenWord)
    {
        PrintLine(TEXT("You are correct! You win!"));
        EndGame();
        return;
    }
    else
    {

        // check player lives
        if (--this->m_PlayerLives > 0)
        {
            // check if length is different
            if (guess.Len() != this->m_HiddenWord.Len())
            {
                PrintLine(TEXT("The hidden word is %i characters long! You have % i lives left"), this->m_HiddenWord.Len(), this->m_PlayerLives);
            }
            else
            {
                PrintLine(TEXT("You guess was wrong! Try again! You have % i lives left"), this->m_PlayerLives);
            }
        }
        else
        {
            PrintLine(TEXT("You ded!"));
            EndGame();
        }
    }
}
