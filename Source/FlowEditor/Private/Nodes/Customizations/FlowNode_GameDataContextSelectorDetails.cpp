// Copyright (c) Game Kombinat

#include "FlowNode_GameDataContextSelectorDetails.h"

#include "DetailWidgetRow.h"
#include "FlowModule.h"
#include "IDetailChildrenBuilder.h"
#include "Widgets/Layout/SWrapBox.h"


void FFlowNode_GameDataContextSelectorDetails::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
                                                               FDetailWidgetRow& HeaderRow,
                                                               IPropertyTypeCustomizationUtils&
                                                               StructCustomizationUtils) {
    PropertyHandle = StructPropertyHandle;
    EnsureNodeData();

    if (!outerNode) {
        HeaderRow.NameContent()[
                PropertyHandle->CreatePropertyNameWidget()
            ]
            .ValueContent()
            .HAlign(HAlign_Fill)[
                GetDefaultPropertyViewWidget()
            ];
        return;
    }

    HeaderRow.NameContent()[
            PropertyHandle->CreatePropertyNameWidget()
        ].ValueContent()
         .HAlign(HAlign_Fill)
        [
            SNew(SComboBox<FItemType>)
                        .OptionsSource(&keyList)
                        .OnGenerateWidget(this, &FFlowNode_GameDataContextSelectorDetails::GenerateEventWidget)
                        .OnSelectionChanged(this, &FFlowNode_GameDataContextSelectorDetails::OnSelectionChanged)
                        .InitiallySelectedItem(GetInitiallySelectedObject())
            [
                SNew(STextBlock)
                .Text(this, &FFlowNode_GameDataContextSelectorDetails::GetSelectedKeyDisplayName)
            ]
        ][
            SNew(SBorder)[
                PropertyHandle->CreatePropertyValueWidget()
            ]
        ];
}

void FFlowNode_GameDataContextSelectorDetails::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
                                                                 IDetailChildrenBuilder& StructBuilder,
                                                                 IPropertyTypeCustomizationUtils&
                                                                 StructCustomizationUtils) {
    PropertyHandle = StructPropertyHandle;
}


FFlowNode_GameDataContextSelectorDetails::FItemType
FFlowNode_GameDataContextSelectorDetails::GetInitiallySelectedObject() {
    if (!outerNode) {
        return nullptr;
    }
    if (PropertyHandle->GetNumPerObjectValues() > 1) {
        return MakeShareable(new FGameDataContextKey("Multiple Values", -1));
    }
    
    void* rawValue = nullptr;
    auto member = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataContextKey, guid));
    member->GetValueData(rawValue);
    FGuid* selectedKey = static_cast<FGuid*>(rawValue);
    if (!selectedKey) {
        UE_LOG(LogTemp, Error, TEXT("Failed to get value for selected properties GUID. Address invalid."));
        return nullptr;
    }
    int idx = keyList.IndexOfByPredicate([&](FItemType x) {
        return x.Get()->guid == *selectedKey;
    });

    if (idx != INDEX_NONE) {
        selectedObject = keyList[idx];
        return keyList[idx];
    }
    
    return nullptr;
}

void FFlowNode_GameDataContextSelectorDetails::CollectDataContextKeys() {
    if (!outerNode || !outerNode->GetFlowAsset()) {
        return;
    }
    auto dc = outerNode->GetDataContext()->GetKeyList();
    TArray<UObject*> outers;
    PropertyHandle->GetOuterObjects(outers);
    keyList.Empty();
    for (const FGameDataContextKey key : dc) {
        keyList.Add(MakeShareable(new FGameDataContextKey(key)));
    }
}

void FFlowNode_GameDataContextSelectorDetails::OnSelectionChanged(const FItemType newItem,
                                                                  ESelectInfo::Type SelectInfo) {
    selectedObject = newItem;
    void* rawValue = nullptr;
    // for some reason this works for writing but reading (get initially selected object) this doesn't work when reading.
    // I have not the faintest idea why that is. I'm probably getting something confuzzled.
    // Important part is: it works
    PropertyHandle->GetValueData(rawValue);
    if (PropertyHandle->GetNumPerObjectValues() > 1) {
        return;
    }
    FGameDataContextKey* keyInParent = static_cast<FGameDataContextKey*>(rawValue);
    keyInParent->guid = newItem->guid;
    keyInParent->name = newItem->name;
    keyInParent->value = newItem->value; // this isn't necessary, really but for good measure we oughta keep it.
}

void FFlowNode_GameDataContextSelectorDetails::EnsureNodeData() {
    if (!outerNode) {
        TArray<UObject*> outers;
        PropertyHandle->GetOuterObjects(outers);
        outerNode = Cast<UFlowNode>(outers[0]);
    }
    CollectDataContextKeys();
    selectedObject = GetInitiallySelectedObject();
}

void FFlowNode_GameDataContextSelectorDetails::OnDataKeyNameChanged(const FText& newText, ETextCommit::Type textType) const {
    void* rawValue = nullptr;
    PropertyHandle->GetValueData(rawValue);
    FGameDataContextKey* keyInParent = static_cast<FGameDataContextKey*>(rawValue);
    keyInParent->name = FName(newText.ToString());
    TArray<UObject*> outers;
    PropertyHandle->GetOuterObjects(outers);
    UGameDataContext* gc = Cast<UGameDataContext>(outers[0]);
    if (gc) {
        gc->InvalidateKeyCache();
    }
}

TSharedRef<SWidget> FFlowNode_GameDataContextSelectorDetails::GenerateEventWidget(FItemType element) const {
    // return entry type for item
    // pretty sure there ain't much else that we need to do here
    return SNew(STextBlock).Text(FText::FromName(element.Get()->name));
}

FText FFlowNode_GameDataContextSelectorDetails::GetSelectedKeyDisplayName() const {
    if (!selectedObject.IsValid()) {
        return FText::FromString("None");
    }
    return  FText::FromString(selectedObject.Get()->name.ToString());
}

TSharedRef<SWidget> FFlowNode_GameDataContextSelectorDetails::GetDefaultPropertyViewWidget() const {
    const auto nameProp = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataContextKey, name));
    const auto defaultValueProp = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataContextKey, value));
    const auto guidProp = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGameDataContextKey, guid));
    void* rawValue = nullptr;
    guidProp.Get()->GetValueData(rawValue);
    FText txt;
    if (rawValue) {
        txt = FText::FromString(static_cast<FGuid*>(rawValue)->ToString());
    }
    else {
        txt = FText::FromString("No GUID");
    }
    FName name;
    nameProp.Get()->GetValue(name);
    auto nameWidget = SNew(SEditableTextBox).Text(FText::FromName(name)).OnTextCommitted(this, &FFlowNode_GameDataContextSelectorDetails::OnDataKeyNameChanged);

    return SNew(SWrapBox)

        .UseAllottedWidth(true)
        + SWrapBox::Slot()
        .Padding(5.f, 0.f)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                nameProp->CreatePropertyNameWidget()
            ]
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                nameWidget
            ]
        ]
        + SWrapBox::Slot()
        .Padding(5.f, 0.f)
        [
            SNew(SBox)
            .MinDesiredWidth(70.f)
            [
                SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    defaultValueProp->CreatePropertyNameWidget()
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    defaultValueProp->CreatePropertyValueWidget()
                ]
            ]
            // ]
        ]
        + SWrapBox::Slot()
        .Padding(5.f, 0.f)
        [
            SNew(SBox)
            .MinDesiredWidth(70.f)
            [
                SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    guidProp->CreatePropertyNameWidget()
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(STextBlock).Text(txt)
                ]
            ]
            // ]
        ];
}
