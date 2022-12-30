#pragma once

enum e_resource_id
{
	_resource_id_bg,
	_resource_id_button_large,
	_resource_id_checkbox,
	_resource_id_icon_modded,
	_resource_id_icon_vanilla,
	_resource_id_icon_launcher_logo,
	_resource_id_icon_window_button_close,
	_resource_id_icon_window_button_minimise,
	_resource_id_font_barlow,
	_resource_id_shader_texcard_vert,
	_resource_id_shader_texcard_frag,
	k_number_of_resource_ids
};

void load_resource(e_resource_id id, void*& data, size_t& size);
