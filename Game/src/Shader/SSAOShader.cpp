#ifndef SSAO_SHADER_CPP
#define SSAO_SHADER_CPP

#include <Components/Camera.h>
#include <Resources/Shader.h>

#ifdef MEM_DEBUG
#include "PhotonBox/util/MEMDebug.h"
#define new DEBUG_NEW
#endif

class SSAOShader : public InstancedShader<SSAOShader>
{
public:
	std::string getFilePath() override
	{
		return std::string("./res/shaders/post-processing/ssao");
	}

	void update(Transform* transform) override
	{
		glUniform1f(uniforms["screenWidth"], GLfloat(Display::getWidth()));
		glUniform1f(uniforms["screenHeight"], GLfloat(Display::getHeight()));
		glUniformMatrix4fv(uniforms["projection"], 1, GL_FALSE, &(Camera::getMainCamera()->getProjectionMatrix()(0, 0)));
	}

	void addUniforms() override
	{
		addUniform("projection");
		addUniform("screenWidth");
		addUniform("screenHeight");

		for (size_t i = 0; i < 64; i++)
		{
			addUniform("samples[" + std::to_string(i) + "]");
		}

		addTexture("gPosition");
		addTexture("gNormal");
		addTexture("texNoise");
	}

	void addAttributes() override
	{
		addAttribut("position", Vertex::AttibLocation::POSITION);
	}
};

#endif // SSAO_SHADER_CPP