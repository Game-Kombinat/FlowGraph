#include "Nodes/Route/FlowNode_Finish.h"

UDEPRECATED_FlowNode_Finish::UDEPRECATED_FlowNode_Finish(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Route");
	NodeStyle = EFlowNodeStyle::InOut;
#endif

	OutputPins = {};
}

void UDEPRECATED_FlowNode_Finish::ExecuteInput(const FName& PinName)
{
	// this will call FinishFlow()
	Finish();
}
