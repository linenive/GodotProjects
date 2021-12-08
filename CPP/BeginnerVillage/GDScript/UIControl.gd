extends CanvasLayer

export var available_popups : Array
export var used_popups : Array

var clicked_position_label : Label

var world_manager
var input_manager
var camera_manager
var static_unit_manager

var MAXIMUM_POPUP_COUNT = 10
var screen_center_pos = Vector2(362, 100)
var next_ui_pos_offset = Vector2(20, 20)

func _ready():
	world_manager = get_node("/root/Main/WorldManager")
	input_manager = get_node("/root/Main/InputManager")
	camera_manager = get_node("/root/Main/CameraManager")
	static_unit_manager = get_node("/root/Main/StaticUnitManager")
	
	clicked_position_label = $HUD/CharacterMove/ClickPositionLabel
	
	for popup in get_node("ObjectInfoUI").get_children():
		available_popups.append(popup)

func show_info_popup(id, type):
	if is_already_shown(id, type):
		set_ui_top(get_popup(id, type))
		return
	
	var instantiate_pos = get_instantiate_pos()
	var popup = get_available_popup()
	var info = get_object_info(id, type)
	
	popup.show_popup(id, type, info, instantiate_pos)

func get_object_info(id, type):
	var info
	
	if type == "Character":
		info = get_character_info(id)
	elif type == "Building":
		info = static_unit_manager.GetBuildingInfo(id)
		
	return info

func get_character_info(id):
	var character_data = world_manager.GetCharacterInfo(id)
	var inventory_size : int
	var item_info_array : Array
	var character_info = {}
	
	character_info["first_name"] = character_data[3]
	character_info["last_name"] = character_data[2]
	character_info["gender"] = character_data[4]
	inventory_size = 9
			
	for j in inventory_size:
		item_info_array = character_data[9+j]
		character_info["item" + str(j+1)] = item_info_array
	return character_info

func get_available_popup():
	if available_popups.empty():
		set_oldest_used_popup_available()
	
	var popup = available_popups.pop_front()
	set_ui_top(popup)
	
	return popup

func set_oldest_used_popup_available():
	var popup = used_popups.front()
	used_popups.pop_front()
	available_popups.push_back(popup)

func get_instantiate_pos():
	if used_popups.empty():
		return screen_center_pos
	else:
		return get_top_ui_pos() + next_ui_pos_offset

func close_info_popup(popup):
	used_popups.erase(popup)
	available_popups.push_back(popup)

func get_top_ui_pos():
	var popup = used_popups.back()
	return popup.get_position()

func set_ui_top(popup):
	used_popups.erase(popup)
	used_popups.push_back(popup)
	popup.get_parent().move_child(popup, 9)

func get_popup(id, type):
	for popup in used_popups:
		if popup.get_target_id() == id and popup.get_target_type() == type:
			return popup
	
	return null

func is_already_shown(id, type):
	if get_popup(id, type) != null:
		return true
	
	return false

func is_used_popup(popup_):
	for popup in used_popups:
		if popup == popup_:
			return true
	
	return false

func MouseRightClickLabelUpdate(new_click_position):
	clicked_position_label.text = str(new_click_position)

func popup_ui_track_btn_pressed(character_path):
	#$HUD/StopTracingBtn.visible = true
	camera_manager.SetCameraSetting_Trace(character_path)

func _on_CharacterMove_pressed():
	var game_manager = get_node("/root/Main").AIClickUpdate(input_manager.GetNowMouseRightClickPoint())

func _on_StopTracingBtn_pressed():
	#$HUD/StopTracingBtn.visible = false
	camera_manager.StopTracing()

func _on_CameraManager_start_trace():
	$HUD/StopTracingBtn.visible = true

func _on_CameraManager_stop_trace():
	$HUD/StopTracingBtn.visible = false
