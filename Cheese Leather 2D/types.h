#pragma once

#include <glm\glm.hpp>

#ifdef _WIN32

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
#endif
// TODO: ...
#ifdef _WIN64
#endif
#ifdef LINUX32
#endif
#ifdef LINUX64
#endif
#ifdef APPLE32
#endif
#ifdef APPLE64
#endif

using glm::i8vec2;
using glm::u8vec2;
using glm::i16vec2;
using glm::u16vec2;
using glm::i32vec2;
using glm::u32vec2;
using glm::i64vec2;
using glm::u64vec2;
using glm::fvec2;
using glm::dvec2;


using glm::i8vec3;
using glm::u8vec3;
using glm::i16vec3;
using glm::u16vec3;
using glm::i32vec3;
using glm::u32vec3;
using glm::i64vec3;
using glm::u64vec3;
using glm::fvec3;
using glm::dvec3;


using glm::i8vec4;
using glm::u8vec4;
using glm::i16vec4;
using glm::u16vec4;
using glm::i32vec4;
using glm::u32vec4;
using glm::i64vec4;
using glm::u64vec4;
using glm::fvec4;
using glm::dvec4;

template <typename T>
struct tvec2_hash
{
	typedef glm::detail::tvec2<T, glm::precision::highp> tvec2;

	size_t operator()(const tvec2& k)const
	{
		return std::hash<T>()(k.x) ^ std::hash<T>()(k.y);
	}

	bool operator()(const tvec2& a, const tvec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}

	// TODO: Make a functor for std::set and std::map
	//bool operator<(const tvec2 &o) const
	//{
	//	if (x != o.x)
	//		return x < o.x;
	//	else
	//		return y < o.y;
	//}
};

typedef tvec2_hash<i8> i8vec2_hash;
typedef tvec2_hash<u8> u8vec2_hash;
typedef tvec2_hash<i16> i16vec2_hash;
typedef tvec2_hash<u16> u16vec2_hash;
typedef tvec2_hash<i32> i22vec2_hash;
typedef tvec2_hash<u32> u22vec2_hash;
typedef tvec2_hash<i64> i64vec2_hash;
typedef tvec2_hash<u64> u64vec2_hash;
typedef tvec2_hash<float> fvec2_hash;
typedef tvec2_hash<double> dvec2_hash;

// TODO: Better solution than dot2, glm should have dot product.
template<typename T>
T dot2(glm::detail::tvec2<T, glm::precision::highp> a, glm::detail::tvec2<T, glm::precision::highp> b)
{
	return a.x * b.x + a.y * b.y;
}