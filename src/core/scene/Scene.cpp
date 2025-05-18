/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Scene.cpp
*/

#include "Scene.hpp"

using std::array;
using std::make_unique;
using std::size_t;
using std::tan;
using std::unique_ptr;
using std::numeric_limits;

raytracer::Color raytracer::Scene::getLightColor(
    const IPrimitives &primitive,
    HitData &data)
{
    Color color = primitive._bcolor * _ambient;
    Color rlight;
    World world;
    double angle = 0.0;

    if (!_isFastRender) {
        for (const auto &light : _lights) {
            angle = data.normal.dot(math::Vector3D::normalize(
                light.get()->_borigin - data.p
            ));
            if (angle <= 0.0)
                continue;
            rlight = light.get()->directLight(world, data, color, _primitives);
            color += rlight * primitive._bcolor * angle * _diffuse;
        }
    }
    color.clamp();
    return color;
}

raytracer::Color raytracer::Scene::getColor(
    const unsigned int x, const unsigned int y,
    const unsigned int height, const unsigned int width)
{
    Color color(0.0, 0.0, 0.0);
    math::Point3D intersectionPoint;
    math::Vector3D normal;
    const size_t nbPrimitives = _primitives.size();
    const int numSamples = _isFastRender ? 1 : 10;
    double u = 0.0;
    double v = 0.0;
    raytracer::Ray r;
    double closestHit = numeric_limits<double>::max();
    size_t closestPrimitiveIndex = numeric_limits<size_t>::max();

    for (int i = 0; i < numSamples; i++) {
        u = (static_cast<double>(x) + _dis(_gen)) / width;
        v = (static_cast<double>(y) + _dis(_gen)) / height;
        r = _camera.ray(u, v);
        closestHit = numeric_limits<double>::max();
        closestPrimitiveIndex = numeric_limits<size_t>::max();
        HitData hitData;
        for (size_t j = 0; j < nbPrimitives; j++) {
            if(_primitives[j].get()->hits(r, hitData) &&
            (hitData.t > 0.0) && (hitData.t < closestHit)) {
                closestHit = hitData.t;
                closestPrimitiveIndex = j;
            }
        }
        if (closestPrimitiveIndex != numeric_limits<size_t>::max()) {
            intersectionPoint = r._origin + (r._direction * closestHit);
            normal = math::Vector3D::normalize(
                _primitives[closestPrimitiveIndex].get()->getNormal(
                    intersectionPoint
                )
            );
            hitData.p = intersectionPoint,
            hitData.normal = normal;
            color += getLightColor(
                *_primitives[closestPrimitiveIndex],
                hitData
            );
        }
    }
    color /= numSamples;
    return color;
}

void raytracer::Scene::render(raytracer::Image &image)
{
    raytracer::Color color;
    const unsigned int height = image.getHeight();
    const unsigned int width = image.getWidth();

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            color = getColor(x, y, height, width);
            image.setPixel(x, y, color);
        }
    }
}

void raytracer::Scene::initPlanes(const vector<Plane> &planes,
    const size_t o, Factory &factory)
{
    const size_t nbPlanes = planes.size();
    map<string, math::Matrix<double>> matrix;
    double transformation = 0.0;

    for (size_t i = 0; i < nbPlanes; i++) {
        transformation = 0.0;
        _primitives.push_back(
            factory.createPrimitive(Factory::PrimitiveType::PLANE)
        );
        _primitives[i + o].get()->_bcolor = planes[i]._color;
        matrix = planes[i]._allMatrix;
        if (planes[i]._allMatrix.count("translation") > 0) {
            transformation = matrix["translation"](0, 1);
        }
        _primitives[i + o].get()->_bposition =
            static_cast<int>(planes[i]._position + transformation);
        _primitives[i + o].get()->_baxis = planes[i]._axis;
        _primitives[i + o].get()->_ballMatrix = planes[i]._allMatrix;
        _primitives[i + o].get()->_brotation = planes[i]._rotation;
        // _world.addObject(std::move(_primitives[i + o]));
    }
}

void raytracer::Scene::initSpheres(const vector<Sphere> &spheres,
    const size_t o, Factory &factory)
{
    const size_t nbSpheres = spheres.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbSpheres; i++) {
        _primitives.push_back(
            factory.createPrimitive(Factory::PrimitiveType::SPHERE)
        );
        if (spheres[i]._allMatrix.count("translation") > 0) {
            matrix = spheres[i]._allMatrix;
            _primitives[i + o].get()->_bcenter = spheres[i]._center + math::Point3D(
                matrix["translation"](0, 3),
                matrix["translation"](1, 3),
                matrix["translation"](2, 3)
            );
        } else {
            _primitives[i + o].get()->_bcenter = spheres[i]._center;
        }
        if (spheres[i]._allMatrix.count("scale") > 0) {
            matrix = spheres[i]._allMatrix;
            _primitives[i + o].get()->_bradius = spheres[i]._radius
            * (matrix["scale"](0, 0)
            * matrix["scale"](1, 1)
            * matrix["scale"](2, 2));
        } else {
            _primitives[i + o].get()->_bradius = spheres[i]._radius;
        }
        _primitives[i + o].get()->_bcolor = spheres[i]._color;
        _primitives[i + o].get()->_ballMatrix = spheres[i]._allMatrix;
        _primitives[i + o].get()->_brotation = spheres[i]._rotation;
        // _world.addObject(std::move(_primitives[i + o]));
    }
}

// void raytracer::Scene::initCylinders(const vector<Cylinder> &cylinders,
//     const size_t o, Factory &factory)
// {
//     const size_t nbCylinders = cylinders.size();
//     map<string, math::Matrix<double>> matrix;

//     for (size_t i = 0; i < nbCylinders; i++) {
//         _primitives.push_back(
//             factory.createPrimitive(Factory::PrimitiveType::CYLINDER)
//         );
//         _primitives[i + o].get()->_color = cylinders[i].mColor;
//         if (cylinders[i]._allMatrix.contains("translation")) {
//             matrix = cylinders[i]._allMatrix;
//             _primitives[i + o].get()->_center = math::Point3D(
//                 cylinders[i].mX + matrix["translation"](0, 3),
//                 cylinders[i].mY + matrix["translation"](1, 3),
//                 cylinders[i].mZ + matrix["translation"](2, 3)
//             );
//         } else {
//             _primitives[i + o].get()->_center = math::Point3D(
//                 static_cast<double>(cylinders[i].mX),
//                 static_cast<double>(cylinders[i].mY),
//                 static_cast<double>(cylinders[i].mZ)
//             );
//         }
//         if (cylinders[i]._allMatrix.contains("scale")) {
//             matrix = cylinders[i]._allMatrix;
//             _primitives[i + o].get()->_radius = cylinders[i].mRadius
//             * matrix["scale"](0, 0);
//             _primitives[i + o].get()->mBaseHeight = cylinders[i].mHeight
//             * matrix["scale"](1, 1);
//         } else {
//             _primitives[i + o].get()->_radius = cylinders[i].mRadius;
//             _primitives[i + o].get()->mBaseHeight = cylinders[i].mHeight;
//         }
//         _primitives[i + o].get()->mBaseAllMatrix = cylinders[i]._allMatrix;
//         _primitives[i + o].get()->_rotation = cylinders[i]._rotation;
//     }
// }

// void raytracer::Scene::initCones(const vector<Cone> &cones,
//     const size_t o, Factory &factory)
// {
//     const size_t nbCones = cones.size();
//     map<string, math::Matrix<double>> matrix;

//     for (size_t i = 0; i < nbCones; i++) {
//         _primitives.push_back(
//             factory.createPrimitive(Factory::PrimitiveType::CONE)
//         );
//         _primitives[i + o].get()->_color = cones[i].mColor;
//         if (cones[i]._allMatrix.contains("translation")) {
//             matrix = cones[i]._allMatrix;
//             _primitives[i + o].get()->_center = math::Point3D(
//                 cones[i].mX + matrix["translation"](0, 3),
//                 cones[i].mY + matrix["translation"](1, 3),
//                 cones[i].mZ + matrix["translation"](2, 3)
//             );
//         } else {
//             _primitives[i + o].get()->_center = math::Point3D(
//                 static_cast<double>(cones[i].mX),
//                 static_cast<double>(cones[i].mY),
//                 static_cast<double>(cones[i].mZ)
//             );
//         }
//         if (cones[i]._allMatrix.contains("scale")) {
//             matrix = cones[i]._allMatrix;
//             _primitives[i + o].get()->_radius = cones[i].mRadius
//             * matrix["scale"](0, 0);
//             _primitives[i + o].get()->mBaseHeight = cones[i].mHeight
//             * matrix["scale"](1, 1);
//         } else {
//             _primitives[i + o].get()->_radius = cones[i].mRadius;
//             _primitives[i + o].get()->mBaseHeight = cones[i].mHeight;
//         }
//         _primitives[i + o].get()->mBaseAllMatrix = cones[i]._allMatrix;
//         _primitives[i + o].get()->_rotation = cones[i]._rotation;
//     }
// }

void raytracer::Scene::initPoints(const vector<PointLight> &points,
    const size_t o, Factory &factory)
{
    const size_t nbPoints = points.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbPoints; i++) {
        _lights.push_back(
            factory.createLight(Factory::LightType::POINT)
        );
        if (points[i]._allMatrix.count("translation") > 0) {
            matrix = points[i]._allMatrix;
            _lights[i + o].get()->_borigin = points[i]._origin + math::Point3D(
                matrix["translation"](0, 3),
                matrix["translation"](1, 3),
                matrix["translation"](2, 3)
            );
        } else {
            _lights[i + o].get()->_borigin = points[i]._origin;
        }
        _lights[i + o].get()->_bcolor = points[i]._color;
        _lights[i + o].get()->_brotation = points[i]._rotation;
        _lights[i + o].get()->_bdiffuse = points[i]._diffuse;

    }
}

void raytracer::Scene::initDirectionals(const vector<DirectionalLight> &directionals,
    const size_t o, Factory &factory)
{
    const size_t nbDirectionals = directionals.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbDirectionals; i++) {
        _lights.push_back(
            factory.createLight(Factory::LightType::DIRECTIONAL)
        );
        if (directionals[i]._allMatrix.find("translation") != directionals[i]._allMatrix.end()) {
            matrix = directionals[i]._allMatrix;
            _lights[i + o].get()->_borigin =  directionals[i]._origin + math::Point3D(
                matrix["translation"](0, 3),
                matrix["translation"](1, 3),
                matrix["translation"](2, 3)
            );
        } else {
            _lights[i + o].get()->_borigin = directionals[i]._origin;
        }
        _lights[i + o].get()->_bdirection = directionals[i]._direction;
        _lights[i + o].get()->_bcolor = directionals[i]._color;
        _lights[i + o].get()->_brotation = directionals[i]._rotation;
        _lights[i + o].get()->_bdiffuse = directionals[i]._diffuse;
    }
}

void raytracer::Scene::initAmbients(const vector<AmbientLight> &ambients,
    const size_t o, Factory &factory)
{
    const size_t nbAmbients = ambients.size();

    for (size_t i = 0; i < nbAmbients; i++) {
        _lights.push_back(
            factory.createLight(Factory::LightType::AMBIENT)
        );
        _lights[i + o].get()->_bcolor = ambients[i]._color;
        _lights[i + o].get()->_bambient = ambients[i]._ambient;
    }
}

void raytracer::Scene::init(const core::Parser &sceneParser)
{
    Factory factory;
    // const vector<Cylinder> cylinders = sceneParser.getCylinders();
    // const vector<AmbientLight> ambientLights =
    //     sceneParser.getAmbientLights();
    const vector<DirectionalLight> directionalLights =
        sceneParser.getDirectionalLights();
    const vector<Plane> planes = sceneParser.getPlanes();
    const vector<PointLight> pointLights = sceneParser.getPointLights();
    const vector<Sphere> spheres = sceneParser.getSpheres();
    // const vector<Cone> cones = sceneParser.getCones();
    map<string, math::Matrix<double>> matrix;

    initPlanes(planes, _primitives.size(), factory);
    initSpheres(spheres, _primitives.size(), factory);
    // initCylinders(cylinders, _primitives.size(), factory);
    // initCones(cones, _primitives.size(), factory);
    initPoints(pointLights, _lights.size(), factory);
    initDirectionals(directionalLights, _lights.size(), factory);
    // initAmbients(ambientLights, _lights.size(), factory);
    _camera.fieldOfView = _camera.fieldOfView * (M_PI / 180.0);
    const double screenDistance =  1 / (2 * ::tan(_camera.fieldOfView / 2.0));
    const double aspectRatio = static_cast<double>(
        _camera.width
    ) / static_cast<double>(_camera.height);
    const double z = _camera._position.z - screenDistance;
    const math::Point3D screenOrigin(_camera._position.x, _camera._position.y, z);
    const math::Vector3D bottomSide(-aspectRatio, -1, z);
    const math::Vector3D leftSide(aspectRatio, 1, z);
    _camera._screen = Rectangle3D(screenOrigin, bottomSide, leftSide);
    _camera._origin = screenOrigin;
    _ambient = sceneParser.getAmbient();
    _diffuse = sceneParser.getDiffuse();
}

void raytracer::Scene::setFastRender(const bool isFastRender)
{
    _isFastRender = isFastRender;
}