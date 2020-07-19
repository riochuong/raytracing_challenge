#include "data_types.h"

namespace raytracer_challenge {

    ostream& operator<<(ostream & os, const Ray& ray){
        os << "Ray: " << ray.point;
        os << ", " << ray.vect;
        return os;
    }

    ostream& operator<< (ostream & os, const Point &p) {
        os << "p{" << p.x << "," << p.y << "," << p.z << "}\n";
        return os;
    }

    ostream& operator<< (ostream & os, const Vect &p) {
        os << "v{" << p.x << "," << p.y << "," << p.z << "}\n";
        return os;
    }

    ostream& operator<< (ostream & os, const Sphere &s) {
        os << "{origin: " << s.origin << ", radius: " << s.radius << "}\n";
        return os;
    }

    bool operator==(const Point &lhs, const Point &rhs) {
        if (abs(lhs.x - rhs.x) < 0.0001 && 
            abs(lhs.y - rhs.y) < 0.0001 && 
            abs(lhs.z - rhs.z) < 0.0001){
            return true;
        }
        return false;
    }

    bool operator==(const Vect &lhs, const Vect &rhs) {
        if (abs(lhs.x - rhs.x) < 0.0001 && 
            abs(lhs.y - rhs.y) < 0.0001 && 
            abs(lhs.z - rhs.z) < 0.0001){
            return true;
        }
        return false;
    }

    bool operator==(const Sphere &lhs, const Sphere &rhs) {
        if ((lhs.origin == rhs.origin) && abs(lhs.radius - rhs.radius) < 0.0001)  {
            return true;
        }
        return false;
    }

    Vect Sphere::getNormalAt(const Point &world_point) {
        // convert world point to object space
        Point object_point(world_point);
        std::cout << "Spehere tf:\n" << this->getTransform() << "\n";
        auto inv_transform = linalg::inv(this->getTransform());
        object_point.apply_transform(inv_transform);
        Vect world_normal = object_point - this->origin;
        world_normal.apply_transform(xt::transpose(inv_transform));
        // fix w for vector to avoid crazy things 
        return world_normal.normalize();
    }

}