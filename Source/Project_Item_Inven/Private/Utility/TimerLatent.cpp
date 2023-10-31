// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/TimerLatent.h"

void TimerLatent::UpdateOperation(FLatentResponse& Response)
{
	bool isFinish = updateFunc();
	if (isFinish) completeFunc();

	Response.DoneIf(isFinish);
}

