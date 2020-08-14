#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <math.h>
#include "color.h"

using namespace std;
using namespace xt;
using namespace raytracer_challenge;

namespace raytracer_challenge
{
    class XarrayBaseType
    {
    public:
        /**
             * @brief return matrix type data ready for matrix multiplication
             * @return  xarray type 
             */

        virtual xarray<double> get_mat_data() const = 0;
        virtual xarray<double> get_mat_homo_data() const = 0;
        virtual void apply_transform(xarray<double> tmat) = 0;
    };

    class Vect : XarrayBaseType
    {
    public:
        double x;
        double y;
        double z;

        Vect() : x(0), y(0), z(0){};

        /**
             *  @brief  create ray 
             *  @param double: x position
             *  @param double : y position
             *  @param double: z position
             *  @return  xarray: translation matrix
            */
        Vect(double x_, double y_, double z_) : x(x_), y(y_), z(z_){

                                                              };

        Vect(const Vect &rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
        }

        Vect &operator=(const Vect &rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            return *this;
        }

        Vect operator*(double scale) const
        {
            return Vect(this->x * scale,
                        this->y * scale,
                        this->z * scale);
        }

        Vect operator-(const Vect &rhs) const
        {
            return Vect(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        virtual xarray<double> get_mat_data() const
        {
            xarray<double> mat_data = {
                // point is movable so this should be 1
                {x, y, z}};
            mat_data.reshape({3, 1});
            return mat_data;
        }

        virtual xarray<double> get_mat_homo_data() const
        {
            xarray<double> mat_data = {
                // point is movable so this should be 1
                {x, y, z, 0}};
            mat_data.reshape({4, 1});
            return mat_data;
        }

        Vect normalize() const
        {
            double magnitude = sqrt(x * x + y * y + z * z);
            return Vect(
                x / magnitude,
                y / magnitude,
                z / magnitude);
        }

        virtual void apply_transform(xarray<double> tmat)
        {
            auto shape = tmat.shape();
            if (shape.size() != 2)
            {
                throw runtime_error("Trans.Matrix requires to be 2 dimensional !");
            }
            if (shape[0] != 4 && shape[1] != 4)
            {
                throw runtime_error("Trans.Matrix requires shape 4x4");
            }
            auto result = linalg::dot(tmat, get_mat_homo_data());
            x = result[{0, 0}];
            y = result[{1, 0}];
            z = result[{2, 0}];
        }

        double getLength() const
        {
            return sqrt(x * x + y * y + z * z);
        }

        friend ostream &operator<<(ostream &os, const Vect &p);
        friend bool operator==(const Vect &lhs, const Vect &rhs);
    };

    class Point : public XarrayBaseType
    {
    public:
        double x;
        double y;
        double z;

        Point() : x(0), y(0), z(0){};

        /**
             *  @brief  create ray 
             *  @param double: x position
             *  @param double : y position
             *  @param double: z position
             *  @return  xarray: translation matrix
            */
        Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_){};

        Point(const Point &rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
        }

        Point operator=(const Point &rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            return *this;
        }

        Vect operator-(const Point &rhs) const
        {
            return Vect(this->x - rhs.x,
                        this->y - rhs.y,
                        this->z - rhs.z);
        }

        virtual xarray<double> get_mat_data() const
        {
            xarray<double> mat_data = {
                // point is movable so this should be 1
                {x, y, z}};
            mat_data.reshape({3, 1});
            return mat_data;
        }

        virtual xarray<double> get_mat_homo_data() const
        {
            xarray<double> mat_data = {
                // point is movable so this should be 1
                {x, y, z, 1}};
            mat_data.reshape({4, 1});
            return mat_data;
        }

        virtual void apply_transform(xarray<double> tmat)
        {
            auto shape = tmat.shape();
            if (shape.size() != 2)
            {
                throw runtime_error("Trans.Matrix requires to be 2 dimensional !");
            }
            if (shape[0] != 4 && shape[1] != 4)
            {
                throw runtime_error("Trans.Matrix requires shape 4x4");
            }
            auto result = linalg::dot(tmat, get_mat_homo_data());
            std::cout << "result " << result << "\n";
            x = result[{0, 0}];
            y = result[{1, 0}];
            z = result[{2, 0}];
        }
        friend ostream &operator<<(ostream &os, const Point &p);
        friend bool operator==(const Point &lhs, const Point &rhs);
    };

    class Ray
    {
    public:
        Point point;
        Vect vect;

        Ray() = delete;

        /**
             *  @brief  create ray 
             *  @param double: x position
             *  @param double : y position
             *  @param double: z position
             *  @return  xarray: translation matrix
            */
        Ray(const Point &pt, const Vect &dir) : point(pt), vect(dir){};

        Ray(const Ray &rhs)
        {
            this->point = rhs.point;
            this->vect = rhs.vect;
        }

        Ray &operator=(const Ray &rhs)
        {
            this->point = rhs.point;
            this->vect = rhs.vect;
            return *this;
        }
        friend ostream &operator<<(ostream &os, const Ray &r);
    };

    class Material
    {
    public:
        const double DEFAULT_AMBIENT = 0.1;
        const double DEFAULT_DIFFUSE = 0.9;
        const double DEFAULT_SPECULAR = 0.9;
        const double DEFAULT_SHININESS = 200.0;

        double ambient;
        double diffuse;
        double specular;
        double shininess;
        Color color;

        Material() : ambient(DEFAULT_AMBIENT),
                     diffuse(DEFAULT_DIFFUSE),
                     specular(DEFAULT_SPECULAR),
                     shininess(DEFAULT_SHININESS),
                     color(1, 1, 1){};

        Material(double a, double d, double sp, double sh) : ambient(a),
                                                             diffuse(d),
                                                             specular(sp),
                                                             shininess(sh){};


        Material (const Material &m)
        {
            this->ambient = m.ambient;
            this->diffuse = m.diffuse;
            this->specular = m.specular;
            this->shininess = m.shininess;
        }
        
        Material &operator=(const Material &m)
        {
            this->ambient = m.ambient;
            this->diffuse = m.diffuse;
            this->specular = m.specular;
            this->shininess = m.shininess;
            return *this;
        }
    };

    class Sphere
    {
    public:
        double radius;
        Point origin;
        Material material;

        Sphere() : radius(1), origin(0, 0, 0), tf_mat_(xt::eye(4)){};
        Sphere(double r, Point &p) : radius(r), origin(p)
        {
            if (r <= 0)
            {
                throw runtime_error("Radius need to be a positive number");
            }
        };

        Sphere(const Sphere &rhs)
        {
            this->radius = rhs.radius;
            this->origin = rhs.origin;
            this->material = rhs.material;
            this->tf_mat_ = rhs.tf_mat_;
        }

        Sphere &operator=(const Sphere &rhs)
        {
            this->radius = rhs.radius;
            this->origin = rhs.origin;
            this->material = rhs.material;
            this->tf_mat_ = rhs.tf_mat_;
            return *this;
        }
        friend ostream &operator<<(ostream &os, const Sphere &r);
        friend bool operator==(const Sphere &lhs, const Sphere &rhs);

        void setTransform(const xarray<double> &tf)
        {
            auto shape = tf_mat_.shape();
            if (shape.size() != 2)
            {
                throw runtime_error("Trans.Matrix requires to be 2 dimensional !");
            }
            if (shape[0] != 4 && shape[1] != 4)
            {
                throw runtime_error("Trans.Matrix requires shape 4x4");
            }
            tf_mat_ = tf;
        }

        xarray<double> getTransform() const
        {
            // return a copy of tf matrix
            std::cout << "Tf mat: " << tf_mat_ << "\n";
            return tf_mat_;
        }

        /**
             *  @brief  get normal vector on sphere surface
             *  @param Point: point (assumed) it belongs to sphere surface 
             *  @return  Vect: unit normal vector
            */
        Vect getNormalAt(const Point &p);

    private:
        xarray<double> tf_mat_;
    };

    class Intersection
    {
    public:
        double t;
        Sphere object;
        Intersection() = delete;
        Intersection(double tval, Sphere s) : t(tval), object(s){};
            Intersection(Intersection &&other) {
                t = other.t;
                object = other.object;
            }
        Intersection(const Intersection &other) {
            t = other.t;
            object = other.object;
        }
        Intersection &operator=(const Intersection &other) {
            t = other.t;
            object = other.object;
            return *this;
        }
    };

    class PointLight
    {
    public:
        Point position;
        Color intensity;
        PointLight() = delete;
        
        PointLight(const Point &p, const Color &c) : position(p), intensity(c){};
        
        PointLight(const PointLight &rhs): position(rhs.position), intensity(rhs.intensity) {};
        
        PointLight &operator=(const PointLight &rhs) {
            position = rhs.position;
            intensity = rhs.intensity;
            return *this;
        }
    };

    class World {
        public:
            PointLight light;

            World(const PointLight &pl): light(pl) {};

            static World createDefaultWorld();

            // check if a given sphere belongs to the world 
            bool contains(const Sphere &s);
            vector<Sphere> sphere_containers;
    };

} // namespace raytracer_challenge