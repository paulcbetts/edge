#include "edge.h"

BOOL debugMode;
BOOL enableScriptIgnoreAttribute;

NAN_METHOD(initializeClrFunc)
{
    return ClrFunc::Initialize(info);
}

#pragma unmanaged
void init(Handle<Object> target) 
{
    debugMode = (0 < GetEnvironmentVariable("EDGE_DEBUG", NULL, 0));
    DBG("edge::init");
    V8SynchronizationContext::Initialize();
    enableScriptIgnoreAttribute = (0 < GetEnvironmentVariable("EDGE_ENABLE_SCRIPTIGNOREATTRIBUTE", NULL, 0));
    Nan::SetMethod(target, "initializeClrFunc", initializeClrFunc);
}

#pragma unmanaged
NODE_MODULE(edge, init);
