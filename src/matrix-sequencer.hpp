#ifndef MATRIX_SEQUNCER
#define MATRIX_SEQUNCER

#include "plugin.hpp"
#include "sequence_algorithms.hpp"

struct Matrix_sequencer : Module {
	enum ParamId {
		X1_Y1_KNOB_PARAM,
		X2_Y1_KNOB_PARAM,
		X3_Y1_KNOB_PARAM,
		X4_Y1_KNOB_PARAM,
		X1_Y2_KNOB_PARAM,
		X2_Y2_KNOB_PARAM,
		X3_Y2_KNOB_PARAM,
		X4_Y2_KNOB_PARAM,
		X1_Y3_KNOB_PARAM,
		X2_Y3_KNOB_PARAM,
		X3_Y3_KNOB_PARAM,
		X4_Y3_KNOB_PARAM,
		X1_Y4_KNOB_PARAM,
		X2_Y4_KNOB_PARAM,
		X3_Y4_KNOB_PARAM,
		X4_Y4_KNOB_PARAM,
		ALGORITHM_KNOB_PARAM,
		PARAMS_LEN
	};

	enum InputId {
		CLOCK_IN_INPUT,
		RUN_IN_INPUT,
		RESET_IN_INPUT,
		ALGORITHM_FM_INPUT,
		INPUTS_LEN
	};

	enum OutputId {
		Y1_OUT_OUTPUT,
		Y2_OUT_OUTPUT,
		Y3_OUT_OUTPUT,
		Y4_OUT_OUTPUT,
		X1_OUT_OUTPUT,
		X2_OUT_OUTPUT,
		X3_OUT_OUTPUT,
		X4_OUT_OUTPUT,
		TOTAL_PITCH_OUT_OUTPUT,
		OUTPUTS_LEN
	};
	
    enum LightId {
		X1_Y1_LIGHT_LIGHT,
		X2_Y1_LIGHT_LIGHT,
		X3_Y1_LIGHT_LIGHT,
		X4_Y1_LIGHT_LIGHT,
		X1_Y2_LIGHT_LIGHT,
		X2_Y2_LIGHT_LIGHT,
		X3_Y2_LIGHT_LIGHT,
		X4_Y2_LIGHT_LIGHT,
		X1_Y3_LIGHT_LIGHT,
		X2_Y3_LIGHT_LIGHT,
		X3_Y3_LIGHT_LIGHT,
		X4_Y3_LIGHT_LIGHT,
		X1_Y4_LIGHT_LIGHT,
		X2_Y4_LIGHT_LIGHT,
		X3_Y4_LIGHT_LIGHT,
		X4_Y4_LIGHT_LIGHT,
		LIGHTS_LEN
	};

	Matrix_sequencer();

	~Matrix_sequencer();

    void process(const ProcessArgs& args) override;

private:
    inline uint8_t translateCoords();

private:
	bool _run;
    bool _reset;
	uint16_t _algorithm_type;
    sequence_t _current_step;
    dsp::SchmittTrigger clockTrigger;
	std::vector<SequenceAlgorithm_base*> _sequence_algorithms;
};

struct Matrix_sequencerWidget : ModuleWidget
{
	Matrix_sequencerWidget(Matrix_sequencer* module);
};

#endif