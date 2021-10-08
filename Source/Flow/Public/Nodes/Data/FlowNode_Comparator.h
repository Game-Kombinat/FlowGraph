#pragma once
#include "GameDataContext.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_Comparator.generated.h"

UENUM()
enum EComparisonOperator {
    Equals,
    NotEquals,
    Greater,
    GreaterOrEqual,
    Lesser,
    LesserOrEqual
};

UCLASS(NotBlueprintable, meta = (DisplayName = "Comparator"))
class FLOW_API UFlowNode_Comparator final : public UFlowNode {
    GENERATED_BODY()
    public:
    UFlowNode_Comparator();
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameDataContextKey keyA;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TEnumAsByte<EComparisonOperator> operation;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameDataContextKey keyB;
    
    virtual void ExecuteInput(const FName& pinName) override;
};
