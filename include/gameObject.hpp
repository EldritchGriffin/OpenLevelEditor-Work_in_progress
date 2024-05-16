#pragma once
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>
#include <string>

class GameObject
{
    public:
        Model model;
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

        GameObject(std::string modelPath ,Vector3 _position, Vector3 _rotation, Vector3 _scale)
        {
            model = LoadModel(modelPath.c_str());
            position = _position;
            rotation = _rotation;
            scale = _scale;
        };
        
        ~GameObject()
        {
            UnloadModel(model);
        }

        void Update()
        {

        }
        void Draw()
        {
            DrawModel(model, position, 1.0f, WHITE);
            DrawModelWires(model, position, 1.0f, BLACK);
        }
};