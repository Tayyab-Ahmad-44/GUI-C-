﻿//---------------------------------------------------------------------------

#pragma hdrstop

#include "myHeader.h"
#include "ReisterationForm.h"
#include "ServicesProvider.h"
#include "InputCnic.h"
#include "Garage.h"
#include "InputLocation.h"
#include "UserDetails.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vcl.h>
#include <unordered_map>
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;

class ServiceProviders
{
public:
	bool smart_locks;
	bool smart_lighting;
	bool smart_speakers;
	bool smart_curtains;
	bool smart_heating;
	bool smart_cctv;

    ServiceProviders()
    {
        smart_locks = false;
        smart_lighting = false;
        smart_speakers = false;
        smart_curtains = false;
		smart_heating = false;
        smart_cctv = false;
    }

	void subscribeService(bool smart_locks, bool smart_lighting = false, bool smart_speakers = false, bool smart_curtains = false, bool smart_heating = false, bool smart_cctv = false)
	{
		this->smart_locks = smart_locks;
		this->smart_lighting = smart_lighting;
		this->smart_speakers = smart_speakers;
		this->smart_curtains = smart_curtains;
		this->smart_heating = smart_heating;
		this->smart_cctv = smart_cctv;
	}
};

class User : public ServiceProviders
{
public:
    User *lChild;
    User *rChild;
	int height;
    int bf;

    long long key;
	string phoneNumber;
	string firstName;
    string lastName;
	bool hasCar;
	string location;

    User()
    {
		lChild = rChild = NULL;
	}

	User(long long cnic, string phoneNumber, string firstName, string lastName, bool hasCar = false, bool smart_locks = false, bool smart_lighting = false, bool smart_speakers = false, bool smart_curtains = false, bool smart_heating = false, bool smart_cctv = false)
	{
        this->key = cnic;
        this->phoneNumber = phoneNumber;
        this->firstName = firstName;
        this->lastName = lastName;
        this->hasCar = hasCar;
		this->location = "Street";
        this->height = 0;
		this->bf = 0;
		lChild = rChild = NULL;

		subscribeService (smart_locks, smart_lighting, smart_speakers, smart_curtains, smart_heating, smart_cctv);
	}
};

class myMap
{
    User *root;

public:
    myMap()
    {
        root = NULL;
    }

    bool insert(User *newNode)
    {
		if (newNode == NULL)
            return false;

        else
            root = _insert(root, newNode);

        return true;
    }

    void deleteNode(long long key)
    {
		if (!root)
			return;

        root = _deleteNode(root, key);
    }

    bool find(long long key)
    {
		if (!root)
			return false;

		return _search(root, key);
	}

	User *getUser(const long long key)
	{
		return _getUser(root, key);
    }

private:
	User *_insert(User *node, User *newNode)
    {
        if (node == NULL)
            return newNode;

		if (newNode->key < node->key)
		{
			node->lChild = _insert(node->lChild, newNode);
		}
		else
            node->rChild = _insert(node->rChild, newNode);

        //! Update Balance Factor and Height Values.
        _update(node);

        //! Rebalance the tree
        return _balance(node);
    }

	User *_deleteNode(User *node, long long key)
    {
        if (node == NULL)
		{
//            cout << "User with Key = " << key << " not found!" << endl;
			return NULL;
        }

        if (node->key == key)
        {
            if (node->lChild == NULL && node->rChild == NULL)
				return NULL;

            else if (!node->rChild)
                return node->lChild;

            else if (!node->lChild)
                return node->rChild;

			else
            {
                if (node->lChild->height > node->rChild->height)
                {
                    User *successor = _findMax(node->lChild);

                    successor->lChild = _deleteNode(node->lChild, successor->key);

					successor->rChild = node->rChild;

                    _update(successor);

                    return _balance(successor);
				}

                else
				{
                    User *successor = _findMin(node->rChild);

                    successor->rChild = _deleteNode(node->rChild, successor->key);

                    successor->lChild = node->lChild;

                    _update(successor);

                    return _balance(successor);
                }
            }
        }

        else if (key < node->key)
            node->lChild = _deleteNode(node->lChild, key);

        else
            node->rChild = _deleteNode(node->rChild, key);

        _update(node);

        return _balance(node);
    }

	void _update(User *node)
	{

		int lh = -1;
		int rh = -1;

		if (node->lChild)
			lh = node->lChild->height;
		if (node->rChild)
			rh = node->rChild->height;


		node->height = 1 + max(lh, rh);

        node->bf = rh - lh;
    }

	User *_balance(User *node)
	{
        if (node->bf == -2)
            if (node->lChild->bf <= 0)
				return _leftLeftCase(node);
			else
				return _leftRighCase(node);

		else if (node->bf == 2)
            if (node->rChild->bf >= 0)
				return _rightRightCase(node);
			else
				return _rightLeftCase(node);
		return node;
    }

	User *_leftLeftCase(User *node)
    {
        return _rightRotate(node);
    }

	User *_rightRightCase(User *node)
    {
        return _leftRotate(node);
    }

	User *_leftRighCase(User *node)
    {
        node->lChild = _leftRotate(node->lChild);
		return _rightRotate(node);
    }

	User *_rightLeftCase(User *node)
    {
        node->rChild = _rightRotate(node->rChild);
        return _leftRotate(node);
    }

	User *_rightRotate(User *node)
    {
        User *left = node->lChild;

        User *temp = left->rChild;

        left->rChild = node;

        node->lChild = temp;

        // ! After rotation update balance factor and height values
        _update(node);
        _update(left);

        return left;
	}

	User *_leftRotate(User *node)
    {
        User *right = node->rChild;

        User *temp = right->lChild;

		right->lChild = node;

        node->rChild = temp;

        //! After rotation update balance factor and height values
        _update(node);
        _update(right);

		return right;
    }

	User *_findMin(User *node)
    {
        while (node->lChild)
            node = node->lChild;

		return node;
    }

	User *_findMax(User *node)
    {
        while (node->rChild)
            node = node->rChild;

		return node;
    }

	bool _search(User *ptr, long long key)
    {
        if (ptr == NULL)
            return false;
        else if (ptr->key == key)
            return true;
		else if (key < ptr->key)
            return _search(ptr->lChild, key);
        else
            return _search(ptr->rChild, key);
    }

	User *_getUser(User *node, long long key)
    {
        if (node == nullptr)
		{
//            cerr << "User with Key = " << key << " not found!" << endl;
			return nullptr;
        }

        if (key == node->key)
            return node;
        else if (key < node->key)
            return _getUser(node->lChild, key);
		else
            return _getUser(node->rChild, key);
    }
};

class Home
{
public:
//	myMap users; // TODO: replacce with <key, value> = <id, User>

	unordered_map<long long, User*> users;
	int carsPresent;

	Home()
	{
		carsPresent = 0;
//		users.insert(new User(9999, "01234567891", "Sohail", "Khan", 1, 1, 1, 1, 1, 1, 1));
		users[9999] = new User(9999, "01234567891", "Sohail", "Khan", 1, 1, 1, 1, 1, 1, 1);
	}

	long long newUser()
	{
		registerationForm->ShowModal();

//		fstream myFile;
//		myFile.open("userData.txt", ios::in);

		string fN = registerationForm->getFn();
		string lN = registerationForm->getLn();
		string pN = registerationForm->getPn();
		long long cnic = stoll(registerationForm->getCnic());
		bool hasCar = (registerationForm->getCar() == "1") ? true: false;
		bool checkLocks;
		bool checkLights;
		bool checkSpeakers;
		bool checkCurtains;
		bool checkHeating;
		bool checkCameras;

//		myFile >> fN;
//		myFile >> lN;
//		myFile >> pN;
//		myFile >> cnic;
//		myFile >> hasCar;

		if (users.find(cnic) != users.end())
		{
			ShowMessage("Your are already part of this home Sirr!!!");
			return false;
		}


		serviceProviderForm->ShowModal();

		fstream myFile;

		myFile.open("userData.txt", ios::in);

		myFile >> checkLocks;
		myFile >> checkLights;
		myFile >> checkSpeakers;
		myFile >> checkCurtains;
		myFile >> checkHeating;
		myFile >> checkCameras;

//		users.insert(new User(cnic, pN, fN, lN, hasCar, checkLocks, checkLights, checkSpeakers, checkCurtains, checkHeating, checkCameras));

		users[cnic] = new User(cnic, pN, fN, lN, hasCar, checkLocks, checkLights, checkSpeakers, checkCurtains, checkHeating, checkCameras);

		myFile.close();
	}

	// TODO: Garage Implementation
	void carParking()
    {
		inputCnicForm->ShowModal();

		long long cnic = inputCnicForm->getCnic();

		if(users.find(cnic) == users.end())
			ShowMessage("User is not part of this home");
		else
		{
			User *user = users[cnic];
			if(user == NULL)
			{
				ShowMessage("NULL");
			}

			if(!user->hasCar)
				ShowMessage("You dont have any car to park Dude!!!");
			else
			{
				if (carsPresent >= 2)
					ShowMessage("No Space in Garage. Park it OutSide");
				else
				{
					if(user->location == "Home")
						ShowMessage("Your Car is already in Home.");
					else
					{
						carsPresent++;
						user->location = "Home";
						if(carsPresent == 1)
							garageForm->carImage1->Visible = true;
						else
							garageForm->carImage2->Visible = true;
					}
				}

			}
		}
	}

	void takingCarOut()
	{
		if (carsPresent < 1)
		{
			ShowMessage("There isn't any car present in Garage.");
			return;
		}

		inputCnicForm->ShowModal();

		long long key = inputCnicForm->getCnic();

		if (users.find(key) == users.end())
			ShowMessage("You aren't part of this home Sirrr!! Moye Moye");
		else
		{
			if (!users[key]->hasCar)
				ShowMessage("You Don't have any car Sirrrr...");
			else
			{
				if (users[key]->location == "Street")
					ShowMessage("Your Car is Standing Outside on Street Mannnn!!!");
				else if(users[key]->location == "Home")
				{
					if(carsPresent == 2)
						garageForm->carImage2->Visible = false;
					if(carsPresent == 1)
						garageForm->carImage1->Visible = false;

					carsPresent--;

					locationInputForm->ShowModal();

					users[key]->location = locationInputForm->getLocation();
				}
				else
				{
				   ShowMessage("You car is already on a ride Sir!!!");
				}
			}
        }
	}

	void userLocation()
	{
		inputCnicForm->ShowModal();

		long long key = inputCnicForm->getCnic();

		if (users.find(key) == users.end())
            ShowMessage("Sorry! User with this cnic is not part of this Home.");
		else
        {
			if (!users[key]->hasCar)
				ShowMessage("This user is not having a car and is in Home.");
			else if(users[key]->location == "Home" || users[key]->location == "Street")
				ShowMessage("User is at home");
			else
			{
				string str = users[key]->location;
				AnsiString loc = str.c_str();

				ShowMessage("User is off to " + loc);
			}
		}
	}

	void userInfo()
	{
        inputCnicForm->ShowModal();

		long long cnic = inputCnicForm->getCnic();

		if(users.find(cnic) == users.end())
			ShowMessage("User is not part of this home");
		else
		{
//			user = users[cnic];
			User *user = users[cnic];

		fstream myFile;
		myFile.open("userData.txt", ios::out | ios::trunc);

		myFile << user->firstName << endl;
		myFile << user->lastName << endl;
		myFile << user->phoneNumber << endl;
		myFile << user->key << endl;
		myFile << user->hasCar << endl;
		myFile << user->location << endl;
		myFile << user->smart_locks << endl;
		myFile << user->smart_lighting << endl;
		myFile << user->smart_speakers << endl;
		myFile << user->smart_curtains << endl;
		myFile << user->smart_heating << endl;
		myFile << user->smart_cctv << endl;

		myFile.close();
		userDetailsForm->ShowModal();
        }
	}

};


//Home *h1;
