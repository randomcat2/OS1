#!/bin/bash

# Initialize an empty contact list
contacts=()

# Function to show the menu
show_menu() {
    echo "Contact Management System"
    echo "1. Add Contact"
    echo "2. Delete Contact"
    echo "3. Update Contact"
    echo "4. View Contacts"
    echo "5. Search Contact"
    echo "6. Exit"
    read -p "Please select an option (1-6): " choice
}

# Function to add a contact
add_contact() {
    read -p "Enter contact name: " name
    read -p "Enter contact phone number: " phone
    contacts+=("$name:$phone")
    echo "Contact added successfully!"
}

# Function to delete a contact
delete_contact() {
    read -p "Enter the name of the contact to delete: " name
    for i in "${!contacts[@]}"; do
        if [[ "${contacts[i]}" =~ ^$name: ]]; then
            unset 'contacts[i]'
            echo "Contact deleted successfully!"
            return
        fi
    done
    echo "Contact not found."
}

# Function to update a contact
update_contact() {
    read -p "Enter the name of the contact to update: " name
    for i in "${!contacts[@]}"; do
        if [[ "${contacts[i]}" =~ ^$name: ]]; then
            read -p "Enter new phone number: " phone
            contacts[i]="$name:$phone"
            echo "Contact updated successfully!"
            return
        fi
    done
    echo "Contact not found."
}

# Function to view all contacts
view_contacts() {
    if [ ${#contacts[@]} -eq 0 ]; then
        echo "No contacts available."
    else
        echo "Contacts:"
        for contact in "${contacts[@]}"; do
            echo "$contact"
        done
    fi
}

# Function to search for a contact
search_contact() {
    read -p "Enter the name of the contact to search: " name
    for contact in "${contacts[@]}"; do
        if [[ "$contact" =~ ^$name: ]]; then
            echo "Contact found: $contact"
            return
        fi
    done
    echo "Contact not found."
}

# Main script logic
while true; do
    show_menu
    case $choice in
        1) add_contact ;;
        2) delete_contact ;;
        3) update_contact ;;
        4) view_contacts ;;
        5) search_contact ;;
        6) echo "Exiting program. Goodbye!"; exit 0 ;;
        *) echo "Invalid option. Please try again." ;;
    esac
done
#chmod +x address_book.sh
#./address_book.sh



