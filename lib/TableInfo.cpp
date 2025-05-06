#include "TableInfo.h"
void TableInfo::busy(const std::chrono::minutes& time) {
	isBusyAtTheMoment_ = true;
	lastChangeSeatTime_ = time;
}
void TableInfo::notBusy(const std::chrono::minutes& time) {
	isBusyAtTheMoment_ = false;
	auto lastPersonTimeSpent = time - lastChangeSeatTime_;
	profit_ += (lastPersonTimeSpent.count() + 59) / 60;
	totalBusyTime_ += lastPersonTimeSpent;
}
void TableInfo::calculateProfit(size_t costPerHour) { profit_ *= costPerHour; }
