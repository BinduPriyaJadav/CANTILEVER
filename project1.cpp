//PROJECT1-INVENTORY MANAGEMENT SYSTEM
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Product {
    int id;
    string name;
    string category;
    double price;
    int quantity;

public:
    Product(int id, const string& name, const string& category, double price, int quantity) 
        : id(id), name(name), category(category), price(price), quantity(quantity) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void updateDetails(const string& newName, const string& newCategory, double newPrice, int newQuantity) {
        name = newName;
        category = newCategory;
        price = newPrice;
        quantity = newQuantity;
    }

    string toCSV() const {
        return to_string(id) + "," + name + "," + category + "," + to_string(price) + "," + to_string(quantity);
    }

    static Product fromCSV(const string& line) {
        stringstream ss(line);
        string idStr, name, category, priceStr, quantityStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');

        int id = stoi(idStr);
        double price = stod(priceStr);
        int quantity = stoi(quantityStr);

        return Product(id, name, category, price, quantity);
    }
};

class Inventory {
    vector<Product> products;

public:
    void addProduct(const Product& product) {
        if (any_of(products.begin(), products.end(), [&](const Product& p) { return p.getId() == product.getId(); })) {
            cout << "Product ID already exists. Please try a different ID." << endl;
        } else {
            products.push_back(product);
            cout << "Product added successfully." << endl;
        }
    }

    void removeProduct(int id) {
        auto it = remove_if(products.begin(), products.end(), [&](const Product& p) { return p.getId() == id; });
        if (it != products.end()) {
            products.erase(it, products.end());
            cout << "Product removed successfully." << endl;
        } else {
            cout << "Product with ID " << id << " not found." << endl;
        }
    }

    void updateProduct(int id, const string& name, const string& category, double price, int quantity) {
        Product* product = findProduct(id);
        if (product) {
            product->updateDetails(name, category, price, quantity);
            cout << "Product updated successfully." << endl;
        } else {
            cout << "Product with ID " << id << " not found." << endl;
        }
    }

    void viewAllProducts() const {
        if (products.empty()) {
            cout << "No products available in the inventory." << endl;
            return;
        }
        for (const auto& product : products) {
            cout << "ID: " << product.getId() << endl
                 << "Name: " << product.getName() << endl
                 << "Category: " << product.getCategory() << endl
                 << "Price: $" << product.getPrice() << endl
                 << "Quantity: " << product.getQuantity() << endl
                 << "----------------------------" << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for writing." << endl;
            return;
        }
        for (const auto& product : products) {
            file << product.toCSV() << endl;
        }
        file.close();
        cout << "Inventory saved to file successfully." << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for reading." << endl;
            return;
        }
        products.clear();
        string line;
        while (getline(file, line)) {
            products.push_back(Product::fromCSV(line));
        }
        file.close();
        cout << "Inventory loaded from file successfully." << endl;
    }

private:
    Product* findProduct(int id) {
        for (auto& product : products) {
            if (product.getId() == id) {
                return &product;
            }
        }
        return nullptr;
    }
};

void displayMenu() {
    cout << "--------------- Inventory Management System ---------------" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Remove Product" << endl;
    cout << "3. Update Product" << endl;
    cout << "4. View All Products" << endl;
    cout << "5. Save Inventory to File" << endl;
    cout << "6. Load Inventory from File" << endl;
    cout << "7. Quit" << endl;
    cout << "-----------------------------------------------------------" << endl;
}

int getIntInput(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";
    }
    return value;
}

double getDoubleInput(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid price: ";
    }
    return value;
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, value);
    return value;
}

int main() {
    Inventory inventory;
    char choice;

    do {
        displayMenu();
        cin >> choice;

        switch (tolower(choice)) {
            case '1': {
                int id = getIntInput("Enter product ID: ");
                string name = getStringInput("Enter product name: ");
                string category = getStringInput("Enter product category: ");
                double price = getDoubleInput("Enter product price: ");
                int quantity = getIntInput("Enter product quantity: ");
                inventory.addProduct(Product(id, name, category, price, quantity));
                break;
            }
            case '2': {
                int id = getIntInput("Enter product ID to remove: ");
                inventory.removeProduct(id);
                break;
            }
            case '3': {
                int id = getIntInput("Enter product ID to update: ");
                string name = getStringInput("Enter new product name: ");
                string category = getStringInput("Enter new product category: ");
                double price = getDoubleInput("Enter new product price: ");
                int quantity = getIntInput("Enter new product quantity: ");
                inventory.updateProduct(id, name, category, price, quantity);
                break;
            }
            case '4': {
                inventory.viewAllProducts();
                break;
            }
            case '5': {
                inventory.saveToFile("inventory.csv");
                break;
            }
            case '6': {
                inventory.loadFromFile("inventory.csv");
                break;
            }
            case 'q':
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }
    } while (tolower(choice) != 'q');

    return 0;
}