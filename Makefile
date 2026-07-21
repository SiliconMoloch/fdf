NAME        = fdf

CC          = cc
CCFLAGS     = -Wall -Wextra -Werror

MATH_LIB    = -lm
GLFW_LIB    = -L$(GLFW_BUILD)/src -lglfw3
OPENGL_LIB  = -lGL -ldl -lpthread

GLFW_DIR    = external/glfw
GLFW_BUILD  = $(GLFW_DIR)/build

INCLUDE		= -I./include -I$(GLFW_DIR)/include
DEPSFLAGS   = -MMD -MP

SOURCES     = sources/main.c \
              sources/parse_arguments.c \
              sources/open_file.c \
              sources/parse_map.c \
              sources/parse_line.c \
              sources/render.c

OBJECTS_DIR = .objects/
OBJECTS     = ${SOURCES:.c=.o}
OBJECTS     := ${addprefix ${OBJECTS_DIR}, ${OBJECTS}}
DEPS        = ${OBJECTS:.o=.d}

all: ${NAME}

${NAME}: ${GLFW_BUILD} ${OBJECTS}
	@${CC} ${CCFLAGS} ${OBJECTS} -o ${NAME} ${GLFW_LIB} ${OPENGL_LIB} ${MATH_LIB}
	@echo "Building executable..."

${OBJECTS_DIR}%.o: %.c
	@mkdir -p $(dir $@)
	@${CC} ${CCFLAGS} ${INCLUDE} ${DEPSFLAGS} -c $< -o $@
	@echo "Building $@..."

${GLFW_BUILD}:
	cmake -S $(GLFW_DIR) -B $(GLFW_BUILD) \
		-DGLFW_BUILD_WAYLAND=OFF \
		-DGLFW_BUILD_X11=ON
	cmake --build $(GLFW_BUILD)

clean:
	@rm -rf ${OBJECTS_DIR}
	@rm -rf ${GLFW_BUILD}
	@echo "Cleaned up object files."

fclean: clean
	@rm -f ${NAME}
	@echo "Cleaned up executable."

re: fclean all

-include ${DEPS}

.PHONY: all clean fclean re
