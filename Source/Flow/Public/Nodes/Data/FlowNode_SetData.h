#pragma once
#include "GameDataContext.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_SetData.generated.h"

UENUM()
enum EDataOperation {
    Set UMETA(DisplayName = "="),
    Add UMETA(DisplayName = "+"),
    Subtract UMETA(DisplayName = "-"),
    Multiply UMETA(DisplayName = "*"),
    Divide UMETA(DisplayName = "/"),
    Modulo UMETA(DisplayName = "%")
};

UCLASS(NotBlueprintable, meta = (DisplayName = "Edit Data"))
class FLOW_API UFlowNode_SetData final : public UFlowNode {
    GENERATED_BODY()
    public:
    UFlowNode_SetData();
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameDataContextKey key;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TEnumAsByte<EDataOperation> operation;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 valueToSet;
    
    
    
    virtual void ExecuteInput(const FName& pinName) override;
#if WITH_EDITOR
    virtual FString GetNodeDescription() const override;
    virtual FString GetStatusString() const override;
#endif
};
