//
// Created by kisly on 15.07.2025.
//

#ifndef GL_HPP
#define GL_HPP

namespace core
{
    enum TYPE_CULL_FACE : int;
    enum DIRECT_FRONT_FACE : int;
    enum POLYGON_MODE : int;
    enum DIRECT_FACE_POLYGONS : int;

    /// @brief пространсво имён для настроки openGL
    namespace gl
    {
        /// @brief включает проверку буффера глубины
        /// @param flag состояние
        void enableDepthTest(bool flag = true);

        /// @brief включает отбрасывание граний
        /// @param flag состояние
        void enableCullFace(bool flag = true);

        /// @brief устанавливает тип отбрасывание граний
        /// @param tcf тип 
        void setTypeCullFace(const TYPE_CULL_FACE& tcf);

        /// @brief устанавливает порядок прохода для рендера
        /// @param dff напровление (core::DIRECT_CCW - против часовой стрелки, core::DIRECT_CW - по часовой)
        void setDirectFronFace(const DIRECT_FRONT_FACE & dff);

        void setTypePolygonMode(const DIRECT_FACE_POLYGONS& DFP, const POLYGON_MODE& PM);
    };

} 

#endif //GL_HPP
