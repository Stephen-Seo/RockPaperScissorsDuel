ifdef RELEASE
	OTHER_FLAGS = -DNDEBUG -O3
else
	OTHER_FLAGS = -O0
endif

SOURCES = \
		../src/main.cc

HEADERS = \
		../src/constants.h

CXX = source ${HOME}/git/emsdk/emsdk_env.sh && em++

all: | format rock_paper_scissors_duel.html

rock_paper_scissors_duel.html: ${SOURCES} ${HEADERS}
	${CXX} -o rock_paper_scissors_duel.html \
		-s USE_GLFW=3 -I../wasm_includes -L../wasm_libs -lraylib \
		--shell-file custom_shell.html \
		-sEXPORTED_FUNCTIONS=_main,_game_visual_update \
		-sEXPORTED_RUNTIME_METHODS=ccall \
		${OTHER_FLAGS} \
		${SOURCES}

.PHONY: clean format

clean:
	rm -f rock_paper_scissors_duel.html
	rm -f rock_paper_scissors_duel.js
	rm -f rock_paper_scissors_duel.wasm
	rm -f rock_paper_scissors_duel.data

format:
	clang-format -i --style=file ${SOURCES} ${HEADERS}
