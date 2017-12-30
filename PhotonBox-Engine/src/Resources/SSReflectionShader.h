#ifndef SSREFLECTION_SHADER_H
#define SSREFLECTION_SHADER_H

#include "../Resources/Shader.h"
#include "../Resources/Vertex.h"
#include "../Components/Camera.h"

class SSReflectionShader : public InstancedShader<SSReflectionShader> {
public:
	std::string getFilePath() override {
		return std::string("./res/post-processing/ssReflection");
	}

	void update(Transform* transform) override {
		glUniformMatrix4fv(uniforms["projection"], 1, GL_FALSE, &(Camera::getMainCamera()->getProjectionMatrix()(0, 0)));
	}

	void addUniforms() override {
		addUniform("projection");

		addTexture("gFinalImage");
		addTexture("gPosition");
		addTexture("gNormal");
		addTexture("gExtraComponents");
		addTexture("ColorBuffer");
	}

	void addAttributes() override {
		addAttribut("position", Vertex::AttibLocation::POSITION);
	}
};

#endif // SSREFLECTION_SHADER_H