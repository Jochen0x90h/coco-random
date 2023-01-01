# hex generator
separate_arguments(GENERATE_HEX)
macro(generate_hex TARGET)
	if(NOT "${GENERATE_HEX}" STREQUAL "" AND NOT "${GENERATE_HEX}" STREQUAL "None")
		#message("*** Generate Hex for ${TARGET}: ${GENERATE_HEX}")
		add_custom_command(TARGET ${TARGET}
			POST_BUILD
			COMMAND ${GENERATE_HEX} ${TARGET} ${TARGET}.hex
		)
	endif()
endmacro()

if(SERIES)
	# generate RandomTest for every board
	foreach(BOARD ${coco-devboards_COMPONENT_NAMES})
		string(REGEX REPLACE ".*\\:" "RandomTest-" NAME ${BOARD})
		add_executable(${NAME}
			RandomTest.cpp
		)
		target_include_directories(${NAME}
			PRIVATE
				../
		)

		# find link.ld of board
		get_target_property(INCLUDES ${BOARD} INTERFACE_INCLUDE_DIRECTORIES)
		target_link_directories(${NAME}
			PRIVATE	
				${INCLUDES}
		)

		target_link_libraries(${NAME}
			coco::coco
			${BOARD}
			coco-loop::coco-loop
			coco-usb::coco-usb
			${PROJECT_NAME}
		)

		# windows specific libraries
		if(WIN32)
			target_link_libraries(${NAME} wsock32 ws2_32 winmm)
		endif()

		# generate hex file for flashing the target
		generate_hex(${NAME})
	endforeach()
endif()


if(NOT ${CMAKE_CROSSCOMPILING})
	# Host program for USB device test: Run on host computer while USB device is connected
	add_executable(RandomTestHost
		RandomTestHost.cpp
		libusb.hpp
	)
	target_include_directories(RandomTestHost
		PRIVATE
			..
	)
	target_link_libraries(RandomTestHost
		coco::coco
		coco-usb::coco-usb
		libusb::libusb
	)
endif()
