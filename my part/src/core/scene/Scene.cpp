/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include <array>
#include <random>

using std::array;
using std::make_unique;
using std::size_t;
using std::tan;
using std::unique_ptr;
using std::numeric_limits;

raytracer::Color raytracer::Scene::getLightColor(
    const IPrimitive &primitive,
    const math::Point3D &intersectionPoint, const math::Vector3D &normal)
{
    Color color = primitive.mBaseColor * _ambient;
    Color attenuation;
    double angle = 0.0;

    for (const auto &light : _lights) {
        angle = normal.dot(math::Vector3D::normalize(
            light.get()->mBaseOrigin - intersectionPoint));
        if (angle <= 0.0)
            continue;
        attenuation = light.get()->getColorShadow(
            intersectionPoint, normal, _primitives);
        color += (attenuation * angle * primitive.mBaseColor * _diffuse);
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
    double hitResult = 0.0;
    double u = 0.0;
    double v = 0.0;
    raytracer::Ray r;
    double closestHit = numeric_limits<double>::max();
    size_t closestPrimitiveIndex = numeric_limits<size_t>::max();

    u = (static_cast<double>(x) + _dis(_gen)) / width;
    v = (static_cast<double>(y) + _dis(_gen)) / height;
    r = _camera.ray(u, v);
    closestHit = numeric_limits<double>::max();
    closestPrimitiveIndex = numeric_limits<size_t>::max();
    for (size_t j = 0; j < nbPrimitives; j++) {
        hitResult = _primitives[j].get()->hits(r);
        if ((hitResult > 0.0) && (hitResult < closestHit)) {
            closestHit = hitResult;
            closestPrimitiveIndex = j;
        }
    }
    if (closestPrimitiveIndex != numeric_limits<size_t>::max()) {
        intersectionPoint = r.mOrigin + (r.mDirection * closestHit);
        normal = math::Vector3D::normalize(
            _primitives[closestPrimitiveIndex].get()->getNormal(
                intersectionPoint));
        color += getLightColor(
            *_primitives[closestPrimitiveIndex],
            intersectionPoint, normal
        );
    }
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
            factory.createPrimitive(Factory::PrimitiveType::PLANE));
        _primitives[i + o].get()->mBaseColor = planes[i].mColor;
        matrix = planes[i].mAllMatrix;
        if (planes[i].mAllMatrix.count("translation") > 0)
            transformation = matrix["translation"](0, 1);
        _primitives[i + o].get()->mBasePosition =
            static_cast<int>(planes[i].mPosition + transformation);
        _primitives[i + o].get()->mBaseAxis = planes[i].mAxis;
        _primitives[i + o].get()->mBaseAllMatrix = planes[i].mAllMatrix;
        _primitives[i + o].get()->mBaseRotation = planes[i].mVectorRotation;
    }
}

void raytracer::Scene::initSpheres(const vector<Sphere> &spheres,
    const size_t o, Factory &factory)
{
    const size_t nbSpheres = spheres.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbSpheres; i++) {
        _primitives.push_back(
            factory.createPrimitive(Factory::PrimitiveType::SPHERE));
        if (spheres[i].mAllMatrix.count("translation") > 0) {
            matrix = spheres[i].mAllMatrix;
            _primitives[i + o].get()->mBaseCenter = math::Point3D(
                spheres[i].mX + matrix["translation"](0, 3),
                spheres[i].mY + matrix["translation"](1, 3),
                spheres[i].mZ + matrix["translation"](2, 3)
            );
        } else {
            _primitives[i + o].get()->mBaseCenter = math::Point3D(
                static_cast<double>(spheres[i].mX),
                static_cast<double>(spheres[i].mY),
                static_cast<double>(spheres[i].mZ)
            );
        }
        if (spheres[i].mAllMatrix.count("scale") > 0) {
            matrix = spheres[i].mAllMatrix;
            _primitives[i + o].get()->mBaseRadius = spheres[i].mRadius
            * (matrix["scale"](0, 0) * matrix["scale"](1, 1) * matrix["scale"](2, 2));
        } else {
            _primitives[i + o].get()->mBaseRadius = spheres[i].mRadius;
        }
        _primitives[i + o].get()->mBaseColor = spheres[i].mColor;
        _primitives[i + o].get()->mBaseAllMatrix = spheres[i].mAllMatrix;
        _primitives[i + o].get()->mBaseRotation = spheres[i].mVectorRotation;
    }
}

void raytracer::Scene::initCylinders(const vector<Cylinder> &cylinders,
    const size_t o, Factory &factory)
{
    const size_t nbCylinders = cylinders.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbCylinders; i++) {
        _primitives.push_back(
            factory.createPrimitive(Factory::PrimitiveType::CYLINDER)
        );
        _primitives[i + o].get()->mBaseColor = cylinders[i].mColor;
        if (cylinders[i].mAllMatrix.count("translation") > 0) {
            matrix = cylinders[i].mAllMatrix;
            _primitives[i + o].get()->mBaseCenter = math::Point3D(
                cylinders[i].mX + matrix["translation"](0, 3),
                cylinders[i].mY + matrix["translation"](1, 3),
                cylinders[i].mZ + matrix["translation"](2, 3)
            );
        } else {
            _primitives[i + o].get()->mBaseCenter = math::Point3D(
                static_cast<double>(cylinders[i].mX),
                static_cast<double>(cylinders[i].mY),
                static_cast<double>(cylinders[i].mZ)
            );
        }
        if (cylinders[i].mAllMatrix.count("scale") > 0) {
            matrix = cylinders[i].mAllMatrix;
            _primitives[i + o].get()->mBaseRadius = cylinders[i].mRadius
            * matrix["scale"](0, 0);
            _primitives[i + o].get()->mBaseHeight = cylinders[i].mHeight
            * matrix["scale"](1, 1);
        } else {
            _primitives[i + o].get()->mBaseRadius = cylinders[i].mRadius;
            _primitives[i + o].get()->mBaseHeight = cylinders[i].mHeight;
        }
        _primitives[i + o].get()->mBaseAllMatrix = cylinders[i].mAllMatrix;
        _primitives[i + o].get()->mBaseRotation = cylinders[i].mVectorRotation;
    }
}

void raytracer::Scene::initCones(const vector<Cone> &cones,
    const size_t o, Factory &factory)
{
    const size_t nbCones = cones.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbCones; i++) {
        _primitives.push_back(
            factory.createPrimitive(Factory::PrimitiveType::CONE));
        _primitives[i + o].get()->mBaseColor = cones[i].mColor;
        if (cones[i].mAllMatrix.count("translation") > 0) {
            matrix = cones[i].mAllMatrix;
            _primitives[i + o].get()->mBaseCenter = math::Point3D(
                cones[i].mX + matrix["translation"](0, 3),
                cones[i].mY + matrix["translation"](1, 3),
                cones[i].mZ + matrix["translation"](2, 3)
            );
        } else {
            _primitives[i + o].get()->mBaseCenter = math::Point3D(
                static_cast<double>(cones[i].mX),
                static_cast<double>(cones[i].mY),
                static_cast<double>(cones[i].mZ)
            );
        }
        if (cones[i].mAllMatrix.count("scale") > 0) {
            matrix = cones[i].mAllMatrix;
            _primitives[i + o].get()->mBaseRadius = cones[i].mRadius
            * matrix["scale"](0, 0);
            _primitives[i + o].get()->mBaseHeight = cones[i].mHeight
            * matrix["scale"](1, 1);
        } else {
            _primitives[i + o].get()->mBaseRadius = cones[i].mRadius;
            _primitives[i + o].get()->mBaseHeight = cones[i].mHeight;
        }
        _primitives[i + o].get()->mBaseAllMatrix = cones[i].mAllMatrix;
        _primitives[i + o].get()->mBaseRotation = cones[i].mVectorRotation;
    }
}

void raytracer::Scene::initPoints(const vector<PointLight> &points,
    const size_t o, Factory &factory)
{
    const size_t nbPoints = points.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbPoints; i++) {
        _lights.push_back(
            factory.createLight(Factory::LightType::POINT));
        if (points[i].mAllMatrix.count("translation") > 0) {
            matrix = points[i].mAllMatrix;
            _lights[i + o].get()->mBaseOrigin = points[i].mOrigin + math::Point3D(
                matrix["translation"](0, 3),
                matrix["translation"](1, 3),
                matrix["translation"](2, 3)
            );
        } else {
            _lights[i + o].get()->mBaseOrigin = points[i].mOrigin;
        }
        _lights[i + o].get()->mBaseColor = points[i].mColor;
        _lights[i + o].get()->mBaseVectorRotation = points[i].mVectorRotation;
    }
}

void raytracer::Scene::initDirectionals(const vector<DirectionalLight> &directionals,
    const size_t o, Factory &factory)
{
    const size_t nbDirectionals = directionals.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbDirectionals; i++) {
        _lights.push_back(
            factory.createLight(Factory::LightType::DIRECTIONAL));
        if (directionals[i].mAllMatrix.count("translation") > 0) {
            matrix = directionals[i].mAllMatrix;
            _lights[i + o].get()->mBaseOrigin = directionals[i].mOrigin + math::Point3D(
                matrix["translation"](0, 3),
                matrix["translation"](1, 3),
                matrix["translation"](2, 3)
            );
        } else {
            _lights[i + o].get()->mBaseOrigin = directionals[i].mOrigin;
        }
        _lights[i + o].get()->mBaseDirection = directionals[i].mDirection;
        _lights[i + o].get()->mBaseColor = directionals[i].mColor;
        _lights[i + o].get()->mBaseVectorRotation = directionals[i].mVectorRotation;
    }
}

void raytracer::Scene::init(const core::Parser &sceneParser)
{
    Factory factory;
    const vector<Cylinder> cylinders = sceneParser.getCylinders();
    const vector<DirectionalLight> directionalLights =
        sceneParser.getDirectionalLights();
    const vector<Plane> planes = sceneParser.getPlanes();
    const vector<PointLight> pointLights = sceneParser.getPointLights();
    const vector<Sphere> spheres = sceneParser.getSpheres();
    const vector<Cone> cones = sceneParser.getCones();
    map<string, math::Matrix<double>> matrix;

    initPlanes(planes, _primitives.size(), factory);
    initSpheres(spheres, _primitives.size(), factory);
    initCylinders(cylinders, _primitives.size(), factory);
    initCones(cones, _primitives.size(), factory);
    initPoints(pointLights, _lights.size(), factory);
    initDirectionals(directionalLights, _lights.size(), factory);
    _camera.fieldOfView = _camera.fieldOfView * (M_PI / 180.0);
    const double screenDistance =  1 / (2 * ::tan(_camera.fieldOfView / 2.0));
    const double aspectRatio = static_cast<double>(
        _camera.width
    ) / static_cast<double>(_camera.height);
    const double z = _camera.posZ - screenDistance;
    const math::Point3D screenOrigin(_camera.posX, _camera.posY, z);
    const math::Vector3D bottomSide(-aspectRatio, -1, z);
    const math::Vector3D leftSide(aspectRatio, 1, z);
    _camera.mScreen = Rectangle3D(screenOrigin, bottomSide, leftSide);
    _camera.mOrigin = screenOrigin;
    _ambient = sceneParser.getAmbient();
    _diffuse = sceneParser.getDiffuse();
}
