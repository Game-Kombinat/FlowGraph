#pragma once

#include "Nodes/FlowNode.h"
#include "FlowNode_Finish.generated.h"

/**
 * Not sure what this is supposed to be but let me tell ya, it ain't finishing the flow.
 * Deprecated in favour of FinishFlow which does, in fact, finish the flow.
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Finish"), Deprecated)
class FLOW_API UDEPRECATED_FlowNode_Finish : public UFlowNode
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void ExecuteInput(const FName& PinName) override;
};
