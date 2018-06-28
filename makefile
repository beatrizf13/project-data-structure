APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src


all: do_obj app run

do_obj:
	gcc -c $(SRC)/src.c -I $(INCLUDE) -o $(OBJ)/obj.o
app:
	gcc $(APPS)/apps.c $(OBJ)/*.o -I $(INCLUDE) -o $(BIN)/bin
run:
	$(BIN)/bin
clean:
	rm $(BIN)/bin
	rm $(OBJ)/*.o

*.o: $(SRC)/*.c $(INCLUDE)/*.h
	gcc -c $< -I $(INCLUDE) -o $(OBJ)/$@
