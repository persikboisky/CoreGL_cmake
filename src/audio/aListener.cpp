//
// Created by kisly on 08.12.2025.
//

#include "aListener.hpp"
#include "../types/pos.hpp"
#include "../math/Vectors.hpp"
#include <AL/al.h>

namespace core::audio::listener
{
	void setPos(float x, float y, float z)
	{
		alListener3f(AL_POSITION, x, y, z);
	}

	void setPos(const Pos3f& pos)
	{
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	}

	void setPos(const math::Vec3& pos)
	{
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	}

	void setVel(float x, float y, float z)
	{
		alListener3f(AL_VELOCITY, x, y, z);
	}

	void setVel(const Pos3f& pos)
	{
		alListener3f(AL_VELOCITY, pos.x, pos.y, pos.z);
	}

	void setOrientation(
			float tX, float tY, float tZ,
			float upX, float upY, float upZ)
	{
		ALfloat listener_ori[] = {
				tX, tY, tZ,
				upX, upY, upZ
		};
		alListenerfv(AL_ORIENTATION, listener_ori);
	}

	void setOrientation(const math::Vec3& target, const math::Vec3& up)
	{
		ALfloat listener_ori[] = {
				target.x, target.y, target.z,
				up.x, up.y, up.z
		};
		alListenerfv(AL_ORIENTATION, listener_ori);
	}
} // core::audio::listener

