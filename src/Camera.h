#pragma once

#include <nanogui/vector.h>

using namespace nanogui;

/// A class encapsulating a camera for manipulating a 3D scene.
class Camera {
public:
    /// Constructor
    Camera();

    /// Returns the projection matrix for the camera
    /// \return The projection matrix for the camera
    Matrix4f GetProjectionMatrix() const;
    /// Returns the view matrix for the camera
    /// \return The view matrix for the camera
    Matrix4f GetViewMatrix() const;
    /// Changes the camera to look at the target from the origin.
    /// \param origin The point were the camera is placed.
    /// \param target The point the camera should look at.
    /// \param up The direction defining "up" for the camera.
    void LookAt(const Vector3f& origin, const Vector3f& target, const Vector3f& up);
    /// Sets the field of view angle for the camera.
    /// \param fov The field of view to set.
    void SetFov(float fov);
    /// Set the near value, objects closer to the camera than this value are cutoff.
    /// \param near The near value to set.
    void SetNear(float _near);
    /// Set the far value, objects farther from the camera than this value are cutoff.
    /// \param near The near value to set.
    void SetFar(float _far);
    /// Sets the width and height of the camera.
    /// \param size The width and height to set.
    void SetSize(const Vector2i& size);
    /// Returns the width and height of the camera.
    /// \return The widht and height of the camera.
    const Vector2i& GetSize() const;

    /// Rotates the view horizontally
    /// \param angle The angle to rotate about in radians.
    void RotateHorizontally(float angle);
    /// Rotates the view vertically
     /// \param angle The angle to rotate about in radians.
    void RotateVertically(float angle);

private:
    Vector3f m_origin;
    Vector3f m_target;
    Vector3f m_up;
    float m_fov;
    float m_near;
    float m_far;
    Vector2i m_size;
};
