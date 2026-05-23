#include <iostream>
using namespace std;

int main() {
    int defaultPIN = 2222;
    int userPIN = 0;
    double balance = 0;
    int transactions[100];
    int choice;
    int transactionCount = 0;
    int max_attempts = 3;
    int amount = 0;
    int amount1 = 0;

    cout << "\t\t\t===ATM PROGRAM======" << endl;

    do {
        cout << "\t\t\t====Enter your pin====";
        cin >> userPIN;
        if (userPIN == defaultPIN) {
            cout << "\033[1;32m" << "\t\t\tPIN entered successfully!" << "\033[0m" << endl;

            do {
                cout << "\t\t\t1. Check balance" << endl;
                cout << "\t\t\t2. Deposit " << endl;
                cout << "\t\t\t3. Widthdraw" << endl;
                cout << "\t\t\t4. View transactions" << endl;
                cout << "\t\t\t5. Exit" << endl;
                cout << "\t\t\t Enter your choice___ ";
                cin >> choice;

                
                switch (choice) {
                case 1:
                    cout << "\t\t\tYour balance is: " << balance << "" << endl;
                    break;
                case 2: {
                    int amount = 0;
                    cout << "\t\t\tEnter an amount: ";
                    cin >> amount;
                    balance += amount;
                    transactions[transactionCount++] = amount;
                    cout << "\t\t\tYou made a deposit of " << amount << " successfully" << endl;
                    break;
                }
                case 3: {
                    cout << "\t\t\tEnter an amount: ";
                    cin >> amount1;
                    if (amount1 <= balance) {
                        balance -= amount1;
                        transactions[transactionCount++] = -amount1;
                        cout << "\t\t\tYou withdrew " << amount1 << "  successfully" << endl;
                    }
                    else {
                        cout << "\t\t\tInsufficient funds!" << endl;
                    }
                    break;
                }
                case 4:
                    cout << "\t\t\t=== Transaction History ===" << endl;
                    if (transactionCount == 0) {
                        cout << "\t\t\tNo transactions yet." << endl;
                    }
                    else {
                        for (int i = 0; i < transactionCount; i++) {
                            cout << "\t\t\t" << i + 1 << ". " << transactions[i] << endl;
                        }
                    }
                    break;
                }

            } while (choice != 5);

        }
        else {
            cout << "\t\t\tWrong PIN! Try again." << endl;
            max_attempts--;
            cout << "\t\t\tAttempts remaining: " << max_attempts << endl;
            cout << "\033[31m" << "\t\t\tYou have " << max_attempts << " attempts remaining." << "\033[0m" << endl;
        }

    } while (userPIN != defaultPIN && max_attempts > 0);

    cout << "\t\t\twelcome to our ATM!" << "\033[34m" << endl;

    return 0;
}