#include "pch.h"
#include <iostream>
#include "Vector4.h"
#include "Vector4SIMD.h"
#include <vector>
#include <ctime>
#include <random>
#include <Windows.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart);

	QueryPerformanceCounter(&li) / 1000.0;
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

int main()
{
	const int numberOfIterations = 10000000;
	srand(static_cast<unsigned int>(clock()));
	Vector4 sampleVector4(4.2f, 3.1f, 19.0f, -30.0f);
	Vector4SIMD sampleVector4SIMD(4.2f, 3.1f, 19.0f, -30.0f);

	// Prepare Test Items
	std::vector<Vector4> testItems;
	std::vector<Vector4SIMD> testItemsSIMD;

	for (int i = 0; i < numberOfIterations; ++i)
	{
		float x = (rand() / RAND_MAX) + 1.f;
		float y = (rand() / RAND_MAX) + 1.f;
		float z = (rand() / RAND_MAX) + 1.f;
		float w = (rand() / RAND_MAX) + 1.f;

		if (x == 0.f) x = 0.01f;
		if (y == 0.f) y = 0.01f;
		if (z == 0.f) z = 0.01f;
		if (w == 0.f) w = 0.01f;

		testItems.push_back(Vector4(x, y, z, w));
		testItemsSIMD.push_back(Vector4SIMD(x, y, z, w));
	}
	
	// Simple Addition
	StartCounter();
	for (const Vector4& item : testItems)
	{
		item + sampleVector4;
	}
	std::cout << "Simple Addition: " << GetCounter() << "ns" << std::endl;

	StartCounter();
	for (const Vector4SIMD& item : testItemsSIMD)
	{
		item + sampleVector4SIMD;
	}
	std::cout << "SIMD Addition: " << GetCounter() << "ns" << std::endl;

	// Simple Assignment Division

	StartCounter();
	for (Vector4& item : testItems)
	{
		item /= sampleVector4;
	}
	std::cout << "Simple Assignment Division: " << GetCounter() << "ns" << std::endl;

	StartCounter();
	for (Vector4SIMD& item : testItemsSIMD)
	{
		item /= sampleVector4SIMD;
	}
	std::cout << "SIMD Assignment Division: " << GetCounter() << "ns" << std::endl;

	// Normalise

	StartCounter();
	for (Vector4& item : testItems)
	{
		item.Normalise();
	}
	std::cout << "Simple Normalise: " << GetCounter() << "ns" << std::endl;

	StartCounter();
	for (Vector4SIMD& item : testItemsSIMD)
	{
		item.Normalise();
	}
	std::cout << "SIMD Normalise: " << GetCounter() << "ns" << std::endl;

	// Dot Product

	StartCounter();
	for (const Vector4& item : testItems)
	{
		item.Dot(sampleVector4);
	}
	std::cout << "Simple Dot Product: " << GetCounter() << "ns" << std::endl;

	StartCounter();
	for (const Vector4SIMD& item : testItemsSIMD)
	{
		item.Dot(sampleVector4SIMD);
	}
	std::cout << "SIMD Dot Product: " << GetCounter() << "ns" << std::endl;

	// Cross Product

	StartCounter();
	for (const Vector4& item : testItems)
	{
		item.Cross(sampleVector4);
	}
	std::cout << "Simple Cross Product: " << GetCounter() << "ns" << std::endl;

	StartCounter();
	for (const Vector4SIMD& item : testItemsSIMD)
	{
		item.Cross(sampleVector4SIMD);
	}
	std::cout << "SIMD Cross Product: " << GetCounter() << "ns" << std::endl;
}

//RESULTS:
//
//Simple Addition : 0.351403ns
//SIMD Addition : 0.309292ns
//Simple Assignment Division : 0.266086ns
//SIMD Assignment Division : 0.188337ns
//Simple Normalise : 1.09506ns
//SIMD Normalise : 1.20218ns
//Simple Dot Product : 0.19705ns
//SIMD Dot Product : 0.300162ns
//Simple Cross Product : 0.371702ns
//SIMD Cross Product : 0.39883ns