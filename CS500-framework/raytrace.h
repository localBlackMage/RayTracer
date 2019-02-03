///////////////////////////////////////////////////////////////////////
// A framework for a raytracer.
////////////////////////////////////////////////////////////////////////

class Shape;

////////////////////////////////////////////////////////////////////////
// Data structures for storing meshes -- mostly used for model files
// read in via ASSIMP.
//
// A MeshData holds two lists (stl::vector) one for vertices
// (VertexData: consisting of point, normal, texture, and tangent
// vectors), and one for triangles (TriData: consisting of three
// indices into the vertex array).
typedef Eigen::Matrix<unsigned int, 3, 1 > TriData;
    
class VertexData
{
 public:
    Vector3f pnt;
    Vector3f nrm;
    Vector2f tex;
    Vector3f tan;
    VertexData(const Vector3f& p, const Vector3f& n, const Vector2f& t, const Vector3f& a) 
        : pnt(p), nrm(n), tex(t), tan(a) 
    {}
};

struct MeshData
{
    std::vector<VertexData> vertices;
    std::vector<TriData> triangles;
    Material *mat;
};

////////////////////////////////////////////////////////////////////////////////
// Scene
//class Realtime;
class RayTracer;

class Scene {
public:
    int width, height;
    //Realtime* realtime;         // Remove this (realtime stuff)
    RayTracer* m_pRayTracer;
    Material* currentMat;

    Scene();
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
    void TraceImage(Color* image, const int pass);
};
