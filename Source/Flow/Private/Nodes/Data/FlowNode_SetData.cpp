#include "Nodes/Data/FlowNode_SetData.h"

#include "FlowAsset.h"

UFlowNode_SetData::UFlowNode_SetData() {
#if WITH_EDITOR
    Category = TEXT("Operators");
    NodeStyle = EFlowNodeStyle::Logic;
#endif
}

void UFlowNode_SetData::ExecuteInput(const FName& pinName) {
    const auto dc = GetFlowAsset()->GetDataContext();
    const int32 valueA = dc->GetValue(key);
    FGameDataContextKey newKey = FGameDataContextKey(key);
    switch (operation.GetValue()) {
        case Set:
            newKey.value = valueToSet;
            dc->SetValue(newKey);
            break;
        case Add:
            newKey.value += valueToSet;
            dc->SetValue(newKey);
            break;
        case Subtract:
            newKey.value -= valueToSet;
            dc->SetValue(newKey);
            break;
        case Multiply:
            newKey.value *= valueToSet;
            dc->SetValue(newKey);
            break;
        case Divide:
            newKey.value /= FMath::Max(1, valueToSet);
            dc->SetValue(newKey);
            break;
        case Modulo:
            newKey.value = newKey.value % valueToSet;
            dc->SetValue(newKey);
            break;
    }
    TriggerFirstOutput(true);
}

#if WITH_EDITOR
FString UFlowNode_SetData::GetNodeDescription() const {
    FString op;
    switch (operation.GetValue()) {
        case Set:
            op = "=";
            break;
        case Add:
            op = "+";
            break;
        case Subtract:
            op = "-";
            break;
        case Multiply:
            op = "*";
            break;
        case Divide:
            op = "/";
            break;
        case Modulo:
            op = "%";
            break;
        default:
            op = "????";
    }
    return FString::Format(TEXT("{0} {1} {2}"), {key.name.ToString(), op, FString::FromInt(valueToSet)});
}

FString UFlowNode_SetData::GetStatusString() const {
    return Super::GetStatusString();
}
#endif