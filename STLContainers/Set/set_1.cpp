#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef SET
#define SET
#include<set>
#endif

//******************************************************************************
//http://thispointer.com/using-stdset-with-user-defined-classes/
//http://thispointer.com/using-stdset-with-external-sorting-criteria-comparator/

class Message
{
public:
	std::string m_MsgContent;
	std::string m_sentBy;
	std::string m_recivedBy;

	Message(std::string sentBy, std::string recBy, std::string msg) :
		m_MsgContent(msg), m_sentBy(sentBy), m_recivedBy(recBy)
	{}

	bool operator< (const Message & msgObj) const
	{
		std::string rightStr = msgObj.m_MsgContent + msgObj.m_sentBy + msgObj.m_recivedBy;
		std::string leftStr = this->m_MsgContent + this->m_sentBy + this->m_recivedBy;
		return (leftStr < rightStr);
	}

	//Now we want to keep only single message sent by each user i.e. only one sent message is allowed per user
	/*
	Option 1: Modify operator <, but then it can hamper our previous requirements and it might be possible that we don�t have write access to operator <.
	Option 2: Create a new set and use an external soring criteria i.e Comparator.
	*/


	friend std::ostream& operator<<(std::ostream& os, const Message& obj);

};
std::ostream& operator<<(std::ostream& os, const Message& obj)
{
	os << obj.m_sentBy << " :: " << obj.m_MsgContent << " :: " << obj.m_recivedBy << std::endl;
	return os;
}

class MessageUserComparator
{
	std::string m_userName;
public:
	MessageUserComparator(std::string userName): m_userName(userName) {}
	bool operator() (const Message& msg1, const Message& msg2) const
	{
		if (msg1.m_sentBy < msg2.m_sentBy)
			return true;
		else
			return false;
	}
};


int main_external_sorting()
{
	std::set<Message> setOfMsgs;

	Message msg1("user_1", "Hello", "user_2");
	Message msg2("user_1", "Hello", "user_3");
	Message msg3("user_3", "Hello", "user_1");
	// A Duplicate Message
	Message msg4("user_1", "Hello", "user_3");

	setOfMsgs.insert(msg1);
	setOfMsgs.insert(msg2);
	setOfMsgs.insert(msg3);
	setOfMsgs.insert(msg4);
		// msg4 will not get inserted because its duplicate as per the current operator < implementation.

	// Iterate through all the elements in a set and display the value.
	for (std::set<Message>::iterator it = setOfMsgs.begin(); it != setOfMsgs.end(); ++it)
		std::cout << *it;

	std::cout << std::endl;
	// std::set that contains the messages sent by user - "user_1"
	std::cout << "set that contains the messages sent by user - user_1" << std::endl;
	std::set<Message, MessageUserComparator> setOfMsgs_1(MessageUserComparator("user_1"));

	setOfMsgs_1.insert(msg1);
	setOfMsgs_1.insert(msg2);
	setOfMsgs_1.insert(msg3);
	setOfMsgs_1.insert(msg4);
	// msg1, msg2 and msg4 are duplicates according to MessageUserComparator implementation
	// hence only 2 element are actually inserted in std::set
	// Iterate through all the elements in a set and display the value.
	for (std::set<Message>::iterator it = setOfMsgs_1.begin(); it != setOfMsgs_1.end(); ++it)
		std::cout << *it;
	
	return 0;
}


//******************************************************************************
//http://thispointer.com/stdset-tutorial-part-1-set-usage-details-with-default-sorting-criteria/

std::set<int> setOfNumbers;
void checkAndInsert(int num)
{
	if (setOfNumbers.insert(num).second) {
		//????/*std::cout << "First: " << setOfNumbers.insert(num).first << " Second" << setOfNumbers.insert(num).second << std::endl;*/
		std::cout << "Number " << num << " inserted sucessfuly\n";
	}
	
	else
		std::cout << "Number " << num << " was already present in set\n";
}


int main_set_thispointer()
{
	checkAndInsert(2);
	checkAndInsert(3);
	checkAndInsert(2);
	checkAndInsert(1);
	checkAndInsert(4);
	checkAndInsert(3);
	// Check the size of set
	std::cout << setOfNumbers.size() << std::endl;

	// Iterate through all the elements in a set and display the value.
	for (std::set<int>::iterator it = setOfNumbers.begin(); it != setOfNumbers.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << "\n";
	
	setOfNumbers.erase(3);
	for (std::set<int>::iterator it = setOfNumbers.begin(); it != setOfNumbers.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << "\n";
	return 0;
}



int main()
{
	main_set_thispointer();
	main_external_sorting();
	return 0;
}
