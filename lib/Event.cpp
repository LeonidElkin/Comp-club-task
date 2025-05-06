#include "Event.h"

#include "CompClub.h"

void IncEventClientComing::parseBody(std::istream& input) {
	if (!(input >> clientName_)) throw std::runtime_error("Wrong body");
}

void IncEventClientChangingTable::parseBody(std::istream& input) {
	if (!(input >> clientName_ >> tableId_)) throw std::runtime_error("Wrong body");
}

void IncEventClientWaiting::parseBody(std::istream& input) {
	if (!(input >> clientName_)) throw std::runtime_error("Wrong body");
}

void IncEventClientLeft::parseBody(std::istream& input) {
	if (!(input >> clientName_)) throw std::runtime_error("Wrong body");
}

std::optional<std::unique_ptr<OutcEvent>> IncEventClientComing::handle(CompClub& clubInfo) {
	if (clubInfo.getStartTime() > getTime()) {
		return std::make_unique<OutcEventError>(getTime(), "NotOpenYet");
	}
	if (!clubInfo.clientCame(clientName_)) {
		return std::make_unique<OutcEventError>(getTime(), "YouShallNotPass");
	}
	return std::nullopt;
}

std::optional<std::unique_ptr<OutcEvent>> IncEventClientChangingTable::handle(CompClub& clubInfo) {
	if (!clubInfo.isClientHere(clientName_)) {
		return std::make_unique<OutcEventError>(getTime(), "ClientUnknown");
	}
	if (clubInfo.isTableBusy(tableId_)) {
		return std::make_unique<OutcEventError>(getTime(), "PlaceIsBusy");
	}

	clubInfo.changeSeat(clientName_, tableId_, getTime());

	return std::nullopt;
}
std::optional<std::unique_ptr<OutcEvent>> IncEventClientWaiting::handle(CompClub& clubInfo) {
	if (clubInfo.isThereAnyEmptyTable()) {
		return std::make_unique<OutcEventError>(getTime(), "ICanWaitNoLonger!");
	}
	if (clubInfo.checkQueueSize()) {
		clubInfo.clientLeft(clientName_, getTime());
		return std::make_unique<OutcEventClientLeft>(getTime(), clientName_);
	}

	clubInfo.clientCame(clientName_);
	clubInfo.queueClient(clientName_);

	return std::nullopt;
}
std::optional<std::unique_ptr<OutcEvent>> IncEventClientLeft::handle(CompClub& clubInfo) {
	if (!clubInfo.isClientHere(clientName_)) {
		return std::make_unique<OutcEventError>(getTime(), "ClientUnknown");
	}
	auto topClient = clubInfo.clientLeftQueue(clientName_, getTime());
	if (topClient.has_value()) {
		return std::make_unique<OutcEventClientChangingTable>(getTime(), topClient->first, topClient->second);
	}

	return std::nullopt;
}
std::unique_ptr<Event> IncEventClientChangingTable::clone() const {
	return std::make_unique<IncEventClientChangingTable>(*this);
}
std::unique_ptr<Event> IncEventClientComing::clone() const { return std::make_unique<IncEventClientComing>(*this); }
std::unique_ptr<Event> IncEventClientWaiting::clone() const { return std::make_unique<IncEventClientWaiting>(*this); }
std::unique_ptr<Event> IncEventClientLeft::clone() const { return std::make_unique<IncEventClientLeft>(*this); }

std::string IncEventClientChangingTable::formatBody() {
	std::ostringstream oss;
	oss << clientName_ << tableId_;
	return oss.str();
}
std::string IncEventClientComing::formatBody() {
	std::ostringstream oss;
	oss << clientName_;
	return oss.str();
}

std::string IncEventClientWaiting::formatBody() {
	std::ostringstream oss;
	oss << clientName_;
	return oss.str();
}
std::string IncEventClientLeft::formatBody() {
	std::ostringstream oss;
	oss << clientName_;
	return oss.str();
}
std::string OutcEventError::formatBody() {
	std::ostringstream oss;
	oss << msg_;
	return oss.str();
	;
}
std::string OutcEventClientChangingTable::formatBody() {
	std::ostringstream oss;
	oss << clientName_ << tableId_;
	return oss.str();
}
std::string OutcEventClientLeft::formatBody() {
	std::ostringstream oss;
	oss << clientName_;
	return oss.str();
}
