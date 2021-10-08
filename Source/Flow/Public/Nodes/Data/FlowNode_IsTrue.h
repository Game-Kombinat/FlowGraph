#pragma once
#include "GameDataContext.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_IsTrue.generated.h"



UCLASS(NotBlueprintable, meta = (DisplayName = "Is True"))
class FLOW_API UFlowNode_IsTrue final : public UFlowNode {
    GENERATED_BODY()
    public:
    UFlowNode_IsTrue();
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameDataContextKey key;
    
    virtual void ExecuteInput(const FName& pinName) override;
#if WITH_EDITOR
    virtual FString GetNodeDescription() const override;
    virtual FString GetStatusString() const override;
#endif
};
