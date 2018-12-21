#include "stdafx.h"

Vec3 Color(const Ray& a_Ray, Shape * a_World, int a_iDepth)
{
    HitData hData;
    if (a_World->Hit(a_Ray, 0.0001f, FLT_MAX, hData))
    {
        Ray scattered;
        Vec3 attenuation;
        if (a_iDepth < 50 && hData.m_pMaterial->Scatter(a_Ray, hData, attenuation, scattered))
        {
            return attenuation * Color(scattered, a_World, a_iDepth + 1);
        }
        else
            return Vec3(0, 0, 0, 1);
    }
    else
    {
        Vec3 unitDir = Vec3::Normalize(a_Ray.Direction());
        float t = 0.5f * (unitDir.y + 1.f);
        return (1.f - t) * Vec3(1, 1, 1, 1) + t * Vec3(0.5f, 0.7f, 1.f, 1.f);
    }
}

void WriteColor(const Vec3& a_Color)
{
    int ir = int(255.99f * sqrtf(a_Color.x));
    int ig = int(255.99f * sqrtf(a_Color.y));
    int ib = int(255.99f * sqrtf(a_Color.z));

    std::cout << ir << " " << ig << " " << ib << "\n";
}

int main()
{
    int nx = 800;
    int ny = 400;
    int ns = 10;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    const uint32 NUM_OBJS = 4;
    Shape * list[NUM_OBJS];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5f, new Lambertian(Vec3(0.8f, 0.3f, 0.3f)));
    list[1] = new Sphere(Vec3(0, -100.5f, -1), 100.f, new Lambertian(Vec3(0.8f, 0.8f, 0.0f)));
    list[2] = new Sphere(Vec3(1, 0, -1), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 0.3f));
    list[3] = new Sphere(Vec3(-1, 0, -1), 0.5f, new Metal(Vec3(0.8f, 0.8f, 0.8f), 1.f));
    ShapeList * World = new ShapeList(list, NUM_OBJS);

    Camera cam;

    for (int j = ny - 1; j >= 0; --j)
    {
        for (int i = 0; i < nx; ++i)
        {
            Vec3 color(0, 0, 0, 0);
            for (int s = 0; s < ns; ++s)
            {
                float u = float(i + Rand_Zero_LT_One()) / float(nx);
                float v = float(j + Rand_Zero_LT_One()) / float(ny);

                Ray r = cam.GetRay(u, v);

                color += Color(r, World, 0);
            }
            color /= float(ns);
            WriteColor(color);
        }
    }
}