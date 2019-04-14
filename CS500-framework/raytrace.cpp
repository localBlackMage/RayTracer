//////////////////////////////////////////////////////////////////////
// Provides the framework for a raytracer.
////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "raytrace.h"
#include "realtime.h"


Scene::Scene() :
    m_pRayTracer(new RayTracer()),
    currentMat(nullptr)
{ 
}

Scene::~Scene()
{
    delete m_pRayTracer;
}

void Scene::Finit()
{
    m_pRayTracer->Finish();
}

void Scene::triangleMesh(MeshData* mesh) 
{ 
    fprintf(stderr, "\nAdding Tri Mesh: Num Tris - %d\n", uint32(mesh->triangles.size()));
    m_pRayTracer->AddTriangleMesh(mesh, currentMat);
}

Quaternionf Orientation(int i, 
                        const std::vector<std::string>& strings,
                        const std::vector<float>& f)
{
    Quaternionf q(1,0,0,0); // Unit quaternion
    while (i < int(strings.size())) {
        std::string c = strings[i++];
        if (c == "o")
        {
            q *= angleAxis(f[i++] * Radians, Vector3f::UnitX());
            q *= angleAxis(f[i++] * Radians, Vector3f::UnitY());
            q *= angleAxis(f[i++] * Radians, Vector3f::UnitZ());
        }
        else if (c == "x")
        {
            q *= angleAxis(f[i++] * Radians, Vector3f::UnitX());
        }
        else if (c == "y")
        {
            q *= angleAxis(f[i++] * Radians, Vector3f::UnitY());
        }
        else if (c == "z")
        {
            q *= angleAxis(f[i++] * Radians, Vector3f::UnitZ());
        }
        else if (c == "q")  
        {
            q *= Quaternionf(f[i+0], f[i+1], f[i+2], f[i+3]);
            i+=4; 
        }
        else if (c == "a")  
        {
            q *= angleAxis(f[i+0]*Radians, Vector3f(f[i+1], f[i+2], f[i+3]).normalized());
            i+=4; 
        } 
    }
    return q;
}

void Scene::Command(const std::vector<std::string>& strings,
                    const std::vector<float>& f)
{
    if (strings.size() == 0) return;
    std::string c = strings[0];
    
    if (c == "screen") {
        // syntax: screen width height
        //realtime->setScreen(int(f[1]),int(f[2]));
        width = int(f[1]);
        height = int(f[2]);
        m_pRayTracer->SetScreenDimensions(uint32(width), uint32(height));
    }

    else if (c == "camera") {
        // syntax: camera x y z   ry   <orientation spec>
        // Eye position (x,y,z),  view orientation (qw qx qy qz),  frustum height ratio ry
        //realtime->setCamera(Vector3f(f[1],f[2],f[3]), Orientation(5,strings,f), f[4]);
        m_pRayTracer->SetCamera(Vector3f(f[1], f[2], f[3]), Orientation(7, strings, f), f[4], f[5], f[6]);
    }

    else if (c == "ambient") {
        // syntax: ambient r g b
        // Sets the ambient color.  Note: This parameter is temporary.
        // It will be ignored once your raytracer becomes capable of
        // accurately *calculating* the true ambient light.
        //realtime->setAmbient(Vector3f(f[1], f[2], f[3])); 
    }

    else if (c == "brdf")  {
        //         0     1 2 3   4 5 6  7      8 9 10 11
        //               diffuse spec   alpha  trans  ior
        // syntax: brdf  r g b   r g b  alpha
        // later:  brdf  r g b   r g b  alpha  r g b  ior
        // First rgb is Diffuse reflection, second is specular reflection.
        // third is beer's law transmission followed by index of refraction.
        // Creates a Material instance to be picked up by successive shapes
        currentMat = new Material(Color(f[1], f[2], f[3]), Color(f[4], f[5], f[6]), Color(f[8], f[9], f[10]), f[7], f[11]);
    }

    else if (c == "light") {
        // syntax: light  r g b   
        // The rgb is the emission of the light
        // Creates a Material instance to be picked up by successive shapes
        currentMat = new Light(Color(f[1], f[2], f[3])); 
    }

    else if (c == "ibl") {
        // syntax: light  r g b   
        // The rgb is the emission of the light
        // Creates a Material instance to be picked up by successive shapes
        currentMat = new ImageBasedLight(strings[1]);
    }
   
    else if (c == "sphere") {
        // syntax: sphere x y z   r
        // Creates a Shape instance for a sphere defined by a center and radius
        m_pRayTracer->AddSphere(Vector3f(f[1], f[2], f[3]), f[4], currentMat);
    }

    else if (c == "box") {
        // syntax: box bx by bz   dx dy dz
        // Creates a Shape instance for a box defined by a corner point and diagonal vector
        m_pRayTracer->AddBox(Vector3f(f[1], f[2], f[3]), Vector3f(f[4], f[5], f[6]), currentMat);
    }

    else if (c == "cylinder") {
        // syntax: cylinder bx by bz   ax ay az  r
        // Creates a Shape instance for a cylinder defined by a base point, axis vector, and radius
        m_pRayTracer->AddCylinder(Vector3f(f[1], f[2], f[3]), Vector3f(f[4], f[5], f[6]), f[7], currentMat);
    }

    else if (c == "mesh") {
        // syntax: mesh   filename   tx ty tz   s   <orientation>
        // Creates many Shape instances (one per triangle) by reading
        // model(s) from filename. All triangles are rotated by a
        // quaternion (qw qx qy qz), uniformly scaled by s, and
        // translated by (tx ty tz) .
        Matrix4f modelTr = translate(Vector3f(f[2],f[3],f[4]))
                          *scale(Vector3f(f[5],f[5],f[5]))
                          *toMat4(Orientation(6,strings,f));
        ReadAssimpFile(strings[1], modelTr);
    }

    
    else {
        fprintf(stderr, "\n*********************************************\n");
        fprintf(stderr, "* Unknown command: %s\n", c.c_str());
        fprintf(stderr, "*********************************************\n\n");
    }
}

void Scene::TraceImage(Color* image, const uint32 pass)
{
    fprintf(stderr, "Pass Number: %d\n", pass);
    //fprintf(stderr, "\nNumObjects %d\n", m_pRayTracer->NumShapes());
#pragma omp parallel for schedule(dynamic, 1) // Magic: Multi-thread y loop
    for (int y = 0; y < height; y++) {
        //fprintf(stderr, "Rendering %4d\r", y);
        for (int x = 0; x < width; x++) {
            Color c = m_pRayTracer->GetColor(x, y);
            if (IsColorNAN(c))
            {
                std::cout << "Final Color is NAN" << std::endl;
                c = Color(0, 0, 0);
            }
            if (IsColorINF(c))
            { 
                std::cout << "Final Color is INF" << std::endl;
                c = Color(0, 0, 0);
            }
            image[y*width + x] += c;
        }
    }
}
