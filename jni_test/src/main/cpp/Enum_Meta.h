//
//  Enum.h
//  XMacroDemo
//
//  Created by samli on 2025/6/12.
//

#define DECLEAR_ENUM_ITEM_WITH_VALUE(NAME, VALUE) NAME = VALUE,
#define USE_ENUM_ITEM(NAME, VALUE) NAME,

#define ENUM_DEFINE_MACRO(TYPE, LIST, ARR_NAME) \
typedef enum TYPE {\
LIST(DECLEAR_ENUM_ITEM_WITH_VALUE)\
} TYPE;\
static TYPE ARR_NAME[] = {\
LIST(USE_ENUM_ITEM)\
};\
// END
