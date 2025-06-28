//
//  Enum.h
//  XMacroDemo
//
//  Created by samli on 2025/6/12.
//

#include "Enum_Meta.h"

#define APP_TARGET_TYPE_LIST(X) \
X(FTAPPTargetTypeNN, 1) /* 这是一个注释，枚举代表牛牛 app */ \
X(FTAPPTargetTypeMM, 2) /* 这是一个注释，枚举代表moomoo app */ \
// LIST - END

ENUM_DEFINE_MACRO(FTAPPTargetType, APP_TARGET_TYPE_LIST, typeList)

//typedef enum FTAPPTargetType {
//    FTAPPTargetTypeNN = 1, FTAPPTargetTypeMM = 2,
//} FTAPPTargetType;
//static FTAPPTargetType typeList[] = {FTAPPTargetTypeNN, FTAPPTargetTypeMM,};
