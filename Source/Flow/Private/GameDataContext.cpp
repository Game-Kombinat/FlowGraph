#include "GameDataContext.h"

// Right now we don't need an explicit constructor
// UGameDataContext::UGameDataContext() {
//     data = NewObject<UBlackboardData>();
// }

bool UGameDataContext::GetTruthyness(const FGameDataContextKey key) {
    FGameDataContextKey out;
    if (FindEntry(key, out)) {
        return out.value > 0;
    }
    return false;
}

int32 UGameDataContext::GetValue(const FGameDataContextKey key) {
    FGameDataContextKey out;
    if (FindEntry(key, out)) {
        return out.value;
    }
    return -1;
}

void UGameDataContext::SetValue(const FGameDataContextKey key) {
    const int32 idx = GetIndex(key);
    if (idx != INDEX_NONE) {
        data[idx] = key;
    }
}

TArray<FGameDataContextKey> UGameDataContext::GetKeyList() {
    if (!keyListGenerated) {
        keyListGenerated = true;
        TArray<FGameDataContextKey> keys;
        if (parent) {
            keys.Append(parent->GetKeyList());
        }
        consolidatedKeyList.Empty();
        consolidatedKeyList.Append(keys);
        consolidatedKeyList.Append(data);
    }
    return consolidatedKeyList;
}

void UGameDataContext::InvalidateKeyCache() {
    if (parent) {
        parent->InvalidateKeyCache();
    }
    keyListGenerated = false;
    consolidatedKeyList.Empty();
}

bool UGameDataContext::FindEntry(const FGameDataContextKey key, FGameDataContextKey& out) {
    // data->
    const int32 idx = data.IndexOfByKey(key);
    if (idx != INDEX_NONE) {
        out = data[idx];
        return true;
    }
    return false;
}

int32 UGameDataContext::GetIndex(const FGameDataContextKey key) const {
    return data.IndexOfByKey(key);
}