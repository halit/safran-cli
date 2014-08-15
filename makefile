TARGET = safran

SRC_EXT = .c
OBJ_EXT = .o
HDR_EXT = .h

COMPILER = ${CC}
COMPILER_FLAGS = ${CFLAGS} -lcurl -lncurses -Wall -std=c99

SRC = $(shell ls *${SRC_EXT})
HDR = $(shell ls *${HDR_EXT})
OBJ = $(shell ls *${SRC_EXT} | sed s\/${SRC_EXT}$$\/${OBJ_EXT}\/)

all: ${OBJ}
	${COMPILER} ${COMPILER_FLAGS} -o ${TARGET} ${OBJ}

%${OBJ_EXT}: %${SRC_EXT}
	${COMPILER} ${COMPILER_FLAGS} -c $< -o $@

clean:
	@if `test -e ${TARGET}`; then \
	  rm ${TARGET}; \
	fi

	@for file in ${OBJ}; do \
	  if `test -e $$file`; \
	    then rm $$file; \
	  fi \
	done
