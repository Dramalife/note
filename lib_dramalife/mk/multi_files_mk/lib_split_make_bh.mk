# Ref : https://github.com/21cnbao/training/makefile/mul-dir-exam/Makefile

SRC_DIR   :=$(CURRENT_DIR)/
BUILD_DIR :=$(SRC_DIR)build/
OBJ_DIR   :=$(BUILD_DIR)obj/

SRCS := $(wildcard $(SRC_DIR)*.c)
OBJS := $(SRCS:.c=.o)
BUILD := $(OBJS:.o=.out)

# make [TAB] all xx.out yy.out
.SECONDARY: $(OBJS) $(BUILD)

$(OBJS) : %.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD) : %.out:%.o
	$(CC) $< -o $@ $(CFLAGS)
	
part-rename1015 : $(BUILD)
	@echo "SRCS: \n$(SRCS)"
	@echo "OBJS: \n$(OBJS)"
	@echo "BUILD: \n$(BUILD)"
	@echo "PATH \nSRC_DIR: \n$(SRC_DIR) \nOBJ_DIR: \n$(OBJ_DIR) \nBUILD_DIR: \n$(BUILD_DIR) \n"
	-mkdir $(BUILD_DIR)
	-mkdir $(OBJ_DIR)
	mv -f $(BUILD) $(BUILD_DIR)
	mv -f $(OBJS) $(OBJ_DIR)

.PHONY: part-rename1015
