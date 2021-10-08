// Copyright (c) Game Kombinat

#pragma once
#include "CoreMinimal.h"
#include "GameDataContext.h"
#include "Nodes/FlowNode.h"

/**
 * 
 */
class FLOWEDITOR_API FFlowNode_GameDataContextSelectorDetails final : public IPropertyTypeCustomization {
    typedef TSharedPtr<FGameDataContextKey> FItemType;
    TArray<FItemType> keyList;
    UFlowNode* outerNode = nullptr;
public:
    
    
    static TSharedRef<IPropertyTypeCustomization> MakeInstance() {
        return MakeShareable(new FFlowNode_GameDataContextSelectorDetails());
    }

    TSharedPtr<FGameDataContextKey> GetInitiallySelectedObject();
    // IPropertyTypeCustomization interface
    virtual void CustomizeHeader(
        TSharedRef<IPropertyHandle> StructPropertyHandle,
        class FDetailWidgetRow& HeaderRow,
        IPropertyTypeCustomizationUtils& StructCustomizationUtils
    ) override;

    virtual void CustomizeChildren(
        TSharedRef<class IPropertyHandle> StructPropertyHandle,
        class IDetailChildrenBuilder& StructBuilder,
        IPropertyTypeCustomizationUtils& StructCustomizationUtils
    ) override;

private:
    TSharedPtr<IPropertyHandle> PropertyHandle;
    FItemType selectedObject;
    void CollectDataContextKeys();
    void OnSelectionChanged(const FItemType newItem, ESelectInfo::Type SelectInfo);
    void EnsureNodeData();
    void OnDataKeyNameChanged(const FText& newText, ETextCommit::Type textType) const;
    TSharedRef<SWidget> GenerateEventWidget(FItemType element) const;
    FText GetSelectedKeyDisplayName() const;
    TSharedRef<SWidget> GetDefaultPropertyViewWidget() const;

};
