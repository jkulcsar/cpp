
/////////////////////////////////////////////////////////////////////////////////

#include <ptime.h>
#include <pinet.h>

USING_PTYPES

const int maxtoken = 4096;


/////////////////////////////////////////////////////////////////////////////////

trigger g_peerWatch(false, false);
mutex	g_mutex_client_iostatus;
mutex	g_mutex_server_iostatus;

class myclientthread: public thread
{
protected:
    virtual void execute();

public:
	ipstream*	client;
	int			clientport;

	static void client_iostatus(iobase* , int );

    myclientthread(int p) : thread(false), clientport(p) {
		client = new ipstream();
		if( client != NULL)
		{
			client->set_onstatus(&client_iostatus);
			client->set_ip(ipaddress(127, 0, 0, 1));
			client->set_port(clientport);
		}
	}

    ~myclientthread()  
	{
		if(client != NULL)
			client->close();
//		waitfor(); 
	}
};


void myclientthread::execute()
{
	// client should keep trying to connect to server
	// if server closes connection explicitly, then client should quit, too
	int stream_status = 0;
	int ncount = 0;

//	do
//	{
		try
		{

/*
			if( client->get_active() )
				pout.putf("Client active...\n");
			else
				pout.putf("Client not active...\n");


			while(stream_status = client->get_status() != IO_OPENED)
			{
				pout.putf("Trying to connect to server %s on port %d...\n", 
					iptostring(client->get_ip()), 
					client->get_port());

				client->open();
				
				// wait before re-trying
				relax(1000);
			}
*/
			
			client->open();

			pout.put("Sending a request to the server...\n");
			client->putline("Hello");
			client->flush();

			// receive the response
//			string rsp = client->line(maxtoken);
//			pout.putf("Received: %s\n", pconst(rsp));
		   
			// need to close the socket explicitly to gracefully shutdown 
			// the peer host too. otherwise, ~ipstream() will call cancel()
			// and leave the peer in a waiting state (not forever though).

			// client->close();

			ncount++;
			relax(1000);
		}
		catch(estream* e)
		{
			perr.putf("Error: %s code = %d\n", pconst(e->get_message()), e->get_code());
			client->close();
			delete e;
		}
	}
//	while(!get_signaled());
//	while(ncount < 20);
//}



void myclientthread::client_iostatus(iobase* cl, int code)
{
	scopelock sl(g_mutex_client_iostatus);

	int stream_status = ((ipstream*)cl)->get_status();

	// IO_CREATED, IO_OPENING, IO_OPENED, IO_READING, IO_WRITING, IO_EOF, IO_CLOSING, IO_CLOSED
	// IO_RESOLVING, IO_RESOLVED, IO_CONNECTING, IO_CONNECTED 

	if( (stream_status & IO_CREATED) ==  IO_CREATED)
		pout.putf("IO_CREATED\n");
	if( (stream_status & IO_OPENING) == IO_OPENING)
		pout.putf("IO_OPENING\n");
	if( (stream_status & IO_OPENED) == IO_OPENED)
		pout.putf("IO_OPENED\n");
	if( (stream_status & IO_READING) == IO_READING)
		pout.putf("IO_READING\n");
	if( (stream_status & IO_WRITING) == IO_WRITING)
		pout.putf("IO_WRITING\n");
	if( (stream_status & IO_EOF) == IO_EOF)
	{
		pout.putf("IO_EOF\n");
		g_peerWatch.signal();
	}
	if( (stream_status & IO_CLOSING) == IO_CLOSING)
		pout.putf("IO_CLOSING\n");
	if( (stream_status & IO_CLOSED) == IO_CLOSED)
	{
		pout.putf("IO_CLOSED\n");
//		signal(); //signal() the thread
	}

	if( (stream_status & IO_RESOLVING) == IO_RESOLVING)
		pout.putf("IO_RESOLVING\n");
	if( (stream_status & IO_RESOLVED) == IO_RESOLVED)
		pout.putf("IO_RESOLVED\n");
	if( (stream_status & IO_CONNECTING) == IO_CONNECTING)
		pout.putf("IO_CONNECTING\n");
	if( (stream_status & IO_CONNECTED) == IO_CONNECTED)
	{
		pout.putf("IO_CONNECTED\n");
//		cl->open();
	}

	pout.putf("code = %d\n", code);
}





//////////////////////////////////////////////////////////////////////////////////////////////////////

class myserverthread: public thread
{
protected:
    virtual void execute();
public:
	ipstream* client;
	static void server_iostatus(iobase* , int );
    myserverthread(ipstream* iclient) : thread(false), client(iclient) {
		if(client!= NULL)
		{
//			client->set_onstatus(&server_iostatus);
		}
	
	}
    ~myserverthread()  { waitfor(); }
};



void myserverthread::execute()
{
	pout.putf("Serving client...\n");

	try
	{
		string req = lowercase(client->line(maxtoken));
		if (req == "hello")
		{
			// try to reverse-lookup the client's IP
			string host = phostbyaddr(client->get_ip());
			if (isempty(host))
				host = iptostring(client->get_ip());
	        
			// now send our greeting to the client
			client->putline("Hello, " + host + " ("
				+ iptostring(client->get_ip()) + "), nice to see you!");
			client->flush();
		}
		client->close();
	}
	catch(estream* e)
	{
		perr.putf("Error: %s\n", pconst(e->get_message()));
		delete e;
	}
}


void myserverthread::server_iostatus(iobase* cl, int code)
{
	scopelock sl(g_mutex_server_iostatus);

	int stream_status = ((ipstream*)cl)->get_status();

	// IO_CREATED, IO_OPENING, IO_OPENED, IO_READING, IO_WRITING, IO_EOF, IO_CLOSING, IO_CLOSED
	// IO_RESOLVING, IO_RESOLVED, IO_CONNECTING, IO_CONNECTED 

	if( (stream_status & IO_CREATED) ==  IO_CREATED)
		pout.putf("IO_CREATED\n");
	if( (stream_status & IO_OPENING) == IO_OPENING)
		pout.putf("IO_OPENING\n");
	if( (stream_status & IO_OPENED) == IO_OPENED)
		pout.putf("IO_OPENED\n");
	if( (stream_status & IO_READING) == IO_READING)
		pout.putf("IO_READING\n");
	if( (stream_status & IO_WRITING) == IO_WRITING)
		pout.putf("IO_WRITING\n");
	if( (stream_status & IO_EOF) == IO_EOF)
		pout.putf("IO_EOF\n");
	if( (stream_status & IO_CLOSING) == IO_CLOSING)
		pout.putf("IO_CLOSING\n");
	if( (stream_status & IO_CLOSED) == IO_CLOSED)
		pout.putf("IO_CLOSED\n");

	if( (stream_status & IO_RESOLVING) == IO_RESOLVING)
		pout.putf("IO_RESOLVING\n");
	if( (stream_status & IO_RESOLVED) == IO_RESOLVED)
		pout.putf("IO_RESOLVED\n");
	if( (stream_status & IO_CONNECTING) == IO_CONNECTING)
		pout.putf("IO_CONNECTING\n");
	if( (stream_status & IO_CONNECTED) == IO_CONNECTED)
		pout.putf("IO_CONNECTED\n");


	pout.putf("code = %d\n", code);

}




////////////////////////////////////////////////////////////////////////////////////////////////////////

void servermain(ipstmserver& svr, int port)
{
    ipstream* client = new ipstream();

    pout.putf("Ready to answer queries on port %d\n", port);

    while(true)
    {
		// register i/o callback 
		if(client != NULL)
			client->set_onstatus(&myserverthread::server_iostatus);

		//
        svr.serve(*client);

        if (client->get_active())
        {
			myserverthread* st = new myserverthread(client);
			st->start();

			client = new ipstream();
        }
    }
}



int main(int argc , char** argv)
{
	string serverport;
	string clientport;

	pout.putf("This program was invoked with %d arguments\n", argc-1);

	if( argc > 1 )	{
		pout.putf("Command line arguments are:\n");
		for( int i = 1; i < argc; ++i )
			pout.putf("%s\n", argv[i]);
		serverport = argv[1];
		clientport = argv[2];
	}


/*
	// start server role
	// open server port, listening to client connection requests
    ipstmserver svr;

    try
    {
        // bind to all local addresses on port 8085
        svr.bindall(stringtoi(serverport));

        // enter an infinite loop of serving requests
        servermain(svr, stringtoi(serverport));
    }
    catch(estream* e)
    {
        perr.putf("FATAL: %s\n", pconst(e->get_message()));
        delete e;
    }
*/
	// start being a client
	// try to connect to server on client port
	myclientthread clientthread(stringtoi(clientport));
	clientthread.start();
	g_peerWatch.wait();
	clientthread.waitfor();

    return 0;
}

