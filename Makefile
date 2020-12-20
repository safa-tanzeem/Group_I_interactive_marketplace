CC=gcc
INCLUDE=-I include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME IF THEY DO NOT EXIST
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)

all: runmarketplace

#TARGETS TO GENERATE THE OBJECT FILES
buyer_functions.o: src/buyer_functions.c 
	$(CC) -g $(INCLUDE) -c src/buyer_functions.c -o build/buyer_functions.o

scanner.o: src/scanner.c 
	$(CC) -g $(INCLUDE) -c src/scanner.c -o build/scanner.o	

main.o: src/main.c
	$(CC) -g $(INCLUDE) -c src/main.c -o build/main.o	

buyer_wallet.o: src/buyer_wallet.c
	$(CC) -g $(INCLUDE) -c src/buyer_wallet.c -o build/buyer_wallet.o

common.o: src/common.c
	$(CC) -g $(INCLUDE) -c src/common.c -o build/common.o
	
display_inventory.o: src/display_inventory.c
	$(CC) -g $(INCLUDE) -c src/display_inventory.c -o build/display_inventory.o
	
inventory_creation.o: src/inventory_creation.c
	$(CC) -g $(INCLUDE) -c src/inventory_creation.c -o build/inventory_creation.o
	
seller_manager.o: src/seller_manager.c
	$(CC) -g $(INCLUDE) -c src/seller_manager.c -o build/seller_manager.o
	
seller_menu.o: src/seller_menu.c
	$(CC) -g $(INCLUDE) -c src/seller_menu.c -o build/seller_menu.o

stock_update.o: src/stock_update.c
	$(CC) -g $(INCLUDE) -c src/stock_update.c -o build/stock_update.o
	
update_buyer_info.o: src/update_buyer_info.c
	$(CC) -g $(INCLUDE) -c src/update_buyer_info.c -o build/update_buyer_info.o


#TARGET TO GENERATE THE EXECUTABLE OF THE PROGRAM (and the tests) - LINK OBJECT FILES
marketplace: main.o buyer_wallet.o common.o display_inventory.o inventory_creation.o seller_manager.o seller_menu.o stock_update.o update_buyer_info.o buyer_functions.o scanner.o
	$(CC) -g -o bin/MARKETPLACE.exe build/main.o build/buyer_wallet.o build/common.o build/display_inventory.o build/inventory_creation.o build/seller_manager.o build/seller_menu.o build/stock_update.o build/update_buyer_info.o build/buyer_functions.o build/scanner.o


#TARGET TO RUN MARKETPLACE
launchmarketplace:
		cd ./bin; ./MARKETPLACE.exe

#TARGET TO COMPILE/RUN MARKETPLACE
runmarketplace: marketplace launchmarketplace



#CLEAN COMMANDS
clean: 
	rm -f bin/*.exe build/*.o
