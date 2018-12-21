#pragma once

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
protected:
    Vec3 m_vOrigin;
    Vec3 m_vLowerLeftCorner;
    Vec3 m_vHorizontal;
    Vec3 m_vVertical;

public:
    Camera();
    ~Camera();

    Ray GetRay(float a_fU, float a_fV);
};

#endif //CAMERA_H