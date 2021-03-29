// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

// ------
// Struct used to define bulls and cows counts
// --------
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void InitGame();
	void EndGame();

private:
	void ProcessGuess(const FString& guess);
	bool IsIsogram(const FString& word) const;
	TArray<FString> GetValidWords(const TArray<FString>& wordList) const;
	// guess is a const param to go in
	// bull and cowCount are out params by just setting them as refs
	FBullCowCount GetBullCows(const FString& guess) const; 

private:
	FString m_HiddenWord;
	int32 m_PlayerLives;
	bool m_IsGameOver;
	TArray<FString> m_Isograms;
};
