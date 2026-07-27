# 🏧 CLI ATM Machine Simulator in C


A lightweight, robust Command Line Interface (CLI) ATM Machine Simulator built in standard C (C99). The application demonstrates foundational systems engineering concepts including state management, multi-tier execution loops, input validation, and security access control.

---

## 🛠️ System Architecture

The application utilizes a **2-Tier Nested Loop Architecture** to separate the underlying terminal/hardware system from individual user sessions:

```text
┌────────────────────────────────────────────────────────┐
│ TIER 1: System Power / Hardware Loop                   │
│                                                        │
│  ┌──────────────────────────────────────────────────┐  │
│  │ Security Gateway: PIN Authentication Check       │  │
│  └────────────────────────┬─────────────────────────┘  │
│                           │ (Access Granted)           │
│                           v                            │
│  ┌──────────────────────────────────────────────────┐  │
│  │ TIER 2: Active User Session Loop                 │  │
│  │                                                  │  │
│  │   [1] Check Balance   [4] Withdraw Cash          │  │
│  │   [2] Reset PIN       [5] Deposit Cash           │  │
│  │   [3] Renew Account   [6] Logout Session         │  │
│  └────────────────────────┬─────────────────────────┘  │
│                           │                            │
│                           └─► Logout returns to Tier 1 │
│                                (Retains memory state)  │
└────────────────────────────────────────────────────────┘

✨ Features
 1. 🔒 Multi-Tier Session Control: Logging out returns the application to the security gateway screen without resetting memory variables.

 2. 🔑 Dynamic PIN Mutation: Users can safely update their 4-digit PIN during a session. The updated PIN is immediately enforced upon subsequent logouts.

 3. 💵 State-Driven Financial Transactions: Real-time balance accumulation and mutation for deposits and withdrawals.

 4. 🛡️ Defensive Input Validation: Robust checks against negative transactions, overdrafts, and confirmation PIN mismatches.

 5. 📲 Simulated 2FA Renewal: Integrated OTP verification step simulating account renewal protocols.

  SAMPLE USAGE:

  ==================================================
         WELCOME TO THE NO BANK ATM SYSTEM        
==================================================
   [Security Gateway: Please Login to Proceed]   

Enter your 4-digit PIN (or enter -1 to SHUT DOWN): 1234

Access Granted! Initializing user session...

|------------------------------------|
|                                    |
|       --- WELCOME TO THE ATM ---   |
|                                    |
|------------------------------------|
| check balance : 1                  |
| reset pin     : 2                  |
| renew account : 3                  |
| withdraw      : 4                  |
| deposit       : 5                  |
| logout        : 6                  |
|------------------------------------|