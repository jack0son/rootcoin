#include <iostream>
#include <string>
#include <iterator>

#include "Blockchain.hpp"
#include "Wallet.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using Utils::bytesToStr;
using Utils::hashToBytes;
using Utils::Uint256ToBytes;
using Utils::abridgeBytes;

typedef vector<Transaction> Txs;

void printTx(Transaction &tx);
void printBlock(const Block &block);
void printAcc(Account &a);
string balanceStr(Blockchain &blockchain, PublicKey address);

Blockchain instantiateBlockchain(Txs txList) {
	;;
}

string Uint256ToStr(Uint256 val) {
	return bytesToStr(Uint256ToBytes(val));
}

// Demonstrate the Block data structure using a simple linear chain of blocks
// TODO:
//		- traversing blocks using longest chain
//		- block and transaction broadcasting
int main() {
	const Uint256 dummy("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDBAAEDCE6AF48A03BBFD25E8CD0364141");
	Uint256 GAIA_PRIV_INT(CurvePoint::ORDER);
	GAIA_PRIV_INT.shiftRight1(true);
	cout << "ORDER >> 1 : " << bytesToStr(Uint256ToBytes(GAIA_PRIV_INT)) << endl;

	vector<string> privKeys = {
		"E9873D79C6D87DC0FB6A5778633389F4453213303DA61F20BD67FC233AA33262",
		"B8EF4E4640FBBD526166FF260EB65EC2B3B60064CCE2DA9747201BA201E90F7F",
		"7A6D055110F4296A85E8122B32F87AD32A58CF9BB73435088102638D7DECE1F2"
	};

	Uint256 p1(privKeys[0].c_str());
	Uint256 p2(privKeys[1].c_str());
	Uint256 p3(privKeys[2].c_str());

	Uint256 order(CurvePoint::ORDER);
	 //assert(Uint256::ZERO < privExp);
	 //assert(privExp < CurvePoint::ORDER);

	
	Uint256 two("0000000000000000000000000000000000000000000000000000000000000002");
	//const PublicKey gaia(CurvePoint::privateExponentToPublicPoint(Uint256::ONE));
	const PublicKey gaia(CurvePoint::privateExponentToPublicPoint(two));
	cout << "GAIA priv:0x" << Uint256ToStr(two) <<endl;
	cout << "GAIA pub: 0x" << gaia.toString() << endl;

	cout << "Dummy:\t" << Uint256ToStr(dummy);
	cout << endl;
	cout << "ORDER:\t" << Uint256ToStr(order);
	cout << "\nZERO:\t" << Uint256ToStr(Uint256::ZERO);
	cout << "\nONE:\t" << Uint256ToStr(Uint256::ONE);

	string r = (Uint256::ONE < CurvePoint::ORDER) ? "true" : "false";
	cout << "\nONE < ORDER ? " << r << endl;
	r = (Uint256::ZERO < Uint256::ONE) ? "true" : "false";
	cout << " ZERO < ONE ? " << r << endl;
	cout << endl;

	Wallet wallet1;

	for(string key : privKeys) {
		cout << "Adding account using key: " << key << endl;
		wallet1.addAccount(key);
		cout << "\nDistance: " << wallet1.currentAcc - wallet1.accounts.begin();
		cout << "Distance: " << std::distance(wallet1.currentAcc, wallet1.accounts.begin());
		cout << "Size: " << wallet1.accounts.size() << endl;
		cout << endl;
	}
	cout << endl;
	cout << "\nAfter adding all keys to wallet1...";
	cout << "\nDistance: " << std::distance(wallet1.currentAcc, wallet1.accounts.begin());
	cout << "\nSizeof: " << sizeof(*wallet1.currentAcc);
	cout << endl;

	cout << "Wallet 1 - Current account::::\n";
	printAcc(*wallet1.currentAcc);
	cout << endl;

	Wallet wallet2;
	wallet2.addAccount(Account(privKeys[1]));
	cout << "Wallet 2 - Current account::::\n";
	printAcc(*wallet2.currentAcc);
	cout << endl;

	cout << "Wallet 1 - Current account::::\n";
	printAcc(*wallet1.currentAcc);
	cout << endl;

	Wallet wallet3;
	wallet3.addAccount(Account(privKeys[2]));
	cout << "Wallet 3 - Current account::::\n";
	printAcc(*wallet3.currentAcc);
	cout << endl;

	// Get some signed transactions
	Transaction tx1 = wallet1.createTransaction(wallet3.currentAcc->pub, 10);
	//Transaction tx2 = wallet3.createTransaction(wallet2.currentAcc->pub, 10);
	Transaction tx3 = wallet2.createTransaction(wallet1.currentAcc->pub, 10);

	// Create a block
	Block block1(vector<Transaction>({tx1, tx3}), Transaction::DEFAULT_NONCE, Transaction::DEFAULT_NONCE); 
	printBlock(block1);

	cout << " ... Instantiating blockchain.\n";
	Blockchain blockchain;

	cout << " ... Summoning genesis block.\n";
	blockchain.genesis(wallet1.currentAcc->pub);
	printBlock(*blockchain.getTop());
	cout << balanceStr(blockchain, wallet1.currentAcc->pub) << endl; 

	cout << "\n ... Pushing first network block.\n";
	blockchain.addBlock(block1);
	printBlock(*blockchain.getTop());
	cout << balanceStr(blockchain, wallet1.currentAcc->pub) << endl; 
	cout << balanceStr(blockchain, wallet3.currentAcc->pub) << endl; 
	
	cout << "\n ... Pushing second network block.\n";
	tx1 = wallet3.createTransaction(wallet1.currentAcc->pub, 5);
	tx3 = wallet1.createTransaction(wallet2.currentAcc->pub, 7);
	Block block2(vector<Transaction>({tx1, tx3}), Transaction::DEFAULT_NONCE, Transaction::DEFAULT_NONCE); 
	blockchain.addBlock(block1);
	printBlock(*blockchain.getTop());
	cout << balanceStr(blockchain, wallet1.currentAcc->pub) << endl; 
	cout << balanceStr(blockchain, wallet3.currentAcc->pub) << endl; 

	cout << "\n D 0 N 3 ";
	cout << endl;
	return 0;
}


//Txs getDummyTxs(Wallet &wallet) {
Txs getDummyTxs() {

}

string balanceStr(Blockchain &blockchain, PublicKey address) {
	string result = "\tcurrent ballance - " + abridgeBytes(address.toBytes())
		+ "\tBalance: " + std::to_string(blockchain.getAddressBalance(address));
	
	return result;
}


string txSummary(const Transaction &tx) {
	string result;
	result += "from: " + abridgeBytes(tx.fromKey.toBytes());
	result += ",  to: " + abridgeBytes(tx.toKey.toBytes());
	result += ",  amnt: " + std::to_string(tx.amount);

	return result;
}

void printTx(Transaction &tx) {

	cout << " ~~~ Tx Details ~~~ \n";
	cout << "from:\t" << bytesToStr(tx.fromKey.toBytes());
	cout << "\nto:\t" << bytesToStr(tx.toKey.toBytes());
	cout << "\namnt:\t" << tx.amount;
	cout << "\nsig:\t" << bytesToStr(tx.signature.toBytes());
	cout << endl;
}

void printBlock(const Block &block) {
	char d = 176;
	string bookend = "_-_-_-_-_-_-_-_-_-_-_-_";
	string head = "";
	head += bookend + " Block " + bookend;

	string summary = "";
	for(auto &tx : block.txList) {
		summary += "     " + txSummary(tx) + "\n";	
	}

	cout << endl << head << endl;
	//cout << "myHash:\t" << abridgeBytes(hashToBytes(block.getHash()));
	//cout << "\nprevHash:\t" << abridgeBytes(hashToBytes(block.getPrevHash()));
	cout << "blockHash:\t" << bytesToStr(hashToBytes(block.getHash()));
	cout << "\nprevHash:\t" << bytesToStr(hashToBytes(block.getPrevHash()));
	cout << endl << summary;
	cout << endl;
}

void printAcc(Account &a) {
	cout << " ~~~ Account Details ~~~ \n";
	cout << "priv:\t" << bytesToStr(a.priv.toBytes());
	cout << "\npub:\t" << bytesToStr(a.pub.toBytes());
	cout << endl;

}
