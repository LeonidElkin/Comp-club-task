#pragma once

#include <chrono>
#include <format>
#include <fstream>
#include <iostream>

#include "EventIds.h"

class CompClub;

class Event {
	std::chrono::minutes time_;
	uint8_t id_;

   public:
	virtual std::string formatBody() = 0;
	virtual ~Event() = default;
	explicit Event(std::chrono::minutes time, uint8_t eventId) : time_(time), id_(eventId) {}
	Event(const Event& other) = default;
	Event(Event&& other) = default;
	Event& operator=(const Event& other) = default;
	Event& operator=(Event&& other) = default;
	[[nodiscard]] const auto& getTime() { return time_; }
	[[nodiscard]] auto getId() const { return id_; }
};

class OutcEvent : public Event {
   public:
	explicit OutcEvent(std::chrono::minutes time, uint8_t eventId) : Event(time, eventId) {}
};

class OutcEventError : public OutcEvent {
	std::string msg_;

   public:
	std::string formatBody() override;
	explicit OutcEventError(std::chrono::minutes time, std::string msg)
	    : OutcEvent(time, OutcEventErrorId), msg_(std::move(msg)) {}
};

class OutcEventClientLeft : public OutcEvent {
	std::string clientName_;

   public:
	std::string formatBody() override;
	explicit OutcEventClientLeft(std::chrono::minutes time, std::string clientName)
	    : OutcEvent(time, OutcEventClientLeftId), clientName_(std::move(clientName)) {}
};

class OutcEventClientChangingTable : public OutcEvent {
	std::string clientName_;
	size_t tableId_;

   public:
	std::string formatBody() override;
	explicit OutcEventClientChangingTable(std::chrono::minutes time, std::string clientName, size_t tableId)
	    : OutcEvent(time, OutcEventClientChangingTableId), clientName_(std::move(clientName)), tableId_(tableId) {}
};

class IncEvent : public Event {
   public:
	explicit IncEvent(const std::chrono::minutes& time, uint8_t eventId) : Event(time, eventId) {}
	[[nodiscard]] virtual std::unique_ptr<Event> clone() const = 0;
	virtual std::optional<std::unique_ptr<OutcEvent>> handle(CompClub& clubInfo) = 0;
	virtual void parseBody(std::istream& input) = 0;
};

class IncEventClientComing : public IncEvent {
	std::string clientName_;

   public:
	std::string formatBody() override;
	[[nodiscard]] std::unique_ptr<Event> clone() const override;
	explicit IncEventClientComing(const std::chrono::minutes& time) : IncEvent(time, IncEventClientComingId) {}
	void parseBody(std::istream& input) override;
	std::optional<std::unique_ptr<OutcEvent>> handle(CompClub& clubInfo) override;
};

class IncEventClientChangingTable : public IncEvent {
	std::string clientName_;
	size_t tableId_{};

   public:
	std::string formatBody() override;
	explicit IncEventClientChangingTable(const std::chrono::minutes& time)
	    : IncEvent(time, IncEventClientChangingTableId) {}
	[[nodiscard]] std::unique_ptr<Event> clone() const override;
	void parseBody(std::istream& input) override;
	std::optional<std::unique_ptr<OutcEvent>> handle(CompClub& clubInfo) override;
};

class IncEventClientWaiting : public IncEvent {
	std::string clientName_;

   public:
	std::string formatBody() override;
	[[nodiscard]] std::unique_ptr<Event> clone() const override;
	explicit IncEventClientWaiting(const std::chrono::minutes& time) : IncEvent(time, IncEventClientWaitingId) {}
	void parseBody(std::istream& input) override;
	std::optional<std::unique_ptr<OutcEvent>> handle(CompClub& clubInfo) override;
};

class IncEventClientLeft : public IncEvent {
	std::string clientName_;

   public:
	std::string formatBody() override;
	[[nodiscard]] std::unique_ptr<Event> clone() const override;
	explicit IncEventClientLeft(const std::chrono::minutes& time) : IncEvent(time, IncEventClientLeftId) {}
	void parseBody(std::istream& input) override;

	std::optional<std::unique_ptr<OutcEvent>> handle(CompClub& clubInfo) override;
};
