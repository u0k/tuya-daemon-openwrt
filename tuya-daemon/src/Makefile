SRC_DIR := .
BUILD_DIR := ../build/src
INCLUDE_DIR := ./include

SRCS := $(wildcard $(SRC_DIR)/*.c)
DEPS := $(wildcard $(INCLUDE_DIR)/*.h)
_OBJ := $(shell basename -a $(SRCS:.c=.o))
BIN := tuya_daemon
OBJ := $(patsubst %, $(BUILD_DIR)/%, $(_OBJ))
LDFLAGS:= -llink_core -lutils_modules -lplatform_port -lmiddleware_implementation -largp -lubus -lubox -lblobmsg_json
CFLAGS := -Wall -g -I$(INCLUDE_DIR)

.PHONY: all
all: $(SRC) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)/*.o