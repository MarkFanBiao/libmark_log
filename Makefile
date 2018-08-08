DIR_INC=./include
DIR_LIB=./lib
DIR_OBJ=./obj
DIR_SRC=./src
VPATH=$(DIR_SRC):$(DIR_OBJ):$(DIR_LIB)
BSRC=$(wildcard $(DIR_SRC)/*.c)
SRC=$(notdir $(BSRC))
OBJ=$(patsubst %.c, %.o, $(SRC))
CC=gcc

TARGET=libmark_log.so

$(TARGET):$(OBJ)
	$(CC) $(DIR_OBJ)/$< -o $(DIR_LIB)/$@ -shared

$(OBJ):$(SRC)
	$(CC) -c $< -o $(DIR_OBJ)/$@ -fPIC -I$(DIR_INC)

install:
	-mkdir /usr/local/include/mark_log
	cp $(DIR_INC)/*.h /usr/local/include/mark_log/
	cp $(DIR_LIB)/*.so /usr/local/lib/
	ln -s /usr/local/lib/$(TARGET) /usr/lib/$(TARGET)

uninstall:
	-rm -i /usr/local/lib/$(TARGET)
	-rm -i /usr/lib/$(TARGET)
	-rm -rf /usr/local/include/mark_log

.PHONY:clean
clean:
	-rm -i $(DIR_OBJ)/*.o $(DIR_LIB)/*.so
