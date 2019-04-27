BUILD_DIR ?= /,/m2_build

build:
	cmake --build ${BUILD_DIR}
run: build
	${BUILD_DIR}/main /tmp/lol.sock
spec: build
	${BUILD_DIR}/spec 1 2 3 4 5 6
conf: clean
	mkdir -pv ${BUILD_DIR}
	root="$$(pwd)" && cd ${BUILD_DIR} && cmake -G 'Ninja' "$$root"
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
