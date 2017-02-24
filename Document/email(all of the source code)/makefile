CC=gcc
INCLUDE = ./include/
OBJ = ./obj/
BIN = ./bin/
SRC = ./src/

OBJS = ./obj/rule_database.o 
TARGET = ./bin/rule_database
CFLAG2 =-g -w -Wall -O2 -lsqlite3 -lpthread -o 
SRCS = ./src/rule_database.c

all:$(TARGET) $(SRC)*.c
	$(CC) $(CFLAG2) $(BIN)server $(SRC)server.c $(SRC)login_server.c $(SRC)register_server.c $(SRC)send_server.c $(SRC)save_server.c $(SRC)change_password_server.c $(SRC)delete_server.c $(SRC)gettime_server.c $(SRC)openrcvb_server.c  $(SRC)openrcvm_server.c $(SRC)opensndb_server.c $(SRC)opendrftb_server.c $(SRC)openrbb_server.c $(SRC)openydmb_server.c $(SRC)openwdmb_server.c $(SRC)getlinkmen_server.c $(SRC)note_server.c $(SRC)recover_server.c -I $(INCLUDE)
	$(CC) $(CFLAG2) $(BIN)client $(SRC)client.c $(SRC)connect.c $(SRC)window.c $(SRC)callback.c $(SRC)getmailbox.c $(SRC)getmsg.c -I $(INCLUDE) `pkg-config --cflags --libs gtk+-2.0`
	
	


$(TARGET): $(OBJS)
	$(CC) $(CFLAG2)  $(TARGET) $(OBJS)
$(OBJS):$(SRCS)
	$(CC) $(CFLAG2)  $@ -c $(SRCS) -I $(INCLUDE)

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/server
	rm $(BIN)/client
	rm -rf $(OBJS) $(TARGET)
	

	
