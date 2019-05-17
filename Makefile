CXX_FLAGS=-fsanitize=undefined       

#CRYPTO_LIB=$(shell pwd)/cryptolib
CRYPTO_LIB=./cryptolib
CRYPTO_LIB_FILE=bitcoincrypto
LIB_PATH=$(CRYPTO_LIB)/$(CRYPTO_LIB_FILE)

all: test.cpp $(CRYTPO_LIB_FILE)
	g++ $(CXX_FLAGS) test.cpp -o test.out -I$(CRYPTO_LIB) -L$(CRYPTO_LIB) -l$(CRYPTO_LIB_FILE) 

test: TransactionTest.cpp Transaction.cpp Utils.cpp $(CRYTPO_LIB_FILE)
	g++ $(CXX_FLAGS) TransactionTest.cpp Transaction.cpp Utils.cpp -o TransactionTest.out -I$(CRYPTO_LIB) -L$(CRYPTO_LIB) -l$(CRYPTO_LIB_FILE) 
