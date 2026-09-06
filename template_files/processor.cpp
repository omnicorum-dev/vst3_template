#include "processor.h"
#include "plugin.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/vsttypes.h"

using namespace Steinberg;

namespace |NAMESPACENAME| {

//------------------------------------------------------------------------
|NAMESPACENAME|Processor::|NAMESPACENAME|Processor() { setControllerClass(k|NAMESPACENAME|ControllerUID); }

//------------------------------------------------------------------------
tresult PLUGIN_API |NAMESPACENAME|Processor::initialize(FUnknown *context) {
    tresult result = AudioEffect::initialize(context);
    if (result != kResultOk)
        return result;

    addAudioInput(STR16("Stereo In"), Vst::SpeakerArr::kStereo);
    addAudioOutput(STR16("Stereo Out"), Vst::SpeakerArr::kStereo);

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API |NAMESPACENAME|Processor::setBusArrangements(
    Vst::SpeakerArrangement *inputs, int32 numIns,
    Vst::SpeakerArrangement *outputs, int32 numOuts) {

    // Only support matching mono or stereo in/out
    if (numIns == 1 && numOuts == 1 && inputs[0] == outputs[0])
        return AudioEffect::setBusArrangements(inputs, numIns, outputs,
                                               numOuts);
    return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API |NAMESPACENAME|Processor::process(Vst::ProcessData &data) {
    // 1) Pull the latest gain value out of any incoming parameter automation.
    if (data.inputParameterChanges) {

        int32 numParamsChanged =
            data.inputParameterChanges->getParameterCount();

        for (int32 i = 0; i < numParamsChanged; i++) {

            Vst::IParamValueQueue *paramQueue =
                data.inputParameterChanges->getParameterData(i);

            if (paramQueue && paramQueue->getParameterId() == kGainId) {

                int32 numPoints = paramQueue->getPointCount();
                Vst::ParamValue value;
                int32 sampleOffset;

                if (numPoints > 0 &&
                    paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==
                        kResultTrue) {

                    gain = (float)value;
                }
            }
        }
    }

    // 2) Nothing to do if there's no audio this block.
    if (data.numSamples <= 0 || data.numInputs == 0 || data.numOutputs == 0)
        return kResultOk;

    // 3) Apply gain, channel by channel, sample by sample.
    for (int32 ch = 0; ch < data.inputs[0].numChannels; ch++) {
        float *in = data.inputs[0].channelBuffers32[ch];
        float *out = data.outputs[0].channelBuffers32[ch];
        for (int32 s = 0; s < data.numSamples; s++) {
            out[s] = in[s] * gain;
        }
    }

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API |NAMESPACENAME|Processor::setState(IBStream *state) {
    if (!state)
        return kResultFalse;

    IBStreamer streamer(state, kLittleEndian);
    float savedGain = 1.f;
    if (!streamer.readFloat(savedGain))
        return kResultFalse;

    gain = savedGain;
    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API |NAMESPACENAME|Processor::getState(IBStream *state) {
    IBStreamer streamer(state, kLittleEndian);
    streamer.writeFloat(gain);
    return kResultOk;
}

} // namespace |NAMESPACENAME|
