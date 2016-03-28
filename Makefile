PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
LD = $(PREFIX)ld
OBJCOPY = $(PREFIX)objcopy

SRC = src
OBJ = obj
INCLUDE = include

TARGET = kernel.img
ELF_TARGET = kernel.elf
LINKER_SCRIPT = kernel.ld

S_SOURCES = $(SRC)/bootstrap.s $(SRC)/context_switch.s $(SRC)/syscall.s
S_OBJECTS = $(OBJ)/bootstrap.o $(OBJ)/context_switch.o $(OBJ)/syscall.o
C_SOURCES = $(wildcard $(SRC)/*.c)
C_OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(C_SOURCES))
ALL_OBJECTS = $(S_OBJECTS) $(C_OBJECTS)

all: $(TARGET)

$(TARGET): $(ELF_TARGET)
	$(OBJCOPY) -O binary $(ELF_TARGET) $(TARGET)

$(ELF_TARGET): $(ALL_OBJECTS)
	$(LD) -T $(LINKER_SCRIPT) $(ALL_OBJECTS) -o $(ELF_TARGET)

$(OBJ)/%.o: $(SRC)/%.s $(OBJ)
	$(AS) $< -I $(INCLUDE) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) -std=gnu99 -I $(INCLUDE) -c -nostdinc -nostdlib -ffreestanding -O2 $< -o $@

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -rf $(OBJ)
	rm -f $(ELF_TARGET)
	rm -f $(TARGET)
