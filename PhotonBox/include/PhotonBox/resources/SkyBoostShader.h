#ifndef SKY_BOOST_SHADER_H
#define SKY_BOOST_SHADER_H

#include "PhotonBox/components/Camera.h"
#include "PhotonBox/resources/Shader.h"
#include "PhotonBox/resources/Vertex.h"

class SkyBoostShader : public InstancedShader<SkyBoostShader>
{
public:
	std::string getFilePath() override
	{
		return std::string(Resources::ENGINE_RESOURCES + "/shaders/util/skyBoost");
	}

	void update(Transform* transform)
	{
		Matrix4f mvp = Camera::getMainCamera()->getViewProjection() * transform->getTransformationMatrix();

		glUniformMatrix4fv(uniforms["mvp"], 1, GL_FALSE, &(mvp(0, 0)));
	}

	void addUniforms() override
	{
		addUniform("mvp");
		addUniform("boost");
		addTexture("albedoMap");
	}

	void addAttributes() override
	{
		addAttribut("position", Vertex::AttibLocation::POSITION);
		addAttribut("normal", Vertex::AttibLocation::NORMAL);
		addAttribut("uv", Vertex::AttibLocation::TEXTURECOORD);
	}
};

#endif // SKY_BOOST_SHADER_H
