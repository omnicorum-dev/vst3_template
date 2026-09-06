#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace |NAMESPACENAME| {

    //------------------------------------------------------------------------
    // Unique class identifiers for the processor and controller.
    // Generated once for this plug-in; must never change once the plug-in
    // ships.
    static const Steinberg::FUID k|NAMESPACENAME|ProcessorUID(|PROCESSORUID|);

    static const Steinberg::FUID k|NAMESPACENAME|ControllerUID(|CONTROLLERUID|);

    //------------------------------------------------------------------------
    enum ParamIds : Steinberg::Vst::ParamID { kGainId = 0 };

} // namespace |NAMESPACENAME|
