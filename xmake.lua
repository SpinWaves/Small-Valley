add_requires("libsdl_image", "libsdl", "libsdl_ttf", "glew", "glm")

add_rules("mode.debug", "mode.release")
set_languages("c++17")

set_objectdir("build-int/$(os)_$(arch)")
set_targetdir("build/$(os)_$(arch)")

target("World")
	set_kind("binary")
	add_files("src/**.cpp")
	add_includedirs("src")

	if is_mode("debug") then
		add_defines("DEBUG")
	elseif is_mode("release") then
		add_defines("RELEASE")
	end

	add_defines("MAIN_DIR=\"$(projectdir)/\"")
	add_defines("RES_DIR=\"$(projectdir)/ressources/\"")
	add_defines("SDL_MAIN_HANDLED")
    set_pcxxheader("src/pch.h")

	add_packages("libsdl_image", "libsdl", "libsdl_ttf", "glew", "glm")
target_end() -- optional but I think the code is cleaner with this
