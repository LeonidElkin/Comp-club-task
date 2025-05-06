#include "TableInfo.h"
void TableInfo::busy(const std::chrono::minutes& time) {
	isBusyAtTheMoment_ = true;
	lastChangeSeatTime_ = time;
}
void TableInfo::notBusy(const std::chrono::minutes& time) {
	isBusyAtTheMoment_ = false;
	totalBusyTime_ += (time - lastChangeSeatTime_);
}
void TableInfo::calculateProfit(size_t costPerHour) { profit_ = (totalBusyTime_.count() + 59) / 60 * costPerHour; }
