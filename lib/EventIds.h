#pragma once

#include <cstdint>
enum EventsIds : uint8_t {
	OutcEventErrorId = 13,
	OutcEventClientChangingTableId = 12,
	OutcEventClientLeftId = 11,
	IncEventClientComingId = 1,
	IncEventClientChangingTableId = 2,
	IncEventClientWaitingId = 3,
	IncEventClientLeftId = 4,
};
