// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	//Get the patrol points
	///Get the AI controller and the pawn it owns
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	///Find the Patrol route by searching the pawn by class
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	///Protect against no PatrolRoute component
	if (!ensure(PatrolRoute)) {	return EBTNodeResult::Failed; }

	///Retrieve the patrol points from the PatrolRoute
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	///Protect against empty PatrolRoute
	if (PatrolPoints.Num() == 0) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points")); 
		return EBTNodeResult::Failed;
	}

	//Set Next Waypoint
	///Get the blackboard component
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	///Get the current index of the blackboard component
	auto Index = BlackboardComp->GetValueAsInt(IndexKeySelector.SelectedKeyName);
	///Set the next waypoint index of the blackboard component
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle the Waypoint Index
	///Adding 1 to the current index and getting the length of the PatrolPoints array to calculate the modulus
	///And setting as value of the Next index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	///Setting the current index of the blackboard to the NextIndex value
	BlackboardComp->SetValueAsInt(IndexKeySelector.SelectedKeyName, NextIndex);

	///Return successful execution of node
	return EBTNodeResult::Succeeded;
}



