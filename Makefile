CC=gcc
INCLUDE=-I include
INCLUDE_TEST=-I test/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME IF THEY DO NOT EXIST
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
test_bin_folder := $(shell mkdir -p test/bin)
build_folder := $(shell mkdir -p test/build)

#EASY RUN
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
marketplace: buyer_functions.o scanner.o main.o buyer_wallet.o common.o display_inventory.o inventory_creation.o seller_manager.o seller_menu.o stock_update.o update_buyer_info.o
	$(CC) -g -o bin/MARKETPLACE.exe build/buyer_functions.o build/scanner.o build/main.o build/buyer_wallet.o build/common.o build/display_inventory.o build/inventory_creation.o build/seller_manager.o build/seller_menu.o build/stock_update.o build/update_buyer_info.o


#TARGET TO RUN MARKETPLACE
launchmarketplace:
		cd ./bin; ./MARKETPLACE.exe

#TARGET TO COMPILE/RUN MARKETPLACE
runmarketplace: marketplace launchmarketplace

#TEST OBJECT FILES
test_checkout.o: test/src/test_checkout.c
	$(CC) -g $(INCLUDE_TEST) -c test/src/test_checkout.c -o test/build/test_checkout.o
	
test_get_categories.o: test/src/test_get_categories.c
	$(CC) -g $(INCLUDE_TEST) -c test/src/test_get_categories.c -o test/build/test_get_categories.o
	
test_get_products.o: test/src/test_get_products.c
	$(CC) -g $(INCLUDE_TEST) -c test/src/test_get_products.c -o test/build/test_get_products.o
	
test_receipt_exists.o: test/src/test_receipt_exists.c
	$(CC) -g $(INCLUDE_TEST) -c test/src/test_receipt_exists.c -o test/build/test_receipt_exists.o
	
test_update_buyer_info.o: test/src/test_update_buyer_info.c
	$(CC) -g $(INCLUDE_TEST) -c test/src/test_update_buyer_info.c -o test/build/test_update_buyer_info.o

#TEST EXECUTABLES
test_checkout: test_checkout.o buyer_functions.o scanner.o buyer_wallet.o common.o display_inventory.o inventory_creation.o seller_manager.o seller_menu.o stock_update.o update_buyer_info.o
	$(CC) -g -o test/bin/TEST_CHECKOUT.exe test/build/test_checkout.o build/buyer_functions.o build/scanner.o build/buyer_wallet.o build/common.o build/display_inventory.o build/inventory_creation.o build/seller_manager.o build/seller_menu.o build/stock_update.o build/update_buyer_info.o

launch_test_checkout:
		cd ./test/bin; ./TEST_CHECKOUT.exe
		

test_get_categories: test_get_categories.o buyer_functions.o scanner.o buyer_wallet.o common.o display_inventory.o inventory_creation.o seller_manager.o seller_menu.o stock_update.o update_buyer_info.o
	$(CC) -g -o test/bin/TEST_GET_CATEGORIES.exe test/build/test_get_categories.o build/buyer_functions.o build/scanner.o build/buyer_wallet.o build/common.o build/display_inventory.o build/inventory_creation.o build/seller_manager.o build/seller_menu.o build/stock_update.o build/update_buyer_info.o

launch_get_categories:
		cd ./test/bin; ./TEST_GET_CATEGORIES.exe
		

test_get_products: test_get_products.o buyer_functions.o scanner.o buyer_wallet.o common.o display_inventory.o inventory_creation.o seller_manager.o seller_menu.o stock_update.o update_buyer_info.o
	$(CC) -g -o test/bin/TEST_GET_PRODUCTS.exe test/build/test_get_products.o build/buyer_functions.o build/scanner.o build/buyer_wallet.o build/common.o build/display_inventory.o build/inventory_creation.o build/seller_manager.o build/seller_menu.o build/stock_update.o build/update_buyer_info.o

launch_get_products:
		cd ./test/bin; ./TEST_GET_PRODUCTS.exe
		

test_receipt_exists: test_receipt_exists.o buyer_functions.o scanner.o buyer_wallet.o common.o display_inventory.o inventory_creation.o seller_manager.o seller_menu.o stock_update.o update_buyer_info.o
	$(CC) -g -o test/bin/TEST_RECEIPT_EXISTS.exe test/build/test_receipt_exists.o build/buyer_functions.o build/scanner.o build/buyer_wallet.o build/common.o build/display_inventory.o build/inventory_creation.o build/seller_manager.o build/seller_menu.o build/stock_update.o build/update_buyer_info.o

launch_test_receipt_exists:
		cd ./test/bin; ./TEST_RECEIPT_EXISTS.exe
		
test_update_buyer_info: test_update_buyer_info.o buyer_functions.o scanner.o buyer_wallet.o common.o display_inventory.o inventory_creation.o seller_manager.o seller_menu.o stock_update.o update_buyer_info.o
	$(CC) -g -o test/bin/TEST_UPDATE_BUYER_INFO.exe test/build/test_update_buyer_info.o build/buyer_functions.o build/scanner.o build/buyer_wallet.o build/common.o build/display_inventory.o build/inventory_creation.o build/seller_manager.o build/seller_menu.o build/stock_update.o build/update_buyer_info.o

launch_test_update_buyer_info:
		cd ./test/bin; ./TEST_UPDATE_BUYER_INFO.exe
		
#RUN AND LAUNCH TESTS
run_test_checkout: test_checkout launch_test_checkout
run_get_categories: test_get_categories launch_get_categories
run_get_products: test_get_products launch_get_products
run_test_receipt_exists: test_receipt_exists launch_test_receipt_exists
run_test_update_buyer_info: test_update_buyer_info launch_test_update_buyer_info

#CLEAN COMMANDS
clean: 
	rm -f bin/*.exe build/* test/bin/*.exe test/build/*
