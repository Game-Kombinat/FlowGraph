#include "Nodes/Data/FlowNode_IsTrue.h"

#include "FlowAsset.h"

UFlowNode_IsTrue::UFlowNode_IsTrue() {
#if WITH_EDITOR
    Category = TEXT("Operators");
    NodeStyle = EFlowNodeStyle::Condition;
#endif
    OutputPins.Empty();
    AddOutputPins({FName("True"), FName("False")});
}

void UFlowNode_IsTrue::ExecuteInput(const FName& pinName) {
    const auto dc = GetFlowAsset()->GetDataContext();
    if (dc->GetTruthyness(key)) {
        TriggerOutput(FName("True"));
    }
    else {
        TriggerOutput(FName("False"));
    }
}
#if WITH_EDITOR
FString UFlowNode_IsTrue::GetNodeDescription() const {
    return FString::Format(TEXT("If {0} is True"), {key.name.ToString()});
}

FString UFlowNode_IsTrue::GetStatusString() const {
    return Super::GetStatusString();
}
#endif
