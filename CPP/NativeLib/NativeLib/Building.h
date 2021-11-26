#pragma once

#include "StaticUnit.h"
#include "CharacterSlot.h"
#include <vector>

using namespace std;

class Building : public StaticUnit {
public:
    Building(int _id, string _name, Rect2 _ocupation_area, int _character_slot_num)
        : StaticUnit(_id, _name, _ocupation_area), character_slot_num(_character_slot_num) {
    }

    ~Building() {
        for (auto slot : character_slots) {
            delete(slot);
        }
    }

    int character_slot_num;
    vector<CharacterSlot*> character_slots;

    void AssignCharacter(Character* character) {
        if (character_slots.size() < character_slot_num) {
            character_slots.push_back(new CharacterSlot(character));
        }
        else {
            printf("[Building]WARNING: trying to assigned resident to full building.\nbuilding_id = %d\n", id);
        }
    }

    void FreeResident(int resident_id) {
        for (int i = 0; i < character_slots.size(); i++) {
            CharacterSlot* slot = character_slots[i];
            if (slot->GetCharacterId() == resident_id) {
                delete(character_slots[i]);
                character_slots.erase(character_slots.begin()+i);
                return;
            }
        }
        printf("[Building]WARNING: trying to free unassigned resident.\nbuilding_id = %d, character_id = %d\n", id, resident_id);
    }

    Vector2 GetCenterPosition() {
        Vector2 position = ocupation_area.get_position();
        Vector2 size = ocupation_area.get_size();
        return Vector2(position.x + size.x/2, position.y + size.y/2);
    }
};