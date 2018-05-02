// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//TODO protect against empty patrol routes
	
	//Get the patrol points
	///Get the AI controller and then the pawn it owns
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	///Cast the patrolling guard class to the controlled pawn to get the patrolling guard
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	///Retrieve the patrol points of the patrolling guard
	auto PatrolPoints = PatrollingGuard->PatrolPoints_CPP;
	
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



