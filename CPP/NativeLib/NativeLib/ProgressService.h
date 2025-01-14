#pragma once
#pragma execution_character_set("utf-8")
#include "EventGenerator.h"
#include "Common.h"
#include "RepeatitionRandomOcccurrence.h"

class ProgressService {
private:
	ObjectService* object_service;
	RandomRepository* random_repo;
	TimeRepository* time_repo;
	EventLogRepository* event_log_repo;
	RepeatitionRandomOccurrence guest_visit_event;

	Timer time_update_interval;

	void CreateNewTimeEvent() {

	}

	void VisitNewGuest() {
		Character* new_character =  object_service->CreateNewGuest();
		event_log_repo->AddLog(EventLog(
			"�մ� �湮", "�մ� " + to_string(new_character->GetId()) + " �湮��", time_repo->CaptureGameTime(),
			new_character->GetPhysics()->GetPosition()
		));
	}
public:
	ProgressService(ObjectService* _object_service, RandomRepository* _random_repo,
		TimeRepository* _time_repo, EventLogRepository* _event_log_repo)
	: object_service(_object_service), random_repo(_random_repo),
		time_repo(_time_repo), event_log_repo(_event_log_repo),
		time_update_interval(Timer(UPDATE_INTERVAL_TIME)) {
		guest_visit_event.setProbability(0.07f);
	}

	void Update(float delta) {
		time_update_interval.TimeGo(delta);
		int time_update_number = time_update_interval.GetPassNumberAndReset();
		while (time_update_number > 0) {
			time_repo->PassOneTick();
			if (guest_visit_event.isOccurrence(random_repo->GetRandomSeedByNowTime(time_repo->GetOverallTime()))) {
				VisitNewGuest();
			}

			time_update_number--;
		}

	}
};