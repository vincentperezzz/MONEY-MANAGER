#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

struct Node {
	string data;
	Node * next;
} * fNode; 

void addItem(Node * head);
void removeItem(Node * head);
void displayItems(Node * head);
void searchItem(Node * head);
void sortItems(Node * head);
int countNodes(Node * head);
int inquiry(int);

int main(){
	int choiceProcedure, choiceYN, choiceInq;
    bool NEXT = false;
    Node * head = new Node;
    head -> next = NULL;
    
	cout << "--------------------------------------------- Grocery Checklist ---------------------------------------------"  << endl;
	cout << "\nGeneral Guidelines:"
			"\n1. Read the prompts carefully." 
			"\n2. The program has limited functionality in its current state."
			"\n3. The program display the list based on stack data structure." 
			"\n4. Use numerical values when choosing an option."
			"\n5. If the user encounters any bugs or problems, notify the developers accordingly."
			"\n5. Have fun. :)" << endl;
	
	while(choiceProcedure != 6){
		cout << "\nChoose a process for the checklist: " << endl;
		cout << "1 - Add an item." << "\n2 - Remove an item." << "\n3 - Display all items." << "\n4 - Search an item." 
		     << "\n5 - Sort items according to name length." << "\n6 - EXIT." << endl;
		     
		cout << "Enter the number of your choice: ";
		cin >> choiceProcedure;
		
		switch(choiceProcedure){
			case 1:
				addItem(head);
				break;
			
			case 2:
				displayItems(head);
				removeItem(head);
				break;
			
			case 3:
				displayItems(head);
				choiceInq = inquiry(choiceProcedure);
					if (choiceInq != choiceProcedure){
						cout << "\nThank you for using the grocery checklist. Have a nice day! :)";
						exit(0);
					}
				break;
				
			case 4:
				searchItem(head);
				choiceInq = inquiry(choiceProcedure);
					if (choiceInq != choiceProcedure){
						cout << "\nThank you for using the grocery checklist. Have a nice day! :)";
						exit(0);
					}
				break;
			
			case 5:
				sortItems(head);
				choiceInq = inquiry(choiceProcedure);
					if (choiceInq != choiceProcedure){
						cout << "\nThank you for using the grocery checklist. Have a nice day! :)";
						exit(0);
					}
				break;
				
			case 6:
				do{
				cout << "\nAre you sure you want to EXIT?" << "\n1 - YES" << "\n2 - NO" << "\nEnter the number of your choice: ";
				cin >> choiceYN;
					if (choiceYN > 0 && choiceYN < 3){
						switch(choiceYN){
							case 1:
								cout << "\nThank you for using the grocery checklist. Have a nice day! :)";
								exit(0);
								break;
							default:
								choiceProcedure = 0;
								break;
						}
					} else{
						cout << "\nInvalid input. Please try again." << endl;
					}	
				} while (choiceProcedure == 6);
				break;	
					
			default:
				cout << "\nInvalid input. Please try again." << endl;
				break;
		}
	}
	
	return 0;
}

void addItem (Node * head){
	bool NEXT = false;
    string insertItem;
    Node * fNode;
    
	cin.ignore();
	cout << endl;
	
  	do{
        cout << "Enter Item (Input NEXT to stop inserting an item): ";
        getline(cin, insertItem);
		
        if (insertItem == "NEXT"){
            NEXT = true;
        }
        else{
            fNode = new Node;
            fNode -> data = insertItem;

            fNode -> next = head->next;
            head -> next = fNode;
        } 
    } while (!NEXT);
    
    return;
}
	
void removeItem(Node * head){
 	
 	string deleteItem;
    cout << "Enter item name to be deleted:";
    cin.ignore();
    getline(cin, deleteItem);

    Node * prev = head;
    Node * current = head->next;

    while (current)
    {
        if (current -> data == deleteItem){
            prev -> next = current -> next;
            delete current;
            
            cout << "\nThe name "<< deleteItem << " has been deleted!\n";
            cout << "The updated grocery list after deleting " << deleteItem << " is:";
            
            struct Node * fNode;
			fNode = head;
			
			do {
				cout << fNode -> data << endl; 
			    fNode = fNode -> next;               
			} while(fNode != NULL);
			
            return;
        }
        prev = current;
        current = current->next;
    }
    if (!current){
        cout << "\nThe item is not in the list." << endl;
    }
}

void displayItems(Node * head){	
	struct Node * fNode;
	fNode = head;

    if(fNode == NULL)
    	cout<< "\nThe grocery list is empty.";
    else{
    	cout << "\nYou entered the following items: ";
        do {
			cout << fNode -> data << endl; 
            fNode = fNode -> next;           
        } while(fNode != NULL);
    }
}

void searchItem(Node * head){

    struct Node * tmp;  
    int counter = 0, indicator;  
	
    tmp = head;   
    
    string searchItem;
 	cout << "\nEnter the item to be searched: ";
 	cin.ignore();
 	getline(cin, searchItem);
	
    if(tmp == NULL){  
        cout << "\nEmpty List" << endl;;  
    }  
    else{   
        while (tmp != NULL){  
            if(tmp -> data == searchItem){
	                cout << "\nItem found at location: " << counter << endl; 
					indicator = 0;
					break;
				} 
			else {
				indicator++;
				} 
				
			counter++; 
			tmp = tmp -> next;  
	    }  
	    	if(indicator != 0){
				cout << "\nItem not found\n";  
			}     		 
	} 
}

int countNodes(Node * head) {
  
	Node * temp = head;
	
	int counter = 0;
	  
	while(temp != NULL) {
		counter++;
	    temp = temp->next;
	  }
	
	return counter;  
} 

void sortItems(Node * head){
 
    int lengthOfList = countNodes(head);
 
   	string arr[lengthOfList];
 
    int index = 0;
    Node * current = head;

    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }
    
    for (int i = 1 ; i < lengthOfList; i++)
    {
        string temp = arr[i];
        int j = i - 1;
        while (j >= 0 && temp.length() < arr[j].length())
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
 	
 	cout << "\nThe items sorted in terms of name length: ";
 	for (int i = 0; i < lengthOfList; i++){
        cout << arr[i] << endl;
   }
}

int inquiry(int choice){
	int choiceInquiry;
	
	while (choice > 0 && choice < 5){
		cout << "\nDo you have any other revisions for the checklist?" << "\n1 - YES" << "\n2 - NO" << "\nEnter the number of your choice: ";
		cin >> choiceInquiry;
	
		if (choiceInquiry > 0 && choiceInquiry < 3){
			switch(choiceInquiry){
				case 1:
					return choice;
					break;
				default:
					return 0;
					break;
			}
		} else{
				cout << "\nInvalid input. Please try again." << endl;
				choiceInquiry = 0;
		}
	}
}
