#ifndef DEPTH_SHADER_H
#define DEPTH_SHADER_H

#include "PhotonBox/components/Transform.h"
#include "PhotonBox/resources/Shader.h"
#include "PhotonBox/resources/Vertex.h"
#include "PhotonBox/components/Camera.h"
#include "PhotonBox/resources/Resources.h"

class DepthShader : public InstancedShader<DepthShader>
{
public:

	std::string getFilePath() override
	{
		return std::string(Resources::ENGINE_RESOURCES + "/shaders/util/depth");
	}

	void update(Transform* transform)
	{
		Matrix4f mvp = Camera::getMainCamera()->getViewProjection() * transform->getTransformationMatrix();
		glUniformMatrix4fv(uniforms["mvp"], 1, GL_FALSE, &(mvp(0, 0)));
	}

	void addUniforms() override
	{
		addUniform("mvp");

		addTexture("albedoMap");
	}

	void addAttributes() override
	{
		addAttribut("position", Vertex::AttibLocation::POSITION);
		addAttribut("uv", Vertex::AttibLocation::TEXTURECOORD);
	}
};

#endif // DEPTH_SHADER_H
