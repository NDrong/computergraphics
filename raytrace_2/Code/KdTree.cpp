#include "KdTree.h"
#include <algorithm>

KdTree::KdTree(std::vector<std::shared_ptr<Object>> &objects, int depth) : depth(depth) {
    int axis = depth % 3; // 0 = x, 1 = y, 2 = z

    std::sort(objects.begin(), objects.end(), [this, axis](const std::shared_ptr<Object> a, const std::shared_ptr<Object> b) {
        return getP(a->bb.getTopLeft(), axis) < getP(b->bb.getTopLeft(), axis);
    });
    size_t median = objects.size() / 2;

    center.push_back(objects[median]);
    for (const auto& obj : center) {
        bb += obj->bb;
    }

    if (objects.size() > 1) {
        auto objL = std::vector<std::shared_ptr<Object>>(objects.begin(), objects.begin() + median);
        auto objR = std::vector<std::shared_ptr<Object>>(objects.begin() + median, objects.end());
        left = std::make_unique<KdTree>(objL, depth + 1);
        right = std::make_unique<KdTree>(objR, depth + 1);
        bb += left->bb;
        bb += right->bb;
    }
}

double KdTree::getP(const Point &p, int axis) {
    switch (axis) {
        case 0:
            return p.x;
        case 1:
            return p.y;
        default:
            return p.z;
    }
}
