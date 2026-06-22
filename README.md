# AI Agent Permission Manager

A C++ OOP project that simulates a permission and safety system for AI agents.

AI agents request access to tools such as reading files, sending emails, updating databases, or deleting records. The system checks the agent status, role permissions, and risk level before deciding whether to allow, deny, or send the request for admin review.

## Objective

The objective is to build a basic-to-intermediate Object-Oriented Programming project in C++ that demonstrates:

- Encapsulation
- Abstraction
- Inheritance
- Polymorphism
- Composition
- File handling
- Audit logging
- Risk-based decision making

## Methodology

The system follows this flow:

```text
Agent requests tool access
        ↓
StatusPolicy checks whether the agent is active
        ↓
RoleBasedPolicy checks whether the role has permission
        ↓
RiskBasedPolicy checks the risk score
        ↓
System returns ALLOW, DENY, or REVIEW_REQUIRED
        ↓
Audit log is saved
```

## Project Structure

```text
AI-Agent-Permission-Manager
├── data
│   ├── agents.csv
│   ├── tools.csv
│   ├── permissions.csv
│   ├── audit_logs.csv
│   └── pending_reviews.csv
├── include
│   ├── AccessDecision.h
│   ├── AccessRequest.h
│   ├── Agent.h
│   ├── AuditLog.h
│   ├── FileStorage.h
│   ├── Permission.h
│   ├── PermissionManager.h
│   ├── Policy.h
│   ├── RiskAnalyzer.h
│   └── Tool.h
└── src
    ├── AccessDecision.cpp
    ├── AccessRequest.cpp
    ├── Agent.cpp
    ├── AuditLog.cpp
    ├── FileStorage.cpp
    ├── Permission.cpp
    ├── PermissionManager.cpp
    ├── Policy.cpp
    ├── RiskAnalyzer.cpp
    ├── Tool.cpp
    └── main.cpp
```




## Main Features

- Add AI agents
- Add tools/actions
- Assign permissions to roles
- Request tool access
- Apply multiple policy checks
- Calculate risk score
- Save audit logs
- Store risky requests for admin review
- Approve or reject pending requests
- View audit history  

## Contributors

Palash Lahoti - 240721  
Kunal Kumar - 240582  
Aditya Kukreti - 240058  





