ifdef RELEASE
	OTHER_FLAGS = -DNDEBUG -O3
else
	OTHER_FLAGS = -O0
endif

SOURCES = \
		../src/main.cc \
		../src/ems.cc \
		../src/helpers.cc \
		../src/3d_renderer.cc \
		../src/constants.cc \
		../src/3d/obj.cc \
		../src/3d/arrays.cc \
		../src/3d/arrays_conv.cc \
		../src/3d/qm.cc \
		../src/3d/anims.cc \
		../src/3d/anim_concurrent.cc \
		../src/3d/anim_sequence.cc \
		../src/3d/anim_model_shrink.cc \
		../src/3d/anim_model_grow.cc \
		../src/3d/anim_model_attack.cc \
		../src/3d/anim_model_still.cc \
		../src/3d/anim_falling_2d.cc \
		../src/3d/deferred_2d_draw.cc

HEADERS = \
		../src/constants.h \
		../src/ems.h \
		../src/helpers.h \
		../src/game_renderer.h \
		../src/3d_renderer.h \
		../src/3d/obj.h \
		../src/3d/arrays.h \
		../src/3d/arrays_conv.h \
		../src/3d/qm.h \
		../src/3d/anims.h \
		../src/3d/anim_concurrent.h \
		../src/3d/anim_sequence.h \
		../src/3d/anim_model_shrink.h \
		../src/3d/anim_model_grow.h \
		../src/3d/anim_model_attack.h \
		../src/3d/anim_model_still.h \
		../src/3d/anim_falling_2d.h \
		../src/3d/deferred_2d_draw.h

CXX = source ${HOME}/git/emsdk/emsdk_env.sh && em++

OUTDIR = outdir

all: | format ${OUTDIR} ${OUTDIR}/rock_paper_scissors_duel.html ${OUTDIR}/index.html ${OUTDIR}/logic.js ${OUTDIR}/client.js

${OUTDIR}/rock_paper_scissors_duel.html: ${SOURCES} ${HEADERS} ${OUTDIR}/client.js ${OUTDIR}/logic.js
	${CXX} -o ${OUTDIR}/rock_paper_scissors_duel.html \
		-s USE_GLFW=3 -I../wasm_includes -L../wasm_libs -lraylib \
		--shell-file custom_shell.html \
		-sEXPORTED_FUNCTIONS=_main,_game_visual_update \
		-sEXPORTED_RUNTIME_METHODS=ccall \
		-sFETCH \
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
