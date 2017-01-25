
//
// item 43: Know how to access names in templatized base classes

#include <string>

class CompanyA
{
public:
	void sendCleartext(const std::string& msg) {}
	void sendEncrypted(const std::string& msg) {}
	//
	// ... other functions
};

class CompanyB
{
public:
	void sendCleartext(const std::string& msg) {}
	void sendEncrypted(const std::string& msg) {}
	//
	// ... other functions
};

class CompanyZ {                             // this class offers no
public:                                      // sendCleartext function
	//...
	void sendEncrypted(const std::string& msg);
	//...
};



class MsgInfo
{
	//...
};

template< typename Company>
class MsgSender
{
public:
	void sendClear(const MsgInfo& info)
	{
		std::string msg;
		// create message from info
		Company c;
		c.sendCleartext(msg);	// call function on a class instantiation
	}

	void sendSecret(const MsgInfo& info)
	{
		std::string msg;
		// create message from info
		Company c;
		c.sendEncrypted(msg);	// call function on a class instantiation
	}
};

template<>                                 // a total specialization of
class MsgSender<CompanyZ> {                // MsgSender; the same as the
public:                                    // general template, except
  //...                                    // sendCleartext is omitted

  void sendSecret(const MsgInfo& info)
  {
	  //...
  }
};


template<typename Company>
class LoggingMsgSender : public MsgSender<Company>
{
public:
	void sendClearMessage(const MsgInfo& info)
	{
		// ... first log the message about to be sent
		
		// then call the base class to send it:
		sendClear(info);		// this won't compile!

		// ... and log again after the message was sent
	}
};
int main(int argc, char** argv)
{
	MsgInfo messageToBeSent;

	MsgSender<CompanyA> senderToA;
	MsgSender<CompanyB> senderToB;

	senderToA.sendClear(messageToBeSent);
	senderToB.sendSecret(messageToBeSent);

	LoggingMsgSender<CompanyA> loggingSenderToA;
	LoggingMsgSender<CompanyB> loggingSenderToB;
	LoggingMsgSender<CompanyZ> loggingSenderToZ;
	loggingSenderToA.sendClearMessage(messageToBeSent);
	
	// the following won't compile because the 
	// specialized MsgSender for CompanyZ does not have
	// sendClear()
	// loggingSenderToZ.sendClearMessage(messageToBeSent);

	return 0;
}
