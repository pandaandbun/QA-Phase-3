main: main.cpp ./Login/login.cpp ./CurrentBankAccounts/bankaccounts.cpp ./Paybill/paybill.cpp ./Transfer/transfer.cpp ./ChangePlan/changeplan.cpp ./Delete/delete.cpp ./Withdrawal/withdrawal.cpp ./Deposit/deposit.cpp ./Create/create.cpp ./Disable/disable.cpp ./BankAccountTransaction/bankaccounttransaction.cpp ./Logout/logout.cpp
	g++ -o ./bank main.cpp ./Login/login.cpp  ./CurrentBankAccounts/bankaccounts.cpp ./Paybill/paybill.cpp ./Transfer/transfer.cpp ./ChangePlan/changeplan.cpp ./Delete/delete.cpp ./Withdrawal/withdrawal.cpp ./Deposit/deposit.cpp ./Create/create.cpp ./Disable/disable.cpp ./BankAccountTransaction/bankaccounttransaction.cpp ./Logout/logout.cpp
	
clean:
	rm bank