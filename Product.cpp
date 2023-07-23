#include "Header.h"

Product::Product()
{
}

Product::Product(string seller_username)
{
	this->id = ++productID;
	this->price = 0.0;
	this->quantity = 0;
	this->rate = 0.0;
	this->seller_username = seller_username;
}

void Product::setRate(string cutomer_username, int newRate)
{
	this->customers_ratings[cutomer_username] = newRate;
	double avgRate = 0;
	for (auto& rat : this->customers_ratings)
		avgRate += rat.second;
	this->rate = avgRate / this->customers_ratings.size();
}
