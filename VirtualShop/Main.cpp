#pragma once

#include <iostream>
#include <conio.h>
#include "Users.h"
#include "Shop.h"
#include "Product.h"

#include "ASDWindow.h"
#include "ASDWindow.cpp"
#include "ASDString.h"
#include "ASDString.cpp"
#include "ASDArray.h"
#include "ASDArray.cpp"
#include "fun_console.h"
#include "fun_console.cpp"
#include "ASDList.h"
#include "ASDList.cpp"



int main() {
    ASD::Menu mainMenu;
    ASD::Menu adminMenu;
    ASD::Menu userMenu;

    Users user;
    user.initializeUsers();

    Shop shop;
    shop.initProducts();

    ASD::Message mes("");
    mes.SetHeight(100).SetWidth(100).SetBgColor(Black).SetBorderColor(LightGreen).HCenter().VCenter();

    ASD::Message shopInterface("");
    shopInterface.SetHeight(18).SetWidth(120).SetBgColor(Black).SetBorderColor(LightGreen);

    ASD::Message cart("");
    cart.SetHeight(18).SetWidth(120).SetBgColor(Black).SetBorderColor(LightGreen);
    

    mainMenu.SetWidth(37).SetHeight(5).HCenter().VCenter();
    mainMenu.Add("1. Create a new account");
    mainMenu.Add("2. Log in to an existing account");
    mainMenu.Add("3. Exit");

    adminMenu.SetWidth(55).SetHeight(10).HCenter().VCenter();
    adminMenu.Add("1. Show all clients");
    adminMenu.Add("2. Show clients (members of club)");
    adminMenu.Add("3. Show clients (who buy something)");
    adminMenu.Add("4. Show clients who made the most expensive purchase");
    adminMenu.Add("5. Add new product");
    adminMenu.Add("6. Change the quantity of products");
    adminMenu.Add("7. Purchase");
    adminMenu.Add("8. Change name of product");
    adminMenu.Add("9. Change price of product");
    adminMenu.Add("10. Add review");
    adminMenu.Add("11. Display reviews");
    adminMenu.Add("12. Exit");

    userMenu.SetWidth(35).SetHeight(6).HCenter().VCenter();
    userMenu.Add("1. Purchase");
    userMenu.Add("2. Add review");
    userMenu.Add("3. Display reviews");
    userMenu.Add("4. Exit");

    int choice = -1;

    do {
        choice = mainMenu.Select();

        switch (choice) {
        case 0: {
            SetColor(LightGreen, Black);
            cls();
            user.createNewAccount();
            if (user.isEmployeeAccount()) {
                std::cout << "Employee account created" << std::endl;
            }
            else if (user.isClientAccount()) {
                std::cout << "Client account created" << std::endl;
            }
            _getch();
            cls();
            break;
        }

        case 1: {
            SetColor(LightGreen, Black);
            cls();
            user.loginToAccount();
            if (user.isLoggedIn()) {
                if (user.isEmployeeAccount()) {                    
                    int adminChoice = -1;
                    do {
                        adminChoice = adminMenu.Select();
                        switch (adminChoice) {
                        case 0: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            user.toStringAllClients();
                            mes.Draw();

                            _getch();
                            SetColor(LightGreen, Black);
                            cls();
                            break;
                        }
                        case 1: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            user.toStringClubMembers();
                            mes.Draw();
                            _getch();
                            cls();
                            break;
                        }
                        case 2: { // -
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            user.toStringClientsWithPurchases();
                            mes.Draw();
                            _getch();
                            cls();
                            break;
                        }
                        case 3: { // - 
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            Users* highestSpender = user.findClientWithHighestPurchase();
                            if (highestSpender) {
                                cout << "Client who made the most expensive purchase: " << endl;
                                cout << highestSpender->getName() << " " << highestSpender->getSurname() << highestSpender->getHighestPurchase() << endl;
                            }
                            else {
                                cout << "No purchases found." << endl;
                            }
                            mes.Draw();
                            _getch();
                            cls();
                            break;
                        }
                        case 4: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            shop.addProduct();
                            mes.Draw();
                            _getch();
                            cls();
                            break;
                        }
                        case 5: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            shop.refreshQuantity();
                            mes.Draw();
                            _getch();
                            cls();
                            break;
                        }
                        case 6: {
                            cls();
                            unsigned int idCart = 0, quantityCart = 0;
                            int yId = 19;
                            int yQuantity = 20;
                            int x = 10;


                            SetColor(LightGreen, Black);

                            do {
                                shopInterface.Show();
                                shop.toString();
                                shopInterface.Write(55, 0, "SHOP");

                                GotoXY(x, yId);
                                std::cout << "Enter id of product: ";
                                std::cin >> idCart;
                                std::cin.ignore();
                                if (idCart == 1) break;
                                GotoXY(x, yQuantity);
                                std::cout << "Enter quantity of product: ";
                                std::cin >> quantityCart;
                                std::cin.ignore();
                                shop.addToCartById(idCart, quantityCart);
                                _getch();
                                cls();
                            } while (true);

                            cls();

                            cart.Show();
                            shop.showCart();
                            cart.Write(55, 0, "CART");
                            GotoXY(45, 22);
                            std::cout << "Total cost of purchase: " << shop.totalCost(user) << std::endl;
                            cart.Draw();

                            shopInterface.Draw();

                            _getch();
                            cls();
                            break;
                        }
                        case 7: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            shop.refreshName();
                            mes.Draw();
                            _getch();
                            cls();
                            break;

                        }
                        case 8: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            shop.refreshPrice();
                            mes.Draw();
                            _getch();
                            cls();
                            break;
                        }



                        case 9: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            shop.addReview();
                            mes.Draw();
                            cls();
                            break;
                        }

                        case 10: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            shop.displayReviews();
                            mes.Draw();
                            cls();
                            break;
                        }
                        case 11:
                            cls();
                            SetColor(LightGreen, Black);                            
                            cls();
                            break;
                        }
                    } while (adminChoice != 11);
                }
                else if (user.isClientAccount()) {
                    cls();
                    int userChoice = -1;
                    do {
                        userChoice = userMenu.Select();
                        switch (userChoice) {
                        case 0: {


                            cls();
                            unsigned int idCart = 0, quantityCart = 0;
                            int yId = 19;
                            int yQuantity = 20;
                            int x = 10;


                            SetColor(LightGreen, Black);

                            do {
                                shopInterface.Show();
                                shop.toString();
                                shopInterface.Write(55, 0, "SHOP");

                                GotoXY(x, yId);
                                std::cout << "Enter id of product: ";
                                std::cin >> idCart;
                                std::cin.ignore();
                                if (idCart == 1) break;
                                GotoXY(x, yQuantity);
                                std::cout << "Enter quantity of product: ";
                                std::cin >> quantityCart;
                                std::cin.ignore();
                                shop.addToCartById(idCart, quantityCart);
                                _getch();
                                cls();
                            } while (true);

                            cls();

                            cart.Show();
                            shop.showCart();
                            cart.Write(55, 0, "CART");
                            GotoXY(45, 22);
                            std::cout << "Total cost of purchase: " << shop.totalCost(user) << std::endl;
                            cart.Draw();

                            shopInterface.Draw();

                            _getch();
                            cls();
                            break;
                        }
                        case 1: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            shop.addReview();
                            mes.Draw();
                            cls();
                            break;
                        }
                        case 2: {
                            cls();
                            SetColor(LightGreen, Black);
                            mes.Show();
                            shop.displayReviews();
                            mes.Draw();
                            cls();
                            break;
                        }
                        case 3:{
                            cls();
                            SetColor(LightGreen, Black);
                            cls();
                            break;
                        }
                        }
                    } while (userChoice != 3);



                }
            }
            else {
                std::cout << "Login failed. Returning to main menu." << std::endl;
                _getch();
                cls();
            }
            break;
        }

        case 2: {
            break;
        }
        default: {
            std::cout << "Invalid choice!" << std::endl;
            cls();
            break;
        }
        }
    } while (choice != 2);

    return 0;
}


