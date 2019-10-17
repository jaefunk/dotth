/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2019 jaefunk <https://github.com/jaefunk/dotth>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __DOTTH_MATRIX_HPP__
#define __DOTTH_MATRIX_HPP__

#include <cstring>
#include "vector.hpp"

namespace dotth {
	constexpr int matrix_size = (sizeof(float) * 16);
	struct matrix4 {
		
		float m[16];
		matrix4() {};
		matrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
		{
		}
		matrix4(const float* mat) { set(mat); }
		matrix4(const matrix4& copy) { memcpy_s(m, matrix_size, copy.m, matrix_size); }
		static void createLookAt(const Vec3& eyePosition, const Vec3& targetPosition, const Vec3& up, matrix4* dst);

		/**
		* Creates a view matrix4 based on the specified input parameters.
		*
		* @param eyePositionX The eye x-coordinate position.
		* @param eyePositionY The eye y-coordinate position.
		* @param eyePositionZ The eye z-coordinate position.
		* @param targetCenterX The target's center x-coordinate position.
		* @param targetCenterY The target's center y-coordinate position.
		* @param targetCenterZ The target's center z-coordinate position.
		* @param upX The up vector x-coordinate value.
		* @param upY The up vector y-coordinate value.
		* @param upZ The up vector z-coordinate value.
		* @param dst A matrix4 to store the result in.
		*/
		static void createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
			float targetCenterX, float targetCenterY, float targetCenterZ,
			float upX, float upY, float upZ, matrix4* dst) {
			vector4 eye(eyePositionX, eyePositionY, eyePositionZ);
			vector4 target(targetPositionX, targetPositionY, targetPositionZ);
			vector4 up(upX, upY, upZ);
			up.normalize();

			vector4 zaxis;
			Vec3::subtract(eye, target, &zaxis);
			zaxis.normalize();

			vector4 xaxis;
			Vec3::cross(up, zaxis, &xaxis);
			xaxis.normalize();

			vector4 yaxis;
			Vec3::cross(zaxis, xaxis, &yaxis);
			yaxis.normalize();

			dst->m[0] = xaxis.x;
			dst->m[1] = yaxis.x;
			dst->m[2] = zaxis.x;
			dst->m[3] = 0.0f;

			dst->m[4] = xaxis.y;
			dst->m[5] = yaxis.y;
			dst->m[6] = zaxis.y;
			dst->m[7] = 0.0f;

			dst->m[8] = xaxis.z;
			dst->m[9] = yaxis.z;
			dst->m[10] = zaxis.z;
			dst->m[11] = 0.0f;

			dst->m[12] = -vector4::dot(xaxis, eye);
			dst->m[13] = -vector4::dot(yaxis, eye);
			dst->m[14] = -vector4::dot(zaxis, eye);
			dst->m[15] = 1.0f;
		}

		/**
		* Builds a perspective projection matrix4 based on a field of view and returns by value.
		*
		* Projection space refers to the space after applying projection transformation from view space.
		* After the projection transformation, visible content has x- and y-coordinates ranging from -1 to 1,
		* and a z-coordinate ranging from 0 to 1. To obtain the viewable area (in world space) of a scene,
		* create a BoundingFrustum and pass the combined view and projection matrix4 to the constructor.
		*
		* @param fieldOfView The field of view in the y direction (in degrees).
		* @param aspectRatio The aspect ratio, defined as view space width divided by height.
		* @param zNearPlane The distance to the near view plane.
		* @param zFarPlane The distance to the far view plane.
		* @param dst A matrix4 to store the result in.
		*/
		static void createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane, matrix4* dst)
		{
			GP_ASSERT(dst);
			GP_ASSERT(zFarPlane != zNearPlane);

			float f_n = 1.0f / (zFarPlane - zNearPlane);
			float theta = MATH_DEG_TO_RAD(fieldOfView) * 0.5f;
			if (std::abs(std::fmod(theta, MATH_PIOVER2)) < MATH_EPSILON)
			{
				CCLOGERROR("Invalid field of view value (%f) causes attempted calculation tan(%f), which is undefined.", fieldOfView, theta);
				return;
			}
			float divisor = std::tan(theta);
			GP_ASSERT(divisor);
			float factor = 1.0f / divisor;

			memset(dst, 0, matrix4_SIZE);

			GP_ASSERT(aspectRatio);
			dst->m[0] = (1.0f / aspectRatio) * factor;
			dst->m[5] = factor;
			dst->m[10] = (-(zFarPlane + zNearPlane)) * f_n;
			dst->m[11] = -1.0f;
			dst->m[14] = -2.0f * zFarPlane * zNearPlane * f_n;
		}

		/**
		* Creates an orthographic projection matrix4.
		*
		* @param width The width of the view.
		* @param height The height of the view.
		* @param zNearPlane The minimum z-value of the view volume.
		* @param zFarPlane The maximum z-value of the view volume.
		* @param dst A matrix4 to store the result in.
		*/
		static void createOrthographic(float width, float height, float zNearPlane, float zFarPlane, matrix4* dst)
		{
			float halfWidth = width / 2.0f;
			float halfHeight = height / 2.0f;
			createOrthographicOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane, dst);
		}

		/**
		* Creates an orthographic projection matrix4.
		*
		* Projection space refers to the space after applying
		* projection transformation from view space. After the
		* projection transformation, visible content has
		* x and y coordinates ranging from -1 to 1, and z coordinates
		* ranging from 0 to 1.
		*
		* Unlike perspective projection, in orthographic projection
		* there is no perspective foreshortening.
		*
		* The viewable area of this orthographic projection extends
		* from left to right on the x-axis, bottom to top on the y-axis,
		* and zNearPlane to zFarPlane on the z-axis. These values are
		* relative to the position and x, y, and z-axes of the view.
		* To obtain the viewable area (in world space) of a scene,
		* create a BoundingFrustum and pass the combined view and
		* projection matrix4 to the constructor.
		*
		* @param left The minimum x-value of the view volume.
		* @param right The maximum x-value of the view volume.
		* @param bottom The minimum y-value of the view volume.
		* @param top The maximum y-value of the view volume.
		* @param zNearPlane The minimum z-value of the view volume.
		* @param zFarPlane The maximum z-value of the view volume.
		* @param dst A matrix4 to store the result in.
		*/
		static void createOrthographicOffCenter(float left, float right, float bottom, float top,
			float zNearPlane, float zFarPlane, matrix4* dst)
		{
			GP_ASSERT(dst);
			GP_ASSERT(right != left);
			GP_ASSERT(top != bottom);
			GP_ASSERT(zFarPlane != zNearPlane);

			memset(dst, 0, matrix4_SIZE);
			dst->m[0] = 2 / (right - left);
			dst->m[5] = 2 / (top - bottom);
			dst->m[10] = 2 / (zNearPlane - zFarPlane);

			dst->m[12] = (left + right) / (left - right);
			dst->m[13] = (top + bottom) / (bottom - top);
			dst->m[14] = (zNearPlane + zFarPlane) / (zNearPlane - zFarPlane);
			dst->m[15] = 1;
		}

		/**
		* Creates a spherical billboard that rotates around a specified object position.
		*
		* This method computes the facing direction of the billboard from the object position
		* and camera position. When the object and camera positions are too close, the matrix4
		* will not be accurate. To avoid this problem, this method defaults to the identity
		* rotation if the positions are too close. (See the other overload of createBillboard
		* for an alternative approach).
		*
		* @param objectPosition The position of the object the billboard will rotate around.
		* @param cameraPosition The position of the camera.
		* @param cameraUpVector The up vector of the camera.
		* @param dst A matrix4 to store the result in.
		*/
		static void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
			const Vec3& cameraUpVector, matrix4* dst)
		{
			createBillboardHelper(objectPosition, cameraPosition, cameraUpVector, nullptr, dst);
		}

		/**
		* Creates a spherical billboard that rotates around a specified object position with
		* provision for a safe default orientation.
		*
		* This method computes the facing direction of the billboard from the object position
		* and camera position. When the object and camera positions are too close, the matrix4
		* will not be accurate. To avoid this problem, this method uses the specified camera
		* forward vector if the positions are too close. (See the other overload of createBillboard
		* for an alternative approach).
		*
		* @param objectPosition The position of the object the billboard will rotate around.
		* @param cameraPosition The position of the camera.
		* @param cameraUpVector The up vector of the camera.
		* @param cameraForwardVector The forward vector of the camera, used if the positions are too close.
		* @param dst A matrix4 to store the result in.
		*/
		static void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
			const Vec3& cameraUpVector, const Vec3& cameraForwardVector,
			matrix4* dst)
		{
			createBillboardHelper(objectPosition, cameraPosition, cameraUpVector, &cameraForwardVector, dst);
		}

		//Fills in an existing matrix4 so that it reflects the coordinate system about a specified Plane.
		//plane The Plane about which to create a reflection.
		//dst A matrix4 to store the result in.
		//static void createReflection(const Plane& plane, matrix4* dst);

		/**
		* Creates a scale matrix4.
		*
		* @param scale The amount to scale.
		* @param dst A matrix4 to store the result in.
		*/
		static void createScale(const Vec3& scale, matrix4* dst)
		{
			GP_ASSERT(dst);

			memcpy(dst, &IDENTITY, matrix4_SIZE);

			dst->m[0] = scale.x;
			dst->m[5] = scale.y;
			dst->m[10] = scale.z;
		}

		/**
		* Creates a scale matrix4.
		*
		* @param xScale The amount to scale along the x-axis.
		* @param yScale The amount to scale along the y-axis.
		* @param zScale The amount to scale along the z-axis.
		* @param dst A matrix4 to store the result in.
		*/
		static void createScale(float xScale, float yScale, float zScale, matrix4* dst)
		{
			GP_ASSERT(dst);

			memcpy(dst, &IDENTITY, matrix4_SIZE);

			dst->m[0] = xScale;
			dst->m[5] = yScale;
			dst->m[10] = zScale;
		}

		/**
		* Creates a rotation matrix4 from the specified quaternion.
		*
		* @param quat A quaternion describing a 3D orientation.
		* @param dst A matrix4 to store the result in.
		*/
		static void createRotation(const Quaternion& quat, matrix4* dst)
		{
			GP_ASSERT(dst);

			float x2 = q.x + q.x;
			float y2 = q.y + q.y;
			float z2 = q.z + q.z;

			float xx2 = q.x * x2;
			float yy2 = q.y * y2;
			float zz2 = q.z * z2;
			float xy2 = q.x * y2;
			float xz2 = q.x * z2;
			float yz2 = q.y * z2;
			float wx2 = q.w * x2;
			float wy2 = q.w * y2;
			float wz2 = q.w * z2;

			dst->m[0] = 1.0f - yy2 - zz2;
			dst->m[1] = xy2 + wz2;
			dst->m[2] = xz2 - wy2;
			dst->m[3] = 0.0f;

			dst->m[4] = xy2 - wz2;
			dst->m[5] = 1.0f - xx2 - zz2;
			dst->m[6] = yz2 + wx2;
			dst->m[7] = 0.0f;

			dst->m[8] = xz2 + wy2;
			dst->m[9] = yz2 - wx2;
			dst->m[10] = 1.0f - xx2 - yy2;
			dst->m[11] = 0.0f;

			dst->m[12] = 0.0f;
			dst->m[13] = 0.0f;
			dst->m[14] = 0.0f;
			dst->m[15] = 1.0f;
		}

		/**
		* Creates a rotation matrix4 from the specified axis and angle.
		*
		* @param axis A vector describing the axis to rotate about.
		* @param angle The angle (in radians).
		* @param dst A matrix4 to store the result in.
		*/
		static void createRotation(const Vec3& axis, float angle, matrix4* dst)
		{
			GP_ASSERT(dst);

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			// Make sure the input axis is normalized.
			float n = x*x + y*y + z*z;
			if (n != 1.0f)
			{
				// Not normalized.
				n = std::sqrt(n);
				// Prevent divide too close to zero.
				if (n > 0.000001f)
				{
					n = 1.0f / n;
					x *= n;
					y *= n;
					z *= n;
				}
			}

			float c = std::cos(angle);
			float s = std::sin(angle);

			float t = 1.0f - c;
			float tx = t * x;
			float ty = t * y;
			float tz = t * z;
			float txy = tx * y;
			float txz = tx * z;
			float tyz = ty * z;
			float sx = s * x;
			float sy = s * y;
			float sz = s * z;

			dst->m[0] = c + tx*x;
			dst->m[1] = txy + sz;
			dst->m[2] = txz - sy;
			dst->m[3] = 0.0f;

			dst->m[4] = txy - sz;
			dst->m[5] = c + ty*y;
			dst->m[6] = tyz + sx;
			dst->m[7] = 0.0f;

			dst->m[8] = txz + sy;
			dst->m[9] = tyz - sx;
			dst->m[10] = c + tz*z;
			dst->m[11] = 0.0f;

			dst->m[12] = 0.0f;
			dst->m[13] = 0.0f;
			dst->m[14] = 0.0f;
			dst->m[15] = 1.0f;
		}

		/**
		* Creates a matrix4 describing a rotation around the x-axis.
		*
		* @param angle The angle of rotation (in radians).
		* @param dst A matrix4 to store the result in.
		*/
		static void createRotationX(float angle, matrix4* dst)
		{
			GP_ASSERT(dst);

			memcpy(dst, &IDENTITY, matrix4_SIZE);

			float c = std::cos(angle);
			float s = std::sin(angle);

			dst->m[5] = c;
			dst->m[6] = s;
			dst->m[9] = -s;
			dst->m[10] = c;
		}

		/**
		* Creates a matrix4 describing a rotation around the y-axis.
		*
		* @param angle The angle of rotation (in radians).
		* @param dst A matrix4 to store the result in.
		*/
		static void createRotationY(float angle, matrix4* dst)
		{
			GP_ASSERT(dst);

			memcpy(dst, &IDENTITY, matrix4_SIZE);

			float c = std::cos(angle);
			float s = std::sin(angle);

			dst->m[0] = c;
			dst->m[2] = -s;
			dst->m[8] = s;
			dst->m[10] = c;
		}

		/**
		* Creates a matrix4 describing a rotation around the z-axis.
		*
		* @param angle The angle of rotation (in radians).
		* @param dst A matrix4 to store the result in.
		*/
		static void createRotationZ(float angle, matrix4* dst)
		{
			GP_ASSERT(dst);

			memcpy(dst, &IDENTITY, matrix4_SIZE);

			float c = std::cos(angle);
			float s = std::sin(angle);

			dst->m[0] = c;
			dst->m[1] = s;
			dst->m[4] = -s;
			dst->m[5] = c;
		}

		/**
		* Creates a translation matrix4.
		*
		* @param translation The translation.
		* @param dst A matrix4 to store the result in.
		*/
		static void createTranslation(const Vec3& translation, matrix4* dst)
		{
			GP_ASSERT(dst);

			memcpy(dst, &IDENTITY, matrix4_SIZE);

			dst->m[12] = translation.x;
			dst->m[13] = translation.y;
			dst->m[14] = translation.z;
		}

		/**
		* Creates a translation matrix4.
		*
		* @param xTranslation The translation on the x-axis.
		* @param yTranslation The translation on the y-axis.
		* @param zTranslation The translation on the z-axis.
		* @param dst A matrix4 to store the result in.
		*/
		static void createTranslation(float xTranslation, float yTranslation, float zTranslation, matrix4* dst)
		{
			GP_ASSERT(dst);

			memcpy(dst, &IDENTITY, matrix4_SIZE);

			dst->m[12] = xTranslation;
			dst->m[13] = yTranslation;
			dst->m[14] = zTranslation;
		}

		/**
		* Adds a scalar value to each component of this matrix4.
		*
		* @param scalar The scalar to add.
		*/
		void add(float scalar)
		{
			add(scalar, this);
		}

		/**
		* Adds a scalar value to each component of this matrix4 and stores the result in dst.
		*
		* @param scalar The scalar value to add.
		* @param dst A matrix4 to store the result in.
		*/
		void add(float scalar, matrix4* dst)
		{
			GP_ASSERT(dst);
#ifdef __SSE__
			MathUtil::addmatrix4(col, scalar, dst->col);
#else
			MathUtil::addmatrix4(m, scalar, dst->m);
#endif
		}

		/**
		* Adds the specified matrix4 to this matrix4.
		*
		* @param mat The matrix4 to add.
		*/
		void add(const matrix4& mat)
		{
			add(*this, mat, this);
		}

		/**
		* Adds the specified matrices and stores the result in dst.
		*
		* @param m1 The first matrix4.
		* @param m2 The second matrix4.
		* @param dst The destination matrix4 to add to.
		*/
		static void add(const matrix4& m1, const matrix4& m2, matrix4* dst)
		{
			GP_ASSERT(dst);
#ifdef __SSE__
			MathUtil::addmatrix4(m1.col, m2.col, dst->col);
#else
			MathUtil::addmatrix4(m1.m, m2.m, dst->m);
#endif
		}

		/**
		* Decomposes the scale, rotation and translation components of this matrix4.
		*
		* @param scale The scale.
		* @param rotation The rotation.
		* @param translation The translation.
		*/
		bool decompose(Vec3* scale, Quaternion* rotation, Vec3* translation) const
		{
			if (translation)
			{
				// Extract the translation.
				translation->x = m[12];
				translation->y = m[13];
				translation->z = m[14];
			}

			// Nothing left to do.
			if (scale == nullptr && rotation == nullptr)
				return true;

			// Extract the scale.
			// This is simply the length of each axis (row/column) in the matrix4.
			Vec3 xaxis(m[0], m[1], m[2]);
			float scaleX = xaxis.length();

			Vec3 yaxis(m[4], m[5], m[6]);
			float scaleY = yaxis.length();

			Vec3 zaxis(m[8], m[9], m[10]);
			float scaleZ = zaxis.length();

			// Determine if we have a negative scale (true if determinant is less than zero).
			// In this case, we simply negate a single axis of the scale.
			float det = determinant();
			if (det < 0)
				scaleZ = -scaleZ;

			if (scale)
			{
				scale->x = scaleX;
				scale->y = scaleY;
				scale->z = scaleZ;
			}

			// Nothing left to do.
			if (rotation == nullptr)
				return true;

			// Scale too close to zero, can't decompose rotation.
			if (scaleX < MATH_TOLERANCE || scaleY < MATH_TOLERANCE || std::abs(scaleZ) < MATH_TOLERANCE)
				return false;

			float rn;

			// Factor the scale out of the matrix4 axes.
			rn = 1.0f / scaleX;
			xaxis.x *= rn;
			xaxis.y *= rn;
			xaxis.z *= rn;

			rn = 1.0f / scaleY;
			yaxis.x *= rn;
			yaxis.y *= rn;
			yaxis.z *= rn;

			rn = 1.0f / scaleZ;
			zaxis.x *= rn;
			zaxis.y *= rn;
			zaxis.z *= rn;

			// Now calculate the rotation from the resulting matrix4 (axes).
			float trace = xaxis.x + yaxis.y + zaxis.z + 1.0f;

			if (trace > MATH_EPSILON)
			{
				float s = 0.5f / std::sqrt(trace);
				rotation->w = 0.25f / s;
				rotation->x = (yaxis.z - zaxis.y) * s;
				rotation->y = (zaxis.x - xaxis.z) * s;
				rotation->z = (xaxis.y - yaxis.x) * s;
			}
			else
			{
				// Note: since xaxis, yaxis, and zaxis are normalized, 
				// we will never divide by zero in the code below.
				if (xaxis.x > yaxis.y && xaxis.x > zaxis.z)
				{
					float s = 0.5f / std::sqrt(1.0f + xaxis.x - yaxis.y - zaxis.z);
					rotation->w = (yaxis.z - zaxis.y) * s;
					rotation->x = 0.25f / s;
					rotation->y = (yaxis.x + xaxis.y) * s;
					rotation->z = (zaxis.x + xaxis.z) * s;
				}
				else if (yaxis.y > zaxis.z)
				{
					float s = 0.5f / std::sqrt(1.0f + yaxis.y - xaxis.x - zaxis.z);
					rotation->w = (zaxis.x - xaxis.z) * s;
					rotation->x = (yaxis.x + xaxis.y) * s;
					rotation->y = 0.25f / s;
					rotation->z = (zaxis.y + yaxis.z) * s;
				}
				else
				{
					float s = 0.5f / std::sqrt(1.0f + zaxis.z - xaxis.x - yaxis.y);
					rotation->w = (xaxis.y - yaxis.x) * s;
					rotation->x = (zaxis.x + xaxis.z) * s;
					rotation->y = (zaxis.y + yaxis.z) * s;
					rotation->z = 0.25f / s;
				}
			}

			return true;
		}

		/**
		* Computes the determinant of this matrix4.
		*
		* @return The determinant.
		*/
		float determinant() const
		{
			float a0 = m[0] * m[5] - m[1] * m[4];
			float a1 = m[0] * m[6] - m[2] * m[4];
			float a2 = m[0] * m[7] - m[3] * m[4];
			float a3 = m[1] * m[6] - m[2] * m[5];
			float a4 = m[1] * m[7] - m[3] * m[5];
			float a5 = m[2] * m[7] - m[3] * m[6];
			float b0 = m[8] * m[13] - m[9] * m[12];
			float b1 = m[8] * m[14] - m[10] * m[12];
			float b2 = m[8] * m[15] - m[11] * m[12];
			float b3 = m[9] * m[14] - m[10] * m[13];
			float b4 = m[9] * m[15] - m[11] * m[13];
			float b5 = m[10] * m[15] - m[11] * m[14];

			// Calculate the determinant.
			return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
		}

		/**
		* Gets the scalar component of this matrix4 in the specified vector.
		*
		* If the scalar component of this matrix4 has negative parts,
		* it is not possible to always extract the exact scalar component;
		* instead, a scale vector that is mathematically equivalent to the
		* original scale vector is extracted and returned.
		*
		* @param scale A vector to receive the scale.
		*/
		void getScale(Vec3* scale) const
		{
			decompose(scale, nullptr, nullptr);
		}

		/**
		* Gets the rotational component of this matrix4 in the specified quaternion.
		*
		* @param rotation A quaternion to receive the rotation.
		*
		* @return true if the rotation is successfully extracted, false otherwise.
		*/
		bool getRotation(Quaternion* rotation) const
		{
			return decompose(nullptr, rotation, nullptr);
		}

		/**
		* Gets the translational component of this matrix4 in the specified vector.
		*
		* @param translation A vector to receive the translation.
		*/
		void getTranslation(Vec3* translation) const
		{
			decompose(nullptr, nullptr, translation);
		}

		/**
		* Gets the up vector of this matrix4.
		*
		* @param dst The destination vector.
		*/
		void getUpVector(Vec3* dst) const
		{
			GP_ASSERT(dst);

			dst->x = m[4];
			dst->y = m[5];
			dst->z = m[6];
		}

		/**
		* Gets the down vector of this matrix4.
		*
		* @param dst The destination vector.
		*/
		void getDownVector(Vec3* dst) const
		{
			GP_ASSERT(dst);

			dst->x = -m[4];
			dst->y = -m[5];
			dst->z = -m[6];
		}

		/**
		* Gets the left vector of this matrix4.
		*
		* @param dst The destination vector.
		*/
		void getLeftVector(Vec3* dst) const
		{
			GP_ASSERT(dst);

			dst->x = -m[0];
			dst->y = -m[1];
			dst->z = -m[2];
		}

		/**
		* Gets the right vector of this matrix4.
		*
		* @param dst The destination vector.
		*/
		void getRightVector(Vec3* dst) const
		{
			GP_ASSERT(dst);

			dst->x = m[0];
			dst->y = m[1];
			dst->z = m[2];
		}

		/**
		* Gets the forward vector of this matrix4.
		*
		* @param dst The destination vector.
		*/
		void getForwardVector(Vec3* dst) const
		{
			GP_ASSERT(dst);

			dst->x = -m[8];
			dst->y = -m[9];
			dst->z = -m[10];
		}

		/**
		* Gets the backward vector of this matrix4.
		*
		* @param dst The destination vector.
		*/
		void getBackVector(Vec3* dst) const
		{
			GP_ASSERT(dst);

			dst->x = m[8];
			dst->y = m[9];
			dst->z = m[10];
		}

		/**
		* Inverts this matrix4.
		*
		* @return true if the matrix4 can be inverted, false otherwise.
		*/
		bool inverse()
		{
			float a0 = m[0] * m[5] - m[1] * m[4];
			float a1 = m[0] * m[6] - m[2] * m[4];
			float a2 = m[0] * m[7] - m[3] * m[4];
			float a3 = m[1] * m[6] - m[2] * m[5];
			float a4 = m[1] * m[7] - m[3] * m[5];
			float a5 = m[2] * m[7] - m[3] * m[6];
			float b0 = m[8] * m[13] - m[9] * m[12];
			float b1 = m[8] * m[14] - m[10] * m[12];
			float b2 = m[8] * m[15] - m[11] * m[12];
			float b3 = m[9] * m[14] - m[10] * m[13];
			float b4 = m[9] * m[15] - m[11] * m[13];
			float b5 = m[10] * m[15] - m[11] * m[14];

			// Calculate the determinant.
			float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

			// Close to zero, can't invert.
			if (std::abs(det) <= MATH_TOLERANCE)
				return false;

			// Support the case where m == dst.
			matrix4 inverse;
			inverse.m[0] = m[5] * b5 - m[6] * b4 + m[7] * b3;
			inverse.m[1] = -m[1] * b5 + m[2] * b4 - m[3] * b3;
			inverse.m[2] = m[13] * a5 - m[14] * a4 + m[15] * a3;
			inverse.m[3] = -m[9] * a5 + m[10] * a4 - m[11] * a3;

			inverse.m[4] = -m[4] * b5 + m[6] * b2 - m[7] * b1;
			inverse.m[5] = m[0] * b5 - m[2] * b2 + m[3] * b1;
			inverse.m[6] = -m[12] * a5 + m[14] * a2 - m[15] * a1;
			inverse.m[7] = m[8] * a5 - m[10] * a2 + m[11] * a1;

			inverse.m[8] = m[4] * b4 - m[5] * b2 + m[7] * b0;
			inverse.m[9] = -m[0] * b4 + m[1] * b2 - m[3] * b0;
			inverse.m[10] = m[12] * a4 - m[13] * a2 + m[15] * a0;
			inverse.m[11] = -m[8] * a4 + m[9] * a2 - m[11] * a0;

			inverse.m[12] = -m[4] * b3 + m[5] * b1 - m[6] * b0;
			inverse.m[13] = m[0] * b3 - m[1] * b1 + m[2] * b0;
			inverse.m[14] = -m[12] * a3 + m[13] * a1 - m[14] * a0;
			inverse.m[15] = m[8] * a3 - m[9] * a1 + m[10] * a0;

			multiply(inverse, 1.0f / det, this);

			return true;
		}

		/**
		* Get the inversed matrix4.
		*/
		matrix4 getInversed() const
		{
			matrix4 mat(*this);
			mat.inverse();
			return mat;
		}

		/**
		* Determines if this matrix4 is equal to the identity matrix4.
		*
		* @return true if the matrix4 is an identity matrix4, false otherwise.
		*/
		bool isIdentity() const
		{
			return (memcmp(m, &IDENTITY, matrix4_SIZE) == 0);
		}

		/**
		* Multiplies the components of this matrix4 by the specified scalar.
		*
		* @param scalar The scalar value.
		*/
		void multiply(float scalar)
		{
			multiply(scalar, this);
		}

		/**
		* Multiplies the components of this matrix4 by a scalar and stores the result in dst.
		*
		* @param scalar The scalar value.
		* @param dst A matrix4 to store the result in.
		*/
		void multiply(float scalar, matrix4* dst) const
		{
			multiply(*this, scalar, dst);
		}

		/**
		* Multiplies the components of the specified matrix4 by a scalar and stores the result in dst.
		*
		* @param mat The matrix4.
		* @param scalar The scalar value.
		* @param dst A matrix4 to store the result in.
		*/
		static void multiply(const matrix4& mat, float scalar, matrix4* dst)
		{
			GP_ASSERT(dst);
#ifdef __SSE__
			MathUtil::multiplymatrix4(m.col, scalar, dst->col);
#else
			MathUtil::multiplymatrix4(m.m, scalar, dst->m);
#endif
		}

		/**
		* Multiplies this matrix4 by the specified one.
		*
		* @param mat The matrix4 to multiply.
		*/
		void multiply(const matrix4& mat)
		{
			multiply(*this, mat, this);
		}

		/**
		* Multiplies m1 by m2 and stores the result in dst.
		*
		* @param m1 The first matrix4 to multiply.
		* @param m2 The second matrix4 to multiply.
		* @param dst A matrix4 to store the result in.
		*/
		static void multiply(const matrix4& m1, const matrix4& m2, matrix4* dst)
		{
			GP_ASSERT(dst);
#ifdef __SSE__
			MathUtil::multiplymatrix4(m1.col, m2.col, dst->col);
#else
			MathUtil::multiplymatrix4(m1.m, m2.m, dst->m);
#endif
		}

		/**
		* Negates this matrix4.
		*/
		void negate()
		{
#ifdef __SSE__
			MathUtil::negatematrix4(col, col);
#else
			MathUtil::negatematrix4(m, m);
#endif
		}

		/**
		Get the Negated matrix4.
		*/
		matrix4 getNegated() const
		{
			matrix4 mat(*this);
			mat.negate();
			return mat;
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified quaternion rotation.
		*
		* @param q The quaternion to rotate by.
		*/
		void rotate(const Quaternion& q)
		{
			rotate(q, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified quaternion rotation and stores the result in dst.
		*
		* @param q The quaternion to rotate by.
		* @param dst A matrix4 to store the result in.
		*/
		void rotate(const Quaternion& q, matrix4* dst) const
		{
			matrix4 r;
			createRotation(q, &r);
			multiply(*this, r, dst);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified rotation about the specified axis.
		*
		* @param axis The axis to rotate about.
		* @param angle The angle (in radians).
		*/
		void rotate(const Vec3& axis, float angle)
		{
			rotate(axis, angle, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the specified
		* rotation about the specified axis and stores the result in dst.
		*
		* @param axis The axis to rotate about.
		* @param angle The angle (in radians).
		* @param dst A matrix4 to store the result in.
		*/
		void rotate(const Vec3& axis, float angle, matrix4* dst) const
		{
			matrix4 r;
			createRotation(axis, angle, &r);
			multiply(*this, r, dst);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified rotation around the x-axis.
		*
		* @param angle The angle (in radians).
		*/
		void rotateX(float angle)
		{
			rotateX(angle, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified rotation around the x-axis and stores the result in dst.
		*
		* @param angle The angle (in radians).
		* @param dst A matrix4 to store the result in.
		*/
		void rotateX(float angle, matrix4* dst) const
		{
			matrix4 r;
			createRotationX(angle, &r);
			multiply(*this, r, dst);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified rotation around the y-axis.
		*
		* @param angle The angle (in radians).
		*/
		void rotateY(float angle)
		{
			rotateY(angle, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified rotation around the y-axis and stores the result in dst.
		*
		* @param angle The angle (in radians).
		* @param dst A matrix4 to store the result in.
		*/
		void rotateY(float angle, matrix4* dst) const
		{
			matrix4 r;
			createRotationY(angle, &r);
			multiply(*this, r, dst);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified rotation around the z-axis.
		*
		* @param angle The angle (in radians).
		*/
		void rotateZ(float angle)
		{
			rotateZ(angle, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified rotation around the z-axis and stores the result in dst.
		*
		* @param angle The angle (in radians).
		* @param dst A matrix4 to store the result in.
		*/
		void rotateZ(float angle, matrix4* dst) const
		{
			matrix4 r;
			createRotationZ(angle, &r);
			multiply(*this, r, dst);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified scale transformation.
		*
		* @param value The amount to scale along all axes.
		*/
		void scale(float value)
		{
			scale(value, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified scale transformation and stores the result in dst.
		*
		* @param value The amount to scale along all axes.
		* @param dst A matrix4 to store the result in.
		*/
		void scale(float value, matrix4* dst) const
		{
			scale(value, value, value, dst);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified scale transformation.
		*
		* @param xScale The amount to scale along the x-axis.
		* @param yScale The amount to scale along the y-axis.
		* @param zScale The amount to scale along the z-axis.
		*/
		void scale(float xScale, float yScale, float zScale)
		{
			scale(xScale, yScale, zScale, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified scale transformation and stores the result in dst.
		*
		* @param xScale The amount to scale along the x-axis.
		* @param yScale The amount to scale along the y-axis.
		* @param zScale The amount to scale along the z-axis.
		* @param dst A matrix4 to store the result in.
		*/
		void scale(float xScale, float yScale, float zScale, matrix4* dst) const
		{
			matrix4 s;
			createScale(xScale, yScale, zScale, &s);
			multiply(*this, s, dst);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified scale transformation.
		*
		* @param s The scale values along the x, y and z axes.
		*/
		void scale(const Vec3& s)
		{
			scale(s.x, s.y, s.z, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified scale transformation and stores the result in dst.
		*
		* @param s The scale values along the x, y and z axes.
		* @param dst A matrix4 to store the result in.
		*/
		void scale(const Vec3& s, matrix4* dst) const
		{
			scale(s.x, s.y, s.z, dst);
		}

		/**
		* Sets the values of this matrix4.
		*
		* @param m11 The first element of the first row.
		* @param m12 The second element of the first row.
		* @param m13 The third element of the first row.
		* @param m14 The fourth element of the first row.
		* @param m21 The first element of the second row.
		* @param m22 The second element of the second row.
		* @param m23 The third element of the second row.
		* @param m24 The fourth element of the second row.
		* @param m31 The first element of the third row.
		* @param m32 The second element of the third row.
		* @param m33 The third element of the third row.
		* @param m34 The fourth element of the third row.
		* @param m41 The first element of the fourth row.
		* @param m42 The second element of the fourth row.
		* @param m43 The third element of the fourth row.
		* @param m44 The fourth element of the fourth row.
		*/
		void set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

		/**
		* Sets the values of this matrix4 to those in the specified column-major array.
		*
		* @param mat An array containing 16 elements in column-major format.
		*/
		void set(const float* mat)
		{
			GP_ASSERT(mat);
			memcpy(this->m, mat, matrix4_SIZE);
		}

		/**
		* Sets the values of this matrix4 to those of the specified matrix4.
		*
		* @param mat The source matrix4.
		*/
		void set(const matrix4& mat)
		{
			memcpy(this->m, mat.m, matrix4_SIZE);
		}

		/**
		* Sets this matrix4 to the identity matrix4.
		*/
		void setIdentity()
		{
			memcpy(m, &IDENTITY, matrix4_SIZE);
		}

		/**
		* Sets all elements of the current matrix4 to zero.
		*/
		void setZero()
		{
			memset(m, 0, matrix4_SIZE);
		}

		/**
		* Subtracts the specified matrix4 from the current matrix4.
		*
		* @param mat The matrix4 to subtract.
		*/
		void subtract(const matrix4& mat)
		{
			subtract(*this, mat, this);
		}

		/**
		* Subtracts the specified matrix4 from the current matrix4.
		*
		* @param m1 The first matrix4.
		* @param m2 The second matrix4.
		* @param dst A matrix4 to store the result in.
		*/
		static void subtract(const matrix4& m1, const matrix4& m2, matrix4* dst)
		{
			GP_ASSERT(dst);
#ifdef __SSE__
			MathUtil::subtractmatrix4(m1.col, m2.col, dst->col);
#else
			MathUtil::subtractmatrix4(m1.m, m2.m, dst->m);
#endif
		}

		/**
		* Transforms the specified point by this matrix4.
		*
		* The result of the transformation is stored directly into point.
		*
		* @param point The point to transform and also a vector to hold the result in.
		*/
		inline void transformPoint(Vec3* point) const;

		/**
		* Transforms the specified point by this matrix4, and stores
		* the result in dst.
		*
		* @param point The point to transform.
		* @param dst A vector to store the transformed point in.
		*/
		inline void transformPoint(const Vec3& point, Vec3* dst) const;

		/**
		* Transforms the specified vector by this matrix4 by
		* treating the fourth (w) coordinate as zero.
		*
		* The result of the transformation is stored directly into vector.
		*
		* @param vector The vector to transform and also a vector to hold the result in.
		*/
		void transformVector(Vec3* vector) const
		{
			GP_ASSERT(vector);
			transformVector(vector->x, vector->y, vector->z, 0.0f, vector);
		}

		/**
		* Transforms the specified vector by this matrix4 by
		* treating the fourth (w) coordinate as zero, and stores the
		* result in dst.
		*
		* @param vector The vector to transform.
		* @param dst A vector to store the transformed vector in.
		*/
		void transformVector(const Vec3& vector, Vec3* dst) const
		{
			transformVector(vector.x, vector.y, vector.z, 0.0f, dst);
		}

		/**
		* Transforms the specified vector by this matrix4.
		*
		* @param x The vector x-coordinate to transform by.
		* @param y The vector y-coordinate to transform by.
		* @param z The vector z-coordinate to transform by.
		* @param w The vector w-coordinate to transform by.
		* @param dst A vector to store the transformed point in.
		*/
		void transformVector(float x, float y, float z, float w, Vec3* dst) const
		{
			GP_ASSERT(dst);

			MathUtil::transformVec4(m, x, y, z, w, (float*)dst);
		}

		/**
		* Transforms the specified vector by this matrix4.
		*
		* The result of the transformation is stored directly into vector.
		*
		* @param vector The vector to transform.
		*/
		void transformVector(Vec4* vector) const
		{
			GP_ASSERT(vector);
			transformVector(*vector, vector);
		}

		/**
		* Transforms the specified vector by this matrix4.
		*
		* @param vector The vector to transform.
		* @param dst A vector to store the transformed point in.
		*/
		void transformVector(const Vec4& vector, Vec4* dst) const
		{
			GP_ASSERT(dst);
#ifdef __SSE__
			MathUtil::transformVec4(col, vector.v, dst->v);
#else
			MathUtil::transformVec4(m, (const float*)&vector, (float*)dst);
#endif
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified translation.
		*
		* @param x The amount to translate along the x-axis.
		* @param y The amount to translate along the y-axis.
		* @param z The amount to translate along the z-axis.
		*/
		void translate(float x, float y, float z)
		{
			translate(x, y, z, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified translation and stores the result in dst.
		*
		* @param x The amount to translate along the x-axis.
		* @param y The amount to translate along the y-axis.
		* @param z The amount to translate along the z-axis.
		* @param dst A matrix4 to store the result in.
		*/
		void translate(float x, float y, float z, matrix4* dst) const
		{
			matrix4 t;
			createTranslation(x, y, z, &t);
			multiply(*this, t, dst);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified translation.
		*
		* @param t The translation values along the x, y and z axes.
		*/
		void translate(const Vec3& t)
		{
			translate(t.x, t.y, t.z, this);
		}

		/**
		* Post-multiplies this matrix4 by the matrix4 corresponding to the
		* specified translation and stores the result in dst.
		*
		* @param t The translation values along the x, y and z axes.
		* @param dst A matrix4 to store the result in.
		*/
		void translate(const Vec3& t, matrix4* dst) const
		{
			translate(t.x, t.y, t.z, dst);
		}

		/**
		* Transposes this matrix4.
		*/
		void transpose()
		{
#ifdef __SSE__
			MathUtil::transposematrix4(col, col);
#else
			MathUtil::transposematrix4(m, m);
#endif
		}

		/**
		* Get the Transposed matrix4.
		*/
		matrix4 getTransposed() const
		{
			matrix4 mat(*this);
			mat.transpose();
			return mat;
		}

		/**
		* Calculates the sum of this matrix4 with the given matrix4.
		*
		* Note: this does not modify this matrix4.
		*
		* @param mat The matrix4 to add.
		* @return The matrix4 sum.
		*/
		inline matrix4 operator+(const matrix4& mat) const;

		/**
		* Adds the given matrix4 to this matrix4.
		*
		* @param mat The matrix4 to add.
		* @return This matrix4, after the addition occurs.
		*/
		inline matrix4& operator+=(const matrix4& mat);

		/**
		* Calculates the difference of this matrix4 with the given matrix4.
		*
		* Note: this does not modify this matrix4.
		*
		* @param mat The matrix4 to subtract.
		* @return The matrix4 difference.
		*/
		inline matrix4 operator-(const matrix4& mat) const;

		/**
		* Subtracts the given matrix4 from this matrix4.
		*
		* @param mat The matrix4 to subtract.
		* @return This matrix4, after the subtraction occurs.
		*/
		inline matrix4& operator-=(const matrix4& mat);

		/**
		* Calculates the negation of this matrix4.
		*
		* Note: this does not modify this matrix4.
		*
		* @return The negation of this matrix4.
		*/
		inline matrix4 operator-() const;

		/**
		* Calculates the matrix4 product of this matrix4 with the given matrix4.
		*
		* Note: this does not modify this matrix4.
		*
		* @param mat The matrix4 to multiply by.
		* @return The matrix4 product.
		*/
		inline matrix4 operator*(const matrix4& mat) const;

		/**
		* Right-multiplies this matrix4 by the given matrix4.
		*
		* @param mat The matrix4 to multiply by.
		* @return This matrix4, after the multiplication occurs.
		*/
		inline matrix4& operator*=(const matrix4& mat);

		/** equals to a matrix4 full of zeros */
		static const matrix4 ZERO;
		/** equals to the identity matrix4 */
		static const matrix4 IDENTITY;

	private:

		static void createBillboardHelper(const Vec3& objectPosition, const Vec3& cameraPosition,
			const Vec3& cameraUpVector, const Vec3* cameraForwardVector,
			matrix4* dst)
		{
			Vec3 delta(objectPosition, cameraPosition);
			bool isSufficientDelta = delta.lengthSquared() > MATH_EPSILON;

			dst->setIdentity();
			dst->m[3] = objectPosition.x;
			dst->m[7] = objectPosition.y;
			dst->m[11] = objectPosition.z;

			// As per the contracts for the 2 variants of createBillboard, we need
			// either a safe default or a sufficient distance between object and camera.
			if (cameraForwardVector || isSufficientDelta)
			{
				Vec3 target = isSufficientDelta ? cameraPosition : (objectPosition - *cameraForwardVector);

				// A billboard is the inverse of a lookAt rotation
				matrix4 lookAt;
				createLookAt(objectPosition, target, cameraUpVector, &lookAt);
				dst->m[0] = lookAt.m[0];
				dst->m[1] = lookAt.m[4];
				dst->m[2] = lookAt.m[8];
				dst->m[4] = lookAt.m[1];
				dst->m[5] = lookAt.m[5];
				dst->m[6] = lookAt.m[9];
				dst->m[8] = lookAt.m[2];
				dst->m[9] = lookAt.m[6];
				dst->m[10] = lookAt.m[10];
			}
		}
	};
};

#endif // __DOTTH_MATRIX_HPP__