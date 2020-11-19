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

#include "OrbitCamera.h"

namespace scene {

    OrbitCamera::OrbitCamera(
        const glm::vec3& lookAt,
        float theta,
        float phi,
        float distance)
        : _distance(distance)
        , _theta(theta)
        , _phi(phi)
        , _lookAt()
        , _eye()
        , _view()
    {
        setLookAt(lookAt);
    }

    const glm::mat4& OrbitCamera::viewMat() const {
        return _view;
    }

    void OrbitCamera::setLookAt(const glm::vec3& lookAt) {
        _lookAt = lookAt;
        _compViewMat();
    }

    const glm::vec3& OrbitCamera::getLookAt() const {
        return _lookAt;
    }

    glm::vec3 OrbitCamera::getEye() const {
        return _eye;
    }

    void OrbitCamera::setDistance(float distance) {
        _distance = glm::max(distance, 0.0f);
        _compViewMat();
    }

    float OrbitCamera::getDistance() const {
        return _distance;
    }

    void OrbitCamera::setTheta(float radians) {
        _theta = radians;
        _compViewMat();
    }

    float OrbitCamera::getTheta() const {
        return _theta;
    }

    void OrbitCamera::setPhi(float radians) {
        _phi = glm::clamp(radians, -MAX_PHI_ANGLE, MAX_PHI_ANGLE);
        _compViewMat();
    }

    float OrbitCamera::getPhi() const {
        return _phi;
    }

    void OrbitCamera::_compViewMat() {
        // Compute new eye position
        _eye    =  glm::vec3(sin(_theta), 0.0f, -cos(_theta));
        _eye    *= cos(_phi);
        _eye.y  =  sin(_phi);
        _eye    *= _distance;
        _eye    += _lookAt;

        // Compute view matrix
        _view = glm::lookAt(_eye, _lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
    }
}