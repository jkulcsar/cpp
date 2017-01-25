

#include "pstreams.h"
#include "pinet.h"

#define FILE_BUF_SIZE		4096

USING_PTYPES

//logfile  pout;
//logfile  perr;


int clientport = 8085;
const int maxtoken = 4096;

int main(int argc , char** argv)
{
    // create a client socket and send a greeting to the server
    // assuming that the server is on the same host (127.0.0.1)
	if( argc > 1 )	{
		pout.putf("Command line arguments are:\n");
		for( int i = 1; i < argc; ++i )
			pout.putf("%s\n", argv[i]);
		clientport = stringtoi(argv[1]);
	}


    ipstream client(ipaddress(127, 0, 0, 1), clientport);

    try
    {
        client.open();

        pout.put("Sending a request to the server...\n");
        client.putline("hello");
        client.flush();

        // receive the response
/*
		outfile f("temp.jpg");
		try
		{
			f.set_bufsize(0);
			f.open();
		}
		catch(estream* e)
		{
			perr.putf("Error: %s\n", pconst(e->get_message()));
			delete e;
		}

		char buf[FILE_BUF_SIZE];
		int rx;
		do
		{
			rx = client.read(buf, sizeof(buf));
			f.write(buf, rx);
		}
		while (rx > 0);

		f.flush();
		f.close();
*/

        string rsp = client.line(maxtoken);
        pout.putf("Received: %s\n", pconst(rsp));

        // need to close the socket explicitly to gracefully shutdown 
        // the peer host too. otherwise, ~ipstream() will call cancel()
        // and leave the peer in a waiting state (not forever though).
        client.close();
    }
    catch(estream* e)
    {
        perr.putf("Error: %s\n", pconst(e->get_message()));
        delete e;
    }

    return 0;
}
