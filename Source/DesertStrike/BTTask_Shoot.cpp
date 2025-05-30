// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterAIController.h"
#include "ShooterAICharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    if(OwnerComp.GetAIOwner() == nullptr){
        return EBTNodeResult::Failed;
    }
    AShooterAICharacter* Character = Cast<AShooterAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if(Character){
        Character->Shoot();
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}