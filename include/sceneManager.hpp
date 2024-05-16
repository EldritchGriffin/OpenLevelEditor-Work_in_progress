#include <raylib.h>
#include <vector>
#include <string>

class Scene;

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void createScene(const std::string &name);
    void RemoveScene(const std::string &name);
    void SetActiveScene(const std::string &name);
    std::string getActiveScene();
    void renameActiveScene(const std::string &name);
    void Update(Camera3D camera);
    void Draw(Camera3D camera);
    void addObject(std::string modelPath, Vector3 position, Vector3 rotation, Vector3 scale);
    std::vector<Scene *> getScenes();
    bool isEmpty();

private:
    std::vector<Scene *> scenes;
    Scene *activeScene;
};
