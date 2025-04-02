# common_c


## jsoncpp

	cd jsoncpp/
	BUILD_TYPE=release
	#plain, debug, debugoptimized, release, minsize
	LIB_TYPE=shared
	#LIB_TYPE=static
	meson --buildtype ${BUILD_TYPE} --default-library ${LIB_TYPE} . build-${LIB_TYPE}
	ninja -v -C build-${LIB_TYPE} test 
	sudo ninja -v -C build-${LIB_TYPE} install 