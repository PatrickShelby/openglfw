// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
  // mat3 ret;
  // // YOUR CODE FOR HW2 HERE
  // // Please implement this.  Likely the same as in HW 1.
  // return ret;


  float incos_t = 1.0f - glm::cos((glm::radians(degrees)));
  float cos_t   =     glm::cos(double(glm::radians(degrees)));
  float sin_t   =     glm::sin(double(glm::radians(degrees)));

  mat3 identity(
    cos_t * 1.0f,
    cos_t * 0.0f,
    cos_t * 0.0f,
    cos_t * 0.0f,
    cos_t * 1.0f,
    cos_t * 0.0f,
    cos_t * 0.0f,
    cos_t * 0.0f,
    cos_t * 1.0f);

  mat3 aatranspose(
    incos_t * (axis.x * axis.x),
    incos_t * (axis.x * axis.y),
    incos_t * (axis.x * axis.z),
    incos_t * (axis.x * axis.y),
    incos_t * (axis.y * axis.y),
    incos_t * (axis.y * axis.z),
    incos_t * (axis.x * axis.z),
    incos_t * (axis.y * axis.z),
    incos_t * (axis.z * axis.z));

  mat3 crossMat(
    sin_t * 0.0f,
    sin_t * axis.z,
    sin_t * -axis.y,
    sin_t * -axis.z,
    sin_t * 0.0f,
    sin_t * axis.x,
    sin_t * axis.y,
    sin_t * -axis.x,
    sin_t * 0.0f
  );

  mat3 g1 = identity;
  mat3 g2 = aatranspose;
  mat3 g3 = crossMat;
  mat3 rotatrix(g1 + g2 + g3);

  return rotatrix;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  vec3 nrm_up = normalize(up);
  eye = Transform::rotate(degrees, up) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.

  vec3 axi = glm::cross(eye, up);
  vec3 w   = glm::normalize(axi);
  up       = Transform::rotate(degrees, w) * up;
  eye      = Transform::rotate(degrees, w) * eye;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
  // mat4 ret;
  // // YOUR CODE FOR HW2 HERE
  // // Likely the same as in HW 1.
  // return ret;

  vec3 a = eye - center;
  vec3 w = normalize(a);
  vec3 u = normalize(glm::cross(up,w));
  vec3 v = cross(w, u);

  mat4 View;
  View[0][0] = u.x;
  View[1][0] = u.y;
  View[2][0] = u.z;
  View[0][1] = v.x;
  View[1][1] = v.y;
  View[2][1] = v.z;
  View[0][2] = w.x;
  View[1][2] = w.y;
  View[2][2] = w.z;
  View[3][0] = -dot(u,eye);
  View[3][1] = -dot(v,eye);
  View[3][2] = -dot(w,eye);
  View[0][3] = 0.0;
  View[1][3] = 0.0;
  View[2][3] = 0.0;
  View[3][3] = 1.0;

  return View;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.
  ret = glm::perspective(90.0f * glm::pi<float>() / 180.0f, (float)aspect, zNear, zFar);
  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement scaling
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement translation
  return ret;
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
  vec3 x = glm::cross(up,zvec);
  vec3 y = glm::cross(zvec,x);
  vec3 ret = glm::normalize(y);
  return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
