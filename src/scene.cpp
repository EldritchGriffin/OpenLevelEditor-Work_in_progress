#include <scene.hpp>

Scene::Scene(std::string name)
{
    _name = name;
}

Scene::~Scene()
{
    for (auto object : _Objects)
    {
        delete object;
    }
}

void Scene::setName(std::string name)
{
    _name = name;
}

std::string Scene::getName()
{
    return _name;
}

void Scene::Update()
{
}

void Scene::Draw()
{
    for (auto object : _Objects)
    {
        object->Draw();
    }
}

void Scene::addObject(std::string modelPath,Vector3 position, Vector3 rotation, Vector3 scale)
{
    _Objects.push_back(new GameObject(modelPath, position, rotation, scale));
}

