#pragma once
#include "GameWorldForUI.h"
#include "GameWorldForAI.h"
#include "GameWorldForWorld.h"
#include "GameWorldForInput.h"
#include "GameWorldForEvent.h"
#include "GameWorldForStaticUnit.h"
#include <string>

const unsigned int big_prime_number = 154813283;

class GameWorld :
	public GameWorldForUI, public GameWorldForAI,
	public GameWorldForWorld, public GameWorldForInput,
	public GameWorldForEvent, public GameWorldForStaticUnit {

private:
	TimeRepository time_repo;
	TileRepository tile_repo;
	ObjectRepository object_repo;
	VillageRepository village_repo;
	EventLogRepository event_log_repo;
	BuildingRepository building_repo;
	unsigned int base_random_seed;

	unsigned int ExtractSeed(string value) {
		unsigned int new_seed = 13;
		for (int i = 0; i < value.size(); i++)
			new_seed = 31 * new_seed + (int) value[i];
		return new_seed;
	}

public:
	GameWorld();
	virtual GameTime GetGameTime() { return time_repo.GetGameTime(); }
	virtual TimeRepository* GetTimeRepository() { return &time_repo; }	
	//To-do ������ repository ���� ���� �ʴ� �������� ����.
	virtual TileRepository* GetTileMap() { return &tile_repo; }
	virtual ObjectRepository* GetObjectRepository() { return &object_repo; }
	virtual VillageRepository* GetVillageRepository() { return &village_repo; }
	virtual list<EventLog> GetEventLog() { return event_log_repo.GetEventLog(); }
	virtual Tile* GetTileByPos(int pos_x, int pos_y) { return tile_repo.GetTile(pos_x, pos_y); };
	virtual Building* GetBuildingById(int id) { return building_repo.GetBuildingById(id); }
	virtual void AddBuilding(Building* building) { building_repo.AddBuilding(building); }
	virtual void DeleteBuildingFromWorld(int id) { building_repo.DeleteBuildingById(id); }
	void update(float delta);
	virtual EventLogRepository* GetEventLogRepository() { return &event_log_repo; }
	virtual void AddEventLog(EventLog new_log) {
		event_log_repo.AddLog(new_log);
	}
	virtual int GetRandomSeedByNowTime() {
		return big_prime_number * (base_random_seed + time_repo.GetOverallTime());
	}
};
