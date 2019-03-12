///////////////////////////////////////////////////////////////////////
// Provides the framework a raytracer.
//
// Gary Herron
//
// Copyright 2012 DigiPen Institute of Technology
////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <ctime>

#ifdef _WIN32
    // Includes for Windows
    #include <windows.h>
    #include <cstdlib>
    #include <limits>
    #include <crtdbg.h>
#else
    // Includes for Linux
    #include <stdlib.h>
    #include <time.h> 
#endif

#include "stdafx.h"
#include "raytrace.h"

// Read a scene file by parsing each line as a command and calling
// scene->Command(...) with the results.
void ReadScene(const std::string inName, Scene* scene)
{
    std::ifstream input(inName.c_str());
    if (input.fail()) {
        std::cerr << "File not found: "  << inName << std::endl;
        fflush(stderr);
        exit(-1); }

    // For each line in file
    for (std::string line; getline(input, line); ) {
        std::vector<std::string> strings;
        std::vector<float> floats;
        
        // Parse as parallel lists of strings and floats
        std::stringstream lineStream(line);
        for (std::string s; lineStream >> s; ) { // Parses space-separated strings until EOL
            float f;
            //std::stringstream(s) >> f; // Parses an initial float into f, or zero if illegal
            if (!(std::stringstream(s) >> f)) f = nanf(""); // An alternate that produced NANs
            floats.push_back(f);
            strings.push_back(s); }

        if (strings.size() == 0) continue; // Skip blanks lines
        if (strings[0][0] == '#') continue; // Skip comment lines
        
        // Pass the line's data to Command(...)
        scene->Command(strings, floats);
    }

    input.close();
}

Color LinearToGamma(const Color& a_Color)
{
    const static float EXPO = 1.f / 2.2f;
    return pow(a_Color, EXPO);
}

// Write the image as a HDR(RGBE) image.  
#include "rgbe.h"
void WriteHdrImage(const std::string outName, const int width, const int height, Color* image, float numPasses)
{
    // Turn image from a 2D-bottom-up array of Vector3D to an top-down-array of floats
    float* data = new float[width*height*3];
    float* dp = data;
    for (int y=height-1;  y>=0;  --y) {
        for (int x=0;  x<width;  ++x) {
            Color pixel = LinearToGamma(image[y*width + x] / numPasses);
            *dp++ = pixel[0];
            *dp++ = pixel[1];
            *dp++ = pixel[2]; } }

    // Write image to file in HDR (a.k.a RADIANCE) format
    rgbe_header_info info;
    char errbuf[100] = {0};

    FILE* fp = nullptr;
    fopen_s(&fp, outName.c_str(), "wb");
    info.valid = false;
    int r = RGBE_WriteHeader(fp, width, height, &info, errbuf);
    if (r != RGBE_RETURN_SUCCESS)
        printf("error: %s\n", errbuf);

    r = RGBE_WritePixels_RLE(fp, data, width,  height, errbuf);
    if (r != RGBE_RETURN_SUCCESS)
        printf("error: %s\n", errbuf);
    fclose(fp);
    
    delete data;
}

////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    Scene* scene = new Scene();

    // Read the command line argument
    std::string inName =  (argc > 1) ? argv[1] : "testscene.scn";
    std::string baseName = inName.substr(0, inName.size() - 4) + "_";
    std::string hdrName = inName;

    hdrName.replace(hdrName.size()-4, hdrName.size(), "_final.hdr");

    // Read the scene, calling scene.Command for each line.
    ReadScene(inName, scene);

    scene->Finit();

    // Allocate and clear an image array
    Color *image =  new Color[scene->width*scene->height];
    for (int y=0;  y<scene->height;  y++)
        for (int x=0;  x<scene->width;  x++)
            image[y*scene->width + x] = Color(0,0,0);

    const uint32 numPasses = (argc > 2) ? uint32(std::atoi(argv[2])) : 8;

    for (uint32 i = 1; i <= numPasses; ++i)
    {
        // RayTrace the image
        scene->TraceImage(image, i);

        //if (i % 10 == 0 && i != 0)
        if (i == 1 || i == 8 || i == 64 || i == 512)
        {
            // Write the image
            fprintf(stderr, "Writing image...\n");
            WriteHdrImage(baseName + std::to_string(i) + ".hdr", scene->width, scene->height, image, float(i));
            fprintf(stderr, "Finished.\n");
        }
    }
    // Write the image
    fprintf(stderr, "Writing image...\n");
    WriteHdrImage(hdrName, scene->width, scene->height, image, float(numPasses));
    fprintf(stderr, "Finished.\n");

}
