#ifndef CONTROLLER_TOGGLE_SCRIPT_CPP
#define CONTROLLER_TOGGLE_SCRIPT_CPP

#include <Components/Behaviour.h>

#ifdef MEM_DEBUG
#include "PhotonBox/util/MEMDebug.h"
#define new DEBUG_NEW
#endif

class ControllerToggleScript : public Behaviour
{
public:
	CameraControllerScript * cameraController;
	PathWalkerScript* pathWalkerScript;


	void Start()
	{
		cameraController = entity->getComponent<CameraControllerScript>();
		pathWalkerScript = entity->getComponent<PathWalkerScript>();

		cameraController->setEnable(false);
		pathWalkerScript->setEnable(true);
	}

	void Update()
	{
		if (InputManager::keyPressed(InputManager::KEY_BACKSPACE))
			switchState();
	}

	void switchState()
	{
		cameraController->setEnable(!cameraController->getEnable());
		pathWalkerScript->setEnable(!pathWalkerScript->getEnable());
	}
};

#endif // CONTROLLER_TOGGLE_SCRIPT_CPP