BUILD_DIR ?= /,/m3_build

build:
	cmake --build ${BUILD_DIR}
run: build
	${BUILD_DIR}/main
spec: build
	${BUILD_DIR}/spec
conf: clean
	mkdir -pv ${BUILD_DIR}
	root="$$(pwd)" && cd ${BUILD_DIR} && cmake -G 'Unix Makefiles' "$$root"
	ln -svf ${BUILD_DIR}/compile_commands.json .
doc:
	${MAKE} -C doc
clean:
	rm -rf \
		${BUILD_DIR} \
		doc/doxygen/html \
		doc/doxygen/latex \
		doc/doxygen/xml \
		doc/sphinx/build \

setup:
	pip install --user pipenv
	pipenv install
	${MAKE} conf

again: conf test

dumpcpp:
	g++ -dM -E -x c++ -

.PHONY: \
	again \
	clean \
	conf \
	doc \
	setup \
	test \
	dumpcpp
