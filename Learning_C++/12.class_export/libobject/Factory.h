#pragma once

#include "IObject.h"

#ifdef __cplusplus
extern "C" {
#endif

IObject* GetInstance();

void ReleaseInstance(IObject*);

#ifdef __cplusplus
}
#endif