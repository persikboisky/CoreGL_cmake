//
// Created by kisly on 13.07.2025.
//

#ifndef CONFIG_HPP
#define CONFIG_HPP

// ерсия opeGL
constexpr unsigned short OPENGL_VERSION_MAJOR = 3;
constexpr unsigned short OPENGL_VERSION_MINOR = 3;

constexpr bool OPENGL_DEPTH_FUNCTION = false;

constexpr bool OPENGL_CULL_FACE_FUNCTION = true;

// отбрасывание полигонов
// 0 - Отбрасывать только нелицевые полигонов
// 1 - Отбрасывать только лицевые полигонов
// 2 - Отбрасывать и те и другие полигоны
constexpr unsigned short OPENGL_CULL_FACE = 0;

// порядок обхода в треугольнике
// 0 - против часовой стрелки
// 1 - по часовой стрелки
constexpr unsigned short OPENGL_FRONT_FACE = 0;

// разрешить выводить в консоль информацию об проссесах
constexpr bool CORE_INFO = true;

#endif //CONFIG_HPP
