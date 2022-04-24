// Fill out your copyright notice in the Description page of Project Settings.

#include "RollableWidget.h"
#include "Components/ProgressBar.h"


void URollableWidget::SetCurrentCharge(float CurrentCharge, float MaxCharge)
{
	SuperchargeBar->SetPercent(CurrentCharge / MaxCharge );
}