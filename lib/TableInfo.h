#pragma once

#include <chrono>

class TableInfo {
	bool isBusyAtTheMoment_;
	std::chrono::minutes totalBusyTime_;
	std::chrono::minutes lastChangeSeatTime_;
	size_t profit_{0ULL};

   public:
	explicit TableInfo(bool busy) : isBusyAtTheMoment_(busy), totalBusyTime_(0), lastChangeSeatTime_(0) {}

	void busy(const std::chrono::minutes &time);

	void notBusy(const std::chrono::minutes &time);

	void calculateProfit(size_t costPerHour);

	[[nodiscard]] bool isBusy() const { return isBusyAtTheMoment_; }

	[[nodiscard]] auto getProfit() const { return profit_; }

	[[nodiscard]] auto getTotalBusyTime() const { return totalBusyTime_; }
};
