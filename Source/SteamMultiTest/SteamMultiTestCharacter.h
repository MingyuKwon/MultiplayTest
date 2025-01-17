// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SteamMultiTestCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASteamMultiTestCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ASteamMultiTestCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();



	////////////////////////////////////
	IOnlineSessionPtr OnlineSessionInterface;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	UFUNCTION(BlueprintCallable)
	void CreateGameSession();

	UFUNCTION(BlueprintCallable)
	void JoinGameSession();


	void OnCreateGameSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindGameSessionComplete(bool bWasSuccessful);
	void OnJoinGameSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);


	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	/////////////////////


	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	void InitializeOnlineSubSystem();

	UFUNCTION(BlueprintCallable)
	void CreateSessionThroughSubSystem();
	UFUNCTION(BlueprintCallable)
	void JoinSessionThroughSubSystem();

	UFUNCTION()
	void OnCreateSession(bool bwasSuccessFul);
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessFul);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySession(bool bwasSuccessFul);
	void OnStartSession(bool bwasSuccessFul);


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};

