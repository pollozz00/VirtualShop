#pragma once
#include <iostream>
#include "Product.h"
#include "ASDList.h"
#include "fun_console.h"
#include <windows.h>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>


using namespace std;

class Review {
public:
    unsigned int productId;
    string reviewText;
    string reviewerName;
    int rating;

    Review(unsigned int pid, string rText, string rName, int rate)
        : productId(pid), reviewText(rText), reviewerName(rName), rating(rate) {}
};

class Shop : public Product, public Users {
protected:
    ASD::List<Shop> shopProducts;
    ASD::List<Shop> cart;

    unsigned int lastProductId = 1;

    int saveX = 0;
    int saveY = 0;

    vector<Review> reviews;
public:
    Shop() = default;

    unsigned int getId() const { return id; }

    void initProducts() {
        Shop prod1;
        prod1.nameOfProduct = "something";
        prod1.price = 123;
        prod1.quantity = 50;
        prod1.id = lastProductId + 1;
        lastProductId++;
        shopProducts.AddHead(prod1);

        Shop prod2;
        prod2.nameOfProduct = "different";
        prod2.price = 1000;
        prod2.quantity = 76;
        prod2.id = lastProductId + 1;
        lastProductId++;
        shopProducts.AddHead(prod2);
    }

    void toString() {
        cout << endl << endl;

        int y = 3; 
        int xID = 10; 
        int xName = 25; 
        int xPrice = 55;
        int xQuantity = 75;

        ASD::LISTPOSITION pos = shopProducts.GetHead();


        while (pos) {
            Shop& product = shopProducts.GetNext(pos);
                
            
            GotoXY(xID, y);
            cout << "ID: " << product.id;

            GotoXY(xName, y);
            cout << "Name: " << product.nameOfProduct;

            GotoXY(xPrice, y);
            cout << "Price: " << product.price;

            GotoXY(xQuantity, y);
            cout << "Quantity: " << product.quantity;

            y += 1;
        }

       

    }

    void saveXY() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        saveX = csbi.dwCursorPosition.X;
        saveY = csbi.dwCursorPosition.Y;
    };
    void returnXY() {
        GotoXY(saveX, saveY);
    }

    // NEED TO ADD VALIDATION 
    void addProduct() {
        int x = 11;
        cout << "Enter name of product: ";
        getline(cin, nameOfProduct);
        GotoXY(x, 2);
        
        bool priceErrorShown = false;
    
        /*
        while (true) {
        if (priceErrorShown) {
            cout << "Invalid input. Please enter a valid number for the price." << endl;
        }
        cout << "Enter price: ";
        if (cin >> price && price > 0) {
            break; // Корректный ввод
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            priceErrorShown = true;
        }
    }
   
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
        GotoXY(x, 3);
        */
   
        
        while (true) {
            cout << "Enter price: ";
            if (cin >> price) {
                if (price > 0) break;
                else cout << "Price must be positive." << endl;
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore();
            }
        }
        cin.ignore();
        GotoXY(x, 3);

       
        while (true) {
            cout << "Enter quantity: ";
            if (cin >> quantity) {
                if (quantity >= 0) break; 
                else cout << "Quantity cannot be negative." << endl;
            }
            else {
                cout << "Invalid input. Please enter a whole number." << endl;
                cin.clear();
                cin.ignore();
            }
        }
        cin.ignore();
        
       
        Shop newProduct;
        newProduct.nameOfProduct = nameOfProduct;
        newProduct.price = price;
        newProduct.quantity = quantity;
        newProduct.id = lastProductId + 1;
        lastProductId++;
        shopProducts.AddHead(newProduct);

        GotoXY(x, 4);
        cout << "Product added to shop successfully!" << endl;

    }
    bool findProductById(unsigned int id) {
        ASD::LISTPOSITION pos = shopProducts.GetHead();
        while (pos) {
            Shop& product = shopProducts.GetNext(pos);
            if (product.getId() == id) {
                return true;
            }
        }
        return false;
    }

    

    void refreshQuantity() {
        unsigned int idSearch = 0;
        int x = 11;        
        
        cout << "Enter ID: ";
        cin >> idSearch;
        cin.ignore();

        if (idSearch <= 0) {
            GotoXY(x, 2);
            cout << "Invalid ID. Please enter a positive number." << endl;
            return;
        }

        if (findProductById(idSearch)) {

            ASD::LISTPOSITION pos = shopProducts.GetHead();
            while (pos) {
                Shop& product = shopProducts.GetNext(pos);
                if (product.getId() == idSearch) {
                    int newQuantity;
                    GotoXY(x, 2);
                    cout << "Enter new quantity: ";
                    cin >> newQuantity;
                    cin.ignore();

                    if (newQuantity >= 0) {
                        product.setQuantity(newQuantity);
                        GotoXY(x, 3);
                        cout << "Quantity updated successfully!" << endl;
                    }
                    else {
                        GotoXY(x, 3);
                        cout << "Invalid quantity. Please enter a non-negative number." << endl;
                    }
                    return;
                }
            }
        }
        else {
            GotoXY(x, 3);
            cout << "Product not found with ID: " << idSearch << endl;
        }
    }

   
    void refreshName() {
        unsigned int idSearch = 0;
        std::cout << "Enter ID: ";
        std::cin >> idSearch;
        std::cin.ignore();

        if (idSearch <= 0) {
            std::cout << "Invalid ID. Please enter a positive number." << std::endl;
            return;
        }

        ASD::LISTPOSITION pos = shopProducts.GetHead();
        while (pos) {
            Shop& product = shopProducts.GetNext(pos);
            if (product.getId() == idSearch) {
                std::string newName;
                std::cout << "Enter new name: ";
                std::getline(std::cin, newName);

                product.setNameOfProduct(newName);
                std::cout << "Name updated successfully!" << std::endl;
                return;
            }
        }
        std::cout << "Product not found with ID: " << idSearch << std::endl;
    }

    void refreshPrice() {
        unsigned int idSearch = 0;
        cout << "Enter ID: ";
        cin >> idSearch;
        cin.ignore();

        if (idSearch <= 0) {
            cout << "Invalid ID. Please enter a positive number." << endl;
            return;
        }

        if (findProductById(idSearch)) {

            ASD::LISTPOSITION pos = shopProducts.GetHead();
            while (pos) {
                Shop& product = shopProducts.GetNext(pos);
                if (product.getId() == idSearch) {
                    int newPrice;
                    cout << "Enter new quantity: ";
                    cin >> newPrice;
                    cin.ignore();
                                        
                    product.setQuantity(newPrice);
                    cout << "Quantity updated successfully!" << endl;
                    
                    return;
                }
            }
        }
        else {
            cout << "Product not found with ID: " << idSearch << endl;
        }
    }


    void addToCartById(unsigned int id, int quantity) {
        if (findProductById(id)) {
            ASD::LISTPOSITION pos = shopProducts.GetHead();
            while (pos) {
                Shop& product = shopProducts.GetNext(pos);
                if (product.getId() == id) {
                    if (quantity <= product.getQuantity() && quantity > 0) {
                        product.setQuantity(product.getQuantity() - quantity);
                        Shop cartProduct = product;
                        cartProduct.setQuantity(quantity);
                        cart.AddTail(cartProduct);
                        GotoXY(10,21);
                        cout << "Product added to cart successfully!" << endl;
                    }
                    else {
                        GotoXY(10, 21);
                        cout << "Invalid quantity or insufficient stock." << endl;
                    }
                    return;
                }
            }
        }
        else {
            GotoXY(10, 21);
            cout << "Product not found with ID: " << id << endl;
        }
    }

    void showCart() {
        
        int y = 3;        
        int xName = 25;
        int xPrice = 55;
        int xQuantity = 75;

        ASD::LISTPOSITION pos = cart.GetHead();
        while (pos) {
            Shop& product = cart.GetNext(pos);            

            GotoXY(xName, y);
            cout << "Name: " << product.getNameOfProduct();     

            GotoXY(xPrice, y);
            cout << "Price: " << product.getPrice();

            GotoXY(xQuantity, y);
            cout << "Quantity: " << product.getQuantity();

            y += 1;
        }

       
    }

    double getDiscountPercentage(Users& user) {
        double discount = 0.0;

        if (user.isClientAccount() && user.getClubMember()) {
            discount += 0.1; //10% для Club Member
        }

        if (user.isEmployeeAccount() && user.getRank() == 1) {
            discount = 0.1; // 10% для Робітника
        }
        else if (user.isEmployeeAccount() && user.getRank() == 2) {
            discount = 0.2; // 20% для Менеджера
        }
        else if (user.isEmployeeAccount() && user.getRank() == 3) {
            discount = 0.3; // 30% для Member of a management team 
        }

        return discount;
    }

    /*
    double totalCost(Users& user) {
        double totalCost = 0.0;
        double discount = getDiscountPercentage(user);

        ASD::LISTPOSITION pos = cart.GetHead();
        while (pos) {
            Shop& product = cart.GetNext(pos);
            totalCost += (product.getPrice() * product.getQuantity() * (1 - discount));
        }
               
        return totalCost;
    }
    */
    double totalCost(Users& user) {
        double totalCost = 0.0;
        double discount = getDiscountPercentage(user);

        ASD::LISTPOSITION pos = cart.GetHead();
        while (pos) {
            Shop& product = cart.GetNext(pos);
            totalCost += (product.getPrice() * product.getQuantity() * (1 - discount));
        }
        
        if (totalCost > user.getHighestPurchase()) {
            user.setHighestPurchase(totalCost);
        }
        
        user.setHasMadePurchase(true);

        return totalCost;
    }

    void addReview() {
        unsigned int productId;
        string reviewText;
        string reviewerName;
        int rating;

        int x = 11;
        
        cout << "Enter product ID: ";
        cin >> productId;
        cin.ignore();

        if (!findProductById(productId)) {
            GotoXY(x,2);
            cout << "Product not found with ID: " << productId << endl;
            _getch();
            return;
        }

        GotoXY(x, 2);
        cout << "Enter your name: ";
        getline(cin, reviewerName);

        GotoXY(x, 3);
        cout << "Enter your review: ";
        getline(cin, reviewText);

        GotoXY(x, 4);
        cout << "Enter your rating (1-5): ";
        while (!(cin >> rating) || rating < 1 || rating > 5) {
            GotoXY(x, 4);
            cout << "Invalid input. Please enter a number between 1 and 5: ";
            cin.clear();
            cin.ignore();
        }
        cin.ignore();

        Review newReview(productId, reviewText, reviewerName, rating);
        reviews.push_back(newReview);

        GotoXY(x, 5);
        cout << "Review added successfully!" << endl;
        _getch();
    }

    void displayReviews() {
            int y = 1;
            int x = 11;
            
        if (reviews.empty()) {
            cout << "No reviews available." << endl;
            _getch();
            return;
        }

        for (const auto& review : reviews) {


            GotoXY(x, y);
            cout << "Product ID: " << review.productId;
            y += 1;

            GotoXY(x, y);
            cout << "Reviewer: " << review.reviewerName;
            y += 1;

            GotoXY(x, y);
            cout << "Rating: " << review.rating << "/5";
            y += 1;

            GotoXY(x, y);
            cout << "Review: " << review.reviewText;            
            y += 2;
        }
        _getch();
    }
};
