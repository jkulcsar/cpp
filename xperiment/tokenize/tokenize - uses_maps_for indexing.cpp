
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>
#include <exception>
#include <bitset>

#include "boost/shared_ptr.hpp"
#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/cast.hpp"
#include "boost/scoped_array.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp" //no i/o just types

using namespace boost::posix_time;
using namespace std;

class row {
private:
	vector<string> tokens_;
	string str_;

public:
	row(const string& s) : str_(s) {
	}
	
	// http://www.digitalpeer.com/id/simple
	void tokenize(const string& delimiters  = ",") {
		// skip delimiters at beginning.
		string::size_type lastPos = str_.find_first_not_of(delimiters, 0);

		// find first "non-delimiter".
		string::size_type pos = str_.find_first_of(delimiters, lastPos);

		while (string::npos != pos || string::npos != lastPos)
		{
			// found a token, add it to the vector.
			tokens_.push_back(str_.substr(lastPos, pos - lastPos));

			// skip delimiters.  Note the "not_of"
			lastPos = str_.find_first_not_of(delimiters, pos);

			// find next "non-delimiter"
			pos = str_.find_first_of(delimiters, lastPos);
		}
	}

	const vector<string>& get_tokens() const {
		return tokens_;
	}

	~row() {}
};

class value_and_count_info {
	unsigned int value_;
	size_t bit_count_;
public:
	value_and_count_info(unsigned int v, size_t c) : value_(v), bit_count_(c) {
	}
	unsigned int get_value() const {
		return value_;
	}
	void set_value(unsigned int v) {
		value_ = v;
	}
	size_t get_bit_count() const {
		return bit_count_;
	}
};


class ticker_info {
	string ticker_;
	int count_;
	unsigned int code_;
	double price_;
	double max_variation_;
public:

	ticker_info(string s) : code_(0), ticker_(s), price_(0.0), count_(1), max_variation_(0) {}
	void increment() { count_++; }
	const int& get_count() const {
		return count_;
	}
	const double& get_price() const {
		return price_;
	}
	const string& get_ticker() const {
		return ticker_;
	}

	void set_price(const double& p) {
		if(price_ != 0.0) {
			double delta = (double)abs(price_ - p);
			if(delta > max_variation_)
				max_variation_ = delta;
		}
		
		price_ = p;
	}

	double& get_max_variation() {
		return max_variation_;
	}
	void set_max_variation(const double& v) {
		max_variation_ = v;
	}

	void set_ticker_code(unsigned int code) {
		code_ = code;
	}

	unsigned int get_ticker_code() const {
		return code_;
	}
};

class dictionary {
	map<string, boost::shared_ptr<ticker_info> > tickers_;
	map<char, unsigned int> exchanges_;
	map<char, unsigned int> sides_;
	map<char, unsigned int> conditions_;

	vector<string> tickers_lookup_table_;
	vector<char> exchanges_lookup_table_;
	vector<char> sides_lookup_table_;
	vector<char> conditions_lookup_table_;

	long max_time_delta_;
	long max_send_time_;

	size_t ticker_encode_bitcount_;
	size_t exchanges_encode_bitcount_;
	size_t sides_encode_bitcount_;
	size_t condition_encode_bitcount_;
	size_t send_time_bitcount_;
	size_t send_time_broken_down_bitcount_;
	size_t max_time_delta_bitcount_;
	size_t max_event_size_bitcount_;
	size_t max_event_size_;
	size_t total_bitcount_;

	size_t bitcount (size_t n) {
	   size_t count = 0;
	   while (n) {
		  count ++;
		  n >>= 1;
	   }
	   return count;
	}

	size_t bitcount (long n) {
	   size_t count = 0;
	   while (n) {
		  count ++;
		  n >>= 1;
	   }
	   return count;
	}

public:
	dictionary() : 	
	      ticker_encode_bitcount_(0),
		  exchanges_encode_bitcount_(0),
		  sides_encode_bitcount_(0),
		  condition_encode_bitcount_(0),
		  max_send_time_(0),
		  send_time_bitcount_(0),
		  send_time_broken_down_bitcount_(0),
		  max_time_delta_bitcount_(0),
		  max_time_delta_(0),
		  max_event_size_bitcount_(0),
		  max_event_size_(0),
		  total_bitcount_(0) {}

	void create_dictionary(const vector<boost::shared_ptr<row> >& rows) {
		// count the number of unique symbols
		vector<boost::shared_ptr<row> >::const_iterator cit;
		for(cit = rows.begin(); cit != rows.end(); ++cit) {
			if((*cit)->get_tokens().size() == 8) { 
				try {
					//
					// read / analyze tickers
					{
						const string& s = (*cit)->get_tokens().at(0);
						if(tickers_.find(s) != tickers_.end())
							tickers_[s]->increment();
						else {
							tickers_.insert(make_pair(s,boost::shared_ptr<ticker_info>(new ticker_info(s))));
						}
						// read and set the price; will update max_variation
						double p = boost::lexical_cast<double>((*cit)->get_tokens().at(6));
						tickers_[s]->set_price(p);
					}

					//
					// read / analyze exchange codes
					{
						const string& s = (*cit)->get_tokens().at(1);
						if(exchanges_.find(s.at(0)) == exchanges_.end()) {
							exchanges_.insert(make_pair(s.at(0), 0));

//						if(find(exchanges_.begin(), exchanges_.end(), s) == exchanges_.end()) {
//							exchanges_.push_back(s);
						}
					}

					//
					// read / analyze side codes
					{
						const string& s = (*cit)->get_tokens().at(2);
						if(sides_.find(s.at(0)) == sides_.end()) {
							sides_.insert(make_pair(s.at(0), 0));
						}

						//if(find(sides_.begin(), sides_.end(), s.at(0)) == sides_.end()) {
						//	if(s.size() == 1)
						//		sides_.push_back(s.at(0));
						//}
					}

					//
					// read / analyze condition codes
					{
						const string& s = (*cit)->get_tokens().at(3);
						if(conditions_.find(s.at(0)) == conditions_.end()) {
							conditions_.insert(make_pair(s.at(0), 0));
						}

						//if(find(conditions_.begin(), conditions_.end(), s.at(0)) == conditions_.end()) {
						//	if(s.size() == 1)
						//		conditions_.push_back(s.at(0));
						//}
					}

					//
					// read / analyze time delta
					{
						const string& s_sendtime = (*cit)->get_tokens().at(4);
						const string& s_recvtime = (*cit)->get_tokens().at(5);
						long stime = boost::lexical_cast<long>(s_sendtime);
						long rtime = boost::lexical_cast<long>(s_recvtime);
						long delay = rtime - stime;
						if(delay > max_time_delta_)
							max_time_delta_ = delay;
					}
				}
				catch(std::out_of_range& e) {
					cout << e.what() << endl;
				}
				catch(boost::bad_numeric_cast& e) {
					cout << e.what() << endl;
				}
			}
		}

		// now create a priority queue - not needed in this case
		// for the Huffman implementation it works but here
		// the goal is to determine the smallest amount of bytes on 
		// which we can represent the symbols;
		// assigning to the highest frequency symbol the lowest number
		// does not make a difference since it's still represented on the
		// same number of bytes
		
		//
		// determine the total bitcount

		ticker_encode_bitcount_ = bitcount(tickers_.size());
		exchanges_encode_bitcount_ = bitcount(exchanges_.size());
		sides_encode_bitcount_ = bitcount(sides_.size());
		condition_encode_bitcount_ = bitcount(conditions_.size());
		max_time_delta_bitcount_ = bitcount(max_time_delta_);

	}

	void create_dictionary(const string& filename) {
		std::ifstream infile;
		try
		{
			infile.open(filename.c_str(), std::ios::in);
			std::string s;
			while(infile >> s) {
				//rows.push_back(boost::shared_ptr<row> (new row(s)));
				row row_(s);
				row_.tokenize();

				if(row_.get_tokens().size() == 8) { 
					//
					// read / analyze tickers
					{
						const string& s = row_.get_tokens().at(0);
						if(tickers_.find(s) != tickers_.end())
							tickers_[s]->increment();
						else {
							tickers_.insert(make_pair(s,boost::shared_ptr<ticker_info>(new ticker_info(s))));
						}
						// read and set the price; will update max_variation
						double p = boost::lexical_cast<double>(row_.get_tokens().at(6));
						tickers_[s]->set_price(p);
					}

					//
					// read / analyze exchange codes
					{
						const string& s = row_.get_tokens().at(1);
						if(exchanges_.find(s.at(0)) == exchanges_.end()) {
							exchanges_.insert(make_pair(s.at(0), 0));

//						if(find(exchanges_.begin(), exchanges_.end(), s) == exchanges_.end()) {
//							exchanges_.push_back(s);
						}
					}

					//
					// read / analyze side codes
					{
						const string& s = row_.get_tokens().at(2);
						if(sides_.find(s.at(0)) == sides_.end()) {
							sides_.insert(make_pair(s.at(0), 0));

						//if(find(sides_.begin(), sides_.end(), s.at(0)) == sides_.end()) {
						//	if(s.size() == 1)
						//		sides_.push_back(s.at(0));
						}
					}

					//
					// read / analyze condition codes
					{
						const string& s = row_.get_tokens().at(3);
						if(conditions_.find(s.at(0)) == conditions_.end()) {
							conditions_.insert(make_pair(s.at(0), 0));
						}

						//if(find(conditions_.begin(), conditions_.end(), s.at(0)) == conditions_.end()) {
						//	if(s.size() == 1)
						//		conditions_.push_back(s.at(0));
						//}
					}

					//
					// read / analyze time delta
					{
						const string& s_sendtime = row_.get_tokens().at(4);
						const string& s_recvtime = row_.get_tokens().at(5);
						long stime = boost::lexical_cast<long>(s_sendtime);
						long rtime = boost::lexical_cast<long>(s_recvtime);
						if(stime > max_send_time_)
							max_send_time_ = stime;
						long delay = rtime - stime;
						if(delay > max_time_delta_)
							max_time_delta_ = delay;
					}

					//
					// read / analyze size of event
					{
						long event_size = boost::lexical_cast<long>(row_.get_tokens().at(7));
						if(event_size > max_event_size_)
							max_event_size_ = event_size;
					}

				}
			}
			infile.close();
		}
		catch(std::out_of_range& e) {
			cout << e.what() << endl;
		}
		catch(boost::bad_numeric_cast& e) {
			cout << e.what() << endl;
		}
		catch( std::ios_base::failure ex )	{
			std::cout << ex.what();
		}
		catch( std::runtime_error re )	{
			std::cout << re.what();
		}


		// now create a priority queue - not needed in this case
		// for the Huffman implementation it works but here
		// the goal is to determine the smallest amount of bytes on 
		// which we can represent the symbols;
		// assigning to the highest frequency symbol the lowest number
		// does not make a difference since it's still represented on the
		// same number of bytes

		//
		// determine the total bitcount

		// first, analyze the maximum value of send time, in milliseconds
		// break it up in h:m:s:ms - should take less for representation
		time_duration td = milliseconds(max_send_time_);

		long h = td.hours();
		long m = td.minutes();
		long s = td.seconds();
		long ms = td.fractional_seconds();

		time_duration td_ms_only(0,0,0,ms);
		ms = td_ms_only.total_milliseconds();


		ticker_encode_bitcount_ = bitcount(tickers_.size());
		total_bitcount_ += ticker_encode_bitcount_;

		exchanges_encode_bitcount_ = bitcount(exchanges_.size());
		total_bitcount_ += exchanges_encode_bitcount_;

		sides_encode_bitcount_ = bitcount(sides_.size());
		total_bitcount_ += sides_encode_bitcount_;

		condition_encode_bitcount_ = bitcount(conditions_.size());
		total_bitcount_ += condition_encode_bitcount_;

		send_time_bitcount_ = bitcount(max_send_time_);
		total_bitcount_ += send_time_bitcount_;

		send_time_broken_down_bitcount_ = bitcount(h) + bitcount(m) + bitcount(s) + bitcount(ms);
		// experimental calculation for comparison purposes; do not add send_time_broken_down_bitcount_ to grand total

		max_time_delta_bitcount_ = bitcount(max_time_delta_);
		total_bitcount_ += max_time_delta_bitcount_;

		/////
		/// encode / calculate length for price
		/// will be encoding it lexically since most prices take less than the 8 bytes taken by double
		/// so, price = "987.11" takes only 6 bytes 
		/////

		max_event_size_bitcount_ = bitcount(max_event_size_);
		total_bitcount_ += max_event_size_bitcount_;

		encode();

		create_records(filename);
	}


	void encode() {
		{
			// fly through the tickers and assign a unique code to each
			unsigned int c = 0;
			map<string, boost::shared_ptr<ticker_info> >::iterator it;
			for(it = tickers_.begin(); it != tickers_.end(); ++it) {
				it->second->set_ticker_code(c++);
			}
		}

		{
			// fly through the exchanges and assign a unique code to each
			unsigned int c = 0;
			map<char, unsigned int>::iterator it;
			for(it = exchanges_.begin(); it != exchanges_.end(); ++it) {
				it->second = c++;
			}
		}

		{
			// fly through the sides and assign a unique code to each
			unsigned int c = 0;
			map<char, unsigned int>::iterator it;
			for(it = sides_.begin(); it != sides_.end(); ++it) {
				it->second = c++;
			}
		}

		{
			// fly through the conditions and assign a unique code to each
			unsigned int c = 0;
			map<char, unsigned int>::iterator it;
			for(it = conditions_.begin(); it != conditions_.end(); ++it) {
				it->second = c++;
			}
		}

	}

	std::bitset<100> calculate_bitset( const std::vector<value_and_count_info>& vci, size_t total_bit_count) {

		std::bitset<100> record(0);
		size_t shift = total_bit_count;

		std::vector<value_and_count_info>::const_iterator it;
		for(it = vci.begin(); it != vci.end(); ++it) {
			{
				std::bitset<100> mask((*it).get_value());
				shift = shift - (*it).get_bit_count();
				mask <<= shift;
				record |= mask;
			}
		}
		return record;
	}


	// create compressed records based on statistical meta information
	void create_records(const string& filename) {
		// allocate bytes for encoded record
//		size_t bytes = total_bitcount_ % 8;
//		auto_ptr<unsigned char> b(new unsigned char[bytes]);
//		boost::scoped_array<unsigned char> b(new unsigned char[bytes]);


		std::ifstream infile;
		try
		{
			infile.open(filename.c_str(), std::ios::in);
			std::string s;
			while(infile >> s) {
				//rows.push_back(boost::shared_ptr<row> (new row(s)));
				row row_(s);
				row_.tokenize();

				if(row_.get_tokens().size() == 8) {

					std::vector<value_and_count_info> vci;

					{
						const string& s = row_.get_tokens().at(0);
						unsigned int ticker_code = tickers_[s]->get_ticker_code();
						vci.push_back(value_and_count_info(ticker_code, ticker_encode_bitcount_));
					}

					{
						const string& s = row_.get_tokens().at(1);
						unsigned int exchange_code = exchanges_[s.at(0)];
						vci.push_back(value_and_count_info(exchange_code, exchanges_encode_bitcount_));
					}

					{
						const string& s = row_.get_tokens().at(2);
						unsigned int sides_code = sides_[s.at(0)];
						vci.push_back(value_and_count_info(sides_code, sides_encode_bitcount_));
					}

					{
						const string& s = row_.get_tokens().at(3);
						unsigned int conditions_code = conditions_[s.at(0)];
						vci.push_back(value_and_count_info(conditions_code, condition_encode_bitcount_));
					}

					{
						const string& s_sendtime = row_.get_tokens().at(4);
						const string& s_recvtime = row_.get_tokens().at(5);
						long stime = boost::lexical_cast<long>(s_sendtime);
						long rtime = boost::lexical_cast<long>(s_recvtime);
						long delay = rtime - stime;
						vci.push_back(value_and_count_info(stime, send_time_bitcount_));
						vci.push_back(value_and_count_info(delay, max_time_delta_bitcount_));
					}

					////////////////
					// add PRICE to vci here or at the end of the overall record, as a whole number of bytes?
					////////////////

					{
						long event_size = boost::lexical_cast<long>(row_.get_tokens().at(7));
						vci.push_back(value_and_count_info(event_size, max_event_size_bitcount_));
					}

					bitset<100> record  = calculate_bitset(vci, total_bitcount_);

					// this is really not the place for it, but decode / decompress the bitset

					////////
					//// must build lookup maps with code info:
					/// ticker_code --> ticker_symbol
					/// exchaneg_code --> exchange_symbol
					/// and the others

					reset_value_count_info(vci); // reset the values in order to reconstruct
					decode_bitset(record, vci);
					string str = decompress(vci);

//					boost::scoped_array<unsigned char> mask(new unsigned char[bytes]);
//					unsigned char* p_mask = mask.get();
				}

			}
			infile.close();
		}
		catch(std::out_of_range& e) {
			cout << e.what() << endl;
		}
		catch(boost::bad_numeric_cast& e) {
			cout << e.what() << endl;
		}
		catch( std::ios_base::failure ex )	{
			std::cout << ex.what();
		}
		catch( std::runtime_error re )	{
			std::cout << re.what();
		}
	}


	// helper; just to show that we can reconstruct the values from the bitset based on bitcount info
	void reset_value_count_info(std::vector<value_and_count_info>& vci) {
		std::vector<value_and_count_info>::iterator it;

		for(it = vci.begin(); it != vci.end(); ++it) {
			(*it).set_value(0);
		}
	}


	void decode_bitset(const std::bitset<100>& record, std::vector<value_and_count_info>& vci) {

		size_t total_bit_count = 0;
		std::vector<value_and_count_info>::iterator it;

		for(it = vci.begin(); it != vci.end(); ++it) {
			total_bit_count += (*it).get_bit_count();
		}

		size_t shift = total_bit_count;
		for(it = vci.begin(); it != vci.end(); ++it) {
			shift = shift - (*it).get_bit_count();
			std::bitset<100> mask(0);
			for(size_t idx = 0; idx < (*it).get_bit_count(); ++idx)
				mask.set(idx);
			mask <<= shift;
			std::bitset<100> target(0);
			target = record & mask;
			target >>= shift;
			(*it).set_value(target.to_ulong());
		}
	}

	string decompress(std::vector<value_and_count_info>& vci) {
		// decompression is positional
		// we know how to interpret the value at a certain index
		string str;
		std::vector<value_and_count_info>::const_iterator cit;

		size_t idx = 0;
		for(cit = vci.begin(); cit != vci.end(); ++cit) {
			if(idx == 0) {
				unsigned int ticker_code = (*cit).get_value();
			}
			if(idx == 1) {
				unsigned int exchange_code = (*cit).get_value();
			}
			++idx;
		}

		return str;
	}


	void load_dictionary() {
		// load dictionary from file
		// temporary: create lookup tables based on existing information

	}


	void print_ticker_info(const boost::shared_ptr<ticker_info>& ti) const {
		cout << " ticker: " << ti->get_ticker() 
			<< " count: " << ti->get_count() 
			<< " max price delta: " << ti->get_max_variation() 
			<< endl;
	}

	void print_stats() {
		cout << "number of tickers = " << tickers_.size() << endl;
		cout << "number of exchanges = " << exchanges_.size() << endl;
		cout << "ticker_encode_bitcount_ = " << ticker_encode_bitcount_ << endl;
		cout << "exchanges_encode_bitcount_ = " << exchanges_encode_bitcount_ << endl;
		cout << "sides_encode_bitcount_ = " << sides_encode_bitcount_ << endl;
		cout << "condition_encode_bitcount_ = " << condition_encode_bitcount_ << endl;
		cout << "send_time_bitcount_ = " << send_time_bitcount_ << endl;
		cout << "send_time_broken_down_bitcount_ = " << send_time_broken_down_bitcount_ << endl;
		cout << "max_time_delta_ = " << max_time_delta_ << " ms" << endl;
		cout << "max_time_delta_bitcount_ = " << max_time_delta_bitcount_ << endl;
		cout << "max_event_size_ = " << max_event_size_ << endl;
		cout << "max_event_size_bitcount_ = " << max_event_size_bitcount_ << endl;
		cout << "total_bitcount_ = " << total_bitcount_ << endl;
		
		
		//map<string, boost::shared_ptr<ticker_info> >::const_iterator cit;
		//for(cit = tickers_.begin(); cit != tickers_.end(); ++cit)
		//	print_ticker_info((*cit).second);

		////for_each(tickers_.begin(), tickers_.end(), &dictionary::print_ticker_info);

	}
};



class deflater {
	dictionary dictio_;
	const string& filename_;

public:
	deflater(const string& fn) : filename_(fn) {}
	void deflate() {
		dictio_.create_dictionary(filename_);
		dictio_.print_stats();
	}

};

class inflater {
	dictionary dictio_;
	const string& input_file_name_;
	const string& output_file_name_;

public:
	inflater(const string& in, const string& out) :  input_file_name_(in), output_file_name_(out) {}
	void inflate() {
		dictio_.load_dictionary();
	}
};


class thread_pool {
	queue<boost::shared_ptr<row> > queue_;
public:
	thread_pool(const queue<boost::shared_ptr<row> >& q) : queue_(q) {
	}
};








int main(int argc, char** argv) {
	
	string filename;
	typedef vector<boost::shared_ptr<row> > container_type;
	typedef vector<boost::shared_ptr<row> >::iterator iterator_type;
	container_type rows;
	
	
	// read command line argument(s)
	if( argc <= 1 )
		std::cout << "Usage: " << argv[0] << "  <filename>" << std::endl;
	else
		filename = argv[1];

	if( !filename.empty() )
	{
		std::cout << filename << std::endl;

		//
		// deflate here...
		deflater deflater_(filename);
		deflater_.deflate();

		//
		// inflate here...
		string input_file_name = "input_file_name";
		string output_file_name = "output_file_name";
		inflater inflater_(input_file_name, output_file_name);
		inflater_.inflate();


		//std::ifstream infile;
		//try
		//{
		//	infile.open(filename.c_str(), std::ios::in);
		//	std::string s;
		//	while(infile >> s) {
		//		rows.push_back(boost::shared_ptr<row> (new row(s)));
		//		//vector<string> tokenized = tokenize(s, delimiter);
		//	}
		//	infile.close();
		//}
		//catch( std::ios_base::failure ex )	{
		//	std::cout << ex.what();
		//}
		//catch( std::runtime_error re )	{
		//	std::cout << re.what();
		//}
	}

	//iterator_type it;
	//for(it = rows.begin(); it != rows.end(); ++it)
	//	(*it)->tokenize();


//	for(it = rows.begin(); it != rows.end(); ++it)
//		delete (*it);


	//const string to_tokenize("IBM,10.44,B,O,112556, 112558, 45");
	//const string delimiter(",");
	//vector<string> tokenized = tokenize(to_tokenize, delimiter);
	//vector<string>::iterator it = tokenized.begin();
	//while(it != tokenized.end()) {
	//	cout << *it << endl;
	//	++it;
	//}

	return 0;
}
