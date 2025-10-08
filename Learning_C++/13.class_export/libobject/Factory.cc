#include "Factory.h"
#include "Object.h"

IObject* GetInstance() { return new Object(); }

void ReleaseInstance(IObject* instance) { delete instance; }