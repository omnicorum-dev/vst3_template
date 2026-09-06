#include "controller.h"
#include "plugin.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "public.sdk/source/vst/vstparameters.h"

using namespace Steinberg;

namespace |NAMESPACENAME| {

//------------------------------------------------------------------------
tresult PLUGIN_API |NAMESPACENAME|Controller::initialize(FUnknown *context) {
    tresult result = EditController::initialize(context);
    if (result != kResultOk)
        return result;

    // Normalized 0..1 parameter, default at unity gain (1.0), host-automatable.
    parameters.addParameter(STR16("Gain"), nullptr, 0, 1.0,
                            Vst::ParameterInfo::kCanAutomate, kGainId);

    return kResultOk;
}

} // namespace |NAMESPACENAME|
