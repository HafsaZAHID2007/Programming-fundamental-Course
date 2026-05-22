
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

// products
const int totalProducts = 100;
const int maxBillItems = 100;
const int maxSales = 100;
int count = 4;

string productName[totalProducts] = {"hf", "airbuds", "handfree", "mp3s"};
int productPrice[totalProducts] = {350, 450, 400, 250};
int productQty[totalProducts] = {100, 100, 100, 100};

// bill
int billCount = 0;
string billName[maxBillItems];
int billQty[maxBillItems];
int billPrice[maxBillItems];
int billTotal[maxBillItems];

float discount = 0;
float discountAmount = 0;
float finalTotal = 0;

// sales
string salesCustomer[maxSales];
string salesPayment[maxSales];
int salesTotal[maxSales];
int salesCount = 0;
// customer
string customerName;
string customerNo;
string customerPayment;

// function declarations
void adminLogin();
void adminMenu();
void staffMenu();
// product functions
void addProduct();
void viewProduct();
void searchProduct();
void updateProduct();
void deleteProduct();

// sales
void saveSales(string name, string payment, float total);
void salesReport();
void sortSales();
// bill functions
void createBill();
void addItemToBill();
void removeItemToBill();
void addDiscount();
void calculateDiscount(float total);
void displayDiscount(float amount, float ftotal);
void printReciept();
void resetBill();

// file handling
void saveProducts();
void loadProducts();
void saveSalesFile();
void loadSalesFile();

main()
{
    loadProducts();
    loadSalesFile();
    while (true)
    {
        system("cls");
        cout << "-----------------------------------------------------------" << endl; // header
        cout << "----------INVENTORY AND BILLING MANAGEMENT SYSTEM----------" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "1. Admin Login " << endl; // main menu
        cout << "2. Staff Login (billing counter)" << endl;
        cout << "3. Exit " << endl;
        cout << endl;
        string useroption;
        cout << "Enter Option(1-3): ";
        cin >> useroption;
        cout << "\n You have selected option: " << useroption << endl;
        if (useroption == "1") // admin login
        {
            adminLogin();
        }
        else if (useroption == "2") // staff panel
        {
            staffMenu();
        }
        else if (useroption == "3")
        // exit
        {
            cout << "Thanks for using this software ";
            break;
        }
        else
        {
            cout << " You have selected wrong option ";
            getch();
        }
    }
}

void adminLogin()

{
    for (int attempt = 1; attempt <= 3; attempt++)
    {
        system("cls");
        cout << "Admin Login : Attempt  " << attempt << " of 3 " << endl
             << endl;
        string username;
        cout << "Enter Username ";
        cin >> username;
        string password;
        cout << "Enter Password ";
        cin >> password;
        if (username == "admin" && password == "1234")
        {
            cout << "Login successfully ";
            adminMenu();
            cout << "Press any key to continue...";
            getch();
            break;
        }
        else
        {
            cout << "Invalid  credentials! " << endl;
        }
        getch();
    }
}
void adminMenu()
{
    while (true)
    {
        system("cls");
        cout << "-----ADMIN MENU-----" << endl;
        cout << "1. Add product " << endl;
        cout << "2. View all products " << endl;
        cout << "3. Search product   " << endl;
        cout << "4. Update product" << endl;
        cout << "5. Delete product " << endl;
        cout << "6. View sales report" << endl;
        cout << "7. Logout" << endl;
        cout << "--------------------" << endl;
        string adminoption;
        cout << "Enter  Option: ";
        cin >> adminoption;
        if (adminoption == "1")
        {
            addProduct();
        }
        else if (adminoption == "2") // view products
        {

            viewProduct();
        }
        else if (adminoption == "3")
        {
            searchProduct();
        }
        else if (adminoption == "4") // update the product
        {
            updateProduct();
        }
        else if (adminoption == "5")
        {
            deleteProduct();
        }

        else if (adminoption == "6") // sales report
        {
            sortSales();
            salesReport();
        }
        else if (adminoption == "7")
        {
            break;
        }
        else
        {
            cout << "Wrong option selected" << endl;
        }
        cout << "Press any key to continue...";
        getch();
    }
}
void staffMenu()
{
    while (true)
    {
        system("cls");
        cout << "------ STAFF PANEL ------" << endl;
        cout << "1. Create new bill" << endl;
        cout << "2. Add item to bill" << endl;
        cout << "3. Remove item from bill" << endl;
        cout << "4. Add discount" << endl;
        cout << "5. Print reciept " << endl;
        cout << "6. Logout" << endl;

        string staffoption;
        cout << "Enter Option: ";
        cin >> staffoption;

        if (staffoption == "1") // create new bill
        {
            createBill();
        }
        else if (staffoption == "2") // Add item to bill
        {
            addItemToBill();
        }
        else if (staffoption == "3") // remove product from bill
        {
            removeItemToBill();
        }
        else if (staffoption == "4") // apply discount
        {
            addDiscount();
            displayDiscount(discountAmount, finalTotal);
        }
        else if (staffoption == "5") // print reciept
        {
            printReciept();
            saveSales(customerName, customerPayment, finalTotal);
            saveSalesFile(); // save sales to file
            resetBill();
        }
        else if (staffoption == "6")
        {
            break;
        }
        else
        {
            cout << "Wrong option selected" << endl;
        }
        cout << "Press any key to continue" << endl;
        getch();
    }
}

// add products with validations
void addProduct()
{
    if (count >= totalProducts)
    {
        cout << "Inventory Full!\n";
        getch();
        return;
    }
    string name;
    int price;
    int qty;
    cout << " Enter product name: ";
    cin >> name;
    // validation duplicate name
    for (int i = 0; i < count; i++)
    {
        if (productName[i] == name)
        {
            cout << "Product already exists!\n";
            getch();
            return;
        }
    }
    cout << " Enter price: ";
    cin >> price;
    cout << "Enter quantity: ";
    cin >> qty;

    while (price <= 0 || qty <= 0)
    {
        cout << "Invalid input! Price and Quantity must be greater than zero\n";
        cin >> price >> qty;
    }
    productName[count] = name;
    productPrice[count] = price;
    productQty[count] = qty;
    count++;
    saveProducts(); // save products to file

    cout << "Product Added Successfully!\n";
    cout << "Press any kedy to continue\n";
    getch();
}
// view product
void viewProduct()
{
    cout << " Name\tPrice\tQuantity\t\n";
    for (int i = 0; i < count; i++)
    {
        if (productName[i] != "")
        {
            cout << productName[i] << "\t" << productPrice[i] << "\t" << productQty[i] << endl;
        }
    }
    getch();
}
// search product
void searchProduct()
{
    string name;
    cout << "Enter product name: ";
    cin >> name;
    int foundIndex = -1;
    for (int i = 0; i < count; i++)
    {
        if (productName[i] == name)
        {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex != -1)
    {
        cout << "\nProduct Found!\n";
        cout << "Name: " << productName[foundIndex] << endl;
        cout << "Price:" << productPrice[foundIndex] << endl;
        cout << "Quantity:" << productQty[foundIndex] << endl;
    }
    else
    {
        cout << "Product not found!";
    }
    getch();
}
// update produt
void updateProduct()
{
    string name;
    cout << "Enter product name to update: ";
    cin >> name;
    int foundIndex = -1;
    for (int i = 0; i < count; i++)
    {
        if (productName[i] == name)
        {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex != -1)
    {
        cout << "Enter new price: ";
        cin >> productPrice[foundIndex];
        while (productPrice[foundIndex] <= 0)
        {
            cout << "Invalid! Price must be greater than 0 : ";
            cin >> productPrice[foundIndex];
        }
        cout << "Enter new quantity: ";
        cin >> productQty[foundIndex];
        while (productQty[foundIndex] <= 0)
        {
            cout << "Invalid! Qty must be greater than 0 : ";
            cin >> productQty[foundIndex];
        }
        saveProducts();
        cout << "Updated Successfully!";
    }
    else
    {
        cout << " Product not found! ";
    }
    getch();
}
// delete product
void deleteProduct()
{
    string name;
    cout << "Enter product name to delete: ";
    cin >> name;
    bool found = false;
    int foundindex = -1;
    for (int i = 0; i < count; i++)
    {
        if (productName[i] == name && productName[i] != "")
        {
            found = true;
            foundindex = i;
            break;
        }
    }
    if (found)
    {
        char confirm;
        cout << "Are you sure you want to delete this product? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y')
        {
            productName[foundindex] = "";
            productPrice[foundindex] = 0;
            productQty[foundindex] = 0;
            saveProducts();
            cout << "Product Deleted Successfully!" << endl;
        }
        else
        {
            cout << " Delete cancelled!" << endl;
        }
    }
    else
    {
        cout << "Product not found!" << endl;
    }
    getch();
}
void sortSales()
{
    for (int i = 0; i < salesCount - 1; i++)
    {
        for (int j = 0; j < salesCount - i - 1; j++)
        {
            if (salesTotal[j] < salesTotal[j + 1])
            {
                float tempTotal = salesTotal[j];
                salesTotal[j] = salesTotal[j + 1];
                salesTotal[j + 1] = tempTotal;

                string tempCustomer = salesCustomer[j];
                salesCustomer[j] = salesCustomer[j + 1];
                salesCustomer[j + 1] = tempCustomer;

                string tempPayment = salesPayment[j];
                salesPayment[j] = salesPayment[j + 1];
                salesPayment[j + 1] = tempPayment;
            }
        }
    }
}
void saveSales(string name, string payment, float total)
{
    // save sales
    salesCustomer[salesCount] = name;
    salesPayment[salesCount] = payment;
    salesTotal[salesCount] = total;
    salesCount++;
}
void salesReport()
{
    cout << "\n-------Sales Report -------\n";
    int totalSales = 0;
    if (salesCount == 0)
    {
        cout << "No sales yet. \n";
    }
    else
    {

        for (int i = 0; i < salesCount; i++)
        {
            cout << "-------------------------------\n";
            cout << "Bill No:" << i + 1 << endl;
            cout << "Customer:" << salesCustomer[i] << endl;
            cout << "Payment:" << salesPayment[i] << endl;
            cout << "Total: " << salesTotal[i] << endl;
            totalSales += salesTotal[i];
        }
        cout << "-------------------------------\n";
        cout << "Total Sales: " << totalSales << endl;
    }
    getch();
}
void createBill()
{
    billCount = 0;
    discount = 0;
    discountAmount = 0;
    finalTotal = 0;
    cout << "Enter Customer Name: ";
    cin >> customerName;
    cout << "Enter Customer MObile No: ";
    cin >> customerNo;
    cout << "Enter Payment Type (cash/bank/credit): ";
    cin >> customerPayment;
    // validation payment
    while (customerPayment != "cash" && customerPayment != "bank" && customerPayment != "credit")
    {
        cout << "Invalid payment type!" << endl;
        cin >> customerPayment;
    }
    cout << "New Bill Created Successfully\n";
    getch();
}
// add items
void addItemToBill()
{
    char choice = 'y';
    while (choice == 'y' || choice == 'Y')
    {
        if (billCount >= maxBillItems)
        {
            cout << "bill limit reached!" << endl;
            getch();
            return;
        }
        string name;
        int qty;
        bool found = false;
        cout << "Enter product name: ";
        cin >> name;
        for (int i = 0; i < count; i++)
        {
            if (productName[i] == name && productName[i] != "")
            {
                found = true;
                cout << "Available Stock: " << productQty[i] << endl;
                cout << "Enter quantity: ";
                cin >> qty;
                if (qty <= 0)
                {
                    cout << "Invalid quantity!" << endl;
                    getch();
                    return;
                }
                if (qty > productQty[i])
                {
                    cout << "Not enough stock!\n ";
                    getch();
                    return;
                }

                billName[billCount] = productName[i];
                billQty[billCount] = qty;
                billPrice[billCount] = productPrice[i];
                billTotal[billCount] = qty * productPrice[i];
                billCount++;
                productQty[i] -= qty;
                saveProducts();
                cout << "Product Added Successfully!" << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Product not found!" << endl;
        }
        cout << "Add another product? (y/n):";
        cin >> choice;
    }
}
void removeItemToBill()
{
    string name;
    bool found = false;
    cout << "Enter product name to remove from bill: ";
    cin >> name;
    for (int i = 0; i < billCount; i++)
    {
        if (billName[i] == name)
        {
            found = true;
            for (int j = 0; j < count; j++)
            {
                if (productName[j] == name)
                {
                    productQty[j] += billQty[i];
                }
            }
            for (int k = i; k < billCount - 1; k++)
            {
                billName[k] = billName[k + 1];
                billQty[k] = billQty[k + 1];
                billPrice[k] = billPrice[k + 1];
                billTotal[k] = billTotal[k + 1];
            }
            billCount--;
            saveProducts();

            cout << "Products removed from bill successfully!\n";
            break;
        }
    }
    if (!found)
    {
        cout << "Product not found in bill";
    }
    getch();
}
void addDiscount()
{
    char choice;
    float total = 0;
    cout << "Apply dicount? (y/n)";
    cin >> choice;
    for (int i = 0; i < billCount; i++)
    {
        total += billTotal[i];
    }
    if (choice == 'y' || choice == 'Y')
    {
        cout << "Enter Discount %: ";
        cin >> discount;
        if (discount < 0 || discount > 100)
        {
            cout << "Invalid discount! " << endl;
            getch();
            return;
        }
        calculateDiscount(total);
    }

    else
    {
        finalTotal = total;
        discountAmount = 0;
    }
    getch();
}
void calculateDiscount(float total)
{
    discountAmount = (total * discount) / 100;
    finalTotal = total - discountAmount;
}
void displayDiscount(float amount, float ftotal)
{
    cout << "Discount Applied Successfully";
    cout << "Discount Amount: " << discountAmount << endl;
    cout << "Final Total: " << finalTotal << endl;
}
void printReciept()
{
    float total = 0;
    cout << "------- SHOP RECEIPT -------\n";
    cout << "Customer Name : " << customerName << endl;
    cout << "Mobile Number : " << customerNo << endl;
    cout << "Payment Type  : " << customerPayment << endl;
    cout << "ITEM\tQTY\tPRICE\tTOTAL\n";
    for (int i = 0; i < billCount; i++)
    {
        cout << billName[i] << "\t" << billQty[i] << "\t" << billPrice[i] << "\t" << billTotal[i] << endl;
        total += billTotal[i];
    }
    cout << "-------------------------------------\n";
    if (finalTotal == 0)
    {
        finalTotal = total;
    }
    cout << "DISCOUNT: " << discountAmount << endl;
    cout << "FINAL TOTAL: " << finalTotal << endl;
    cout << "-------------------------------------\n";
    cout << "        THANK YOU VISIT AGAIN\n";
    cout << "-------------------------------------\n";
    getch();
}
void resetBill()
{
    // reset bill
    billCount = 0;
    discount = 0;
    discountAmount = 0;
    finalTotal = 0;
}

// save products to file
void saveProducts()
{
    ofstream file("products.txt");
    if (!file)
    {
        cout << " Error in saving products! " << endl;
        return;
    }
    file << count << "\n";
    for (int i = 0; i < count; i++)
    {
        file << productName[i] << "\n";
        file << productPrice[i] << "\n";
        file << productQty[i] << "\n";
    }
    file.close();
}
// load Products from file
void loadProducts()
{
    ifstream file("products.txt");
    if (!file)
        return;
    file >> count;
    file.ignore();
    for (int i = 0; i < count; i++)
    {
        getline(file, productName[i]);
        file >> productPrice[i];
        file >> productQty[i];
        file.ignore();
    }
    file.close();
}
void saveSalesFile()
{
    ofstream file("sales.txt");
    if (!file)
    {
        cout << " Error in saving sales! " << endl;
        return;
    }
    file << salesCount << "\n";
    for (int i = 0; i < salesCount; i++)
    {
        file << salesCustomer[i] << "\n";
        file << salesPayment[i] << "\n";
        file << salesTotal[i] << "\n";
    }
    file.close();
}
void loadSalesFile()
{
    ifstream file("sales.txt");
    if (!file)
        return; //
    file >> salesCount;
    file.ignore();
    for (int i = 0; i < salesCount; i++)
    {
        getline(file, salesCustomer[i]);
        getline(file, salesPayment[i]);
        file >> salesTotal[i];
        file.ignore();
    }
    file.close();
}
void productPriceGreaterThan25()
{
    int foundindex = -1;
    for (int i = 0; i < count; i++)
    {
        if (productPrice[i] > 25)
        {
            foundindex = i;
            break;
        }
    }
    if(foundindex != -1){
        cout<<productName[foundindex]<<"\t"<<productPrice[foundindex]<<"\t"<<productQty[foundindex]<<endl;
    }
    else{
        cout<<"Not found";
    }
}