#include<bits/stdc++.h>
#include <string>
#include <iomanip>
using namespace std;

class Product
{
private:
    int tagNumber;
    string name;
    double price;
    int quantity;

public:
    Product(int tag, string n, double p, int q) : tagNumber(tag), name(n), price(p), quantity(q) {}
    void displayProduct()
    {
        cout << "Tag Number: " << tagNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Price: $" << price << endl;
        cout << "Quantity: " << quantity << endl;
    }
    int getTagNumber()
    {
        return tagNumber;
    }
    int getQuantity()
    {
        return quantity;
    }
    double getPrice()
    {
        return price;
    }
    void decreaseQuantity(int amount)
    {
        if (quantity >= amount)
        {
            quantity -= amount;
        }
    }
    void increaseQuantity(int amount)
    {
        quantity += amount;
    }
    string getName()
    {
        return name;
    }
};

class ProductNode
{
public:
    Product product;
    ProductNode* next;

    ProductNode(const Product& p) : product(p), next(nullptr) {}
};

class Customer
{
private:
    string name;
    int phoneNumber;
    string address;

public:
    void user_profile()
    {
        cout << "Enter your name: ";
        cin>> name;
        cout << "Enter phone number: ";
        cin >> phoneNumber;
        cout << "Enter address: ";
        cin>> address;
        cout << "Account created successfully" << endl;
        cout << "User profile" << endl;
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Address: " << address << endl;
    }
};

class ProductDatabase
{
private:
    ProductNode* head;
    int cart[100];
    int cartQuantities[100];
    int cartCount = 0;

public:
    ProductDatabase() : head(nullptr) {}

    void addProduct(const Product& product)
    {
        ProductNode* newNode = new ProductNode(product);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            ProductNode* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void addToCart()
    {
        int tagNumber, quantity;
        cout << "Enter the Tag Number of the product you want to add to the cart: ";
        cin >> tagNumber;

        bool productFound = false;

        ProductNode* current = head;

        while (current != nullptr)
        {
            if (current->product.getTagNumber() == tagNumber)
            {
                productFound = true;
                cout << "Enter the quantity you want to add to the cart: ";
                cin >> quantity;
                if (current->product.getQuantity() >= quantity)
                {
                    current->product.decreaseQuantity(quantity);
                    cart[cartCount] = tagNumber;
                    cartQuantities[cartCount] = quantity;
                    cartCount++;
                    cout << "Added " << quantity << " of Product with Tag Number " << tagNumber << " to the cart." << endl;
                }
                else
                {
                    cout << "Not enough quantity in stock for Product with Tag Number " << tagNumber << endl;
                }
                break;
            }
            current = current->next;
        }

        if (!productFound)
        {
            cout << "Product with Tag Number " << tagNumber << " not found." << endl;
        }
    }

    void viewProducts()
    {
        ProductNode* current = head;

        if (current == nullptr)
        {
            cout << "No products available." << endl;
            return;
        }

        cout << "Available Products:" << endl;

        while (current != nullptr)
        {
            current->product.displayProduct();
            cout << "-----------------------------------" << endl;
            current = current->next;
        }
    }
    void searching(string iName)
    {
        transform(iName.begin(), iName.end(), iName.begin(), ::tolower);
        ProductNode* current = head;
        while (current != nullptr)
        {
            string item=(current->product.getName());
            transform(item.begin(), item.end(), item.begin(), ::tolower);
            if (item == iName)
            {
                current->product.displayProduct();
                return;
            }
            current=current->next;
        }
        cout<< "Not found";
    }
    void viewCart()
    {
        if (cartCount == 0)
        {
            cout << "Cart is empty." << endl;
            return;
        }

        cout << "Cart Contents:" << endl;
        cout << "-----------------------------------" << endl;
        cout << "Tag Number  |  Name       |  Quantity  |  Price/Item  |  Total Price" << endl;
        cout << "-----------------------------------" << endl;

        double grandTotal = 0.0;

        for (int i = 0; i < cartCount; i++)
        {
            int tagNumber = cart[i];
            int quantity = cartQuantities[i];
            ProductNode* current = head;

            while (current != nullptr)
            {
                if (current->product.getTagNumber() == tagNumber)
                {
                    double pricePerItem = current->product.getPrice();
                    double totalItemPrice = pricePerItem * quantity;
                    grandTotal += totalItemPrice;
                    cout << left << setw(12) << tagNumber << " | ";
                    cout << left << setw(12) << current->product.getName() << " | ";
                    cout << left << setw(10) << quantity << " | ";
                    cout << fixed << setprecision(2) << left << setw(13) << pricePerItem << " | ";
                    cout << fixed << setprecision(2) << left << setw(12) << totalItemPrice << endl;

                    break;
                }
                current = current->next;
            }
        }

        cout << "-----------------------------------" << endl;
        cout << "Grand Total: $" << grandTotal << endl;
    }

    void removeFromCart(int tagNumber)
    {
        for (int i = 0; i < cartCount; i++)
        {
            if (cart[i] == tagNumber)
            {
                int removedQuantity = cartQuantities[i];
                cartCount--;

                for (int j = i; j < cartCount; j++)
                {
                    cart[j] = cart[j + 1];
                    cartQuantities[j] = cartQuantities[j + 1];
                }

                ProductNode* current = head;

                while (current != nullptr)
                {
                    if (current->product.getTagNumber() == tagNumber)
                    {
                        current->product.increaseQuantity(removedQuantity);
                        break;
                    }
                    current = current->next;
                }

                cout << "Removed Product with Tag Number " << tagNumber << " from the cart." << endl;
                return;
            }
        }
        cout << "Product with Tag Number " << tagNumber << " not found in the cart." << endl;
    }

    void removeFromCartMenu()
    {
        int tagNumber;
        cout << "Enter the Tag Number of the product you want to remove from the cart: ";
        cin >> tagNumber;
        removeFromCart(tagNumber);
    }

    double calculateTotalCost()
    {
        double totalCost = 0.0;

        for (int i = 0; i < cartCount; i++)
        {
            int tagNumber = cart[i];
            int quantity = cartQuantities[i];
            ProductNode* current = head;

            while (current != nullptr)
            {
                if (current->product.getTagNumber() == tagNumber)
                {
                    totalCost += (current->product.getPrice() * quantity);
                    break;
                }
                current = current->next;
            }
        }

        return totalCost;
    }

    ~ProductDatabase()
    {
        while (head != nullptr)
        {
            ProductNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    Customer user;
    cout << "Welcome! To get started, please create an account" << endl;
    cout << "Type 1 to create an account" << endl;
    int ch_account;
    cin >> ch_account;
    if (ch_account == 1)
    {
        user.user_profile();
    }

    ProductDatabase productDB;

    productDB.addProduct(Product(1001, "Pen", 1.99, 100));
    productDB.addProduct(Product(1002, "Paper", 5.99, 200));
    productDB.addProduct(Product(1003, "Pencil", 0.99, 150));

    int choice;
    do
    {
        cout << "1. View available products\n2. Add product to cart\n3. View cart\n4. Remove product from cart\n5. Calculate total cost\n6. Searching\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            productDB.viewProducts();
            break;
        case 2:
            productDB.addToCart();
            break;
        case 3:
            productDB.viewCart();
            break;
        case 4:
            productDB.removeFromCartMenu();
            break;
        case 5:
            cout << "Total Cost: $" << productDB.calculateTotalCost() << endl;
            break;
        case 7:
            cout << "Goodbye!" << endl;
            break;
        case 6:
        {
            cout << "Search for?" << endl;
            string sea;
            cin>> sea;
            productDB.searching(sea);
            break;
        }
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    }
    while (choice != 7);
    return 0;
}
