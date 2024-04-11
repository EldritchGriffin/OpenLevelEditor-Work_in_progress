#include <sceneManager.hpp>
#include <scene.hpp>
#include <stdexcept>

SceneManager::SceneManager()
{
    activeScene = nullptr;
}

SceneManager::~SceneManager()
{
    for (auto scene : scenes)
    {
        delete scene;
    }
}

void SceneManager::createScene(const std::string &name)
{
    if(name.empty())
        throw std::runtime_error("sceneName must not be empty");
    for (auto scene : scenes)
    {
        if (scene->getName() == name)
        {
            throw std::runtime_error("Scene already exists");
        }
    }
    Scene *scene = new Scene(name);
    scenes.push_back(scene);
}

void SceneManager::RemoveScene(const std::string &name) {
    for (auto it = scenes.begin(); it != scenes.end();) {
        if ((*it)->getName() == name) {
            if (activeScene && activeScene->getName() == name)
                activeScene = nullptr;
            delete *it;
            it = scenes.erase(it); 
            return;
        } else {
            ++it;
        }
    }
    throw std::runtime_error("Scene not found");
}

void SceneManager::SetActiveScene(const std::string &name)
{
    for (auto scene : scenes)
    {
        if (scene->getName() == name)
        {
            activeScene = scene;
            return;
        }
    }
    throw std::runtime_error("Scene not found");
}

std::string SceneManager::getActiveScene()
{
    if (activeScene)
    {
        return activeScene->getName();
    }
    return "";
}

void SceneManager::renameActiveScene(const std::string &name)
{
    if(activeScene == nullptr)
        throw std::runtime_error("No Selected Scene");
    for(auto scene : scenes)
    {
        if(scene->getName() == name)
        {
            throw std::runtime_error("sceneName already exists");
        }
    }
    activeScene->setName(name);
}

void SceneManager::addObject(std::string modelPath, Vector3 position, Vector3 rotation, Vector3 scale)
{
    if (activeScene)
    {
        activeScene->addObject(modelPath, position, rotation, scale);
    }
}

void SceneManager::Update()
{
    if (activeScene)
    {
        activeScene->Update();
    }
}

void SceneManager::Draw()
{
    if (activeScene)
    {
        activeScene->Draw();
    }
    else
    {
        DrawText("No active scene", 500, 500, 50, BLACK);
    }
}

std::vector<Scene *> SceneManager::getScenes()
{
    return scenes;
}

bool SceneManager::isEmpty()
{
    return scenes.empty();
}
