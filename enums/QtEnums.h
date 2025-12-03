#pragma once

namespace QtEnums {
    enum class SearchBookMode {
        Title,
        Author,
        Both
    };

    enum class UserManageMode {
        AddUser,
        DeleteUser
    };

    enum class LoanManageMode {
        AddLoan,
        ListUsersLoans,
        RemoveLoan,
        RenewLoan
    };
}

