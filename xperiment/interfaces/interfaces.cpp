
#include <iostream>
#include <string.h>
class MessageListener {
public:
	virtual void messageReceived(const std::string& message)	=	0;
	virtual void subjectRemoved(const std::string& subject)	=	0;
	
	virtual ~MessageListener() { };
};

//MessageListener::~MessageListener()
//{
//}


class ChainListener : public MessageListener {
public:
	virtual void processChainComplete()	=	0;
	virtual void processChainPartial()	=	0;
	virtual void processChainResize()	=	0;
	virtual void processChainUpdate()	=	0;

	virtual ~ChainListener() { };
};

//ChainListener::~ChainListener()
//{
//}



class GeneralListener : public ChainListener {
public:
	void messageReceived(const std::string& message) {
	}
	
	void subjectRemoved(const std::string& subject) {
	}

	void processChainComplete() {
	}

	void processChainPartial() {
	}

	void processChainResize() {
	}

	void processChainUpdate() {
	}
};

typedef struct _struct_addition_prepay_info
{
      void                    *reserved1;
      void                    *m_client_data;
      char                    m_tune_param_id[64];
      char                    m_ppfunc_name[64];
      char                    m_ppname[64];           // output - name of prepay function called
      void                    *reserved2;
      void                    *m_user_data;
      void                    *reserved3;
      char                    m_default_tune_param[64];
      char                    m_loss_tune_param_id[64];
      char                    m_loss_func_name[64];
      char                m_loss_name[64];            // output - name of loss function called
} PLPAdditionalPrepayInfo;



int main( int argc , char** argv )
{
	std::cout << "The name of this program is " << argv[0] << std::endl;
	std::cout << "This program was invoked with " << argc-1 << " arguments" << std::endl;

	if( argc > 1 )	{
		std::cout << "Command line arguments are:" << std::endl;
		for( int i = 0; i < argc; ++i )
			std::cout << argv[i] << std::endl;
	}

	std::string msg;
	GeneralListener gl;

	gl.messageReceived( msg );

PLPAdditionalPrepayInfo *add = NULL;
add = new PLPAdditionalPrepayInfo();
if(add)
strcpy(add->m_loss_name, "DUMMY_STRING");

delete add;

	return 0;
}