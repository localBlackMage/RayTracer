///////////////////////////////////////////////////////////////////////
// A framework for a raytracer.
////////////////////////////////////////////////////////////////////////

class Shape;

////////////////////////////////////////////////////////////////////////////////
// Scene
//class Realtime;
class RayTracer;
class RTStopWatch;

class Scene {
public:
    int width, height;
    //Realtime* realtime;         // Remove this (realtime stuff)
    RayTracer* m_pRayTracer;
    Material* currentMat;
    RTStopWatch* m_pStopWatch;

    Scene();
    ~Scene();
    void Finit();

    // The scene reader-parser will call the Command method with the
    // contents of each line in the scene file.
    void Command(const std::vector<std::string>& strings,
                 const std::vector<float>& f);

    // To read a model file into the scene via ASSIMP, call ReadAssimpFile.  
    void ReadAssimpFile(const std::string& path, const Matrix4f& M);

    // Once ReadAssimpFile parses the information from the model file,
    // it will call:
    void triangleMesh(MeshData* mesh);

    // The main program will call the TraceImage method to generate
    // and return the image.  This is the Ray Tracer!
    void TraceImage(Color* image, const uint32 pass);
};
