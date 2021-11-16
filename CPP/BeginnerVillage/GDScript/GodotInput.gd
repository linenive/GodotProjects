extends Control
var input_manager
var world_manager
var camera_manager
var tile_info_label
var uicontrol

func _ready():
	input_manager = get_node("/root/Main/InputManager")
	world_manager = get_node("/root/Main/WorldManager")
	camera_manager = get_node("/root/Main/CameraManager/CameraCPP")
	tile_info_label = get_node("/root/Main/UIControl/HUD/TileInfoTest")
	uicontrol = get_node("/root/Main/UIControl")

func _input(event):
	input_process_for_game_world(event)
	input_process_for_ui(event)

func input_process_for_ui(event):
	# To-do: ui 입력 처리
	pass

func input_process_for_game_world(event):
	if event is InputEventMouseButton:
		var mouse_pos = convert_position_by_camera(event.position)
		if event.button_index == BUTTON_LEFT: 
			if event.pressed:
				left_mouse_button_pressed(mouse_pos)
			else:
				left_mouse_button_released(mouse_pos)
	if event is InputEventMouseMotion:
		var mouse_pos = convert_position_by_camera(event.position)
		mouse_motion(mouse_pos)

func convert_position_by_camera(position):
	var camera_pos = camera_manager.GetCurrentCameraPosition()
	var camera_zoom = camera_manager.GetCurrentZoom()
	var camera_relative_pos = position - get_viewport_rect().size / 2
	var new_pos = camera_pos + camera_relative_pos * camera_zoom
	
	return new_pos

func left_mouse_button_pressed(position):
	input_manager.MouseClick(position)

func left_mouse_button_released(position):
	input_manager.MouseRelease(position)

func mouse_motion(position):
	input_manager.MouseHover(position)
	update_tile_info(position)
	#uicontrol.show_tile_info(position)

func update_tile_info(mouse_vector):
	var tile_id = world_manager.GetTileId(mouse_vector)
	if tile_id >= 0:
		tile_info_label.text \
			= String(tile_id)+": "+world_manager.GetTileName(tile_id) \
			+ ", scale: (" \
			+ String(world_manager.GetTileScale().x) + "," \
			+ String(world_manager.GetTileScale().y) + ")"
	else:
		tile_info_label.text = ""

func _process(_delta):
	update()
		
func _draw():
	draw_rect(Rect2(100, 100, 100, 100), Color.yellow, false, 2.0, false)
	if input_manager.IsDragging():
		draw_drag_box(input_manager.GetDragRect())
	if input_manager.IsTileHighlighting():
		draw_highlight_box(input_manager.GetTileHighlight())
	
func draw_drag_box(rect):
	draw_rect(rect, Color.white, false, 1.0, false)

func draw_highlight_box(rect):
	draw_rect(rect, Color.darkgray, false, 1.0, false)
