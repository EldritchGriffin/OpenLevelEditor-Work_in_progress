#pragma once
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>

class Transform
{
public:
    Matrix transformMatrix;
    Transform(Vector3 _position, Vector3 _rotation, Vector3 _scale)
    {
        transformMatrix = MatrixIdentity();
        transformMatrix = MatrixMultiply(transformMatrix, MatrixRotateXYZ(_rotation));
        transformMatrix = MatrixMultiply(transformMatrix, MatrixScale(_scale.x, _scale.y, _scale.z));
        transformMatrix = MatrixMultiply(transformMatrix, MatrixTranslate(_position.x, _position.y, _position.z));
    }
    void rotate(Vector3 rotation)
    {
        transformMatrix = MatrixMultiply(transformMatrix, MatrixRotateXYZ(rotation));
    }
    void translate(Vector3 position)
    {
        transformMatrix = MatrixMultiply(transformMatrix, MatrixTranslate(position.x, position.y, position.z));
    }
    void scale(Vector3 scale)
    {
        transformMatrix = MatrixMultiply(transformMatrix, MatrixScale(scale.x, scale.y, scale.z));
    }
    ~Transform(){
    }
};