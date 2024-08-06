#pragma once
#include <numeric>

namespace dgn
{
	using base_type = uint8_t;

	inline constexpr char g_DefaultEmptyBase = '*';

	inline std::vector<char> g_ValidBases =
	{
		'N', 'D', 'V', 'B', 'H',
		'W', 'S', 'K', 'M', 'Y', 'R',
		'A', 'C', 'G', 'T',
		'.', '-', '*',
	};

	inline std::unordered_map<char, uint8_t> g_BaseToNibble = {
		{ 'A', 0x0 },
		{ 'C', 0x1 },
		{ 'G', 0x2 },
		{ 'T', 0x3 },
		{ '*', 0x4 },

		{ 'Y', 0x5 },
		{ 'W', 0x6 },
		{ 'S', 0x7 },
		{ 'R', 0x8 },
		{ 'M', 0x9 },
		{ 'K', 0xA },

		{ 'V', 0xB },
		{ 'H', 0xC },
		{ 'D', 0xD },
		{ 'B', 0xE },

		{ 'N', 0xF },
	};

	// TODO: convert to consteval:
	inline std::unordered_map<char, uint8_t> g_NibbleToBase = {
		{ 0x0, 'A' },
		{ 0x1, 'C' },
		{ 0x2, 'G' },
		{ 0x3, 'T' },
		{ 0x4, '*' },

		{ 0x5, 'Y' },
		{ 0x6, 'W' },
		{ 0x7, 'S' },
		{ 0x8, 'R' },
		{ 0x9, 'M' },
		{ 0xA, 'K' },

		{ 0xB, 'V' },
		{ 0xC, 'H' },
		{ 0xD, 'D' },
		{ 0xE, 'B' },

		{ 0xF, 'N' },
	};

	inline constexpr char g_LastNormalBase		= 0x4;		// *
	inline constexpr char g_LastDualBase		= 0xA;		// K
	inline constexpr char g_LastTripleBase		= 0xE;		// B

	inline std::unordered_map<base_type, std::vector<base_type>> g_BaseMap =
	{
		{ 0x0, { 0x0 }},
		{ 0x1, { 0x1 }},
		{ 0x2, { 0x2 }},
		{ 0x3, { 0x3 }},
		{ 0x4, { 0x4 }},

		{ 0x5, { 0x1, 0x3 }},
		{ 0x6, { 0x0, 0x3 }},
		{ 0x7, { 0x1, 0x2 }},
		{ 0x8, { 0x0, 0x2 }},
		{ 0x9, { 0x0, 0x1 }},
		{ 0xA, { 0x2, 0x3 }},

		{ 0xB, { 0x0, 0x1, 0x2 }},
		{ 0xC, { 0x0, 0x1, 0x3 }},
		{ 0xD, { 0x0, 0x2, 0x3 }},
		{ 0xE, { 0x1, 0x2, 0x3 }},

		{ 0xF, { 0x0, 0x1, 0x2, 0x3 }}
	};

	constexpr inline bool isDegenerateBase(base_type base)
	{
		return !(base <= g_LastNormalBase);
	}
}