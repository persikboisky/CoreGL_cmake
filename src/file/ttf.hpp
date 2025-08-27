//
// Created by kisly on 25.08.2025.
//


#ifndef TTF_HPP
#define TTF_HPP

namespace core
{
	class TTF
	{
	private:
		TTF(const char* path);

	public:
		static TTF load(const char* path);
		static TTF* ptrLoad(const char* path);

		~TTF();
	};
}

#endif //TTF_HPP