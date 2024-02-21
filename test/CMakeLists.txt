function(board_test TEST TARGET)
	#message("*** Target: ${TARGET}")
	# check if target exists
	if(TARGET ${TARGET})
		string(REGEX REPLACE ".*\\:" "" BOARD ${TARGET})
		set(NAME "${TEST}-${BOARD}")
		message("*** Board: ${BOARD}")

		add_executable(${NAME}
			${TEST}.cpp
		)
		target_include_directories(${NAME}
			PRIVATE
				../
				${BOARD}
		)
		target_link_libraries(${NAME}
			${TARGET}
			coco-usb::coco-usb
			${PROJECT_NAME}
		)

		# generate hex file for flashing the target
		if(${CMAKE_CROSSCOMPILING})
			#message("*** Generate Hex for ${NAME} using ${CMAKE_OBJCOPY}")
			add_custom_command(TARGET ${NAME}
				POST_BUILD
				COMMAND ${CMAKE_OBJCOPY} -O ihex ${NAME} ${NAME}.hex
			)
		endif()
	endif()
endfunction()

#message("*** coco-devboards: ${coco-devboards_COMPONENT_NAMES}")

board_test(RandomTest coco-devboards::native)
board_test(RandomTest coco-devboards::nrf52dongle)

board_test(RandomTestHost coco-devboards::native)



# hex generator
macro(generate_hex TARGET)
	if(${CMAKE_CROSSCOMPILING})
		#message("*** Generate Hex for ${TARGET} using ${CMAKE_OBJCOPY}")
		add_custom_command(TARGET ${TARGET}
			POST_BUILD
			COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET} ${TARGET}.hex
		)
	endif()
endmacro()
if(false)
# iterate over boards and generate tests
foreach(COMPONENT ${coco-devboards_COMPONENT_NAMES})
	string(REGEX REPLACE ".*\\:" "" BOARD ${COMPONENT})
	message("*** Boad: ${BOARD}")

	# check if board specific header exists
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${BOARD}/RandomTest.hpp)
		set(NAME "RandomTest-${BOARD}")
		add_executable(${NAME}
			RandomTest.cpp
		)
		target_include_directories(${NAME}
			PRIVATE
				../
				${BOARD}
		)

		# find link.ld of board
		get_target_property(INCLUDES ${COMPONENT} INTERFACE_INCLUDE_DIRECTORIES)
		target_link_directories(${NAME}
			PRIVATE
				${INCLUDES}
		)

		target_link_libraries(${NAME}
			coco::coco
			${COMPONENT}
			coco-loop::coco-loop
			coco-usb::coco-usb
			${PROJECT_NAME}
		)

		# generate hex file for flashing the target
		generate_hex(${NAME})
	endif()

	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${BOARD}/RandomTestHost.hpp)
		set(NAME "RandomTestHost-${BOARD}")
		add_executable(${NAME}
			RandomTestHost.cpp
		)
		target_include_directories(${NAME}
			PRIVATE
				../
				${BOARD}
		)
		target_link_libraries(${NAME}
			coco::coco
			${COMPONENT}
			coco-loop::coco-loop
			coco-usb::coco-usb
		)
	endif()
endforeach()
endif()