//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <unordered_map>
#include <fstream>

#include "Unit1.h"
#include <Unit2.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------

using namespace std;


class Customer;

class LinkedList
{
public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    void insert(Customer *cus);

    Customer *remove();

    void display();

private:
    Customer *head, *tail;
    int size;
};

class Customer
{
public:
    Customer(){}

	Customer(TForm1* form) : form(form)
    {
		noOfProducts = 0;
        l1_count = 0;
        l2_count = 0;
		l3_count = 0;
		l1_cus_count = 0;
		l2_cus_count = 0;
		l3_cus_count = 0;
		count = 0;
		i = 0;
		map_count = 0;
        for_map_max = 0;
        next = NULL;
	}

    Customer(int pN)
    {
        noOfProducts = pN;
        next = NULL;
    }

    void setNext(Customer *next)
    {
        this->next = next;
    }

    Customer *getNext()
    {
        return this->next;
    }

    int getNoOfProducts()
    {
        return noOfProducts;
    }

    void addCustomerInLine(Customer *cus)
	{
		if(count == 0)
		{
			form->checkOutButton->Enabled = true;
		}
        if (l1_count <= l2_count && l1_count <= l3_count)
        {
            val = 'a';
			form->addCustomerLabel->Text = "Customer added to Line 1";
			System::UnicodeString temp = cus->getNoOfProducts();
			form->Line1StringGrid->Cells[0][l1_cus_count] = map_count + 1;
			form->Line1StringGrid->Cells[1][l1_cus_count++] = "\t" + temp;
			line1.insert(cus);
			l1_count += cus->getNoOfProducts();

			if(l1_cus_count >= 10)
                form->Line1StringGrid->RowCount = l1_cus_count + 1;

		}
		else if (l2_count < l1_count && l2_count <= l3_count)
		{
			val = 'b';
			form->addCustomerLabel->Text = "Customer added to Line 2";
			System::UnicodeString temp = cus->getNoOfProducts();
			form->Line2StringGrid->Cells[0][l2_cus_count] = map_count + 1;
			form->Line2StringGrid->Cells[1][l2_cus_count++] = "\t" + temp;
            line2.insert(cus);
			l2_count += cus->getNoOfProducts();

			if(l2_cus_count >= 10)
				form->Line2StringGrid->RowCount = l2_cus_count + 1;
        }
        else
        {
			val = 'c';
			form->addCustomerLabel->Text = "Customer added to Line 3";
			System::UnicodeString temp = cus->getNoOfProducts();
			form->Line3StringGrid->Cells[0][l3_cus_count] = map_count + 1;
			form->Line3StringGrid->Cells[1][l3_cus_count++] = "\t" + temp;
			line3.insert(cus);
			l3_count += cus->getNoOfProducts();

			if(l3_cus_count >= 10)
				form->Line3StringGrid->RowCount = l3_cus_count + 1;
		}
        count++;
		sequence[map_count++] = val;
	}

	Customer *checkOutCustomer()
	{
        if (count != 0)
        {
            val = sequence[i++];
            count--;
			if(count == 0)
		   		form->checkOutButton->Enabled = false;

			if (val == 'a')
			{
				Customer *temp = line1.remove();
				form->addCustomerLabel->Text = "Customer from line 1 is checked out.\nDetail:\n\tCustomer Id = " + IntToStr(i) + "\n\tNo of Products = " + IntToStr(temp->getNoOfProducts());

				for(int x = 0; x < l1_cus_count; x++)
				{
					form->Line1StringGrid->Cells[0][x] = form->Line1StringGrid->Cells[0][x+1];
                    form->Line1StringGrid->Cells[1][x] = form->Line1StringGrid->Cells[1][x+1];
				}
				l1_count -= temp->getNoOfProducts();
                sequence.erase(i - 1);
				l1_cus_count--;
                return temp;
            }
            else if (val == 'b')
			{
				Customer *temp = line2.remove();
				form->addCustomerLabel->Text = "Customer from line 2 is checked out.\nDetail:\n\tCustomer Id = " + IntToStr(i) + "\n\tNo of Products = " + IntToStr(temp->getNoOfProducts());

				for(int x = 0; x < l2_cus_count; x++)
				{
					form->Line2StringGrid->Cells[0][x] = form->Line2StringGrid->Cells[0][x+1];
					form->Line2StringGrid->Cells[1][x] = form->Line2StringGrid->Cells[1][x+1];
				}

				l2_count -= temp->getNoOfProducts();
				sequence.erase(i - 1);
                l2_cus_count--;
                return temp;
            }
            else
			{
				Customer *temp = line3.remove();
				form->addCustomerLabel->Text = "Customer from line 3 is checked out.\nDetail:\n\tCustomer Id = " + IntToStr(i) + "\n\tNo of Products = " + IntToStr(temp->getNoOfProducts());

				for(int x = 0; x < l3_cus_count; x++)
				{
					form->Line3StringGrid->Cells[0][x] = form->Line3StringGrid->Cells[0][x+1];
					form->Line3StringGrid->Cells[1][x] = form->Line3StringGrid->Cells[1][x+1];
				}

                l3_count -= temp->getNoOfProducts();
                sequence.erase(i - 1);
                l3_cus_count--;
                return temp;
            }
		}
		else
		{
			return NULL;
		}
    }

	void display()
	{
		cout << "Line-1:\t";
		line1.display();
		cout << "Line-2:\t";
		line2.display();
		cout << "Line-3:\t";
		line3.display();
        cout << endl;
    }

private:
    int noOfProducts, l1_count, l2_count, l3_count, count, i, for_map_max,l1_cus_count, l2_cus_count, l3_cus_count, map_count;
    Customer *next;
    unordered_map<int, char> sequence; //! mapping are used just to keep track of which customer comes first so that customer will be checked out first
    char val;
	static LinkedList line1, line2, line3;
	TForm1* form;
};


//! Function Definitions of Linked List Class
LinkedList Customer::line1;
LinkedList Customer::line2;
LinkedList Customer::line3;

void LinkedList::insert(Customer *cus)
{
    if (size == 0)
    {
        head = cus;
        tail = cus;
    }
    else
    {
        tail->setNext(cus);
        tail = cus;
    }
    size++;
}

Customer *LinkedList::remove()
{
    if (size != 0)
    {
        Customer *temp = head;

        head = head->getNext();
        size--;

        return temp;
	}
	else
		return NULL;
}

void LinkedList::display()
{
    Customer *ptr = head;

    for (int i = 0; i < size; i++)
    {
        cout << ptr->getNoOfProducts() << " ";
        ptr = ptr->getNext();
    }

    cout << endl;
}

Customer shop;
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Line1StringGrid->RowCount = 10;
	Line2StringGrid->RowCount = 10;
	Line3StringGrid->RowCount = 10;
	shop = Customer(this);
}
void __fastcall TForm1::AddCustomerButtonClick(TObject *Sender)
{
	AskingForProductsForm = new TAskingForProductsForm(this);

	AskingForProductsForm->ShowModal();

	fstream myFile;
	myFile.open("customersData.txt", ios::in);
	if (myFile.is_open())
	{
		string products;
		myFile >> products;

		if(products == "emptyy")
			ShowMessage("Customer Wergaya. Allah de Oobakhe!");
		else
		{
			shop.addCustomerInLine(new Customer(stoi(products)));
			myFile.close();

			myFile.open("customersData.txt", ios::out | ios::trunc);
			myFile << "emptyy";
			myFile.close();
		}
	}

    delete AskingForProductsForm;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::checkOutButtonClick(TObject *Sender)
{
    shop.checkOutCustomer();
}
//---------------------------------------------------------------------------
