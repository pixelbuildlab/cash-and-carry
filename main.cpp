//***************************************************************
//                   HEADER FILES USED IN PROJECT
//***************************************************************

#include<conio.h>
#include<string>
#include<stdio.h>
#include<fstream>
#include<iostream>
using namespace std;
//***************************************************************
//                   CLASSES USED IN PROJECT
//****************************************************************

class Product
{
private:
	int barcode;
	char name[50];
	float price, qty, dis;
public:
	void create_product();//using the default constructor to create object
	void show_product();
	int  retbarcode();
	float retprice();
	char* retname();
	int retdis();
};   
void Product::create_product()
{
	cout << "\nPlease Enter The Barcode Number of The Product ";
	cin >> barcode;
	cout << "\n\nPlease Enter The Name of The Product ";
	cin >> name;
//	cout << "\n\nPlease Enter The Quantity of The Product ";
	//cin >> qty;
	cout << "\nPlease Enter The Price of The Product ";
	cin >> price;
	cout << "\nPlease Enter The Discount (%) ";
	cin >> dis;
}

void Product::show_product()
{
	cout << "\nThe Barcode Number of The Product : " << barcode;
	cout << "\nThe Name of The Product : "<<name;
	cout << "\nThe Price of The Product : " << price;
//	cout << "\nThe Quantity of The Product : " << qty;
	cout << "\nDiscount : " << dis;
}

int Product::retbarcode()
{
	return barcode;
}

float  Product::retprice()
{
	return price;
}

char* Product::retname()
{
	return name;
}

int  Product::retdis()
{
	return dis;
}
//***************************************************************
//                   INHERITED CLASSES
//***************************************************************
class Grocery:public Product
{
	int day, month, year;
public:
	void create_poduct()
	{
		Product::create_product();
	
	}
};

//***************************************************************
//    	global declaration for stream object, functions
//***************************************************************

fstream file;
Product pr;
int position;
void intro();
void admin_menu();
void write_product();
void display_all();
void display_sp(int);
void modify_product();
void delete_product();
void delete_record();
void menu();
void place_order();


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//***************************************************************


void main()
{
	int ch;
	intro();
	do
	{
		
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t1. CUSTOMER";
		cout << "\n\n\t2. ADMINISTRATOR";
		cout << "\n\n\t3. EXIT";
		cout << "\n\n\tPlease Select Your Option (1-3) ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			
			place_order();
			break;
		case 2:
			system("cls");
			admin_menu();
			break;
		case 3:
			exit(0);
		default:cout << "\a";
		}
	} while (ch != 3);
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//***************************************************************

void intro()
{
	cout << "\t\tCASH AND CARRY BILLING";
	cout << "\n\t\t\tPROJECT";
	cout << "\n\n\tMADE BY : Muhammad Waqar ";
	cout << "\n\n\tINTERNATIONAL ISLAMIC UNIVERSITY ISLAMABAD\n";
}
//***************************************************************
//    	ADMINSTRATOR MENU FUNCTION
//***************************************************************
void admin_menu()
{

	int ch2;
	cout << "\n\n\n\tADMIN MENU";
	cout << "\n\n\t1.CREATE PRODUCT";
	cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
	cout << "\n\n\t3.QUERY ";
	cout << "\n\n\t4.MODIFY PRODUCT";
	cout << "\n\n\t5.DELETE PRODUCT";
	cout << "\n\n\t6.DELETE ALL RECORD";
	cout << "\n\n\t7.VIEW PRODUCT MENU";
	cout << "\n\n\t8.BACK TO MAIN MENU";
	cout << "\n\n\tPlease Enter Your Choice (1-7) ";
	cin >> ch2;
	switch (ch2)
	{
	case 1:

		write_product();
		break;
	case 2:
		system("cls");
		display_all();
		break;
	case 3:
		system("cls");
		int num;
		cout << "\n\n\tPlease Enter The Barcode Number ";
		cin >> num;
		display_sp(num);
		break;
	case 4:
		system("cls");
		modify_product();
		break;
	case 5: 
		system("cls");
		delete_product();
		break;
	case 6:
		system("cls");
		delete_record();
		break;
	case 7:
		system("cls");
		menu();
	case 8: 
		break;
	default:
		cout << "\a";
		admin_menu();
	}
}

//***************************************************************
//    	function to write in file
//***************************************************************

void write_product()
{
	file.open("Shop.dat", ios::in| ios::out|ios::app | ios::binary);
	pr.create_product();
	file.write(reinterpret_cast<char*>(&pr), sizeof(Product));
	file.close();
	cout << "\n\nThe Product Has Been Created \n";
	system("pause");
	system("cls");
}


//***************************************************************
//    	function to read all records from file
//***************************************************************


void display_all()
{
	file.open("Shop.dat",ios::out | ios::binary);
		cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
		while (file.read(reinterpret_cast<char*>(&pr), sizeof(Product)))
		{
			pr.show_product();
			cout << "\n\n====================================\n";
			system("pause");
		}
	
	file.close();
}


//***************************************************************
//    	function to read specific record from file
//***************************************************************


void display_sp(int n)
{
	int flag = 0;
	file.open("Shop.dat", ios::in|ios::binary);
	while (file.read(reinterpret_cast<char*>(&pr), sizeof(Product)))
	{
		if (pr.retbarcode() == n)
		{
			pr.show_product();
			flag = 1;
		}
	}
	file.close();
	if (flag == 0)
		cout << "\n\n\tRecord not exist";

}


//***************************************************************
//    	function to modify record of file
//***************************************************************


void modify_product()
{
	int no, found = 0;
	file.open("Shop.dat", ios::in | ios::out | ios::binary);
	
	
	cout << "\n\n\tTo Modify ";
	cout << "\n\n\tPlease Enter The Barcode Number of The Product";
	cin >> no;

		while (file.read(reinterpret_cast<char*>(&pr), sizeof(Product)) && found == 0)
		{
			if (pr.retbarcode() == no)
			{
				pr.show_product();
				cout << "\nPlease Enter The New Details of Product" << endl;
				pr.create_product();
				int pos = 1 * sizeof(pr);
				file.seekp(pos, ios::cur);
				file.write(reinterpret_cast<char*>(&pr), sizeof(Product));
				cout << "\n\n\t Record Updated";
				found = 1;
			}
		}
		if (found == 0)
			cout << "\n\n\tRECORD NOT FOUND";

	file.close();
	system("pause");
}


//***************************************************************
//    	function to delete record of file
//***************************************************************


void delete_product()
{
	int no;
	//clrscr();
	cout << "\n\n\n\tDelete Record";
	cout << "\n\nPlease Enter The Barcode Number of The Product You Want To Delete";
	cin >> no;
	file.open("Shop.dat", ios::in | ios::out|ios::binary);
	fstream file2;
	file2.open("Temp.dat", ios::out|ios::binary);
	file.seekg(0, ios::beg);
	while (file.read(reinterpret_cast<char*>(&pr), sizeof(Product)))
	{
		if (pr.retbarcode() != no)
		{
			file2.write(reinterpret_cast<char*>(&pr), sizeof(Product));
		}
	}
	file2.close();
	file.close();
	remove("Shop.dat");
	rename("Temp.dat", "Shop.dat");
	cout << "\n\n\tRecord Deleted";

}

void delete_record()
{
	file.open("Tem.dat",ios::binary);
	file.close();
	remove("Shop.dat");
	rename("Tem.dat", "Shop.dat");
	cout << "\n\n\tRECORDS DELETED.";
}


//***************************************************************
//    	FUNCTION TO DISPLAY ALL PRODUCTS PRICE LIST
//***************************************************************

void menu()
{
	file.open("Shop.dat", ios::in | ios::binary);
	if (!file)
	{
		cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n Go To Admin Menu to create File";
		cout << "\n\n\n Program is closing ....\n";
		system("pause");
		exit(0);
	}
	file.read(reinterpret_cast<char*>(&pr), sizeof(Product));

		cout << "\n\n\t\tProduct MENU\n\n";
		cout << "====================================================\n";
		cout << "BARCODE\t\tNAME\t\tPRICE\n";
		cout << "====================================================\n";

		while (file.read(reinterpret_cast<char*>(&pr), sizeof(Product)))
		{
			cout << pr.retbarcode() << "\t\t" << pr.retname() << "\t\t" << pr.retprice() << endl;
		}
		file.close();

}




//***************************************************************
//    	FUNCTION TO PLACE ORDER AND GENERATING BILL FOR PRODUCTS
//***************************************************************

void place_order()
{
	system("cls");
	int  order_arr[50], quan[50], check = 0, c = 0;
	float amt, damt, total = 0;
	char ch = 'y';
	menu();
	cout << "\n\tEnter -99 to proceed order";
	cin >> check;
	if (check == -99)
	{
		cout << "\n============================";
		cout << "\n    PLACE YOUR ORDER";
		cout << "\n============================\n";
		while (ch != 'n') {
			cout << "\n\nEnter The Barcode Number Of The Product : ";
			cin >> order_arr[c];
			cout << "\nQuantity in number : ";
			cin >> quan[c];
			c++;
			cout << "\nDo You Want To Order Another Product ? (y/n)";
			cin >> ch;
			if (ch == 'N')
			{
				break;
			}
		}


		cout << "\n\nThank You For Placing The Order";
		cout << "\n\n********************************INVOICE************************\n";
		cout << "\nBarcode\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
		for (int x = 0; x < c; x++)
		{
			file.open("Shop.dat", ios::in | ios::binary);
			file.read(reinterpret_cast<char*>(&pr), sizeof(Product));
			while (!file.eof())
			{
				if (pr.retbarcode() == order_arr[x])
				{
					amt = pr.retprice() * quan[x];
					damt = amt - (amt * pr.retdis() / 100);
					cout << "\n" << order_arr[x] << "\t" << pr.retname() << "\t" << quan[x] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
					total += damt;
				}
				file.read(reinterpret_cast<char*>(&pr), sizeof(Product));
			}

			file.close();
		}
		cout << "\n\n\t\t\t\t\tTOTAL = " << total;

	}
}


//***************************************************************
//    			END OF PROJECT
//***************************************************************