#include <stdio.h>
#include <string.h>

int main() {
    // =========================================================================
    // 1. STATE MANAGEMENT (PERSISTENT STATE ACROSS USER SESSIONS)
    // =========================================================================
    int system_active = 1; // Outer loop control: Keeps the ATM hardware running
    int default_pin = 1234; // Dynamic PIN state: Retains updates across logouts
    float balance = 1000.00; // Account balance state in memory
    
    // Constant OTP for simulation
    const int system_otp = 8842;

    // =========================================================================
    // TIER 1: ATM HARDWARE / POWER LOOP
    // =========================================================================
    while (system_active) {
        int authenticated = 0; // Tracks if current user cleared PIN check
        int entered_pin;

        printf("\n==================================================\n");
        printf("         WELCOME TO THE NO BANK ATM SYSTEM        \n");
        printf("==================================================\n");
        printf("   [Security Gateway: Please Login to Proceed]   \n\n");

        // --- SECURITY ACCESS GATE ---
        while (!authenticated) {
            printf("Enter your 4-digit PIN (or enter -1 to SHUT DOWN): ");
            scanf("%d", &entered_pin);

            // Secret Maintenance/Power-Off Option
            if (entered_pin == -1) {
                printf("\nShutting down ATM terminal hardware... Power Off.\n");
                system_active = 0; // Terminate hardware loop
                break;
            }

            // PIN Verification Check
            if (entered_pin == default_pin) {
                printf("\nAccess Granted! Initializing user session...\n\n");
                authenticated = 1; // Unlocks Tier 2 (Inner Session Loop)
            } else {
                printf("\nERROR: Incorrect PIN! Please try again.\n\n");
            }
        }

        // If user chose to power off at security gateway, skip inner loop
        if (!system_active) {
            break;
        }

        // =====================================================================
        // TIER 2: ACTIVE USER SESSION LOOP
        // =====================================================================
        int session_active = 1; // Inner loop control: Controls main menu lifecycle

        while (session_active) {
            int choice;

            // --- MAIN MENU INTERFACE ---
            printf("|------------------------------------|\n");
            printf("| %-34s |\n", "");
            printf("| %-34s |\n", "    --- WELCOME TO THE ATM ---    ");
            printf("| %-34s |\n", "");
            printf("|------------------------------------|\n");
            printf("| %-34s |\n", "");
            printf("|====================================|\n");
            printf("| %-34s |\n", "");
            printf("| %-34s |\n", "check balance : 1");
            printf("| %-34s |\n", "reset pin     : 2");
            printf("| %-34s |\n", "renew account : 3");
            printf("| %-34s |\n", "withdraw      : 4");
            printf("| %-34s |\n", "deposit       : 5");
            printf("| %-34s |\n", "logout        : 6");
            printf("| %-34s |\n", "");
            printf("|====================================|\n");
            printf("| %-34s |\n", "");
            printf("|------------------------------------|\n");
            printf("\nEnter your choice number: ");
            scanf("%d", &choice);

            // =================================================================
            // CORE TRANSACTION LOGIC ROUTER
            // =================================================================

            // --- OPTION 1: BALANCE INQUIRY ---
            if (choice == 1) {
                printf("\nYour current account balance is: $%.2f\n", balance);
            }

            // --- OPTION 2: DYNAMIC PIN RESET ---
            else if (choice == 2) {
                int verification;
                printf("\nEnter your current PIN: ");
                scanf("%d", &verification);

                // Authenticate before allowing modification
                if (verification == default_pin) {
                    int new_pin, confirm_pin;

                    printf("Enter new 4-digit PIN: ");
                    scanf("%d", &new_pin);
                    printf("Re-enter new PIN to confirm: ");
                    scanf("%d", &confirm_pin);

                    // Confirm matching PIN inputs
                    if (new_pin == confirm_pin) {
                        default_pin = new_pin; // Mutate dynamic state in memory
                        printf("\nSUCCESS: PIN updated successfully to: %d\n", default_pin);
                    } else {
                        printf("\nERROR: Confirmation PIN mismatch! Update aborted.\n");
                    }
                } else {
                    printf("\nERROR: Incorrect current PIN! Access denied.\n");
                }
            }

            // --- OPTION 3: OTP ACCOUNT RENEWAL ---
            else if (choice == 3) {
                int user_otp;
                printf("\n--- ACCOUNT RENEWAL SYSTEM ---\n");
                printf("[SMS Simulator] Your 4-digit OTP is: %d\n", system_otp);
                printf("Enter the OTP to renew your account: ");
                scanf("%d", &user_otp);

                if (user_otp == system_otp) {
                    printf("\nSUCCESS: OTP Verified! Your ATM account is fully renewed.\n");
                } else {
                    printf("\nERROR: Invalid OTP! Account renewal aborted.\n");
                }
            }

            // --- OPTION 4: WITHDRAWAL SYSTEM ---
            else if (choice == 4) {
                float withdraw_amount;
                printf("\nEnter the amount to withdraw: $");
                scanf("%f", &withdraw_amount);

                // Bounds & Sufficiency Validation
                if (withdraw_amount <= 0) {
                    printf("ERROR: Invalid amount! Please enter a value greater than $0.00.\n");
                } else if (withdraw_amount > balance) {
                    printf("ERROR: Insufficient funds! Current balance: $%.2f\n", balance);
                } else {
                    balance -= withdraw_amount; // Mutate balance state
                    printf("Withdrawal successful! Remaining balance: $%.2f\n", balance);
                }
            }

            // --- OPTION 5: DEPOSIT SYSTEM ---
            else if (choice == 5) {
                float deposit_amount;
                printf("\nEnter the amount to deposit: $");
                scanf("%f", &deposit_amount);

                // Input Validation
                if (deposit_amount <= 0) {
                    printf("ERROR: Invalid amount! Please enter a value greater than $0.00.\n");
                } else {
                    balance += deposit_amount; // Accumulate balance state
                    printf("Deposit successful! New balance: $%.2f\n", balance);
                }
            }

            // --- OPTION 6: LOG OUT (RETURN TO SECURITY GATE) ---
            else if (choice == 6) {
                printf("\nLogging out... Returning to Security Gateway.\n");
                session_active = 0; // Terminate inner loop, drop back to Tier 1
            }

            // --- FALLBACK: INVALID MENU CHOICE ---
            else {
                printf("\nInvalid selection! Please pick a number between 1 and 6.\n");
            }

            // --- INTERFACE PAUSE SCREEN ---
            if (session_active) {
                printf("\nPress Enter to return to the main menu...");
                getchar(); // Consume trailing '\n' character from previous scanf
                getchar(); // Block execution until Enter key press
                printf("\n");
            }
        }
    }

    return 0;
}