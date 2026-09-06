#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"

namespace |NAMESPACENAME| {

//------------------------------------------------------------------------
class |NAMESPACENAME|Controller : public Steinberg::Vst::EditController {
  public:
    static Steinberg::FUnknown *createInstance(void * /*context*/) {
        return (Steinberg::Vst::IEditController *)new |NAMESPACENAME|Controller;
    }

    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown *context)
        SMTG_OVERRIDE;
};

} // namespace |NAMESPACENAME|
