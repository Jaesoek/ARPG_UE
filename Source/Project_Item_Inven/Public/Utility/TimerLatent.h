// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LatentActions.h"
#include <functional>

/**
 * 
 */
class PROJECT_ITEM_INVEN_API TimerLatent : public FPendingLatentAction
{

private:
	std::function<bool()> updateFunc;
	std::function<void()> completeFunc;

public:
	TimerLatent(std::function<bool()> updateFunc, std::function<void()> completeFunc)
	{
		TimerLatent::updateFunc = updateFunc;
		TimerLatent::completeFunc = completeFunc;
	};

	virtual void UpdateOperation(FLatentResponse& Response) override;
};
