// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GridLibrary.h"
#include "Syrup/MapUtilities/FieldType.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


/* \/ ===== \/ *\
|  \/ ATile \/  |
\* \/ ===== \/ */
/**
 * An object that snaps to the grid. 
 * 
 * May take up multiple grid locations by adding to the grid locations array.
 */
UCLASS(Abstract)
class SYRUP_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	/**
	 * Sets up the root and sub-tile mesh components.
	 */
	ATile();

	/**
	 * Adjusts the sub-tile mesh location so that it is always snapped to the
	 * grid location and orientation closest to its world transform.
	 * 
	 * @param Transform - The new transform of the tile.
	 */
	virtual void OnConstruction(const FTransform& Transform) override;

	/**
	 * Gets the grid transform this tile.
	 *
	 * @return The grid transform this tile.
	 */
	UFUNCTION(BlueprintPure)
	FGridTransform GetGridTransform() const;

	/**
	 * Applies a field to this tile.
	 *
	 * @param Type - The type of field to apply.
	 */
	UFUNCTION()
	void ApplyField(EFieldType Type);

	/**
	 * Removes a field to this tile.
	 *
	 * @param Type - The type of field to remove.
	 */
	UFUNCTION()
	void RemoveField(EFieldType Type);

protected:
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* TileMaterial;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UInstancedStaticMeshComponent* SubtileMesh;

	/*
	 * The relative locations of all of the sub-tiles of this tile.
	 * 
	 * @return The relative locations of all of the sub-tiles of this tile.
	 */
	UFUNCTION(BlueprintPure)
	virtual TSet<FIntPoint> GetRelativeSubTileLocations() const;

	/*
	 * The locations of all of the sub-tiles of this tile.
	 * 
	 * @return The locations of all of the sub-tiles of this tile.
	 */
	UFUNCTION(BlueprintPure)
	TSet<FIntPoint> GetSubTileLocations() const;

private:
	//The mesh used for each tile as the ground.
	UPROPERTY()
	UStaticMesh* TileMesh;

	//The field data for this tile.
	UPROPERTY(Transient)
	TMap<EFieldType, int> FieldsToStrengths = TMap<EFieldType, int>();
};
/* /\ ===== /\ *\
|  /\ ATile /\  |
\* /\ ===== /\ */