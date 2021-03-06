#ifndef TEST_SCENE_CPP
#define TEST_SCENE_CPP

#include <Components/MeshRenderer.h>
#include <Components/TransparentMeshRenderer.h>
#include <Components/Camera.h>
#include <Components/SpotLight.h>
#include <Components/PointLight.h>
#include <Components/PointRenderer.h>
#include <Components/AmbientLight.h>
#include <Resources/OBJLoader.h>
#include <Resources/BasicShader.h>
#include <Resources/LitShader.h>
#include <Resources/Scene.h>
#include <Resources/IrradianceShader.h>
#include <Resources/Texture.h>
#include <Resources/TransparentShader.h>
#include <Resources/SkyBoostShader.h>
#include <components/LightProbe.h>

#include "../PostProcessors/SSAOProcessor.cpp"
#include "../PostProcessors/SSReflectionProcessor.cpp"
#include "../PostProcessors/AutoExposureProcessor.cpp"
#include "../PostProcessors/ToneMappingProcessor.cpp"
#include "../Scripts/MaterialScript.cpp"
#include "../PostProcessors/BloomProcessor.cpp"
#include "../PostProcessors/BlurProcessor.cpp"
#include "../Scripts/PrinterScript.cpp"
#include "../Scripts/TransformerScript.cpp"
#include "../Scripts/CameraControllerScript.cpp"
#include "../Scripts/StateControllerScript.cpp"
#include "../Scripts/PathWalkerScript.cpp"
#include "../Scripts/ControllerToggleScript.cpp"
#include "../Shader/BlurShader.cpp"

#ifdef MEM_DEBUG
#include "PhotonBox/util/MEMDebug.h"
#define new DEBUG_NEW
#endif

class TestScene : public Scene
{
public:

	void Load()
	{
		/* --------------------------- ENVIROMENT --------------------------- */
		std::vector<std::string> white = {
			Resources::ENGINE_RESOURCES + "/default_ao.png",
			Resources::ENGINE_RESOURCES + "/default_ao.png",
			Resources::ENGINE_RESOURCES + "/default_ao.png",
			Resources::ENGINE_RESOURCES + "/default_ao.png",
			Resources::ENGINE_RESOURCES + "/default_ao.png",
			Resources::ENGINE_RESOURCES + "/default_ao.png",
		};

		Renderer::setSkyBox(createResource<CubeMap>(white));
		//Renderer::setSkyBox(new CubeMap(white));
		Renderer::getSkyBox()->intensity = 10;


		/* --------------------------- POST PROCESSING --------------------------- */

		SSAOProcessor* p_ssao = new SSAOProcessor(0);
		SSReflectionProcessor* p_ssreflection = new SSReflectionProcessor(1);
		FXAAProcessor* p_fxaa = new FXAAProcessor(2);
		AutoExposureProcessor* p_autoExposure = new AutoExposureProcessor(3);
		BloomProcessor* p_bloom = new BloomProcessor(4);
		ToneMappingProcessor* p_tonemapping = new ToneMappingProcessor(5);


		/* --------------------------- OBJ --------------------------- */
		Mesh* sphere = createResource<Mesh>(Resources::ENGINE_RESOURCES + "/primitives/sphere.obj");
		Mesh* couchMesh = createResource<Mesh>("./res/Realistic-Rendering/Couch/couch.obj");
		Mesh* wallMesh = createResource<Mesh>("./res/Realistic-Rendering/Walls/Room.obj");
		Mesh* floorMesh = createResource<Mesh>("./res/Realistic-Rendering/Floor/Floor.obj");
		Mesh* doorsMesh = createResource<Mesh>("./res/Realistic-Rendering/Doors/Doors.obj");
		Mesh* tableMesh = createResource<Mesh>("./res/Realistic-Rendering/Table/Table.obj");
		Mesh* longCouchMesh = createResource<Mesh>("./res/Realistic-Rendering/Couch/Long_Couch.obj");
		Mesh* slidingDoorMesh = createResource<Mesh>("./res/Realistic-Rendering/SlidingDoor/SlideDoor.obj");
		Mesh* floorEdgeMesh = createResource<Mesh>("./res/Realistic-Rendering/FloorEdge/FloorEdge.obj");
		Mesh* shelveMesh = createResource<Mesh>("./res/Realistic-Rendering/Shelving/Shelving.obj");
		Mesh* carpetMesh = createResource<Mesh>("./res/Realistic-Rendering/Carpet/Carpet.obj");
		Mesh* carpetFloorMesh = createResource<Mesh>("./res/Realistic-Rendering/Carpet/CarpetFloor.obj");
		Mesh* occluderMesh = createResource<Mesh>("./res/Realistic-Rendering/Occluder/occluder.obj");
		Mesh* windowMesh = createResource<Mesh>("./res/Realistic-Rendering/Window/Window.obj");
		Mesh* panoramaMesh = createResource<Mesh>("./res/Realistic-Rendering/Panorama/Panorama.obj");
		Mesh* lampMesh = createResource<Mesh>("./res/Realistic-Rendering/Lamp/Lamp.obj");
		Mesh* ceilingLightMesh = createResource<Mesh>("./res/Realistic-Rendering/CeilingLight/CeilingLight.obj");
		Mesh* vaseMesh = createResource<Mesh>("./res/Realistic-Rendering/Vase/Vase.obj");
		Mesh* bookMesh1 = createResource<Mesh>("./res/Realistic-Rendering/Books/Books_1.obj");
		Mesh* bookMesh2 = createResource<Mesh>("./res/Realistic-Rendering/Books/Books_2.obj");
		Mesh* bookMesh3 = createResource<Mesh>("./res/Realistic-Rendering/Books/Books_3.obj");
		Mesh* bookMesh4 = createResource<Mesh>("./res/Realistic-Rendering/Books/Books_4.obj");
		Mesh* balconyFloorMesh = createResource<Mesh>("./res/Realistic-Rendering/BalconyFloor/Balcony_Floor.obj");
		Mesh* balconyRailingMesh = createResource<Mesh>("./res/Realistic-Rendering/Railing/Balcony_Railing.obj");
		Mesh* frameMesh = createResource<Mesh>("./res/Realistic-Rendering/Frame/Frame.obj");
		Mesh* frameGlassMesh = createResource<Mesh>("./res/Realistic-Rendering/Frame/GlassPane.obj");
		Mesh* painting1Mesh = createResource<Mesh>("./res/Realistic-Rendering/Frame/Painting1.obj");
		Mesh* painting2Mesh = createResource<Mesh>("./res/Realistic-Rendering/Frame/Painting2.obj");
		Mesh* painting3Mesh = createResource<Mesh>("./res/Realistic-Rendering/Frame/Painting3.obj");


		/* --------------------------- TEXTURES --------------------------- */
		Texture* woodAlbedo = createResource<Texture>(std::string("./res/materials/mahogfloor/mahogfloor_basecolor.png"), true);
		Texture* woodRough = createResource<Texture>(std::string("./res/materials/mahogfloor/mahogfloor_roughness.png"), true);
		Texture* woodNormal = createResource<Texture>(std::string("./res/materials/mahogfloor/mahogfloor_normal.png"), true);
		Texture* woodAo = createResource<Texture>(std::string("./res/materials/mahogfloor/mahogfloor_AO.png"), true);
		Texture* woodMetal = createResource<Texture>(std::string("./res/materials/mahogfloor/mahogfloor_metalness.png"), true);
		
		Texture* doorAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Doors/T_Door_D.tga"), true);
		Texture* doorRough = createResource<Texture>(std::string("./res/Realistic-Rendering/Doors/T_Door_R.tga"), true);
		Texture* doorNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Doors/T_Door_N.TGA"), true);
		Texture* doorAo = createResource<Texture>(std::string("./res/Realistic-Rendering/Doors/T_Door_AOMask.TGA"), true);
		Texture* doorMetal = createResource<Texture>(std::string("./res/Realistic-Rendering/Doors/T_Door_M.tga"), true);
		
		Texture* tableAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Table/T_Table_D.tga"), true);
		Texture* tableRough = createResource<Texture>(std::string("./res/Realistic-Rendering/Table/T_Table_R.tga"), true);
		Texture* tableNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Table/T_Table_N.TGA"), true);
		Texture* tableAo = createResource<Texture>(std::string("./res/Realistic-Rendering/Table/T_Table_AOMASK.TGA"), true);
		Texture* tableMetal = createResource<Texture>(std::string("./res/Realistic-Rendering/Table/T_Table_M.tga"), true);
		
		Texture* slidingDoorRough = createResource<Texture>(std::string("./res/Realistic-Rendering/SlidingDoor/T_SlidingDoor_R.tga"), true);
		Texture* slidingDoorNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/SlidingDoor/T_SlidingDoor_N.TGA"), true);
		Texture* slidingDoorAo = createResource<Texture>(std::string("./res/Realistic-Rendering/SlidingDoor/T_SlidingDoor_AOMask.TGA"), true);
		Texture* slidingDoorMetal = createResource<Texture>(std::string("./res/Realistic-Rendering/SlidingDoor/T_SlidingDoor_M.TGA"), true);
		
		Texture* shelveAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Shelving/T_Shelving_D.TGA"), true);
		Texture* shelveRough = createResource<Texture>(std::string("./res/Realistic-Rendering/Shelving/T_Shelving_R.TGA"), true);
		Texture* shelveNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Shelving/T_Shelving_N.TGA"), true);
		Texture* shelveAo = createResource<Texture>(std::string("./res/Realistic-Rendering/Shelving/T_Shelving_AO.TGA"), true);
		
		Texture* carpetAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Carpet/T_Carpet_D.png"), true);
		Texture* carpetNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Carpet/T_Carpet_N.TGA"), true);
		Texture* carpetAo = createResource<Texture>(std::string("./res/Realistic-Rendering/Carpet/T_Carpet_AO.TGA"), true);
		 
		Texture* lampAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Lamp/T_FloorLamp_Albedo.TGA"), true);
		Texture* lampRough = createResource<Texture>(std::string("./res/Realistic-Rendering/Lamp/T_FloorLamp_Roughness.TGA"), true);
		Texture* lampNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Lamp/T_FloorLamp_N.TGA"), true);
		Texture* lampAo = createResource<Texture>(std::string("./res/Realistic-Rendering/Lamp/T_FloorLamp_AO.TGA"), true);
		Texture* lampMetal = createResource<Texture>(std::string("./res/Realistic-Rendering/Lamp/T_FloorLamp_M.TGA"), true);
		
		Texture* ceilingAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/CeilingLight/T_RoundCeilingLight_Albedo.TGA"), true);
		Texture* ceilingRough = createResource<Texture>(std::string("./res/Realistic-Rendering/CeilingLight/T_RoundCeilingLight_Roughness.TGA"), true);
		Texture* ceilingNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/CeilingLight/T_RoundCeilingLight_N.TGA"), true);
		Texture* ceilingAo = createResource<Texture>(std::string("./res/Realistic-Rendering/CeilingLight/T_RoundCeilingLight_AO.TGA"), true);
		Texture* ceilingMetal = createResource<Texture>(std::string("./res/Realistic-Rendering/CeilingLight/T_RoundCeilingLight_M.TGA"), true);
		
		Texture* vaseAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Vase/Vase_Albedo.png"), true);
		Texture* vaseRough = createResource<Texture>(std::string("./res/Realistic-Rendering/Vase/Vase_Roughness.png"), true);
		
		Texture* frameAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Frame/T_Frame_Albedo.tga"), true);
		Texture* frameNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Frame/T_Frame_N.tga"), true);
		Texture* frameRoughness = createResource<Texture>(std::string("./res/Realistic-Rendering/Frame/T_Frame_Roughness.tga"), true);
		
		Texture* painting1D = createResource<Texture>(std::string("./res/Realistic-Rendering/Frame/T_Painting4_D.tga"), true);
		Texture* painting2D = createResource<Texture>(std::string("./res/Realistic-Rendering/Frame/T_Painting2_D.tga"), true);
		Texture* painting3D = createResource<Texture>(std::string("./res/Realistic-Rendering/Frame/T_Painting3_D.tga"), true);
		
		Texture* bookAo = createResource<Texture>(std::string("./res/Realistic-Rendering/Books/book_occlusion.tga"), true);
		Texture* bookNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Books/book_normals.tga"), true);
		Texture* bookAlbedo1 = createResource<Texture>(std::string("./res/Realistic-Rendering/Books/book_albedo_1.tga"), true);
		Texture* bookAlbedo2 = createResource<Texture>(std::string("./res/Realistic-Rendering/Books/book_albedo_2.tga"), true);
		Texture* bookAlbedo3 = createResource<Texture>(std::string("./res/Realistic-Rendering/Books/book_albedo_3.tga"), true);
		Texture* bookAlbedo4 = createResource<Texture>(std::string("./res/Realistic-Rendering/Books/book_albedo_4.tga"), true);
		
		Texture* balconyFloorAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/BalconyFloor/T_StoneMix_D.tga"), true);
		Texture* balconyFloorNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/BalconyFloor/T_StoneMix_N.tga"), true);
		Texture* balconyFloorRoughness = createResource<Texture>(std::string("./res/Realistic-Rendering/BalconyFloor/T_StoneMix_R.tga"), true);
		
		Texture* galvanizedAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Railing/T_Galvanized_D.tga"), true);
		Texture* galvanizedRough = createResource<Texture>(std::string("./res/Realistic-Rendering/Railing/T_Galvanized_Roughness.tga"), true);
		Texture* galvanizedNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Railing/T_Galvanized_N.tga"), true);
		Texture* railingAo = createResource<Texture>(std::string("./res/Realistic-Rendering/Railing/T_Railing_AOMASK.tga"), true);
		Texture* railingNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Railing/T_Railing_N.tga"), true);
		
		Texture* windowAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Window/albedo.png"), true);
		
		Texture* couchAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Couch/T_Couch_D.TGA"), true);
		Texture* couchNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Couch/T_Couch_N.TGA"), true);
		Texture* couchRoughness = createResource<Texture>(std::string("./res/Realistic-Rendering/Couch/T_Couch_R.tga"), true);
		Texture* couchAo = createResource<Texture>(std::string("./res/Realistic-Rendering/Couch/T_Couch_AO.TGA"), true);
		Texture* couchMetal = createResource<Texture>(std::string("./res/Realistic-Rendering/Couch/T_Couch_M.TGA"), true);
		
		Texture* wallNormal = createResource<Texture>(std::string("./res/Realistic-Rendering/Walls/T_PaintedWall_N.TGA"), true);
		
		Texture* default_normal = createResource<Texture>(std::string(Resources::ENGINE_RESOURCES + "/default_normal.png"), false);
		Texture* default_specular = createResource<Texture>(std::string(Resources::ENGINE_RESOURCES + "/default_specular.png"), false);
		Texture* default_emission = createResource<Texture>(std::string(Resources::ENGINE_RESOURCES + "/default_emission.png"), false);
		Texture* default_ao = createResource<Texture>(std::string(Resources::ENGINE_RESOURCES + "/default_ao.png"), false);
		Texture* default_roughness = createResource<Texture>(std::string(Resources::ENGINE_RESOURCES + "/default_roughness.png"), false);
		Texture* gradient = createResource<Texture>(std::string(Resources::ENGINE_RESOURCES + "/gradient.png"), false);
		
		Texture* panoramaAlbedo = createResource<Texture>(std::string("./res/Realistic-Rendering/Panorama/T_Background_D.TGA"), true);
		Texture* blinds = createResource<Texture>(std::string("./res/textures/blinds.png"), true);


		/* --------------------------- SHADERS --------------------------- */
		LitShader* litShader = LitShader::getInstance();
		TransparentShader* transparentShader = TransparentShader::getInstance();
		SkyBoostShader* skyBoost = SkyBoostShader::getInstance();
		GShader* defaultShader = GShader::getInstance();


		/* --------------------------- MATERIALS --------------------------- */

		Material* couchMaterial = createResource<Material>(defaultShader);
		couchMaterial->setTexture("albedoMap", couchAlbedo);
		couchMaterial->setTexture("normalMap", couchNormal);
		couchMaterial->setTexture("roughnessMap", couchRoughness);
		couchMaterial->setTexture("aoMap", couchAo);
		couchMaterial->setTexture("metallicMap", couchMetal);
		couchMaterial->setTexture("emissionMap", default_emission);

		Material* wallMaterial = createResource<Material>(defaultShader);
		wallMaterial->setTexture("albedoMap", default_ao);
		wallMaterial->setTexture("normalMap", wallNormal);
		wallMaterial->setTexture("roughnessMap", default_ao);
		wallMaterial->setTexture("aoMap", default_ao);
		wallMaterial->setTexture("metallicMap", default_emission);
		wallMaterial->setTexture("emissionMap", default_emission);

		Material* wood = createResource<Material>(defaultShader);
		wood->setTexture("albedoMap", woodAlbedo);
		wood->setTexture("normalMap", woodNormal);
		wood->setTexture("roughnessMap", woodRough);
		wood->setTexture("aoMap", woodAo);
		wood->setTexture("metallicMap", woodMetal);
		wood->setTexture("emissionMap", default_emission);

		Material* doorMaterial = createResource<Material>(defaultShader);
		doorMaterial->setTexture("albedoMap", doorAlbedo);
		doorMaterial->setTexture("normalMap", doorNormal);
		doorMaterial->setTexture("roughnessMap", doorRough);
		doorMaterial->setTexture("aoMap", doorAo);
		doorMaterial->setTexture("metallicMap", doorMetal);
		doorMaterial->setTexture("emissionMap", default_emission);

		Material* tableMaterial = createResource<Material>(defaultShader);
		tableMaterial->setTexture("albedoMap", tableAlbedo);
		tableMaterial->setTexture("normalMap", tableNormal);
		tableMaterial->setTexture("roughnessMap", tableRough);
		tableMaterial->setTexture("aoMap", tableAo);
		tableMaterial->setTexture("metallicMap", tableMetal);
		tableMaterial->setTexture("emissionMap", default_emission);

		Material* shelveMaterial = createResource<Material>(defaultShader);
		shelveMaterial->setTexture("albedoMap", shelveAlbedo);
		shelveMaterial->setTexture("normalMap", shelveNormal);
		shelveMaterial->setTexture("roughnessMap", shelveRough);
		shelveMaterial->setTexture("aoMap", shelveAo);
		shelveMaterial->setTexture("metallicMap", default_emission);
		shelveMaterial->setTexture("emissionMap", default_emission);

		Material* slidingDoorMaterial = createResource<Material>(defaultShader);
		slidingDoorMaterial->setTexture("albedoMap", default_ao);
		slidingDoorMaterial->setTexture("normalMap", slidingDoorNormal);
		slidingDoorMaterial->setTexture("roughnessMap", slidingDoorRough);
		slidingDoorMaterial->setTexture("aoMap", slidingDoorAo);
		slidingDoorMaterial->setTexture("metallicMap", slidingDoorMetal);
		slidingDoorMaterial->setTexture("emissionMap", default_emission);

		Material* carpetMaterial = createResource<Material>(defaultShader);
		carpetMaterial->setTexture("albedoMap", carpetAlbedo);
		carpetMaterial->setTexture("normalMap", default_normal);
		carpetMaterial->setTexture("roughnessMap", default_ao);
		carpetMaterial->setTexture("aoMap", carpetAo);
		carpetMaterial->setTexture("metallicMap", default_emission);
		carpetMaterial->setTexture("emissionMap", default_emission);

		Material* carpetFloorMaterial = createResource<Material>(defaultShader);
		carpetFloorMaterial->setTexture("albedoMap", carpetAlbedo);
		carpetFloorMaterial->setTexture("normalMap", default_normal);
		carpetFloorMaterial->setTexture("roughnessMap", default_ao);
		carpetFloorMaterial->setTexture("aoMap", carpetAo);
		carpetFloorMaterial->setTexture("metallicMap", default_emission);
		carpetFloorMaterial->setTexture("emissionMap", default_emission);

		Material* lampMaterial = createResource<Material>(defaultShader);
		lampMaterial->setTexture("albedoMap", lampAlbedo);
		lampMaterial->setTexture("normalMap", lampNormal);
		lampMaterial->setTexture("roughnessMap", lampRough);
		lampMaterial->setTexture("aoMap", lampAo);
		lampMaterial->setTexture("metallicMap", lampMetal);
		lampMaterial->setTexture("emissionMap", default_emission);

		Material* ceilingLightMaterial = createResource<Material>(defaultShader);
		ceilingLightMaterial->setTexture("albedoMap", ceilingAlbedo);
		ceilingLightMaterial->setTexture("normalMap", ceilingNormal);
		ceilingLightMaterial->setTexture("roughnessMap", ceilingRough);
		ceilingLightMaterial->setTexture("aoMap", ceilingAo);
		ceilingLightMaterial->setTexture("metallicMap", ceilingMetal);
		ceilingLightMaterial->setTexture("emissionMap", default_emission);

		Material* vaseMaterial = createResource<Material>(defaultShader);
		vaseMaterial->setTexture("albedoMap", vaseAlbedo);
		vaseMaterial->setTexture("normalMap", default_normal);
		vaseMaterial->setTexture("roughnessMap", vaseRough);
		vaseMaterial->setTexture("aoMap", default_ao);
		vaseMaterial->setTexture("metallicMap", default_emission);
		vaseMaterial->setTexture("emissionMap", default_emission);

		Material* frameMaterial = createResource<Material>(defaultShader);
		frameMaterial->setTexture("albedoMap", frameAlbedo);
		frameMaterial->setTexture("normalMap", frameNormal);
		frameMaterial->setTexture("roughnessMap", frameRoughness);
		frameMaterial->setTexture("aoMap", default_ao);
		frameMaterial->setTexture("metallicMap", default_emission);
		frameMaterial->setTexture("emissionMap", default_emission);

		Material* painting1Material = createResource<Material>(defaultShader);
		painting1Material->setTexture("albedoMap", painting1D);
		painting1Material->setTexture("normalMap", default_normal);
		painting1Material->setTexture("roughnessMap", default_ao);
		painting1Material->setTexture("aoMap", default_ao);
		painting1Material->setTexture("metallicMap", default_emission);
		painting1Material->setTexture("emissionMap", default_emission);
		Material* painting2Material = createResource<Material>(defaultShader);
		painting2Material->setTexture("albedoMap", painting2D);
		painting2Material->setTexture("normalMap", default_normal);
		painting2Material->setTexture("roughnessMap", default_ao);
		painting2Material->setTexture("aoMap", default_ao);
		painting2Material->setTexture("metallicMap", default_emission);
		painting2Material->setTexture("emissionMap", default_emission);
		Material* painting3Material = createResource<Material>(defaultShader);
		painting3Material->setTexture("albedoMap", painting3D);
		painting3Material->setTexture("normalMap", default_normal);
		painting3Material->setTexture("roughnessMap", default_ao);
		painting3Material->setTexture("aoMap", default_ao);
		painting3Material->setTexture("metallicMap", default_emission);
		painting3Material->setTexture("emissionMap", default_emission);


		Material* bookMaterial1 = createResource<Material>(defaultShader);
		bookMaterial1->setTexture("albedoMap", bookAlbedo1);
		bookMaterial1->setTexture("normalMap", bookNormal);
		bookMaterial1->setTexture("roughnessMap", default_ao);
		bookMaterial1->setTexture("aoMap", bookAo);
		bookMaterial1->setTexture("metallicMap", default_emission);
		bookMaterial1->setTexture("emissionMap", default_emission);
		Material* bookMaterial2 = createResource<Material>(defaultShader);
		bookMaterial2->setTexture("albedoMap", bookAlbedo2);
		bookMaterial2->setTexture("normalMap", bookNormal);
		bookMaterial2->setTexture("roughnessMap", default_ao);
		bookMaterial2->setTexture("aoMap", bookAo);
		bookMaterial2->setTexture("metallicMap", default_emission);
		bookMaterial2->setTexture("emissionMap", default_emission);
		Material* bookMaterial3 = createResource<Material>(defaultShader);
		bookMaterial3->setTexture("albedoMap", bookAlbedo3);
		bookMaterial3->setTexture("normalMap", bookNormal);
		bookMaterial3->setTexture("roughnessMap", default_ao);
		bookMaterial3->setTexture("aoMap", bookAo);
		bookMaterial3->setTexture("metallicMap", default_emission);
		bookMaterial3->setTexture("emissionMap", default_emission);
		Material* bookMaterial4 = createResource<Material>(defaultShader);
		bookMaterial4->setTexture("albedoMap", bookAlbedo4);
		bookMaterial4->setTexture("normalMap", bookNormal);
		bookMaterial4->setTexture("roughnessMap", default_ao);
		bookMaterial4->setTexture("aoMap", bookAo);
		bookMaterial4->setTexture("metallicMap", default_emission);
		bookMaterial4->setTexture("emissionMap", default_emission);

		Material* railingMaterial = createResource<Material>(defaultShader);
		railingMaterial->setTexture("albedoMap", galvanizedAlbedo);
		railingMaterial->setTexture("normalMap", railingNormal);
		railingMaterial->setTexture("roughnessMap", galvanizedRough);
		railingMaterial->setTexture("aoMap", railingAo);
		railingMaterial->setTexture("metallicMap", default_ao);
		railingMaterial->setTexture("emissionMap", default_emission);

		Material* balconyFloorMaterial = createResource<Material>(defaultShader);
		balconyFloorMaterial->setTexture("albedoMap", balconyFloorAlbedo);
		balconyFloorMaterial->setTexture("normalMap", balconyFloorNormal);
		balconyFloorMaterial->setTexture("roughnessMap", balconyFloorRoughness);
		balconyFloorMaterial->setTexture("aoMap", default_ao);
		balconyFloorMaterial->setTexture("metallicMap", default_emission);
		balconyFloorMaterial->setTexture("emissionMap", default_emission);

		Material* blindsMaterial = createResource<Material>(defaultShader);
		blindsMaterial->setTexture("albedoMap", blinds);
		blindsMaterial->setTexture("normalMap", default_normal);
		blindsMaterial->setTexture("roughnessMap", default_emission);
		blindsMaterial->setTexture("aoMap", default_ao);
		blindsMaterial->setTexture("metallicMap", default_ao);
		blindsMaterial->setTexture("emissionMap", default_emission);


		Material* def = createResource<Material>(defaultShader);
		def->setTexture("albedoMap", default_specular);
		def->setTexture("normalMap", default_normal);
		def->setTexture("roughnessMap", default_emission);
		def->setTexture("aoMap", default_ao);
		def->setTexture("metallicMap", default_ao);
		def->setTexture("emissionMap", default_emission);

		Material* glassMaterial = createResource<Material>(transparentShader);
		glassMaterial->setTexture("albedoMap", windowAlbedo);
		glassMaterial->setTexture("normalMap", default_normal);
		glassMaterial->setTexture("roughnessMap", default_roughness);
		glassMaterial->setTexture("aoMap", default_ao);
		glassMaterial->setTexture("metallicMap", default_emission);
		glassMaterial->setTexture("emissionMap", default_emission);


		Material* occluderMaterial = createResource<Material>(litShader);
		occluderMaterial->setProperty<Vector3f>("color", Vector3f(0, 0, 0));

		Material* panoramaMaterial = createResource<Material>(skyBoost);
		panoramaMaterial->setTexture("albedoMap", panoramaAlbedo);
		panoramaMaterial->setProperty("boost", 30.0f);

		/* --------------------------- CAMERA --------------------------- */

		Entity* s1 = instanciate("start");
		s1->getComponent<Transform>()->setPosition(Vector3f(-1.275343f, 0.609712f, 3.92936f));
		s1->getComponent<Transform>()->setRotation(Vector3f(-0.406666f, 2.218385f, 0.00000f));

		Entity* f1 = instanciate("�fin");
		f1->getComponent<Transform>()->setPosition(Vector3f(-1.701402f, 0.896463f, 3.75409f));
		f1->getComponent<Transform>()->setRotation(Vector3f(0.070667f, 2.363519f, 0.00000f));

		Entity* s2 = instanciate("start");
		s2->getComponent<Transform>()->setPosition(Vector3f(0.042963f, 0.564167f, 0.744266f));
		s2->getComponent<Transform>()->setRotation(Vector3f(-0.441667f, -4.278056f, 0.000000f));

		Entity* f2 = instanciate("fin");
		f2->getComponent<Transform>()->setPosition(Vector3f(0.325749f, 0.647959f, 0.665603f));
		f2->getComponent<Transform>()->setRotation(Vector3f(-0.323334f, -4.136055f, 0.000000f));

		Entity* s3 = instanciate("start");
		s3->getComponent<Transform>()->setPosition(Vector3f(1.849994f, 1.612600f, 0.045660f));
		s3->getComponent<Transform>()->setRotation(Vector3f(-0.133326f, 3.428171f, 0.000000f));

		Entity* f3 = instanciate("fin");
		f3->getComponent<Transform>()->setPosition(Vector3f(1.719618f, 1.658098f, 1.163731f));
		f3->getComponent<Transform>()->setRotation(Vector3f(-0.098326f, 3.107171f, 0.000000f));

		Entity* s4 = instanciate("start");
		s4->getComponent<Transform>()->setPosition(Vector3f(-1.432103f, 0.233059f, 3.00573f));
		s4->getComponent<Transform>()->setRotation(Vector3f(-0.910666f, 0.317027f, 0.00000f));

		Entity* f4 = instanciate("fin");
		f4->getComponent<Transform>()->setPosition(Vector3f(-1.254720f, 0.108683f, -0.22882f));
		f4->getComponent<Transform>()->setRotation(Vector3f(0.086667f, 0.071351f, 0.00000f));

		Entity* s5 = instanciate("start");
		s5->getComponent<Transform>()->setPosition(Vector3f(1.497587f, 1.648782f, 2.544615f));
		s5->getComponent<Transform>()->setRotation(Vector3f(-0.126667f, -2.622055f, 0.000000f));

		Entity* f5 = instanciate("fin");
		f5->getComponent<Transform>()->setPosition(Vector3f(1.335855f, 0.571176f, 2.610204f));
		f5->getComponent<Transform>()->setRotation(Vector3f(-0.126667f, -2.622055f, 0.000000f));

		Entity* s6 = instanciate("start");
		s6->getComponent<Transform>()->setPosition(Vector3f(-1.708001f, 0.232390f, 0.078278f));
		s6->getComponent<Transform>()->setRotation(Vector3f(0.028630f, -1.570984f, 0.000000f));

		Entity* f6 = instanciate("fin");
		f6->getComponent<Transform>()->setPosition(Vector3f(-0.610981f, 0.718269f, 0.078073f));
		f6->getComponent<Transform>()->setRotation(Vector3f(0.028630f, -1.570984f, 0.000000f));

		Entity* s7 = instanciate("start");
		s7->getComponent<Transform>()->setPosition(Vector3f(1.163253f, 2.849120f, -0.82634f));
		s7->getComponent<Transform>()->setRotation(Vector3f(-1.466666f, 7.874601f, 0.00000f));

		Entity* f7 = instanciate("fin");
		f7->getComponent<Transform>()->setPosition(Vector3f(1.112261f, 2.849120f, 1.64630f));
		f7->getComponent<Transform>()->setRotation(Vector3f(-1.466666f, 7.874601f, 0.00000f));

		Entity* s8 = instanciate("start");
		s8->getComponent<Transform>()->setPosition(Vector3f(1.269536f, 2.121249f, 4.091350f));
		s8->getComponent<Transform>()->setRotation(Vector3f(-0.606236f, 2.979938f, 0.000000f));

		Entity* f8 = instanciate("fin");
		f8->getComponent<Transform>()->setPosition(Vector3f(0.237463f, 1.906774f, 3.826429f));
		f8->getComponent<Transform>()->setRotation(Vector3f(-0.576903f, 3.178587f, 0.000000f));

		Entity* s9 = instanciate("start");
		s9->getComponent<Transform>()->setPosition(Vector3f(1.5f, 0.7f, -2.4f));
		s9->getComponent<Transform>()->setRotation(Vector3f(-0.1f, 0.4f, 0.0f));

		Entity* f9 = instanciate("fin");
		f9->getComponent<Transform>()->setPosition(Vector3f(-1.8f, 1.1f, -2.9f));
		f9->getComponent<Transform>()->setRotation(Vector3f(-0.1f, -0.3f, 0.0f));


		Entity* cam = instanciate("Camera");
		cam->addComponent<Camera>()->setFOV(60);
		cam->getComponent<Transform>()->setPosition(Vector3f(0, 2, -2));
		cam->getComponent<Transform>()->setRotation(Vector3f(0, 0, 0));
		cam->addComponent<StateControllerScript>();
		cam->addComponent<CameraControllerScript>();

		/*
		cam->addComponent<PathWalkerScript>()->speed = 0.1f;
		cam->getComponent<PathWalkerScript>()->path.push_back(*(s1->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(f1->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(s2->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(f2->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(s3->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(f3->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(s4->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(f4->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(s5->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(f5->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(s6->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(f6->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(s7->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(f7->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(s8->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(f8->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(s9->transform));
		cam->getComponent<PathWalkerScript>()->path.push_back(*(f9->transform));
		*/
		//cam->addComponent<ControllerToggleScript>();


		/* --------------------------- LIGHT HELPER --------------------------- */
		
		Entity* lightProbe = instanciate("LightProbe");
		lightProbe->getComponent<Transform>()->setPosition(Vector3f(0, 1.2f, 0));
		lightProbe->addComponent<LightProbe>()->resolution = 512;
		lightProbe->getComponent<LightProbe>()->bounds.setMinBound(Vector3f(-2.1f, -1.3f, -3.4f));
		lightProbe->getComponent<LightProbe>()->bounds.setMaxBound(Vector3f(2.1f, 2.0f, 6));
		

		Entity* min = instanciate("min");
		min->getComponent<Transform>()->setPosition(Vector3f(-2.1f, -1.3f, -3.4f));

		Entity* max = instanciate("max");
		max->getComponent<Transform>()->setPosition(Vector3f(2.1f, 2.0f, 6));


		/* --------------------------- LIGHTS --------------------------- */
		Entity* ambient = instanciate("Ambient");
		ambient->addComponent<AmbientLight>();
		ambient->getComponent<AmbientLight>()->color = Vector3f(0.3f, 0.3f, 0.3f);
		ambient->getComponent<AmbientLight>()->intensity = 0;

		Entity* sun = instanciate("Sun");
		sun->addComponent<DirectionalLight>();
		sun->getComponent<DirectionalLight>()->color = Vector3f(253.0f/255.0f, 248.0f / 255.0f, 230.0f / 255.0f);
		sun->getComponent<DirectionalLight>()->direction = Vector3f(0.4f, -0.6f, 2.0f);
		sun->getComponent<DirectionalLight>()->intensity = 300.0f;



		/* --------------------------- OBJECTSS --------------------------- */

		Entity* couch = instanciate("Couch");
		couch->addComponent<MeshRenderer>();
		couch->getComponent<MeshRenderer>()->setMesh(couchMesh);
		couch->getComponent<MeshRenderer>()->setMaterial(couchMaterial);

		Entity* longCouch = instanciate("Long-Couch");
		longCouch->addComponent<MeshRenderer>();
		longCouch->getComponent<MeshRenderer>()->setMesh(longCouchMesh);
		longCouch->getComponent<MeshRenderer>()->setMaterial(couchMaterial);

		Entity* table = instanciate("Rable");
		table->addComponent<MeshRenderer>()->getReflected = false;
		table->getComponent<MeshRenderer>()->setMesh(tableMesh);
		table->getComponent<MeshRenderer>()->setMaterial(tableMaterial);
		//table->setEnable(false);

		Entity* shelve = instanciate("Shelve");
		shelve->addComponent<MeshRenderer>();
		shelve->getComponent<MeshRenderer>()->setMesh(shelveMesh);
		shelve->getComponent<MeshRenderer>()->setMaterial(shelveMaterial);

		Entity* room = instanciate("Room");
		room->addComponent<MeshRenderer>();
		room->getComponent<MeshRenderer>()->setMesh(wallMesh);
		room->getComponent<MeshRenderer>()->setMaterial(wallMaterial);

		Entity* occluder = instanciate("Occluder");
		occluder->addComponent<MeshRenderer>();
		occluder->getComponent<MeshRenderer>()->setMesh(occluderMesh);
		occluder->getComponent<MeshRenderer>()->setMaterial(occluderMaterial);

		Entity* floor = instanciate("Floor");
		floor->addComponent<MeshRenderer>();
		floor->getComponent<MeshRenderer>()->setMesh(floorMesh);
		floor->getComponent<MeshRenderer>()->setMaterial(wood);

		Entity* floorEdge = instanciate("FloorEdge");
		floorEdge->addComponent<MeshRenderer>();
		floorEdge->getComponent<MeshRenderer>()->setMesh(floorEdgeMesh);
		floorEdge->getComponent<MeshRenderer>()->setMaterial(wood);

		Entity* doors = instanciate("Doors");
		doors->addComponent<MeshRenderer>();
		doors->getComponent<MeshRenderer>()->setMesh(doorsMesh);
		doors->getComponent<MeshRenderer>()->setMaterial(doorMaterial);

		Entity* slidingDoor = instanciate("Sliding-Doors");
		slidingDoor->addComponent<MeshRenderer>();
		slidingDoor->getComponent<MeshRenderer>()->setMesh(slidingDoorMesh);
		slidingDoor->getComponent<MeshRenderer>()->setMaterial(slidingDoorMaterial);

		Entity* carpet = instanciate("Carpet");
		carpet->addComponent<MeshRenderer>()->setRenderType(RenderType::cutout);
		carpet->getComponent<MeshRenderer>()->setMesh(carpetMesh);
		carpet->getComponent<MeshRenderer>()->setMaterial(carpetMaterial);

		Entity* carpetFloor = instanciate("CarpetFloor");
		carpetFloor->addComponent<MeshRenderer>();
		carpetFloor->getComponent<MeshRenderer>()->setMesh(carpetFloorMesh);
		carpetFloor->getComponent<MeshRenderer>()->setMaterial(carpetFloorMaterial);

		Entity* lamp = instanciate("Lamp");
		lamp->addComponent<MeshRenderer>();
		lamp->getComponent<MeshRenderer>()->setMesh(lampMesh);
		lamp->getComponent<MeshRenderer>()->setMaterial(lampMaterial);

		Entity* ceilingLight = instanciate("CeilingLight");
		ceilingLight->addComponent<MeshRenderer>();
		ceilingLight->getComponent<MeshRenderer>()->setMesh(ceilingLightMesh);
		ceilingLight->getComponent<MeshRenderer>()->setMaterial(ceilingLightMaterial);

		Entity* vase = instanciate("Vase");
		vase->addComponent<MeshRenderer>();
		vase->getComponent<MeshRenderer>()->setMesh(vaseMesh);
		vase->getComponent<MeshRenderer>()->setMaterial(vaseMaterial);

		Entity* frame = instanciate("Frame");
		frame->addComponent<MeshRenderer>();
		frame->getComponent<MeshRenderer>()->setMesh(frameMesh);
		frame->getComponent<MeshRenderer>()->setMaterial(frameMaterial);

		Entity* frameGlass = instanciate("FrameGlass");
		frameGlass->addComponent<TransparentMeshRenderer>();
		frameGlass->getComponent<TransparentMeshRenderer>()->setMesh(frameGlassMesh);
		frameGlass->getComponent<TransparentMeshRenderer>()->setMaterial(glassMaterial);

		Entity* painting1 = instanciate("Painting1");
		painting1->addComponent<MeshRenderer>();
		painting1->getComponent<MeshRenderer>()->setMesh(painting1Mesh);
		painting1->getComponent<MeshRenderer>()->setMaterial(painting1Material);

		Entity* painting2 = instanciate("Painting2");
		painting2->addComponent<MeshRenderer>();
		painting2->getComponent<MeshRenderer>()->setMesh(painting2Mesh);
		painting2->getComponent<MeshRenderer>()->setMaterial(painting2Material);

		Entity* painting3 = instanciate("Painting3");
		painting3->addComponent<MeshRenderer>();
		painting3->getComponent<MeshRenderer>()->setMesh(painting3Mesh);
		painting3->getComponent<MeshRenderer>()->setMaterial(painting3Material);


		Entity* book1 = instanciate("Book1");
		book1->addComponent<MeshRenderer>();
		book1->getComponent<MeshRenderer>()->setMesh(bookMesh1);
		book1->getComponent<MeshRenderer>()->setMaterial(bookMaterial1);
		Entity* book2 = instanciate("Book2");
		book2->addComponent<MeshRenderer>();
		book2->getComponent<MeshRenderer>()->setMesh(bookMesh2);
		book2->getComponent<MeshRenderer>()->setMaterial(bookMaterial2);
		Entity* book3 = instanciate("Book3");
		book3->addComponent<MeshRenderer>();
		book3->getComponent<MeshRenderer>()->setMesh(bookMesh3);
		book3->getComponent<MeshRenderer>()->setMaterial(bookMaterial3);
		Entity* book4 = instanciate("Book4");
		book4->addComponent<MeshRenderer>();
		book4->getComponent<MeshRenderer>()->setMesh(bookMesh4);
		book4->getComponent<MeshRenderer>()->setMaterial(bookMaterial4);

		Entity* balconyFloor = instanciate("Balcony Floor");
		balconyFloor->addComponent<MeshRenderer>();
		balconyFloor->getComponent<MeshRenderer>()->setMesh(balconyFloorMesh);
		balconyFloor->getComponent<MeshRenderer>()->setMaterial(balconyFloorMaterial);

		Entity* balconyRailing = instanciate("Balcony Railing");
		balconyRailing->addComponent<MeshRenderer>();
		balconyRailing->getComponent<MeshRenderer>()->setMesh(balconyRailingMesh);
		balconyRailing->getComponent<MeshRenderer>()->setMaterial(railingMaterial);

		Entity* probe = instanciate("Probe");
		probe->getComponent<Transform>()->setPosition(Vector3f(0.0f, 1.2f, 0.0f));
		probe->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		probe->addComponent<MeshRenderer>();
		probe->getComponent<MeshRenderer>()->setMesh(sphere);
		probe->getComponent<MeshRenderer>()->setMaterial(def);

		
		Entity* window = instanciate("Window");
		window->addComponent<TransparentMeshRenderer>();
		window->getComponent<TransparentMeshRenderer>()->setMesh(windowMesh);
		window->getComponent<TransparentMeshRenderer>()->setMaterial(glassMaterial);
		//window->setEnable(false);
		
		/*
		Entity* window = instanciate("Window");
		window->addComponent<MeshRenderer>();
		window->getComponent<MeshRenderer>()->setMesh(windowMesh);
		window->getComponent<MeshRenderer>()->setMaterial(blindsMaterial);
		*/

		Entity* panorama = instanciate("Panorama");
		panorama->addComponent<MeshRenderer>();
		panorama->getComponent<MeshRenderer>()->setMesh(panoramaMesh);
		panorama->getComponent<MeshRenderer>()->setMaterial(panoramaMaterial);


		/*
		for (int x = 0; x < 8; x++) {
		for (int z = 0; z < 10; z++) {
		for (int y = 0; y < 4; y++) {
		Entity* probe = instanciate("Probe" + x + y + z);
		probe->getComponent<Transform>()->setPosition(Vector3f(x-4, y, z-5));
		probe->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		probe->addComponent<MeshRenderer>();
		probe->getComponent<MeshRenderer>()->setMesh(sphere);
		probe->getComponent<MeshRenderer>()->setMaterial(def);
		}
		}
		}
		*/

	}

	void OnUnload() {}

};
#endif // TEST_SCENE_CPP