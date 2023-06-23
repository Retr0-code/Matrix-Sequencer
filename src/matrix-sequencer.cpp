#include "matrix-sequencer.hpp"


Matrix_sequencer::Matrix_sequencer()
{
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
		configInput(CLOCK_IN_INPUT, "Clock");
		configInput(RUN_IN_INPUT, "Start sequence");
		configInput(RESET_IN_INPUT, "Reset sequence");
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

	_run = false;
	_reset = false;
	_current_step = X4_Y4_LIGHT_LIGHT;
}

void Matrix_sequencer::process(const ProcessArgs& args)
{
	if (inputs[RUN_IN_INPUT].getVoltage())
		_run = !_run;

	// Reset sequencer
	if (inputs[RESET_IN_INPUT].getVoltage())
	{
		lights[_current_step].setBrightness(0);
		_current_step = X4_Y4_LIGHT_LIGHT;
	}

	// Process trigger clock
	if (clockTrigger.process(inputs[CLOCK_IN_INPUT].getVoltage()))
	{
		// Turn off current light
		lights[_current_step].setBrightness(0);

		// Switch light
		_current_step++ ;
		_current_step %= LIGHTS_LEN;

		// Turn on new light
		lights[_current_step].setBrightness(1);
	}
}


Matrix_sequencerWidget::Matrix_sequencerWidget(Matrix_sequencer* module) {
	setModule(module);
	setPanel(createPanel(asset::plugin(pluginInstance, "res/matrix-sequencer.svg")));

	addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(35.56, 20.32)), module, Matrix_sequencer::X1_Y1_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(63.5, 20.32)), module, Matrix_sequencer::X2_Y1_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(91.44, 20.32)), module, Matrix_sequencer::X3_Y1_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(119.38, 20.32)), module, Matrix_sequencer::X4_Y1_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(35.56, 43.18)), module, Matrix_sequencer::X1_Y2_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(63.5, 43.18)), module, Matrix_sequencer::X2_Y2_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(91.44, 43.18)), module, Matrix_sequencer::X3_Y2_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(119.38, 43.18)), module, Matrix_sequencer::X4_Y2_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(35.56, 66.04)), module, Matrix_sequencer::X1_Y3_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(63.5, 66.04)), module, Matrix_sequencer::X2_Y3_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(91.44, 66.04)), module, Matrix_sequencer::X3_Y3_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(119.38, 66.04)), module, Matrix_sequencer::X4_Y3_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(35.56, 88.9)), module, Matrix_sequencer::X1_Y4_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(63.5, 88.9)), module, Matrix_sequencer::X2_Y4_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(91.44, 88.9)), module, Matrix_sequencer::X3_Y4_KNOB_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(119.38, 88.9)), module, Matrix_sequencer::X4_Y4_KNOB_PARAM));

	addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.7, 25.4)), module, Matrix_sequencer::CLOCK_IN_INPUT));
	addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.7, 43.18)), module, Matrix_sequencer::RUN_IN_INPUT));
	addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.7, 60.96)), module, Matrix_sequencer::RESET_IN_INPUT));

	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(137.16, 20.32)), module, Matrix_sequencer::Y1_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(137.16, 43.18)), module, Matrix_sequencer::Y2_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(137.16, 66.04)), module, Matrix_sequencer::Y3_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(137.16, 88.9)), module, Matrix_sequencer::Y4_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(35.56, 119.38)), module, Matrix_sequencer::X1_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(63.5, 119.38)), module, Matrix_sequencer::X2_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(91.44, 119.38)), module, Matrix_sequencer::X3_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(119.38, 119.38)), module, Matrix_sequencer::X4_OUT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(137.16, 119.38)), module, Matrix_sequencer::TOTAL_PITCH_OUT_OUTPUT));

	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(35.56, 31.75)), module, Matrix_sequencer::X1_Y1_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(63.5, 31.75)), module, Matrix_sequencer::X2_Y1_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(91.44, 31.75)), module, Matrix_sequencer::X3_Y1_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(119.38, 31.75)), module, Matrix_sequencer::X4_Y1_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(35.56, 54.61)), module, Matrix_sequencer::X1_Y2_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(63.5, 54.61)), module, Matrix_sequencer::X2_Y2_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(91.44, 54.61)), module, Matrix_sequencer::X3_Y2_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(119.38, 54.61)), module, Matrix_sequencer::X4_Y2_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(35.56, 77.47)), module, Matrix_sequencer::X1_Y3_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(63.5, 77.47)), module, Matrix_sequencer::X2_Y3_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(91.44, 77.47)), module, Matrix_sequencer::X3_Y3_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(119.38, 77.47)), module, Matrix_sequencer::X4_Y3_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(35.56, 100.33)), module, Matrix_sequencer::X1_Y4_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(63.5, 100.33)), module, Matrix_sequencer::X2_Y4_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(91.44, 100.33)), module, Matrix_sequencer::X3_Y4_LIGHT_LIGHT));
	addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(119.38, 100.33)), module, Matrix_sequencer::X4_Y4_LIGHT_LIGHT));
}



Model* modelMatrix_sequencer = createModel<Matrix_sequencer, Matrix_sequencerWidget>("matrix-sequencer");