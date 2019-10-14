SRC_DIR   :="$(CURRENT_DIR)/"
OBJ_DIR   :="$(CURRENT_DIR)/obj/"
BUILD_DIR :="$(CURRENT_DIR)/build/"

#OBJS := $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
#BUILD := $(OBJS:$(OBJ_DIR)%.o=$(BUILD_DIR)%)
#BUILD3 := $(OBJS:$(OBJ_DIR)%.o=$(BUILD_DIR)%.out)

#OBJS := $(SRCS:./%.c=./obj/%.o)
#BUILD := $(OBJS:./obj/%.o=./build/%)
#BUILD3 := $(OBJS:./obj/%.o=./build/%.out)

OBJS := $(SRCS:./%.c=./%.o)
BUILD := $(OBJS:./%.o=./%)
BUILD3 := $(OBJS:./%.o=./%.out)

.SECONDARY: $(OBJS)

part-all: $(BUILD3)
	@echo "SRC,OBJ,BUILD: \n$(SRCS)::: \n$(OBJS)::: \n$(BUILD)::: \n"
	@echo "PATH \n$(SRC_DIR)::: \n$(OBJ_DIR)::: \n$(BUILD_DIR)::: \n \n"
	-mkdir ./build/
	-mkdir ./obj/
	mv -f $(BUILD) ./build/
	mv -f $(OBJS) ./obj/

.PHONY: all-part
