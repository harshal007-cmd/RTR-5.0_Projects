#include <iostream>
#include <GL/glut.h>
#include <cmath>

struct Vec3 {
    float x, y, z;
};

struct Ray {
    Vec3 origin;
    Vec3 direction;
};

struct Sphere {
    Vec3 center;
    float radius;
};

// Function to calculate the intersection of a ray and a sphere
bool intersectSphere(const Ray& ray, const Sphere& sphere, float& t) {
    Vec3 oc = { ray.origin.x - sphere.center.x, ray.origin.y - sphere.center.y, ray.origin.z - sphere.center.z };
    float a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
    float b = 2.0f * (oc.x * ray.direction.x + oc.y * ray.direction.y + oc.z * ray.direction.z);
    float c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    float sqrtDiscriminant = std::sqrt(discriminant);
    float t0 = (-b - sqrtDiscriminant) / (2.0f * a);
    float t1 = (-b + sqrtDiscriminant) / (2.0f * a);

    if (t0 > t1)
        std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0)
            return false;
    }

    t = t0;
    return true;
}

void display() {
    int width = 500;
    int height = 500;

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0f);

    glBegin(GL_POINTS);

    // Define the camera
    Vec3 camera = { 0.0f, 0.0f, 0.0f };

    // Define the sphere
    Sphere sphere = { { 0.0f, 0.0f, -5.0f }, 1.0f };

    // Define the viewport
    float aspectRatio = float(width) / float(height);
    float viewportHeight = 2.0f;
    float viewportWidth = aspectRatio * viewportHeight;
    float focalLength = 1.0f;

    // Iterate over each pixel and cast a ray
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calculate the ray direction
            float u = float(x) / float(width - 1);
            float v = float(y) / float(height - 1);
            Vec3 direction = {
                viewportWidth * (u - 0.5f),
                viewportHeight * (v - 0.5f),
                focalLength
            };
            Ray ray = { camera, direction };
            float t;

            // Check for intersection with the sphere
            if (intersectSphere(ray, sphere, t)) {
                // Calculate the intersection point
                Vec3 intersection = {
                    ray.origin.x + t * ray.direction.x,
                    ray.origin.y + t * ray.direction.y,
                    ray.origin.z + t * ray.direction.z
                };

                // Calculate the surface normal
                Vec3 normal = {
                    (intersection.x - sphere.center.x) / sphere.radius,
                    (intersection.y - sphere.center.y) / sphere.radius,
                    (intersection.z - sphere.center.z) / sphere.radius
                };

                // Normalize the surface normal
                float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
                normal.x /= length;
                normal.y /= length;
                normal.z /= length;

                // Map the surface normal to RGB color
                Vec3 color = {
                    0.5f * (normal.x + 1.0f),
                    0.5f * (normal.y + 1.0f),
                    0.5f * (normal.z + 1.0f)
                };

                // Draw the intersection point as a pixel with the surface color
                glColor3f(color.x, color.y, color.z);
                glVertex2i(x, y);
            }
        }
    }

    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Sphere Ray Tracing");
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background color
    glOrtho(0, 500, 0, 500, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
