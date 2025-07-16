//
// Created by kisly on 15.07.2025.
//

#include "gl.hpp"
#include "../../util/types.hpp"
#include <glad/glad.h>

void core::gl::enableDepthTest(bool flag)
{
    (flag) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void core::gl::enableCullFace(bool flag)
{
    if (flag) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
}

void core::gl::setTypeCullFace(const core::TYPE_CULL_FACE &tcf)
{
    switch (tcf)
    {
    case core::CULL_BACK:
        glCullFace(GL_BACK);
        break;

    case core::CULL_FRONT:
        glCullFace(GL_FRONT);
        break;

    case core::CULL_FRONT_AND_BACK:
        glCullFace(GL_FRONT_AND_BACK);
        break;
    }
}

void core::gl::setDirectFronFace(const core::DIRECT_FRONT_FACE& dff)
{
    switch(dff)
    {
    case core::DIRECT_CCW:
        glFrontFace(GL_CCW); 
        break;
        
    case core::DIRECT_CW:
        glFrontFace(GL_CW); 
        break;
    }
}
