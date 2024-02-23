#include <scene.hpp>

Scene::Scene(std::string name)
{
    _name = name;
}

Scene::~Scene()
{
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
    DrawText(_name.c_str(), 500, 500, 50, BLACK);
}
