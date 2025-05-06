#include "CompClub.h"

#include "Event.h"
#include "utils.h"

void CompClub::parseEvent(const std::string &curString) {
	std::string timeStr;
	std::chrono::minutes eventTime;
	std::istringstream curLineStream(curString);
	uint32_t eventId = 0;

	if (!(curLineStream >> timeStr)) {
		throw std::runtime_error("Could parse time as string");
	}

	try {
		eventTime = parseTimeToMinutes(timeStr);
	} catch (const std::invalid_argument &) {
		throw std::runtime_error("Couldn't parse event time");
	}

	if (!(curLineStream >> eventId)) {
		throw std::runtime_error("Couldn't parse event id");
	}

	std::unique_ptr<IncEvent> curEvent;

	switch (eventId) {
		case IncEventClientComingId: {
			curEvent = std::make_unique<IncEventClientComing>(eventTime);
			break;
		}
		case IncEventClientChangingTableId: {
			curEvent = std::make_unique<IncEventClientChangingTable>(eventTime);
			break;
		}
		case IncEventClientWaitingId: {
			curEvent = std::make_unique<IncEventClientWaiting>(eventTime);
			break;
		}
		case IncEventClientLeftId: {
			curEvent = std::make_unique<IncEventClientLeft>(eventTime);
			break;
		}
		default: {
			throw std::runtime_error("Couldn't parse event body");
		}
	}

	try {
		curEvent->parseBody(curLineStream);
	} catch (std::runtime_error &e) {
		throw std::runtime_error(curString);
	}

	incEvents_.push_back(std::move(curEvent));
}
void CompClub::parseEventsAndValidate(std::istream &input) {
	std::string line;
	while (std::getline(input, line)) {
		try {
			parseEvent(line);
		} catch (std::runtime_error &e) {
			throw std::runtime_error(line);
		}
	}
}
void CompClub::handleEvents() {
	for (const auto &event : incEvents_) {
		allEvents_.push_back(event->clone());
		auto outcEvent = event->handle(*this);
		if (outcEvent.has_value()) {
			allEvents_.push_back(std::move(*outcEvent));
		}
	}
	for (const auto &client : clients_) {
		allEvents_.push_back(std::make_unique<OutcEventClientLeft>(endTime_, client.first));
		auto table = clients_.find(client.first)->second;
		if (table != 0) {
			tablesInfo_.at(table).notBusy(endTime_);
			busyTablesNum_--;
		}
	}
	clients_.clear();
	for (auto &table : tablesInfo_) {
		table.calculateProfit(costPerHour_);
	}
}
void CompClub::printResults(std::ostream &out) {
	out << std::format("{:%R}", startTime_) << '\n';
	for (const auto &event : allEvents_) {
		out << std::format("{:%R}", event->getTime()) << " " << event->getId() << " " << event->formatBody() << '\n';
	}
	out << std::format("{:%R}", endTime_) << '\n';
	for (size_t i = 1; i < tablesInfo_.size(); ++i) {
		out << i << ' ' << tablesInfo_[i].getProfit() << ' ' << std::format("{:%R}", tablesInfo_[i].getTotalBusyTime())
		    << '\n';
	}
}
std::optional<std::pair<std::string, size_t>> CompClub::clientLeftQueue(const std::string &leftClient,
                                                                        const std::chrono::minutes &time) {
	if (!clientQueue_.empty()) {
		auto topClient = clientQueue_.front();
		clientQueue_.pop();
		auto leftClientTable = clients_.find(leftClient)->second;
		clientLeft(leftClient, time);
		clients_[topClient] = leftClientTable;
		tablesInfo_.at(leftClientTable).busy(time);
		return std::make_pair(topClient, leftClientTable);
	}
	clientLeft(leftClient, time);
	return std::nullopt;
}
void CompClub::clientLeft(const std::string &name, const std::chrono::minutes &time) {
	if (clients_.contains(name)) {
		auto table = clients_.find(name)->second;
		if (table != 0) {
			tablesInfo_.at(table).notBusy(time);
			busyTablesNum_--;
		}
		clients_.erase(name);
	}
}
void CompClub::changeSeat(const std::string &name, size_t tableId, const std::chrono::minutes &time) {
	auto table = clients_.find(name)->second;
	if (table == 0) {
		busyTablesNum_++;
	} else {
		tablesInfo_.at(table).notBusy(time);
	}
	tablesInfo_.at(tableId).busy(time);
	clients_[name] = tableId;
}
void CompClub::queueClient(const std::string &name) { clientQueue_.push(name); }
bool CompClub::isTableBusy(size_t tableId) { return tablesInfo_.at(tableId).isBusy(); }
bool CompClub::isClientHere(const std::string &name) { return clients_.contains(name); }
bool CompClub::clientCame(const std::string &name) { return clients_.emplace(name, 0).second; }
