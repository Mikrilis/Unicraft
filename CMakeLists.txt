cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Unicraft")

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)
add_subdirectory(lib/imgui-docking)

find_package(TBB REQUIRED)
find_package(Vulkan REQUIRED)
#find_package(X11 REQUIRED) #Uncomment when compiling for Linux

set(noOut false)
if(noOut AND WIN32)
add_executable (Unicraft WIN32
	"src/main/main.cpp" "src/main/main.h" 

	"src/render/render.cpp" "src/render/render.h"  

	"src/render/gui/gui.cpp" "src/render/gui/gui.h" 
	"src/render/gui/registergui.cpp" "src/render/gui/registergui.h" 
	"src/render/gui/initgui.cpp" "src/render/gui/initgui.h"
	
	"src/render/glfw/initglfw.cpp" "src/render/glfw/initglfw.h" 
	"src/render/glfw/registerinput.cpp" "src/render/glfw/registerinput.h" 
	
	"src/render/vulkan/initvulkan.cpp" "src/render/vulkan/initvulkan.h" 
	"src/render/vulkan/helperfunctions.cpp" "src/render/vulkan/helperfunctions.h" 

	"src/render/mainloop.cpp" "src/render/mainloop.h" 
	"src/render/runtimeservices.cpp" "src/render/runtimeservices.h" 
	
	"src/setup/setup.h" "src/setup/setup.cpp" 
	
	"lib/stb/stb_image.h"#[[ stb for loading images ]])
set_target_properties(Unicraft PROPERTIES
	LINK_FLAGS "/ENTRY:mainCRTStartup")
else()
add_executable (Unicraft
	"src/main/main.cpp" "src/main/main.h" 

	"src/render/render.cpp" "src/render/render.h"  

	"src/render/gui/gui.cpp" "src/render/gui/gui.h" 
	"src/render/gui/registergui.cpp" "src/render/gui/registergui.h" 
	"src/render/gui/initgui.cpp" "src/render/gui/initgui.h"
	
	"src/render/glfw/initglfw.cpp" "src/render/glfw/initglfw.h" 
	"src/render/glfw/registerinput.cpp" "src/render/glfw/registerinput.h" 

	"src/render/vulkan/initvulkan.cpp" "src/render/vulkan/initvulkan.h" 
	"src/render/vulkan/helperfunctions.cpp" "src/render/vulkan/helperfunctions.h" 

	"src/render/mainloop.cpp" "src/render/mainloop.h" 
	"src/render/runtimeservices.cpp" "src/render/runtimeservices.h" 
	
	"src/setup/setup.h" "src/setup/setup.cpp" 
	
	"lib/stb/stb_image.h"#[[ stb for loading images ]])
endif()


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Unicraft PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Unicraft PRIVATE glfw glm Vulkan::Vulkan TBB::tbb imgui #[[X11 #[[Uncomment when compiling for Linux]])
