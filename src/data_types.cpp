#include "data_types.h"
#include "matrix_transforms.h"

namespace raytracer_challenge
{

    ostream &operator<<(ostream &os, const Ray &ray)
    {
        os << "Ray: " << ray.point;
        os << ", " << ray.vect;
        return os;
    }

    ostream &operator<<(ostream &os, const Point &p)
    {
        os << "p{" << p.x << "," << p.y << "," << p.z << "}\n";
        return os;
    }

    ostream &operator<<(ostream &os, const Vect &p)
    {
        os << "v{" << p.x << "," << p.y << "," << p.z << "}\n";
        return os;
    }

    ostream &operator<<(ostream &os, const Sphere &s)
    {
        os << "{origin: " << s.origin << ", radius: " << s.radius << "}\n";
        return os;
    }

    bool operator==(const Point &lhs, const Point &rhs)
    {
        if (abs(lhs.x - rhs.x) < 0.0001 &&
            abs(lhs.y - rhs.y) < 0.0001 &&
            abs(lhs.z - rhs.z) < 0.0001)
        {
            return true;
        }
        return false;
    }

    bool operator==(const Vect &lhs, const Vect &rhs)
    {
        if (abs(lhs.x - rhs.x) < 0.0001 &&
            abs(lhs.y - rhs.y) < 0.0001 &&
            abs(lhs.z - rhs.z) < 0.0001)
        {
            return true;
        }
        return false;
    }

    bool operator==(const Sphere &lhs, const Sphere &rhs)
    {
        if ((lhs.origin == rhs.origin) && abs(lhs.radius - rhs.radius) < 0.0001)
        {
            return true;
        }
        return false;
    }

    Vect Sphere::getNormalAt(const Point &world_point)
    {
        // convert world point to object space
        Point object_point(world_point);
        std::cout << "Spehere tf:\n"
                  << this->getTransform() << "\n";
        auto inv_transform = linalg::inv(this->getTransform());
        object_point.apply_transform(inv_transform);
        Vect world_normal = object_point - this->origin;
        world_normal.apply_transform(xt::transpose(inv_transform));
        // fix w for vector to avoid crazy things
        return world_normal.normalize();
    }
    
    World World::createDefaultWorld()
    {
        PointLight light(Point(-10, 10, -10), Color(1, 1, 1));
        Sphere s1;
        Material m1;
        m1.color = Color(0.8, 1.0, 0.6);
        m1.diffuse = 0.7;
        m1.specular = 0.2;
        s1.material = m1;

        Sphere s2;
        s2.setTransform(tf::scaling(0.5, 0.5, 0.5));

        std::cout << "S1: " << s1.getTransform() << "\n";
        std::cout << "S2: " << s2.getTransform() << "\n";
        World w(light);
        w.sphere_containers.push_back(s1);
        w.sphere_containers.push_back(s2);
        return w;
    }

} // namespace raytracer_challenge