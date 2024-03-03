#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>
#include <string>
#include <gameObject.hpp>

class Scene
{
public:
    Scene(std::string name);
    ~Scene();

    void setName(std::string name);
    std::string getName();

    void Update();
    void Draw();

    void addObject(std::string modelPath,Vector3 position, Vector3 rotation, Vector3 scale);



private:
    std::string _name;
    std::vector<GameObject *> _Objects;
};
