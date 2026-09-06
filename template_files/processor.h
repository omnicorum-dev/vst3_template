#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

namespace |NAMESPACENAME| {

//------------------------------------------------------------------------
class |NAMESPACENAME|Processor : public Steinberg::Vst::AudioEffect {
  public:
    |NAMESPACENAME|Processor();

    static Steinberg::FUnknown *createInstance(void * /*context*/) {
        return (Steinberg::Vst::IAudioProcessor *)new |NAMESPACENAME|Processor;
    }

    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown *context)
        SMTG_OVERRIDE;

    Steinberg::tresult PLUGIN_API setBusArrangements(
        Steinberg::Vst::SpeakerArrangement *inputs, Steinberg::int32 numIns,
        Steinberg::Vst::SpeakerArrangement *outputs,
        Steinberg::int32 numOuts) SMTG_OVERRIDE;

    Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData &data)
        SMTG_OVERRIDE;

    Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream *state)
        SMTG_OVERRIDE;

    Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream *state)
        SMTG_OVERRIDE;

  protected:
    // Normalized gain value (0..1), applied directly as a linear multiplier.
    // 1.0 = unity (0 dB), 0.0 = silence.
    float gain = 1.f;
};

} // namespace |NAMESPACENAME|
