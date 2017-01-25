
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>
#include <exception>

#include "boost/shared_ptr.hpp"
#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/cast.hpp"

using namespace std;

class row {
private:
	vector<string> tokens_;
	string str_;

	void analyze();
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
};

class ticker_info {
	string ticker_;
	int count_;
	double price_;
	double max_variation_;
public:

	ticker_info(string s) : ticker_(s), price_(0.0), count_(1), max_variation_(0) {}
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
};

class dictionary {
	map<string, boost::shared_ptr<ticker_info> > tickers_;
	vector<string> exchanges_;
	vector<char> sides_;
	vector<char> conditions_;

	long max_time_delta_;

	size_t ticker_encode_bitcount_;
	size_t exchanges_encode_bitcount_;
	size_t sides_encode_bitcount_;
	size_t condition_encode_bitcount_;
	size_t max_time_delta_bitcount_;

	size_t bitcount (size_t n) {
	   size_t count = 0;
	   while (n) {
		  count += n & 0x1u;
		  n >>= 1;
	   }
	   return count;
	}

	size_t bitcount (long n) {
	   size_t count = 0;
	   while (n) {
		  count += n & 0x1l;
		  n >>= 1;
	   }
	   return count;
	}

public:
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
						if(find(exchanges_.begin(), exchanges_.end(), s) == exchanges_.end()) {
							exchanges_.push_back(s);
						}
					}

					//
					// read / analyze side codes
					{
						const string& s = (*cit)->get_tokens().at(2);
						if(find(sides_.begin(), sides_.end(), s.at(0)) == sides_.end()) {
							if(s.size() == 1)
								sides_.push_back(s.at(0));
						}
					}

					//
					// read / analyze condition codes
					{
						const string& s = (*cit)->get_tokens().at(3);
						if(find(conditions_.begin(), conditions_.end(), s.at(0)) == conditions_.end()) {
							if(s.size() == 1)
								conditions_.push_back(s.at(0));
						}
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


	void load_dictionary() {
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
		cout << "max_time_delta_ = " << max_time_delta_ << " ms" << endl;
		cout << "max_time_delta_bitcount_ = " << max_time_delta_bitcount_ << endl;
		
		//map<string, boost::shared_ptr<ticker_info> >::const_iterator cit;
		//for(cit = tickers_.begin(); cit != tickers_.end(); ++cit)
		//	print_ticker_info((*cit).second);
		////for_each(tickers_.begin(), tickers_.end(), &dictionary::print_ticker_info);

	}
};

class deflater {
	dictionary dictio_;
	const vector<boost::shared_ptr<row> >& rows_;

public:
	deflater(const vector<boost::shared_ptr<row> >& r) : rows_(r) {}
	void deflate() {
		dictio_.create_dictionary(rows_);
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

		std::ifstream infile;
		try
		{
			infile.open(filename.c_str(), std::ios::in);
			std::string s;
			while(infile >> s) {
				rows.push_back(boost::shared_ptr<row> (new row(s)));
				//vector<string> tokenized = tokenize(s, delimiter);
			}
			infile.close();
		}
		catch( std::ios_base::failure ex )	{
			std::cout << ex.what();
		}
		catch( std::runtime_error re )	{
			std::cout << re.what();
		}
	}

	iterator_type it;
	for(it = rows.begin(); it != rows.end(); ++it)
		(*it)->tokenize();

	//
	// deflate here...
	deflater deflater_(rows);
	deflater_.deflate();

	//
	// inflate here...
	string input_file_name = "input_file_name";
	string output_file_name = "output_file_name";
	inflater inflater_(input_file_name, output_file_name);
	inflater_.inflate();

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
