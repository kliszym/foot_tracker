#pragma once

#ifdef FOOTTRACKER_EXPORTS
#define FOOTTRACKER_API __declspec(dllexport)
#else
#define FOOTTRACKER_API __declspec(dllimport)
#endif

#define FILE_NOT_FOUND	1
#define OUT_OF_BUFFER	2
#define MEMORY_ERROR	3

#define CAVE_SIZE		0

struct Point {
	float x;
	float y;
};

extern "C" FOOTTRACKER_API void peopleFindByFoot(char* path);

extern "C" FOOTTRACKER_API int errorCheck();
extern "C" FOOTTRACKER_API int peopleCount();

extern "C" FOOTTRACKER_API Point peopleCoordsNormalized(int number);
extern "C" FOOTTRACKER_API Point peopleCoordsPixels(int number);
extern "C" FOOTTRACKER_API Point peopleCoordsMeters(int number);
extern "C" FOOTTRACKER_API Point peopleCoordsPixelsCorner(int number);
