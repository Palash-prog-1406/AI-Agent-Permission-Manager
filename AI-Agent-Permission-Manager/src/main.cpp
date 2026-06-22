#include "PermissionManager.h"
#include <iostream>

void showMenu() {
    std::cout << "\n===== AI Agent Permission Manager =====\n";
    std::cout << "1. View Agents\n";
    std::cout << "2. View Tools\n";
    std::cout << "3. View Permissions\n";
    std::cout << "4. Add Agent\n";
    std::cout << "5. Add Tool\n";
    std::cout << "6. Assign Permission\n";
    std::cout << "7. Request Tool Access\n";
    std::cout << "8. View Audit Logs\n";
    std::cout << "9. View Pending Reviews\n";
    std::cout << "10. Approve/Reject Pending Request\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter choice: ";
}

int main() {
    PermissionManager manager("data");
    manager.loadData();

    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                manager.viewAgents();
                break;
            case 2:
                manager.viewTools();
                break;
            case 3:
                manager.viewPermissions();
                break;
            case 4:
                manager.addAgent();
                break;
            case 5:
                manager.addTool();
                break;
            case 6:
                manager.assignPermission();
                break;
            case 7:
                manager.requestAccess();
                break;
            case 8:
                manager.viewAuditLogs();
                break;
            case 9:
                manager.viewPendingReviews();
                break;
            case 10:
                manager.reviewPendingRequest();
                break;
            case 0:
                std::cout << "Exiting project. Goodbye.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

