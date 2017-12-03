#ifndef AUTO_EXPOSURE_SHADER_H
#define AUTO_EXPOSURE_SHADER_H

#include "Shader.h"
#include "Vertex.h"

class AutoExposureShader : public InstancedShader<AutoExposureShader> {
public:
	std::string getFilePath() override {
		return std::string("./res/post-processing/autoexposure");
	}

	void update(Transform* t) override {
		glUniform1f(uniforms["delteTime"], Time::deltaTime);
	}

	void addUniforms() override {
		addUniform("maxMip");
		addUniform("delteTime");
		addUniform("adaptationSpeed");

		addTexture("luminanceSampleCurrent");
		addTexture("luminanceSampleLast");
	}

	void addAttributes() override {
		addAttribut("position", Vertex::AttibLocation::POSITION);
	}
};

#endif // AUTO_EXPOSURE_SHADER_H