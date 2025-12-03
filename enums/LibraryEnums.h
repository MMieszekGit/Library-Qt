#pragma once

namespace Library {
    enum class AddResult {
		Success,
		DuplicatedId,
		DuplicatedTitle
	};
	enum class AddLoanResult {
		Success,
		InvalidLoanId,
		InvalidUserId,
		InvalidBookId,
		NoAvailableBook,
        NoAvailableUserLoanSlot,
		HasBorrowedBook
	};
	enum class RemoveUserResult {
		Success,
		InvalidUserName,
		HasActiveLoans
	};
	enum class RemoveLoanResult {
		Success,
		InvalidLoanId
	};
	enum class RenewLoanResult {
		Success,
		InvalidLoanId
	};
}
