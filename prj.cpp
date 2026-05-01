#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h> // For _getch()
#include<bits/stdc++.h>

using namespace std;

// --- Data Structure ---
struct Product {
    string name;
    double price, costPrice, qty, gstRate, total, profitOrLoss;
};

// --- Masked Password Login ---
bool adminLogin() {
    string username = "";
    string password = "";
    char ch;

    cout << "\n==================================\n";
    cout << "      ADMIN SYSTEM ACCESS         \n";
    cout << "==================================\n";
    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;
    
    // while (ch != 13) 
    // { // 13 is Enter
    //     ch = getch();
    //     if (ch == 8) { // 8 is Backspace
    //         if (password.length() > 0) {
    //             password.pop_back();
    //             cout << "\b \b";
    //         }
    //     } else {
    //         password += ch;
    //         cout << '*';
    //     }
    // }

    if (username == "admin" && password == "123") {
        cout << "\n\n[SUCCESS] Access Granted!\n";
        return true;
    } else {
        cout << "\n\n[ERROR] Access Denied!\n";
        return false;
    }
}

// --- Main Billing Logic ---
void generateBill(bool isAdmin) {
    string custName;
    cout << "\n>>> Enter Customer Name: "; 
    cin.ignore(); 
    getline(cin, custName);
    
    vector<Product> cart;
    double grandTotal = 0, totalTax = 0, totalProfitLoss = 0;
    char addMore;

    do {
        Product p;
        cout << "\n--- Item Entry ---\n";
        cout << "Item Name: "; getline(cin, p.name);
        cout << "Selling Price: "; cin >> p.price;
        
        // Strategy Logic: Admin enters Cost Price to track Profit/Loss
        if(isAdmin) { 
            cout << "Buying Cost Price: "; cin >> p.costPrice; 
        } else { 
            p.costPrice = p.price; 
        }
        
        cout << "Quantity: "; cin >> p.qty;
        cout << "GST Rate (%): "; cin >> p.gstRate;

        double itemTax = (p.price * p.qty) * (p.gstRate / 100);
        p.total = (p.price * p.qty) + itemTax;
        p.profitOrLoss = (p.price - p.costPrice) * p.qty;

        cart.push_back(p);
        grandTotal += p.total;
        totalTax += itemTax;
        totalProfitLoss += p.profitOrLoss;

        cout << "Add another item? (y/n): "; cin >> addMore;
        cin.ignore();
    } while (addMore == 'y' || addMore == 'Y');

    // --- DISPLAY FINAL RECEIPT ---
    cout << fixed << setprecision(2);
    cout << "\n==========================================";
    cout << "\n          GST RECEIPT GENERATOR           ";
    cout << "\n==========================================";
    cout << "\nCustomer: " << custName;
    cout << "\n------------------------------------------";
    cout << "\n" << left << setw(15) << "Item" << setw(8) << "Qty" << "Total";
    
    for (const auto& item : cart) {
        cout << "\n" << left << setw(15) << item.name << setw(8) << item.qty << item.total;
    }

    cout << "\n------------------------------------------";
    cout << "\nTotal Tax:   Rs. " << totalTax;
    cout << "\nGrand Total: Rs. " << grandTotal;
    cout << "\n------------------------------------------";

    // --- PROFIT/LOSS & STRATEGY FEATURE ---
    if (isAdmin) {
        cout << "\n\nProfit Analysis: " << (totalProfitLoss >= 0 ? "PROFIT: " : "LOSS: ") << totalProfitLoss;
        if (totalProfitLoss < 0) {
            cout << "\n[STRATEGY] Loss Detected. Review 'Cost Price' to balance margins.";
        } else {
            cout << "\n[STRATEGY] Profits are stable. Maintain current pricing.";
        }
        cout << "\n------------------------------------------\n";

        // Save to file (Database feature)
        ofstream file("sales_report.txt", ios::app);
        file << "Customer: " << custName << " | Total: " << grandTotal << " | P/L: " << totalProfitLoss << endl;
        file.close();
    }
}

int main() {
    int mode;
    cout << "----------------------------------\n";
    cout << "   CHARUSAT GST BILLING SYSTEM    \n";
    cout << "----------------------------------\n";
    cout << "Select Access Mode:\n1. Admin (Full Analysis)\n2. Staff (Basic Billing)\nChoice: ";
    cin >> mode;

    if (mode == 1) {
        if (adminLogin()) {
            while(true) {
                int cmd;
                cout << "\n1. Create Bill\n2. Exit to Main Menu\nChoice: ";
                cin >> cmd;
                if(cmd == 1) generateBill(true);
                else break;
            }
        }
    } else {
        generateBill(false);
    }

    cout << "\nSystem Shutdown. Press any key...";
    getch();
    return 0;
}