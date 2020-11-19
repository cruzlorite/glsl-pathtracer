//    Copyright(C) 2019, 2020 José María Cruz Lorite
//
//    This file is part of voxfracturer.
//
//    voxfracturer is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    voxfracturer is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with voxfracturer.  If not, see <https://www.gnu.org/licenses/>.

#ifndef VOXFRACTURER_ORBIT_CAMERA_H_
#define VOXFRACTURER_ORBIT_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace scene {

    /** Simple camera used to orbit around a lookAt position. */
    class OrbitCamera {
    public:

        /** Camera max phi angle (89,95 degress, 1.57 radians) */
        constexpr static float MAX_PHI_ANGLE = 1.57f;

        /**
         * Construct camera
         * @param[in] lookAt    Camera lookAt position
         * @param[in] theta     Orbit angle over Y axis
         * @param[in] phi       Orbit angle over X axis
         * @param[in] distance  Distance between camera eye and lookAt
         */
        OrbitCamera(const glm::vec3& lookAt = glm::vec3(0.0f),
                    float theta             = 0.0f,
                    float phi               = 0.0f,
                    float distance          = 1.0f);

        /** Get camera view matrix */
        const glm::mat4& viewMat() const;

        /**
         * Set camera lookAt position
         * @param lookAt Camera lookAt position
         */
        void setLookAt(const glm::vec3& lookAt);

        /** Get camera lookAt position */
        const glm::vec3& getLookAt() const;

        /** Get camera eye position */
        glm::vec3 getEye() const;

        /** Distance from eye to lookAt */ 
        void setDistance(float distance);

        /** Get camera distance */ 
        float getDistance() const;

        /**
         * Set camera theta rotation
         * @param theta New orbit angle over Y axis
         */ 
        void setTheta(float radians);

        /** Get camera Y axis orbit angle */ 
        float getTheta() const;

        /**
         * Set camera phi rotation.
         * @param phi New orbit angle over X axis
         */
        void setPhi(float radians);

        /** Get camera X axis orbit angle */ 
        float getPhi() const;

    private:

        /** Private method that updates view matrix */
        void _compViewMat();

        float _distance;    //!< Distance between eye and lookAt
        float _theta;       //!< Rotation over Y axis
        float _phi;         //!< Rotation over X axis

        glm::vec3 _lookAt;  //!< Camera lookAt position
        glm::vec3 _eye;     //!< Camera eye position

        glm::mat4 _view;    //!< Computed view matrix
    };
}

#endif //VOXFRACTURER_ORBIT_CAMERA_H_
