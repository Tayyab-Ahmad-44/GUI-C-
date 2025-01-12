﻿//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H

#include <iostream>
// #include "assignment_03.cpp"
#include <algorithm>
#include "RegisterationForm.h"

using namespace std;

class ServiceProviders
{
	void subscribe(int num)
	{
		switch (num)
		{
        case 1:
            smart_locks = true;
            break;
        case 2:
            smart_lighting = true;
            break;
        case 3:
            smart_speakers = true;
            break;
        case 4:
            smart_curtains = true;
            break;
        case 5:
            smart_heating = true;
            break;
        case 6:
            smart_cctv = true;
            break;

        default:
//			cout << "Please provide us with the iven numbers..." << endl;
			break;
		}
    }

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

//    void subscribeService()
//	{
////        cout << "Here are the services we provide:" << endl;
////		cout << "1- Smart Locks\n2- Smart Lighting\n 3- Smart Speakers\n4- Smart Curtains\n5- Smart Heating System\n6- Smart CCTV" << endl;
////		cout << "Write relevant numbers one by one to subscribe(-1 if you are done)\n\n";
//
//		for (int i = 0; i < 6; i++)
//		{
//			int num;
//			cin >> num;
//			if (num == -1)
//				break;
//			subscribe(num);
//		}
//
////        cout << "Thanks for subscribing to our services" << endl;
//	}

//	void displaySubscribedServices()
//	{
////        cout << "\nHere are services: " << endl;
////		cout << "Service:\t\tSubscribed(1) or Not(0)" << endl;
////		cout << "Smart Locks: \t\t" << smart_locks << endl
////			 << "Smart Lightning: \t\t" << smart_lighting << endl
////			 << "Smart Speakers: \t\t" << smart_speakers << endl
////			 << "Smart Curtains: \t\t" << smart_curtains << endl
////			 << "Smart Heating: \t\t" << smart_heating << endl
////			 << "Smart CCTV: \t\t" << smart_cctv << endl;
//	}
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

    User(long long cnic, string phoneNumber, string firstName, string lastName, bool hasCar = false)
    {
        this->key = cnic;
        this->phoneNumber = phoneNumber;
        this->firstName = firstName;
        this->lastName = lastName;
        this->hasCar = hasCar;
        this->location = "";
        this->height = 0;
        this->bf = 0;
        lChild = rChild = NULL;
    }

//    void display()
//	{
//		cout << "Name: " << firstName << " " << lastName << endl;
//		cout << "Phone No: " << phoneNumber << endl;
//		cout << "Cnic: " << key << endl;
//	}
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
		{
//            cerr << "Tree is Empty" << endl;
			return;
        }

        root = _deleteNode(root, key);
    }

    bool find(long long key)
    {
        if (!root)
        {
            return false;
        }

        return _search(root, key);
    }

    User *operator[](const long long key)
    {
        return _getUser(root, key);
    }

private:
    User *_insert(User *node, User *newNode)
    {
        if (node == NULL)
            return newNode;

        if (newNode->key < node->key)
            node->lChild = _insert(node->lChild, newNode);
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
        //? Variables for left/right subtrees heights
        int lh = -1;
        int rh = -1;

        //* These are assigned to -1 coz when the node is leaf node (no left or right subtrees),
        //* max will return -1 and it will be added to +1 so node's height will be equal to 0

        if (node->lChild)
            lh = node->lChild->height;
        if (node->rChild)
            rh = node->rChild->height;

        //! Update this node's height
        node->height = 1 + max(lh, rh);

        //! Update this node's Balance Factor
        node->bf = rh - lh;
    }

    User *_balance(User *node)
    {
        //! Left Heavy SubTree
        if (node->bf == -2)
            if (node->lChild->bf <= 0)
                return _leftLeftCase(node); //* means right rotation
            else
                return _leftRighCase(node); //* means one left then one right rotation

        //! Right Heavy SubTree
        else if (node->bf == 2)
            if (node->rChild->bf >= 0)
                return _rightRightCase(node); //* means left rotation
            else
                return _rightLeftCase(node); //* means one left then one right rotation

        //! User has balance factor of -1, 0, +1,
        //* which we do not need to balance.
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
    myMap users; // TODO: replacce with <key, value> = <id, User>
    int carsPresent;

    Home()
    {
        carsPresent = 0;
    }

    // TODO: Create User
    bool newUser()
    {
//        long long cnic;
//        string pN;
//        string fN;
//        string lN;

//        cout << "Enter Your First Name: ";
//		cin >> fN;
//        cout << "Enter Your Last Name: ";
//		cin >> lN;
//        cout << "Enter Your Phone Number: ";
//		cin >> pN;
//        cout << "Enter Your Cnic: ";
//		cin >> cnic;

        registerationForm = new TregisterationForm(this);
		registerationForm->ShowModal();

//		if (users.find(cnic))
//		{

//            cout << "Se ke zalima already da kor heasa ee. Ka pesa dersara dera e mala e raka..." << endl;
//			return false;
//		}

//		users.insert(new User(cnic, pN, fN, lN));

//        cout << "\nLet me ask some for the services now..." << endl;
//		cout << "Wanna space in Garage? Do You have a car?? (Yes: 1, No: 0):  ";
//		bool hasCar;
//        cin >> hasCar;
//		users[cnic]->hasCar = hasCar;

//        cout << "\nNow its time for the smart services that you can get in this house..." << endl;

//        users[cnic]->subscribeService();
	}

	// TODO: Garage Implementation
//	void carParking()
//	{
//		long long key;
////        cout << "Enter Cnic for Authentication: ";
//		cin >> key;
//
//		if (!users.find(key))
////            cout << "Wapasi Kwa Da De Kor Hesa Na Ye!!" << endl;
//		else
//		{
//            if (!users[key]->hasCar)
////				cout << "Alka garee dersara nesta or parking ta raghleee" << endl;
//			else
//            {
//                if (carsPresent >= 2)
////                    cout << "Gaare de Bahar Oodrawa Ze Neshta Kor Ke. Moye Moye!" << endl;
//				else
//                    carsPresent++;
//				users[key]->location = "";
//            }
//		}
//	}
//
//	void takingCarOut()
//	{
//		if (carsPresent < 1)
//		{
////			cout << "There isn't any car in Garage." << endl;
//			return;
//		}
//
//		long long key;
//		cout << "Kindly provide your cnic: ";
//		cin >> key;
//
//		if (!users.find(key))
//			cout << "You aren't part of this home Sirrr!! Moye Moye" << endl;
//		else
//		{
//			if (!users[key]->hasCar)
//				cout << "You Dont have any car Sirrrr... Go Buy car for yourself first Gharebooooooooooo..." << endl;
//			else
//			{
//				if (users[key]->location != "")
//					cout << "Your car isn't in Garage. Park kare de kor ke nade or lagya ee gaare bahar oobase Wrak sha mara..." << endl;
//				else
//				{
//					carsPresent--;
//					string location;
//					cout << "Your Life is in danger Boss!! Atleast tell us where are you going.. We might dont see you again Bossssssssssssssssssss...";
//					cin >> location;
//
//					users[key]->location = location;
//                }
//			}
//        }
//	}
//
//	void carLocation()
//    {
//		long long key;
//        cout << "Enter your Cnic: ";
//		cin >> key;
//
//		if (!users.find(key))
//            cout << "Sorry! You aren't part of this home. Ase pase da khalqo locatione ma check ko Zalima Police wala kho na ee cherta..." << endl;
//		else
//        {
//			if (!users[key]->hasCar)
//				int i = 0;
////                cout << "Sorry But User with this cnic is not having a carrrrr... Ghareeb kas de dumra tawako de werna shta che gaaree bam wersara eeeeeeeeee..." << endl;
//			else
//			{
//				string location = users[key]->location;
////                if (location == "")
////					cout << "This user's car is at home..." << endl;
////				else
////					cout << "User is having a cool ride...\nLocation: " << location << endl;
//			}
//		}
//	}
//
//	// TODO: Every User Data Storage / Displaying The Services that user subscribed for
////    void userDetails()
////	{
////		long long cnic;
////
////		cout << "Kindly Provide Your Cnic: ";
////		cin >> cnic;
////
////		if (users.find(cnic))
////			users[cnic]->display();
////        else
////			cout << "User with Cnic: " << cnic << " isn't part of this home. Sara koruno ke ye oogora ka melao shi" << endl;
////
////		users[cnic]->displaySubscribedServices();
////	}
};

//---------------------------------------------------------------------------
#endif
