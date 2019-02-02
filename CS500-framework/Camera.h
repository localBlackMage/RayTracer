#pragma once

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
protected:
    Vector3f m_vOrigin;
    Vector3f m_vLowerLeftCorner;
    Vector3f m_vHorizontal;
    Vector3f m_vVertical;

public:
    Camera();
    ~Camera();

    Ray GetRay(float a_fU, float a_fV);
};

#endif //CAMERA_H