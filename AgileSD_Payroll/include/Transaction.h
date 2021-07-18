#pragma once

class Transaction
{
public:
    Transaction() = default;
    Transaction(const Transaction& other) = default;
    Transaction(Transaction&& other) noexcept = default;
    Transaction& operator=(const Transaction& other) = default;
    Transaction& operator=(Transaction&& other) noexcept = default;
    virtual ~Transaction() = default;
    virtual void Execute() = 0;
};

