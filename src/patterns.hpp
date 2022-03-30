#pragma once

#include <SPTLib\memutils.hpp>
#include <SPTLib\patterns.hpp>
#include <array>
#include <cstddef>

namespace patterns
{
	namespace ifm
	{
		// TODO: Find a better pattern for this.
		PATTERNS(CMovieDocOnDataChanged,
			"5841",
			"A1 ?? ?? ?? ?? 85 C0 75 ?? 68 58 02 00 00 E8 ?? ?? ?? ?? 83 C4 04 85 C0 74 ?? 8B C8 E8 ?? ?? ?? ?? 50");
		PATTERNS(PaintViewport,
			"5841",
			"55 8B EC 81 EC 24 02 00 00 A1 ?? ?? ?? ?? 33 C5 89 45 ?? A1 ?? ?? ?? ??");
	} // namespace ifm
} // namespace patterns
