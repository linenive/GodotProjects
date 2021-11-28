#pragma once
#include "Character.h"
#include "TaskReserveInfo.h"
#include "AIExecuter.h"
#include "TaskService.h"
#include "CoordinatesSystem.h"
#include "Timer.h"
#include "GameRule.h"
#include "ResidentService.h"

class AIService {

private:
	ObjectService* object_service;
	TaskService* task_service;
	ResidentService* resident_service;

	map<int, Character*>* characters;
	map<int, Guest*>* guests;
	map<int, Resident*>* residents;
	AIExecuter ai_executer;
	
	Timer task_assign_timer;
	Timer task_execute_timer;

	void ReserveWorldObject(WorldObject target, TaskReserveInfo task_reserve_info);
	void AddSeekTask(Character* character, Vector2 leave_point) {
		Task* new_task = task_service->CreateSeekTask(character, leave_point);
		character->GetSchedule()->SetTask(new_task);
	}
	void AddSeekTaskToHome(Character* character) {
		Vector2 home_pos = resident_service->GetResidentHomePosition(character->GetId());
		AddSeekTask(character, home_pos);
	}
	void AddLeaveVillageTask(Guest* character) {
		Task* new_task = task_service->CreateLeaveVillageTask(character);
		character->GetSchedule()->SetTask(new_task);
	}
	void AddIdleTask(Character* performer) {
		Task* new_task = task_service->CreateWanderTask(performer);
		performer->GetSchedule()->SetTask(new_task);
	}
	void FindNewTaskToResident(Character* resident) {
		AddSeekTaskToHome(resident);
		//AddIdleTask(resident);
	}
	// To-do: hard coding -> algorithm which use DB
	void FindNewTaskToGuest(Guest* guest) {
		vector<PurposeOfVisit*> purposes = ((GuestSchedule*)(guest->GetSchedule()))->GetPurposOfVisit();
		for (PurposeOfVisit* p : purposes) {
			if (p->CanExecute()) {
				// To-do: 
				AddIdleTask(guest);
				return;
			}
		}
		AddLeaveVillageTask(guest);
		//AddIdleTask(guest);
	}
	void AssignTaskToResidents() {
		// To-do: task allocator for task priority
		for (auto &kv : *residents) {
			if (!kv.second->GetSchedule()->HasTask())
				FindNewTaskToResident(kv.second);
		}
	}
	void AssignTaskToGuests() {
		// To-do: task allocator for task priority
		for (auto& kv : *guests) {
			if (!kv.second->GetSchedule()->HasTask())
				FindNewTaskToGuest(kv.second);
		}
	}
	void AssignTaskToWholeCharacter() {
		AssignTaskToResidents();
		AssignTaskToGuests();
	}
	void ExecuteCharactersTask() {
		for (auto& kv : *characters) {
			ai_executer.ExecuteCharacterTask(kv.second);
		}
	}

	void DeleteLeavers() {
		queue<int>* village_leavers = &ai_executer.village_leavers;
		while (!village_leavers->empty()) {
			int id = village_leavers->front();
			village_leavers->pop();
			object_service->DeleteCharacter(id);
		}
	}

public:
	~AIService() {
		delete task_service;
	}
	AIService(ObjectService* _object_service, TaskService* _task_service, ResidentService* _resident_service)
		: object_service(_object_service), task_service(_task_service), resident_service(_resident_service),
		task_assign_timer(Timer(ASSIGN_TASK_INTERVAL_TIME)), task_execute_timer(Timer(EXECUTE_TASK_INTERVAL_TIME)){
		characters = object_service->GetCharacters();
		guests = object_service->GetGuests();
		residents = object_service->GetResidents();
	}
	void Update(float delta) {
		task_assign_timer.TimeGo(delta);
		int task_assign_number = task_assign_timer.GetPassNumberAndReset();
		while (task_assign_number > 0) {
			AssignTaskToWholeCharacter();
			task_assign_number--;
		}

		task_execute_timer.TimeGo(delta);
		int task_execute_number = task_execute_timer.GetPassNumberAndReset();
		while (task_execute_number > 0) {
			ExecuteCharactersTask();
			task_execute_number--;
		}
		
		DeleteLeavers();
	}
};