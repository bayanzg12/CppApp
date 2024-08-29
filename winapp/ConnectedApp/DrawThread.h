#pragma once
#include "CommonObject.h"

class DrawThread {
public:
    void operator()(CommonObjects& common);
    void operator()(void* data);
};
