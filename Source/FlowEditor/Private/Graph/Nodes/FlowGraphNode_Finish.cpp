#include "Graph/Nodes/FlowGraphNode_Finish.h"
#include "Graph/Widgets/SFlowGraphNode_Finish.h"

#include "Nodes/Route/FlowNode_FinishFlow.h"

UFlowGraphNode_Finish::UFlowGraphNode_Finish(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AssignedNodeClasses = {UFlowNode_FinishFlow::StaticClass()};
}

TSharedPtr<SGraphNode> UFlowGraphNode_Finish::CreateVisualWidget()
{
	return SNew(SFlowGraphNode_Finish, this);
}
