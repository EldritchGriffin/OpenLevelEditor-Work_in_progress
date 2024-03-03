#pragma once
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>
#include <string>

class GameObject
{
    public:
        Transform *transform;
        Model model;

        GameObject(std::string modelPath ,Vector3 _position, Vector3 _rotation, Vector3 _scale)
        {
            model = LoadModel(modelPath.c_str());
        };
        
        ~GameObject()
        {
            UnloadModel(model);
            delete transform;
        }

        void Update();
        void Draw()
        {
            DrawModel(model, {0.0f,0.0f,0.0f}, 1.0f, WHITE);
        }
};