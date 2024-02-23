#include <sceneManager.hpp>
#include <scene.hpp>
#include <exception>

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

void SceneManager::RemoveScene(const std::string &name)
{
    for (auto it = scenes.begin(); it != scenes.end(); it++)
    {
        if ((*it)->getName() == name)
        {
            delete *it;
            scenes.erase(it);
            if (activeScene && activeScene->getName() == name)
                activeScene = nullptr;
            return;
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
