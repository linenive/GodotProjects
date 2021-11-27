#pragma once

#include "ObjectRepository.h"
#include "BuildingRepository.h"
#include "House.h"
#include "WorkSpace.h"

class ResidentService {
private:
	ObjectRepository* object_repo;
	BuildingRepository* building_repo;

	void AssignCharacterToBuilding(Character* villager, int building_id) {
		Building* building = building_repo->GetBuildingById(building_id);
		building->AssignCharacter(villager);
	}

	bool HasHome(Character* resident) {
		return resident->home_id != -1;
	}

	bool HasWorkSpace(Character* resident) {
		return resident->work_space_id != -1;
	}

public:
	ResidentService(ObjectRepository* object_repo, BuildingRepository* building_repo) 
		: object_repo(object_repo), building_repo(building_repo) {}
	
	void AssignResidentToHome(int resident_id, int home_id) {
		Character* resident = object_repo->GetCharacter(resident_id);
		if (HasHome(resident)) {
			Building* home = building_repo->GetBuildingById(resident->home_id);
			home->FreeResident(resident_id);
		}

		resident->home_id = home_id;
		AssignCharacterToBuilding(resident, home_id);
	}

	void AssignResidentToWorkSpace(int resident_id, int work_space_id) {
		Character* resident = object_repo->GetCharacter(resident_id);
		if (HasWorkSpace(resident)) {
			Building* work_space = building_repo->GetBuildingById(resident->work_space_id);
			work_space->FreeResident(resident_id);
		}

		resident->work_space_id = work_space_id;
		AssignCharacterToBuilding(resident, work_space_id);
	}


	void FreeFromHome(int resident_id) {
		Character* resident = object_repo->GetCharacter(resident_id);
		Building* home = building_repo->GetBuildingById(resident->home_id);

		home->FreeResident(resident_id);
		resident->home_id = -1;
	}

	void FreeFromWorkSpace(int resident_id) {
		Character* resident = object_repo->GetCharacter(resident_id);
		Building* work_space = building_repo->GetBuildingById(resident->home_id);

		work_space->FreeResident(resident_id);
		resident->work_space_id = -1;
	}

	Vector2 GetResidentHomePosition(int resident_id) {
		Character* resident = object_repo->GetCharacter(resident_id);
		if (resident->home_id == -1) {
			printf("[ResidentService]ERROR: this resident doesn't have home! id: %d\n", resident_id);
			return Vector2(10, 10); //dummy position
		}
		else {
			Building* home = building_repo->GetBuildingById(resident->home_id);
			return home->GetCenterPosition();
		}
	}

	Vector2 GetResidentWorkPlacePosition(int resident_id) {
		Character* resident = object_repo->GetCharacter(resident_id);
		if (resident->work_space_id == -1) {
			printf("[ResidentService]ERROR: this resident doesn't have work place! id: %d\n", resident_id);
			return Vector2(10, 10); //dummy position
		}
		else {
			Building* work_place = building_repo->GetBuildingById(resident->work_space_id);
			return work_place->GetCenterPosition();
		}
	}
};