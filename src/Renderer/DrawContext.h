#pragma once
#include "Light.h"
#include "glm/glm.hpp"


struct DrawContext
{
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 lightSpaceMatrix;

    unsigned int shadowMap;

    const Light& light;
};
