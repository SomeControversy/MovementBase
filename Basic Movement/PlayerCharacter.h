UCLASS()
class VERTIGO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		//Built-in functionality
protected:
	virtual void BeginPlay() override;

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Custom Code
protected:

	///MOVEMENT FUNCTIONS (EXPOSED)
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	///MOVEMENT FUNCTIONS (EXPOSED)

	///FLIPPING FUNCTIONS (EXPOSED)
	UFUNCTION()
		void FlipUp(FHitResult hit, FVector initalVelocity, float jumpZ);
	//UFUNCTION()
	//void FlipDown(FHitResult hit);
	///FLIPPING FUNCTIONS (EXPOSED)