#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition.hpp"

#include "boost/ref.hpp"

#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>

boost::mutex io_mutex;

class string_queue {

	typedef boost::mutex::scoped_lock scoped_lock;

	boost::mutex mutex_;
	std::queue<std::string> q_;
public:
	static const std::queue<std::string>::size_type MAX_QUEUE_SIZE = 20000;
	void add(std::string s) {
		scoped_lock lock(mutex_);
		q_.push(s);
	}

	std::string get() {
		scoped_lock lock(mutex_);
		std::string s;
		s.erase();
		if(!q_.empty()) {
			s = q_.front();
			q_.pop();
		}
		
		return s;
	}

	const bool empty() {
		scoped_lock lock(mutex_);
		return q_.empty();
	}

	const std::queue<std::string>::size_type size() {
		scoped_lock lock(mutex_);
		return q_.size();
	}
};

class file_reader {
	const std::string source_filename_;
public:

	file_reader() {}
	
	void operator()(string_queue& q, 
			boost::condition& queue_status, 
			boost::mutex& queue_status_mutex,
			boost::mutex& is_done_mutex,
			bool& is_done_flag
			) {

		std::cout << "File reader thread running..." << std::endl;

		// read from file and add CSV strings to the queue to be processed
		std::ifstream infile;

		try
		{
			infile.open("cmeebat_short.csv", std::ios::in);
			unsigned long counter = 0;

			std::string s;
			while(std::getline(infile,s)) {
			//{
			//	boost::mutex::scoped_lock lock(io_mutex);
			//	std::cout << "Lines read: " << ++counter << std::endl;
			//}


				if(q.size() >= string_queue::MAX_QUEUE_SIZE) {
					
					boost::mutex::scoped_lock lock(queue_status_mutex);
					
					{
						boost::mutex::scoped_lock lock(io_mutex);
						std::cout << "String queue to tokenize is full. Waiting..." << std::endl;
					}
					while(q.size() >= q.MAX_QUEUE_SIZE)
						queue_status.wait(lock);
				}
				else {
					// add the line just read to the queue to be processed
					q.add(s);
					// signal that element was just added to the queue
					queue_status.notify_all();
				}
			}
			infile.close();
			{
				boost::mutex::scoped_lock lock(io_mutex);
				std::cout << "Done reading file!" << std::endl;
			}

			//// add special message to the queue to signal
			//// the processing thread it can quit, the reader is done
			//// adding messages to the queue, this is the last one
			//q.add("QUIT!");
			//// signal that element was just added to the queue
			//// just in case the queue processing thread is blocked
			//// on the queue, this way for sure it will pick up the message
			//// to quit
			//queue_status.notify_all();

			{
				boost::mutex::scoped_lock lock(is_done_mutex);
				is_done_flag = true;
			}

			// send out another notification as if there was another
			// element added to the queue; not true but all waiting consumers
			// are woken up and firts they'll check the flag if they should quit
			queue_status.notify_all();
		}
		catch( std::ios_base::failure ex )	{
			std::cout << ex.what();
		}
		catch( std::runtime_error re )	{
			std::cout << re.what();
		}
	}
};

class tokenizer {
	std::vector<std::string> tokens_;


	void tokenize(std::string str) {
		// this must be set as a default parameter, perhaps as a tss?
		std::string delimiters = ",";

		// skip delimiters at beginning
		std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

		// find first "non-delimiter"
		std::string::size_type pos = str.find_first_of(delimiters, lastPos);

		while (std::string::npos != pos || std::string::npos != lastPos)
		{
			// found a token, add it to the vector
			tokens_.push_back(str.substr(lastPos, pos - lastPos));

			// skip delimiters
			lastPos = str.find_first_not_of(delimiters, pos);

			// find next "non-delimiter"
			pos = str.find_first_of(delimiters, lastPos);
		}
	}

public:

	void operator()(string_queue& q, 
		boost::condition& queue_status, 
		boost::mutex& queue_status_mutex,
		boost::mutex& is_done_mutex,
		bool& is_done_flag) {
		{
			boost::mutex::scoped_lock lock(io_mutex);
			std::cout << "String tokenizer thread running..." << std::endl;
		}

		
		while(true) {

			boost::mutex::scoped_lock queue_status_lock(queue_status_mutex);	
			if(q.empty()) {
				{
					boost::mutex::scoped_lock lock(io_mutex);
					std::cout << "String queue to tokenize is empty. Waiting..." << std::endl;
				}
				while(q.empty())
					queue_status.wait(queue_status_lock);
			}

			while(!q.empty()) {
				std::string s = q.get();
				tokenize(s);
				//std::vector<std::string>::const_iterator citer;
				//{	
				//	boost::mutex::scoped_lock lock(io_mutex);
				//	for(citer = tokens_.begin(); citer != tokens_.end(); ++citer) {
				//		std::cout << *citer << " | ";
				//	}
				//	std::cout << std::endl;
				//}

				// done with token processing, now erase them!
				tokens_.erase(tokens_.begin(), tokens_.end());
				// send out a notification that at least one element from the queue was processed
				queue_status.notify_one();
			}

			{
				boost::mutex::scoped_lock lock(is_done_mutex);
				if(is_done_flag == true)
					break;
			}
		}

		{
			boost::mutex::scoped_lock lock(io_mutex);
			std::cout << "Tokenizer thread quit!" << std::endl;
		}

	}
};


class tokenize_manager {

	struct is_done_checker {
	public:
		bool operator()() {
			return true;
		}
	};

	is_done_checker is_done_checker_;

	// 
	const std::string& source_filename_;

	// for now, only used by the tokenizer thread
	// should be a shared structure with a thread that does
	// something with the tokens, e.g. display or write to file...
	std::string tokens_;

	// shared queue of strings read from file and processed from
	string_queue q_;

	// add a flag and a mutex fir sync,
	// flagging when the producer is done; each consumer thread
	// should quit after the queue is empty
	// 
	boost::mutex is_done_mutex_;
	bool is_done_flag_;

	//
	boost::condition queue_status_;
	boost::mutex queue_status_mutex_;

	file_reader file_reader_object_;
	tokenizer tokenizer_object_;

	boost::thread file_reader_thread_;
	boost::thread tokenizer_thread_;
	boost::thread_group tokenizer_thread_group_;

public:
	tokenize_manager(const std::string& fn) : source_filename_(fn), is_done_flag_(false) {
		file_reader_thread_ = boost::thread(file_reader_object_, 
			boost::ref<string_queue>(q_),
			boost::ref<boost::condition>(queue_status_),
			boost::ref<boost::mutex>(queue_status_mutex_),
			boost::ref<boost::mutex>(is_done_mutex_),
			boost::ref<bool>(is_done_flag_)
			);
		tokenizer_thread_ = boost::thread(tokenizer_object_, 
			boost::ref<string_queue>(q_),
			boost::ref<boost::condition>(queue_status_),
			boost::ref<boost::mutex>(queue_status_mutex_),
			boost::ref<boost::mutex>(is_done_mutex_),
			boost::ref<bool>(is_done_flag_)
			);
		    
		for (int i = 0; i < 10; ++i)
			tokenizer_thread_group_.add_thread(
				new boost::thread(tokenizer_object_, 
				boost::ref<string_queue>(q_),
				boost::ref<boost::condition>(queue_status_),
				boost::ref<boost::mutex>(queue_status_mutex_),
				boost::ref<boost::mutex>(is_done_mutex_),
				boost::ref<bool>(is_done_flag_))
				);



		file_reader_thread_.join();
		//tokenizer_thread_.join();
		tokenizer_thread_group_.join_all();
	}
};

int main(int argc, char** argv)
{
	tokenize_manager tokenize_manager_instance("filename");

	return 0;
}