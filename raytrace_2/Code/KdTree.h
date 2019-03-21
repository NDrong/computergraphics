//
// Created by Julius on 20-3-2019.
//

#ifndef RAY_KDTREE_H
#define RAY_KDTREE_H

#include <vector>
#include "triple.h"
#include "object.h"

class KdTree {
    double getP(const Point &p, int axis);
public:
    int depth;
    std::unique_ptr<KdTree> left, right;
    std::vector<std::shared_ptr<Object>> center;

    KdTree(std::vector<std::shared_ptr<Object>>& objects, int depth);

    BoundingBox bb;
};


#endif //RAY_KDTREE_H
