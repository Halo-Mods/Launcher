add_library(common STATIC
	bcs/callback.cpp
	bcs/callback.h
	bcs/callback_impl.c
	bcs/string_lookup.h
	
	cseries/cseries.cpp
	cseries/cseries.h
	cseries/flags.h
	cseries/static_string.h
	text/unicode.cpp
	text/unicode.h
	
	common_public_pch.h
	common_private_pch.h)

set_common_props(common)

set_source_files_properties(bcs/callback_impl.c PROPERTIES
	DISABLE_PRECOMPILE_HEADERS ON)

target_precompile_headers(common PRIVATE
	common_private_pch.h)
