#include "plugin.h"
#include "controller.h"
#include "processor.h"

#include "public.sdk/source/main/pluginfactory.h"

#define stringPluginName "|PLUGINNAME|"

using namespace Steinberg::Vst;
using namespace |NAMESPACENAME|;

//------------------------------------------------------------------------
BEGIN_FACTORY_DEF("|COMPANYNAME|", "|COMPANYWEBSITE|", "|COMPANYEMAIL|")

DEF_CLASS2(INLINE_UID_FROM_FUID(k|NAMESPACENAME|ProcessorUID),
           PClassInfo::kManyInstances, kVstAudioEffectClass, stringPluginName,
           0, "Fx", "1.0.0", kVstVersionString,
           |NAMESPACENAME|Processor::createInstance)

DEF_CLASS2(INLINE_UID_FROM_FUID(k|NAMESPACENAME|ControllerUID),
           PClassInfo::kManyInstances, kVstComponentControllerClass,
           stringPluginName "Controller", 0, "", "1.0.0", kVstVersionString,
           |NAMESPACENAME|Controller::createInstance)

END_FACTORY
