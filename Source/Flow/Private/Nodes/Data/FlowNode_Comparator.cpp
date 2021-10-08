#include "Nodes/Data/FlowNode_Comparator.h"

#include "FlowAsset.h"

UFlowNode_Comparator::UFlowNode_Comparator() {
#if WITH_EDITOR
    Category = TEXT("Operators");
    NodeStyle = EFlowNodeStyle::Logic;
#endif
    OutputPins.Empty();
    AddOutputPins({FName("True"), FName("False")});
}

void UFlowNode_Comparator::ExecuteInput(const FName& pinName) {
    // const auto dc = GetFlowAsset()->GetDataContext();
    // const int32 valueA = dc->GetValue(keyA);
    // const int32 valueB = dc->GetValue(keyB);
    //
    // switch (operation.GetValue()) {
    //     case Equals:
    //         TriggerOutput(valueA == valueB ? FName("True") : FName("False"), true);
    //         break;
    //     case NotEquals:
    //         TriggerOutput(valueA != valueB ? FName("True") : FName("False"), true);
    //         break;
    //     case Greater:
    //         TriggerOutput(valueA > valueB ? FName("True") : FName("False"), true);
    //         break;
    //     case GreaterOrEqual:
    //         TriggerOutput(valueA >= valueB ? FName("True") : FName("False"), true);
    //         break;
    //     case Lesser:
    //         TriggerOutput(valueA < valueB ? FName("True") : FName("False"), true);
    //         break;
    //     case LesserOrEqual:
    //         TriggerOutput(valueA <= valueB ? FName("True") : FName("False"), true);
    //         break;
    //     default:
    //         // todo: note about unhandled enum type?
    //         TriggerOutput(FName("False"), true);
    // }
}
