#ifndef GODOT_CPP_VISUALSCRIPTRETURN_HPP
#define GODOT_CPP_VISUALSCRIPTRETURN_HPP


#include <gdnative_api_struct.gen.h>
#include <stdint.h>

#include <core/CoreTypes.hpp>
#include <core/Ref.hpp>
#include "Variant.hpp"

#include "VisualScriptNode.hpp"
namespace godot {


class VisualScriptReturn : public VisualScriptNode {
	struct ___method_bindings {
		godot_method_bind *mb_get_return_type;
		godot_method_bind *mb_is_return_value_enabled;
		godot_method_bind *mb_set_enable_return_value;
		godot_method_bind *mb_set_return_type;
	};
	static ___method_bindings ___mb;
	static void *_detail_class_tag;

public:
	static void ___init_method_bindings();
	inline static size_t ___get_id() { return (size_t)_detail_class_tag; }

	static inline const char *___get_class_name() { return (const char *) "VisualScriptReturn"; }
	static inline const char *___get_godot_class_name() { return (const char *) "VisualScriptReturn"; }
	static inline Object *___get_from_variant(Variant a) { godot_object *o = (godot_object*) a; return (o) ? (Object *) godot::nativescript_1_1_api->godot_nativescript_get_instance_binding_data(godot::_RegisterState::language_index, o) : nullptr; }

	// enums

	// constants


	static VisualScriptReturn *_new();

	// methods
	Variant::Type get_return_type() const;
	bool is_return_value_enabled() const;
	void set_enable_return_value(const bool enable);
	void set_return_type(const int64_t type);

};

}

#endif