#include "PhotonBox/core/systems/Lighting.h"

#include "PhotonBox/components/LightProbe.h"
#include "PhotonBox/components/Transform.h"

#ifdef MEM_DEBUG
#include "PhotonBox/util/MEMDebug.h"
#define new DEBUG_NEW
#endif

std::unordered_map<std::type_index, std::vector<LightEmitter*>> Lighting::_lights;
std::vector<LightProbe*> Lighting::_lightProbes;

void Lighting::start()
{
	for (std::vector<LightProbe*>::iterator it = _lightProbes.begin(); it != _lightProbes.end(); ++it)
	{
		(*it)->bounds.setTransform((*it)->transform);
		(*it)->capture();
		//(*it)->generateLightMap();
	}
}

void Lighting::addLightProbe(LightProbe * lightProbe)
{
	_lightProbes.push_back(lightProbe);
}

void Lighting::removeFromLightProbeList(LightProbe * lightProbe)
{
	_lightProbes.erase(std::remove(_lightProbes.begin(), _lightProbes.end(), lightProbe), _lightProbes.end());
}

LightProbe * Lighting::findInLightProberVolume(Transform * transform)
{
	if (_lightProbes.size() < 1) return nullptr;

	for (std::vector<LightProbe*>::iterator it = _lightProbes.begin(); it != _lightProbes.end(); ++it)
	{
		if ((*it)->bounds.collide(transform->getPositionWorld()))
		{
			return (*it);
		}
	}

	return nullptr;
}
