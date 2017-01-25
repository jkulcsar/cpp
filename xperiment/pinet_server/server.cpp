
#include "pstreams.h"
#include "ptime.h"
#include "pinet.h"
#include <limits.h>
#include <sys/stat.h>

#define FILE_BUF_SIZE		4096

USING_PTYPES

const int testport = 8085;
const int maxtoken = 4096;


large get_file_size(const char* name)
{
    struct stat st;
    if (stat(name, &st) != 0)
        return -1;
    return st.st_size;
}


bool file_not_found()
{
	return true;
}


void servermain(ipstmserver& svr)
{
    ipstream client;

    pout.putf("Ready to answer queries on port %d\n", testport);

    while(true)
    {
        // serve() will wait for a connection request and will prepare
        // the supplied ipstream object for talking to the peer.
        // note that (unlikely) exceptions thrown in serve() will be 
        // caught in main()
        svr.serve(client);
        
        // for better performance the server would start a new thread
        // for each client request. for simplicity, we serve the request
        // in-place. see multithreading examples for the full multithreaded
        // server template.
        if (client.get_active())
        {
            try
            {
                // read the request line:
                // real-world network applications should limit input data
                // to prevent potential denial-of-service attacks
                string req = lowercase(client.line(maxtoken));
                if (req == "hello")
                {
                    // try to reverse-lookup the client's IP
                    string host = phostbyaddr(client.get_ip());
                    if (isempty(host))
                        host = iptostring(client.get_ip());
                    
                    // now send our greeting to the client
                    client.putline("Hello, " + host + " ("
                      + iptostring(client.get_ip()) + "), nice to see you!");
                    client.flush();
/*
					// open the binary file and read it in buffer
					large fsize64 = get_file_size("picture.jpg");
					// large files are not supported yet
					if (fsize64 >= (large)INT_MAX)
						file_not_found();
					int fsize = (int)fsize64;
					if (fsize < 0)
						file_not_found();

					infile f("picture.jpg");
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
					int txsize = fsize;
					while (txsize > 0)
					{
						int r = f.read(buf, imin(sizeof(buf), txsize));
						if (r <= 0)
							break;
						client.write(buf, r);
						txsize -= r;
					}
*/

					// if still data in buffer, write it to client ipstream
//					client.write();

                    // log this request
                    pout.putf("%t  greeting received from %s (%a)\n",
                        now(), pconst(host), long(client.get_ip()));
                }

//                client.close();
            }
            catch(estream* e)
            {
                perr.putf("Error: %s\n", pconst(e->get_message()));
                delete e;
            }
        }
    }
}

int main()
{
    ipstmserver svr;

    try
    {
        // bind to all local addresses on port 8085
        svr.bindall(testport);

        // enter an infinite loop of serving requests
        servermain(svr);
    }
    catch(estream* e)
    {
        perr.putf("FATAL: %s\n", pconst(e->get_message()));
        delete e;
    }

    return 0;
}
