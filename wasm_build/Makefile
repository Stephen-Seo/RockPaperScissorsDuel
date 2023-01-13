ifdef RELEASE
	OTHER_FLAGS = -DNDEBUG -O3
else
	OTHER_FLAGS = -O0
endif

SOURCES = \
		../src/main.cc \
		../src/ems.cc \
		../src/basic_renderer.cc \
		../src/helpers.cc \
		../src/3d_renderer.cc \
		../src/constants.cc \
		../src/3d/obj.cc \
		../src/3d/a3f.cc \
		../src/3d/a3f_conv.cc \
		../src/3d/qm.cc

HEADERS = \
		../src/constants.h \
		../src/ems.h \
		../src/basic_renderer.h \
		../src/helpers.h \
		../src/game_renderer.h \
		../src/3d_renderer.h \
		../src/3d/obj.h \
		../src/3d/a3f.h \
		../src/3d/a3f_conv.h \
		../src/3d/qm.h

CXX = source ${HOME}/git/emsdk/emsdk_env.sh && em++

OUTDIR = outdir

all: | format ${OUTDIR} ${OUTDIR}/rock_paper_scissors_duel.html ${OUTDIR}/index.html ${OUTDIR}/logic.js ${OUTDIR}/client.js

${OUTDIR}/rock_paper_scissors_duel.html: ${SOURCES} ${HEADERS} ${OUTDIR}/client.js ${OUTDIR}/logic.js
	${CXX} -o ${OUTDIR}/rock_paper_scissors_duel.html \
		-s USE_GLFW=3 -I../wasm_includes -L../wasm_libs -lraylib \
		--shell-file custom_shell.html \
		-sEXPORTED_FUNCTIONS=_main,_game_visual_update \
		-sEXPORTED_RUNTIME_METHODS=ccall \
		--preload-file ../resources \
		${OTHER_FLAGS} \
		${SOURCES}

${OUTDIR}:
	mkdir ${OUTDIR}

${OUTDIR}/logic.js: logic.js
	cp logic.js ${OUTDIR}/

${OUTDIR}/client.js: client.js
	cp client.js ${OUTDIR}/

.PHONY: clean format index.html

${OUTDIR}/index.html:
	ln -sf rock_paper_scissors_duel.html ${OUTDIR}/index.html

clean:
	rm -rf ${OUTDIR}

format:
	clang-format -i --style=google ${SOURCES} ${HEADERS} || true
