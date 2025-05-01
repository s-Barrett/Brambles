#include <Brambles/Brambles.h>
#include <iostream>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/emscripten.h>
#endif

using namespace Brambles;
std::shared_ptr<Brambles::Core> core;

std::string getUserInput()
{
#ifdef __EMSCRIPTEN__
    // JavaScript prompt() from browser console
    char* map = (char*)EM_ASM_PTR({
        let response = prompt("Enter map name (relative to assets/map/):", "hl1/1.obj");
        let lengthBytes = lengthBytesUTF8(response) + 1;
        let stringOnWasmHeap = _malloc(lengthBytes);
        stringToUTF8(response, stringOnWasmHeap, lengthBytes);
        return stringOnWasmHeap;
    });

    std::string result(map);
    free(map);
    return result;
#else
    std::string input;
    std::getline(std::cin, input);
    return input;
#endif
}

bool getDebugChoice()
{
#ifdef __EMSCRIPTEN__
    int choice = EM_ASM_INT({
        return confirm("Enable debug renderers?") ? 1 : 0;
    });
    return choice != 0;
#else
    std::string input;
    std::cout << "Enable debug renderers? (y/n): ";
    std::getline(std::cin, input);
    return input == "y" || input == "Y";
#endif
}

int main(int argc, char* argv[])
{
    std::cout << "Enter map path (e.g., hl1/1.obj): ";
    std::string mapName = getUserInput();
    std::string mapPath = "../assets/map/" + mapName;

    bool debugEnabled = getDebugChoice();

    int winsizeX = 1920;
    int winsizeY = 1080;

    core = Core::initialize(winsizeX, winsizeY);

    core->getLightManager()->setAmbient(glm::vec3(0.1, 0.1, 0.1));
    core->getLightManager()->addLight("light1", glm::vec3(8.0, 5.0, -10.0), glm::vec3(1.0, 1.0, 0.9), 0.9);
    core->getLightManager()->addLight("light2", glm::vec3(-14.0, 5.0, -10.0), glm::vec3(1.0, 1.0, 0.9), 0.9);
    core->getLightManager()->addLight("light3", glm::vec3(10.0, -180.0, 0.0), glm::vec3(1.0, 1.0, 1.0), 0.3);
    core->getLightManager()->addLight("light4", glm::vec3(0.0, -10.0, -10.0), glm::vec3(0.1, 0.1, 1.0), 0.3);

    std::shared_ptr<Entity> map = core->addEntity();
    std::shared_ptr<Renderer> mapRenderer = map->addComponent<Renderer>();
    mapRenderer->setModel(core->getResources()->load<Model>(mapPath));
    map->getComponent<Transform>()->setPosition(glm::vec3(0, 0, 0.0));
    map->getComponent<Transform>()->setScale(glm::vec3(1.0, 1.0, 1.0));

    std::shared_ptr<MeshCollider> mapMeshCollider = map->addComponent<MeshCollider>(core->getResources()->load<Model>(mapPath));
    mapMeshCollider->setDebugRenderer(debugEnabled);
    core->getPhysics()->registerMeshCollider(mapMeshCollider);

    std::shared_ptr<RigidBody> mapRigidBody = map->addComponent<RigidBody>();
    mapRigidBody->setMass(100.0);
    mapRigidBody->setStatic(true);
    core->getPhysics()->registerRigidBody(mapRigidBody);

    std::shared_ptr<Entity> player = core->addEntity();
    std::shared_ptr<Renderer> playerRenderer = player->addComponent<Renderer>();
    player->addComponent<PlayerController>();
    player->addComponent<Gui>();
    playerRenderer->setModel(core->getResources()->load<Model>("../assets/objects/walter/walter.obj"));
    player->getComponent<Transform>()->setPosition(glm::vec3(0, -10, -15.0));
    player->getComponent<Transform>()->setScale(glm::vec3(2.0, 2.0, 2.0));
    player->getComponent<Transform>()->setRotation(glm::vec3(0.0, 180.0, 0.0));

    std::shared_ptr<Camera> playerCamera = player->addComponent<Camera>();
    playerCamera->setFov(70.0);
    playerCamera->setCameraPosition(glm::vec3(0, 4.0, 0));
    playerCamera->setPriority(1.0);

    std::shared_ptr<BoxCollider> playerBoxCollider = player->addComponent<BoxCollider>();
    playerBoxCollider->setSize(glm::vec3(1.0, 3.7, 1.0));
    playerBoxCollider->setOffset(glm::vec3(0.0, 1.75, 0.0));
    playerBoxCollider->setDebugRenderer(debugEnabled);
    core->getPhysics()->registerCollider(playerBoxCollider);

    std::shared_ptr<RigidBody> playerRigidBody = player->addComponent<RigidBody>();
    playerRigidBody->setMass(200.0);
    core->getPhysics()->registerRigidBody(playerRigidBody);

    std::shared_ptr<Entity> entity = core->addEntity();
    std::shared_ptr<Renderer> entityRenderer = entity->addComponent<Renderer>();
    entityRenderer->setModel(core->getResources()->load<Model>("../assets/objects/medkit/Medkit.obj"));
    entity->getComponent<Transform>()->setPosition(glm::vec3(5, -10, -10.0));
    entity->getComponent<Transform>()->setScale(glm::vec3(0.1, 0.1, 0.1));

    std::shared_ptr<BoxCollider> entityBoxCollider = entity->addComponent<BoxCollider>();
    entityBoxCollider->setSize(glm::vec3(0.5, 0.5, 0.5));
    entityBoxCollider->setOffset(glm::vec3(0.0, 0.2, 0.0));
    entityBoxCollider->setDebugRenderer(debugEnabled);
    core->getPhysics()->registerCollider(entityBoxCollider);

    std::shared_ptr<RigidBody> entityRigidBody = entity->addComponent<RigidBody>();
    entityRigidBody->setMass(50.0);
    core->getPhysics()->registerRigidBody(entityRigidBody);

    std::shared_ptr<Entity> freeCam = core->addEntity();
    std::shared_ptr<Renderer> freeCamRenderer = freeCam->addComponent<Renderer>();
    freeCamRenderer->setModel(core->getResources()->load<Model>("../assets/objects/walter/walter.obj"));
    freeCam->getComponent<Transform>()->setPosition(glm::vec3(-4, -12, -13.0));
    freeCam->getComponent<Transform>()->setScale(glm::vec3(2.0, 2.0, 2.0));

    std::shared_ptr<AudioSource> freeAudio = freeCam->addComponent<AudioSource>();
    freeAudio->setSound(core->getResources()->load<Sound>("../assets/sounds/halflife/hellofreeman"));
    freeAudio->play();
    freeAudio->setGain(0.6);
    freeAudio->setPitch(1.0);

    freeCam->addComponent<CameraController>();
    std::shared_ptr<Camera> freeCamCamera = freeCam->addComponent<Camera>();
    freeCamCamera->setFov(100.0);
    freeCamCamera->setPriority(0.0);
    freeCamCamera->setCameraPosition(glm::vec3(0, 3.8, 0));

    SDL_SetRelativeMouseMode(SDL_TRUE);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop([]() {
        core->runSingleFrame();
    }, 0, 1);
#else
    core->run();
#endif

    return 0;
}
