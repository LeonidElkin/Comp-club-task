#pragma once

#include <chrono>
#include <format>
#include <map>
#include <queue>
#include <unordered_map>

#include "Event.h"
#include "EventIds.h"
#include "TableInfo.h"

class CompClub {
	size_t tablesNum_;
	size_t costPerHour_;
	size_t busyTablesNum_{0ULL};
	std::chrono::minutes startTime_;
	std::chrono::minutes endTime_;
	std::map<std::string, size_t> clients_;
	std::vector<TableInfo> tablesInfo_;
	std::queue<std::string> clientQueue_;
	std::vector<std::unique_ptr<IncEvent>> incEvents_;
	std::vector<std::unique_ptr<Event>> allEvents_;

	void parseEvent(const std::string &curString);

   public:
	explicit CompClub(size_t tablesNum, size_t costPerHour, std::chrono::minutes stTimeMinutes,
	                  std::chrono::minutes endTimeMinutes)
	    : tablesNum_(tablesNum),
	      costPerHour_(costPerHour),
	      startTime_(stTimeMinutes),
	      endTime_(endTimeMinutes),
	      tablesInfo_(tablesNum + 1, TableInfo(false)) {}

	void parseEventsAndValidate(std::istream &input);

	void handleEvents();

	void printResults(std::ostream &out);

	bool clientCame(const std::string &name);
	bool isClientHere(const std::string &name);
	bool isTableBusy(size_t tableId);
	void queueClient(const std::string &name);
	void clientLeft(const std::string &name, const std::chrono::minutes &time);
	void changeSeat(const std::string &name, size_t tableId, const std::chrono::minutes &time);
	std::optional<std::pair<std::string, size_t>> clientLeftQueue(const std::string &leftClient,
	                                                              const std::chrono::minutes &time);
	[[nodiscard]] auto checkQueueSize() { return clientQueue_.size() >= tablesNum_; }
	[[nodiscard]] bool isThereAnyEmptyTable() const { return busyTablesNum_ < tablesNum_; }
	[[nodiscard]] auto getStartTime() const { return startTime_; }
};
