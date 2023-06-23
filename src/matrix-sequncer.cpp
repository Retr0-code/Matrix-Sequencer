#include "plugin.hpp"


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
		PARAMS_LEN
	};
	enum InputId {
		PATH5098_INPUT,
		RUN_IN_INPUT,
		RESET_IN_INPUT,
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

	Matrix_sequencer() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(X1_Y1_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X2_Y1_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X3_Y1_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X4_Y1_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X1_Y2_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X2_Y2_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X3_Y2_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X4_Y2_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X1_Y3_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X2_Y3_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X3_Y3_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X4_Y3_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X1_Y4_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X2_Y4_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X3_Y4_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(X4_Y4_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configInput(PATH5098_INPUT, "");
		configInput(RUN_IN_INPUT, "");
		configInput(RESET_IN_INPUT, "");
		configOutput(Y1_OUT_OUTPUT, "");
		configOutput(Y2_OUT_OUTPUT, "");
		configOutput(Y3_OUT_OUTPUT, "");
		configOutput(Y4_OUT_OUTPUT, "");
		configOutput(X1_OUT_OUTPUT, "");
		configOutput(X2_OUT_OUTPUT, "");
		configOutput(X3_OUT_OUTPUT, "");
		configOutput(X4_OUT_OUTPUT, "");
		configOutput(TOTAL_PITCH_OUT_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct Matrix_sequencerWidget : ModuleWidget {
	Matrix_sequencerWidget(Matrix_sequencer* module) {
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

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.7, 25.4)), module, Matrix_sequencer::PATH5098_INPUT));
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

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(35.56, 31.75)), module, Matrix_sequencer::X1_Y1_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(63.5, 31.75)), module, Matrix_sequencer::X2_Y1_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(91.44, 31.75)), module, Matrix_sequencer::X3_Y1_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(119.38, 31.75)), module, Matrix_sequencer::X4_Y1_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(35.56, 54.61)), module, Matrix_sequencer::X1_Y2_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(63.5, 54.61)), module, Matrix_sequencer::X2_Y2_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(91.44, 54.61)), module, Matrix_sequencer::X3_Y2_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(119.38, 54.61)), module, Matrix_sequencer::X4_Y2_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(35.56, 77.47)), module, Matrix_sequencer::X1_Y3_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(63.5, 77.47)), module, Matrix_sequencer::X2_Y3_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(91.44, 77.47)), module, Matrix_sequencer::X3_Y3_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(119.38, 77.47)), module, Matrix_sequencer::X4_Y3_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(35.56, 100.33)), module, Matrix_sequencer::X1_Y4_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(63.5, 100.33)), module, Matrix_sequencer::X2_Y4_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(91.44, 100.33)), module, Matrix_sequencer::X3_Y4_LIGHT_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(119.38, 100.33)), module, Matrix_sequencer::X4_Y4_LIGHT_LIGHT));
	}
};


Model* modelMatrix_sequencer = createModel<Matrix_sequencer, Matrix_sequencerWidget>("matrix-sequencer");