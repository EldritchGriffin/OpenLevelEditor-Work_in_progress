#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>
#include <string>

class Scene
{
public:
    Scene(std::string name);
    ~Scene();

    void setName(std::string name);
    std::string getName();

    void Update();
    void Draw();

    void addObject();



private:
    std::string _name;
    std::vector<Model*> _Objects;
};
