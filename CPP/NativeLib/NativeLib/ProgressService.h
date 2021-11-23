#pragma once
#include "EventGenerator.h"
#include "GameWorldForProgressService.h"
#include "Common.h"
#include "RepeatitionRandomOcccurrence.h"

class ProgressService {
private:
	GameWorldForProgressService* game_service;
	ObjectService* object_service;
	TimeRepository* time_repo;
	RepeatitionRandomOccurrence guest_visit_event;

	int test_guest_num = 1;

	void CreateNewTimeEvent() {

	}
public:
	ProgressService(GameWorldForProgressService* world) {
		game_service = world;
		time_repo = world->GetTimeRepository();

		guest_visit_event.setProbability(0.1f);
	}

	void Update(float delta) {
		time_repo->TimeGo(delta);
		if (time_repo->SignalByPassOneTIck()) {
			if (guest_visit_event.isOccurrence(game_service->GetRandomSeedByNowTime())) {
				// printf("[ProgressManager]guest visit\n");
				game_service->AddEventLog(EventLog("Guest Visit", "Visit Guest " + to_string(test_guest_num), time_repo->CaptureGameTime()));
				test_guest_num++;
				object_service->CreateNewGuest();
			}
		}
	}
};