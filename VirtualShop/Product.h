#pragma once
#include <iostream>
#include "Users.h"

using namespace std;

class Product {
protected:
	string nameOfProduct;
	double price;
	int quantity;
	double discountPercentage;  
	unsigned int id;
	
public:	

	string getNameOfProduct() { return nameOfProduct; }
	double getPrice() { return price; }
	int getQuantity() { return quantity; }	
	unsigned int getId() { return id; }
		
	void setQuantity(int q) { quantity = q; }
	void setNameOfProduct(string str) { nameOfProduct = str; }
};