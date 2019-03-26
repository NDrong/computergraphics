#include "raytracer.h"

#include "image.h"
#include "light.h"
#include "material.h"
#include "triple.h"
#include "objloader.h"
#include <omp.h>

// =============================================================================
// -- Include all your shapes here ---------------------------------------------
// =============================================================================

#include "shapes/sphere.h"
#include "shapes/triangle.h"
#include "shapes/cylinder.h"
#include "shapes/cone.h"
#include "shapes/MeshTriangle.h"
#include "shapes/MirrorPlane.h"

// =============================================================================
// -- End of shape includes ----------------------------------------------------
// =============================================================================

#include "json/json.h"
#include "KdTree.h"

#include <exception>
#include <fstream>
#include <iostream>

using namespace std;        // no std:: required
using json = nlohmann::json;

bool Raytracer::parseObjectNode(json const &node) {
    ObjectPtr obj = nullptr;

// =============================================================================
// -- Determine type and parse object parametrers ------------------------------
// =============================================================================

    if (node["type"] == "sphere") {
        Point pos(node["position"]);
        double radius = node["radius"];

        auto rot = node.find("rotation");
        auto angle = node.find("angle");
        if ((rot != node.end()) && (angle != node.end()))
            obj = ObjectPtr(new Sphere(pos, radius, Vector(*rot), *angle));
        else
            obj = ObjectPtr(new Sphere(pos, radius));
    } else if (node["type"] == "triangle") {
        Point va(node["vertex_a"]);
        Point vb(node["vertex_b"]);
        Point vc(node["vertex_c"]);
        obj = ObjectPtr(new Triangle(va, vb, vc));
    } else if (node["type"] == "cylinder") {
        Point position(node["position"]);
        double radius(node["radius"]);
        double height(node["height"]);
        obj = ObjectPtr(new Cylinder(position, radius, height));
    } else if (node["type"] == "cone") {
        Point position(node["position"]);
        double radius(node["radius"]);
        double height(node["height"]);
        obj = ObjectPtr(new Cone(position, radius, height));
    } else if (node["type"] == "mesh") {
        std::string filename = node["filename"];
        OBJLoader loader(filename);
        auto vertices = loader.vertex_data();
        Material objMaterial = parseMaterialNode(node["material"]);

        for (size_t i = 0; i < vertices.size() / 3; i++) {
            double scale(node["scale"]);
            Point pos(node["position"]);

            for (int bla = 0; bla < 3; bla++) {
                vertices[i * 3 + bla].x = static_cast<float>(scale * vertices[i * 3 + bla].x + pos.x);
                vertices[i * 3 + bla].y = static_cast<float>(scale * vertices[i * 3 + bla].y + pos.y);
                vertices[i * 3 + bla].z = static_cast<float>(scale * vertices[i * 3 + bla].z + pos.z);
            }

            ObjectPtr o(new MeshTriangle(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]));
            o->material = objMaterial;
            scene.addObject(o);
        }
        return true;
    } else if (node["type"] == "mplane") {
        Point center(node["center"]);
        double size(node["size"]);
        Vector N(node["normal"]);
        obj = ObjectPtr(new MirrorPlane(center, size, N));
    } else {
        cerr << "Unknown object type: " << node["type"] << ".\n";
    }

// =============================================================================
// -- End of object reading ----------------------------------------------------
// =============================================================================

    if (!obj)
        return false;

    // Parse material and add object to the scene
    obj->material = parseMaterialNode(node["material"]);
    scene.addObject(obj);
    return true;
}

Light Raytracer::parseLightNode(json const &node) const {
    Point pos(node["position"]);
    Color col(node["color"]);
    return Light(pos, col);
}

Material Raytracer::parseMaterialNode(json const &node) const {
    auto jColor = node.find("color");
    Color color(0.0, 0.0, 0.0);
    if (jColor != node.end()) {
        color = Color(*jColor);
    }

    double ka = node["ka"];
    double kd = node["kd"];
    double ks = node["ks"];
    double n = node["n"];

    auto texture = node.find("texture");
    if (texture != node.end()) {
        return Material(color, ka, kd, ks, n, *texture, false);
    }

    bool isMirror = node.find("mirror") != node.end() && bool(*node.find("mirror"));

    return Material(color, ka, kd, ks, n, isMirror);
}

bool Raytracer::readScene(string const &ifname)
try {
    // Read and parse input json file
    ifstream infile(ifname);
    if (!infile) throw runtime_error("Could not open input file for reading.");
    json jsonscene;
    infile >> jsonscene;

// =============================================================================
// -- Read your scene data in this section -------------------------------------
// =============================================================================

    Point eye(jsonscene["Eye"]);
    scene.setEye(eye);

    // TODO: add your other configuration settings here
    auto shadows = jsonscene.find("Shadows");
    scene.setUseShadows(shadows != jsonscene.end() ? bool(*shadows) : false);

    auto maxRecursionDepth = jsonscene.find("MaxRecursionDepth");
    scene.setMaxRecursionDepth(maxRecursionDepth != jsonscene.end() ? int(*maxRecursionDepth) : 0);

    auto superSamplingFactor = jsonscene.find("SuperSamplingFactor");
    scene.setSuperSamplingFactor(superSamplingFactor != jsonscene.end() ? int(*superSamplingFactor) : 1);

    for (auto const &lightNode : jsonscene["Lights"])
        scene.addLight(parseLightNode(lightNode));

    unsigned objCount = 0;
    for (auto const &objectNode : jsonscene["Objects"])
        if (parseObjectNode(objectNode))
            ++objCount;

    cout << "Parsed " << objCount << " objects.\n";

// =============================================================================
// -- End of scene data reading ------------------------------------------------
// =============================================================================

    return true;
}
catch (exception const &ex) {
    cerr << ex.what() << '\n';
    return false;
}

void Raytracer::renderToFile(string const &ofname) {
    // TODO: the size may be a settings in your file
    Image img(1600, 1600);
    cout << "Tracing on " << omp_get_max_threads() << " threads...\n";
    scene.render(img);
    cout << "Writing image to " << ofname << "...\n";
    img.write_png(ofname);
    cout << "Done.\n";
}
