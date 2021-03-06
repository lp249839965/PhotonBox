#ifndef SKY_BOX_SHADER_H
#define SKY_BOX_SHADER_H

#include "PhotonBox/resources/Shader.h"
#include "PhotonBox/resources/Resources.h"

class SkyBoxShader : public InstancedShader<SkyBoxShader>
{
public:
	std::string getFilePath() override
	{
		return std::string(Resources::ENGINE_RESOURCES + "/shaders/util/skyBox");
	}

	void update(Matrix4f& vp)
	{
		glUniformMatrix4fv(uniforms["vp"], 1, GL_FALSE, &(vp(0, 0)));
	}

	void addUniforms() override
	{
		addUniform("vp");
		addUniform("mip");
		addUniform("intensity");
	}

	void addAttributes() override
	{
		addAttribut("position", Vertex::AttibLocation::POSITION);
	}
};

#endif // SKY_BOX_SHADER_H
