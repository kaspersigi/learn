#pragma once

#include "IObject.h"

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((visibility("default"))) IObject* GetInstance();

__attribute__((visibility("default"))) void ReleaseInstance(IObject*);

#ifdef __cplusplus
}
#endif