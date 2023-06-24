#include "matrix-sequencer.hpp"


Matrix_sequencer::Matrix_sequencer() : _current_step(0, 0, 0), _run(true), _reset(false)
{
	_sequence_algorithms = {
		new StraightSequence(),
		new LeftRight_UpDown(),
		new SpiralSequence()
	};

	{
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(X1_Y1_KNOB_PARAM, -10.f, 10.f, 0.f, "(1; 1)", "V");
		configParam(X2_Y1_KNOB_PARAM, -10.f, 10.f, 0.f, "(2; 1)", "V");
		configParam(X3_Y1_KNOB_PARAM, -10.f, 10.f, 0.f, "(3; 1)", "V");
		configParam(X4_Y1_KNOB_PARAM, -10.f, 10.f, 0.f, "(4; 1)", "V");
		configParam(X1_Y2_KNOB_PARAM, -10.f, 10.f, 0.f, "(1; 2)", "V");
		configParam(X2_Y2_KNOB_PARAM, -10.f, 10.f, 0.f, "(2; 2)", "V");
		configParam(X3_Y2_KNOB_PARAM, -10.f, 10.f, 0.f, "(3; 2)", "V");
		configParam(X4_Y2_KNOB_PARAM, -10.f, 10.f, 0.f, "(4; 2)", "V");
		configParam(X1_Y3_KNOB_PARAM, -10.f, 10.f, 0.f, "(1; 3)", "V");
		configParam(X2_Y3_KNOB_PARAM, -10.f, 10.f, 0.f, "(2; 3)", "V");
		configParam(X3_Y3_KNOB_PARAM, -10.f, 10.f, 0.f, "(3; 3)", "V");
		configParam(X4_Y3_KNOB_PARAM, -10.f, 10.f, 0.f, "(4; 3)", "V");
		configParam(X1_Y4_KNOB_PARAM, -10.f, 10.f, 0.f, "(1; 4)", "V");
		configParam(X2_Y4_KNOB_PARAM, -10.f, 10.f, 0.f, "(2; 4)", "V");
		configParam(X3_Y4_KNOB_PARAM, -10.f, 10.f, 0.f, "(3; 4)", "V");
		configParam(X4_Y4_KNOB_PARAM, -10.f, 10.f, 0.f, "(4; 4)", "V");
		configParam(ALGORITHM_KNOB_PARAM, 0.f, _sequence_algorithms.size() - 1, 0.f, "Algorithm");
		configInput(CLOCK_IN_INPUT, "Clock");
		configInput(RUN_IN_INPUT, "Start sequence");
		configInput(RESET_IN_INPUT, "Reset sequence");
		configInput(ALGORITHM_FM_INPUT, "Control algorithms");
		configOutput(Y1_OUT_OUTPUT, "Out Y:1");
		configOutput(Y2_OUT_OUTPUT, "Out Y:2");
		configOutput(Y3_OUT_OUTPUT, "Out Y:3");
		configOutput(Y4_OUT_OUTPUT, "Out Y:4");
		configOutput(X1_OUT_OUTPUT, "Out X:1");
		configOutput(X2_OUT_OUTPUT, "Out X:2");
		configOutput(X3_OUT_OUTPUT, "Out X:3");
		configOutput(X4_OUT_OUTPUT, "Out X:4");
		configOutput(TOTAL_PITCH_OUT_OUTPUT, "Sequence output");
	}

	paramQuantities[ALGORITHM_KNOB_PARAM]->snapEnabled = true;
	_algorithm_type = params[ALGORITHM_KNOB_PARAM].getValue();
}


Matrix_sequencer::~Matrix_sequencer()
{
	for (auto alg_ptr : _sequence_algorithms)
		delete alg_ptr;
}


void Matrix_sequencer::process(const ProcessArgs& args)
{
	// Stop / Run control
	if (!_run)
		for (auto& out : outputs)
			out.setVoltage(0);


	// Reset sequencer
	if (inputs[RESET_IN_INPUT].getVoltage())
	{
		lights[translateCoords()].setBrightness(0);
		_current_step = {0, 0, 0};
	}

	_algorithm_type = params[ALGORITHM_KNOB_PARAM].getValue();
	if (inputs[ALGORITHM_FM_INPUT].isConnected())
	{
		_algorithm_type = std::ceil(inputs[ALGORITHM_FM_INPUT].getVoltage());

		if (_algorithm_type >= _sequence_algorithms.size())
			_algorithm_type = _sequence_algorithms.size() - 1;

		if (_algorithm_type < 0)
			_algorithm_type = 0;
	}

	// Process trigger clock
	if (clockTrigger.process(inputs[CLOCK_IN_INPUT].getVoltage()))
	{
		// Turn off current light
		lights[translateCoords()].setBrightness(0);

		//------------ Current Step = chosen callback algorithm ------------//
		_sequence_algorithms.at(_algorithm_type)->callback(_current_step);
		float param_voltage = params[translateCoords()].getValue();
		
		outputs[_current_step.y].setVoltage(param_voltage);
		outputs[_current_step.x + 3].setVoltage(param_voltage);
		outputs[TOTAL_PITCH_OUT_OUTPUT].setVoltage(param_voltage);

		// Turn on new light
		lights[translateCoords()].setBrightness(1);
	}
}


inline uint8_t Matrix_sequencer::translateCoords()
{
	return _current_step.x + (_current_step.y << 2);
}


Matrix_sequencerWidget::Matrix_sequencerWidget(Matrix_sequencer* module)
{
	setModule(module);
	setPanel(createPanel(asset::plugin(pluginInstance, "res/matrix-sequencer.svg")));

	addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.18, 20.32)), module, Matrix_sequencer::X1_Y1_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(71.12, 20.32)), module, Matrix_sequencer::X2_Y1_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(99.06, 20.32)), module, Matrix_sequencer::X3_Y1_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(127.0, 20.32)), module, Matrix_sequencer::X4_Y1_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.18, 43.18)), module, Matrix_sequencer::X1_Y2_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(71.12, 43.18)), module, Matrix_sequencer::X2_Y2_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(99.06, 43.18)), module, Matrix_sequencer::X3_Y2_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(127.0, 43.18)), module, Matrix_sequencer::X4_Y2_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.18, 66.04)), module, Matrix_sequencer::X1_Y3_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(71.12, 66.04)), module, Matrix_sequencer::X2_Y3_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(99.06, 66.04)), module, Matrix_sequencer::X3_Y3_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(127.0, 66.04)), module, Matrix_sequencer::X4_Y3_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.18, 88.9)), module, Matrix_sequencer::X1_Y4_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(71.12, 88.9)), module, Matrix_sequencer::X2_Y4_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(99.06, 88.9)), module, Matrix_sequencer::X3_Y4_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(127.0, 88.9)), module, Matrix_sequencer::X4_Y4_KNOB_PARAM));

	addParam(createParamCentered<RoundHugeBlackKnob>(mm2px(Vec(20.32, 88.9)), module, Matrix_sequencer::ALGORITHM_KNOB_PARAM));

	addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.32, 25.4)), module, Matrix_sequencer::CLOCK_IN_INPUT));
	addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.32, 43.18)), module, Matrix_sequencer::RUN_IN_INPUT));
	addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.32, 60.96)), module, Matrix_sequencer::RESET_IN_INPUT));
	addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.32, 73.66)), module, Matrix_sequencer::ALGORITHM_FM_INPUT));

	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(144.78, 20.32)), module, Matrix_sequencer::Y1_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(144.78, 43.18)), module, Matrix_sequencer::Y2_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(144.78, 66.04)), module, Matrix_sequencer::Y3_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(144.78, 88.9)), module, Matrix_sequencer::Y4_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(43.18, 119.38)), module, Matrix_sequencer::X1_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(71.12, 119.38)), module, Matrix_sequencer::X2_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(99.06, 119.38)), module, Matrix_sequencer::X3_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(127.0, 119.38)), module, Matrix_sequencer::X4_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(144.78, 119.38)), module, Matrix_sequencer::TOTAL_PITCH_OUT_OUTPUT));

	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(43.18, 31.75)), module, Matrix_sequencer::X1_Y1_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(71.12, 31.75)), module, Matrix_sequencer::X2_Y1_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(99.06, 31.75)), module, Matrix_sequencer::X3_Y1_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(127.0, 31.75)), module, Matrix_sequencer::X4_Y1_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(43.18, 54.61)), module, Matrix_sequencer::X1_Y2_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(71.12, 54.61)), module, Matrix_sequencer::X2_Y2_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(99.06, 54.61)), module, Matrix_sequencer::X3_Y2_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(127.0, 54.61)), module, Matrix_sequencer::X4_Y2_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(43.18, 77.47)), module, Matrix_sequencer::X1_Y3_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(71.12, 77.47)), module, Matrix_sequencer::X2_Y3_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(99.06, 77.47)), module, Matrix_sequencer::X3_Y3_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(127.0, 77.47)), module, Matrix_sequencer::X4_Y3_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(43.18, 100.33)), module, Matrix_sequencer::X1_Y4_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(71.12, 100.33)), module, Matrix_sequencer::X2_Y4_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(99.06, 100.33)), module, Matrix_sequencer::X3_Y4_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(127.0, 100.33)), module, Matrix_sequencer::X4_Y4_LIGHT_LIGHT));
}


Model* modelMatrix_sequencer = createModel<Matrix_sequencer, Matrix_sequencerWidget>("matrix-sequencer");