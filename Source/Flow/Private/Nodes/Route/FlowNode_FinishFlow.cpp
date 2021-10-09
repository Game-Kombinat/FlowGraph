#include "Nodes/Route/FlowNode_FinishFlow.h"

#include "FlowAsset.h"
#include "FlowSubsystem.h"

UFlowNode_FinishFlow::UFlowNode_FinishFlow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Route");
	NodeStyle = EFlowNodeStyle::InOut;
#endif

	OutputPins = {};
}

void UFlowNode_FinishFlow::ExecuteInput(const FName& PinName)
{
	if (const auto subSys = GetFlowSubsystem()) {
		subSys->FinishRootFlow(GetFlowAsset()->GetOwner(), EFlowFinishPolicy::Abort);
	}
}
