#ifndef UTILS_H
#define UTILS_H

#include <vector>

// Required Section 4.3 Template Utility: Generic Search Tool [cite: 45]
template <typename T>
T* genericSearchByID(const std::vector<T*>& items, const std::string& id) {
    for (auto item : items) {
        if (item->getID() == id) {
            return item;
        }
    }
    return nullptr;
}

#endif
