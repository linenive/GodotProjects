#pragma once
#include <list>
#include "Common.h"
#include "GameRule.h"
#include "EventLog.h"

class EventLogRepository {
private:
	int max_stack = EVENT_LOG_STACK_MAX;
	list<EventLog> logs;

	bool IsStackFull() {
		return logs.size() >= max_stack;
	}

public:
	void LoadData() {
		// To-do: ���̺����Ͽ��� ����Ÿ �ε�
	}

	void AddLog(EventLog new_log) {
		if (IsStackFull()) {
			logs.pop_front();
		}
		logs.push_back(new_log);
	}

	list<EventLog> GetEventLog() {
		return logs;
	}

	Array GetSerialized_event_log() {
		Array log_array = Array();
		for (EventLog log : logs) {
			Array serialized_event_log = Array();
			serialized_event_log.append(String(log.GetEventName().c_str()));
			serialized_event_log.append(String(log.GetEventDescription().c_str()));
			serialized_event_log.append(log.GetOccurrenceTime().GetYear().val);
			serialized_event_log.append(log.GetOccurrenceTime().GetMonth().val);
			serialized_event_log.append(log.GetOccurrenceTime().GetDay().val);
			serialized_event_log.append(log.GetOccurrenceTime().GetHour().val);
			serialized_event_log.append(log.GetOccurrenceTime().GetMinute().val);
			serialized_event_log.append(log.GetPosition());

			log_array.append(serialized_event_log);
		}

		return log_array;
	}
};