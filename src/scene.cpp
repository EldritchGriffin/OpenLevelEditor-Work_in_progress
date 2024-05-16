#include <scene.hpp>
#include <iostream>

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

void Scene::Update(Camera3D camera)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Ray ray = GetMouseRay(GetMousePosition(), camera);
        for (int i = 0; i < _Objects.size(); i++)
        {
            RayCollision collision = GetRayCollisionMesh(ray, _Objects[i]->model.meshes[0], _Objects[i]->model.transform);
            if (collision.hit)
            {
                _selectedObject = i;
                break;
            }
            if(i == _Objects.size() - 1 && _gizmo.state == RGIZMO_STATE_COLD)
            {
                _selectedObject = -1;
            }
        }
    }
    for (auto object : _Objects)
    {
        object->Update();
    }
    if (_selectedObject >= 0)
    {
        Vector3 position = {_Objects[_selectedObject]->model.transform.m12, 
                            _Objects[_selectedObject]->model.transform.m13,
                            _Objects[_selectedObject]->model.transform.m14};
        rgizmo_update(&_gizmo, camera, position);
        _Objects[_selectedObject]->model.transform = MatrixMultiply(
            _Objects[_selectedObject]->model.transform, rgizmo_get_tranform(_gizmo, position));
    }
}

void Scene::Draw(Camera3D camera)
{
    std::cout << _selectedObject << std::endl;
    for (auto object : _Objects)
    {
        object->Draw();
    }
    if (_selectedObject >= 0)
    {
        Vector3 position = {_Objects[_selectedObject]->model.transform.m12, 
                    _Objects[_selectedObject]->model.transform.m13,
                    _Objects[_selectedObject]->model.transform.m14};
        rgizmo_draw(_gizmo, camera, position);
    }
}

void Scene::addObject(std::string modelPath, Vector3 position, Vector3 rotation, Vector3 scale)
{
    _Objects.push_back(new GameObject(modelPath, position, rotation, scale));
}
