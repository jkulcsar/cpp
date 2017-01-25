
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/operations.hpp> // get, EOF, WOULD_BLOCK

#include <boost/lexical_cast.hpp>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>    
//#include <boost/thread/lock_types.hpp>

namespace io = boost::iostreams;



//
// the compression thread has to wait until the decompressor thread is done.
// here: wait for a condition variable set by the decompressor thread
// for this algorithm (here: gzip)

void test_gzip_compression(
	boost::condition_variable& condition_go_gzip_compr, 
	boost::mutex& gzip_compr_mutex) {

	boost::unique_lock<boost::mutex> lock(gzip_compr_mutex);
	condition_go_gzip_compr.wait(lock);

	try {


		std::ofstream out_gzip_file(".//data//compressed.gz", std::ios_base::out | std::ios_base::binary | std::ios_base::app);

		io::filtering_ostream out_gzip;
		out_gzip.push(io::gzip_compressor());
		out_gzip.push(out_gzip_file);

		std::string filename(".//data//decompressed_gzip");
		std::ifstream input_text_file;
		input_text_file.open(filename.c_str(), std::ios::in | std::ios::binary);
		std::string s;
		while(input_text_file >> s) {
			// write to the compressed streams (here: file(s))
			out_gzip << s;
		}
		input_text_file.close();
	}
	catch( std::ios_base::failure ex )	{
		std::cout << ex.what();
	}
	catch( std::runtime_error re )	{
		std::cout << re.what();
	}
}


void test_gzip_decompression(
	boost::condition_variable& condition_go_gzip_compr, 
	boost::mutex& gzip_compr_mutex) {

	try {

		std::ifstream in_gzip_file(".//data//C.txt.gz", std::ios_base::in | std::ios_base::binary);
		std::ofstream out_decompressed_gzip_file( ".//data//decompressed_gzip", std::ios_base::out | std::ios_base::binary);
		

		//
		// setup a gzip decompressor stream
		// and copy the output of this stream it into a file
		io::filtering_streambuf<io::input> in_gzip;
		in_gzip.push(io::gzip_decompressor());
		in_gzip.push(in_gzip_file);
		io::copy(in_gzip, out_decompressed_gzip_file);


		//////int c;
		//////std::string line;
		//////while( (c = io::get(in_gzip)) != EOF) {
		//////	line += c;
		//////	
		//////	if( c == '\n' ) {
		//////		out_decompressed_gzip_file << line;
		//////		line.clear();
		//////	}
		//////}

		//FILE* testFd = fopen(".//data//C.gz", "r");
		//if(testFd != NULL) {
		//	std::cout << "success opening gzip file for read while opened by gzip filter stream" << std::endl;
		//	fclose(testFd);
		//}
		//else
		//	std::cout << "failed opening gzip file for read while opened by gzip filter stream" << std::endl;
	}
	
	catch( std::ios_base::failure ex )	{
		std::cout << ex.what();
	}
	catch( std::runtime_error re )	{
		std::cout << re.what();
	}

	//
	// done with decompression;
	// signal it by notifying all threads that want to start compressing
	boost::lock_guard<boost::mutex> lock(gzip_compr_mutex);
	condition_go_gzip_compr.notify_all();
}

void test_bzip2_decompression(
	boost::condition_variable& condition_go_bzip2_compr, 
	boost::mutex& bzip2_compr_mutex) {

	try {
		std::ifstream in_bzip2_file(".//data//C.txt.bz2", std::ios_base::in | std::ios_base::binary);
		std::ofstream out_decompressed_bzip2_file( ".//data//decompressed_bzip2", std::ios_base::out | std::ios_base::binary);

		//
		// setup a bzip2 decompressor stream
		// and copy the output of this stream it into a file
		io::filtering_streambuf<io::input> in_bzip2;
		in_bzip2.push(io::bzip2_decompressor());
		in_bzip2.push(in_bzip2_file);
		io::copy(in_bzip2, out_decompressed_bzip2_file);

	}
	catch( std::ios_base::failure ex )	{
		std::cout << ex.what();
	}
	catch( std::runtime_error re )	{
		std::cout << re.what();
	}

	//
	// done with decompression;
	// signal it by notifying all threads that want to start compressing
	boost::lock_guard<boost::mutex> lock(bzip2_compr_mutex);
	condition_go_bzip2_compr.notify_all();
}

//
// the compression thread has to wait until the decompressor thread is done.
// here: wait for a condition variable set by the decompressor thread
// for this algorithm (here: bzip2)


void test_bzip2_compression(
	boost::condition_variable& condition_go_bzip2_compr, 
	boost::mutex& bzip2_compr_mutex) {

	boost::unique_lock<boost::mutex> lock(bzip2_compr_mutex);
	condition_go_bzip2_compr.wait(lock);

	try {

		std::ofstream out_bzip2_file(".//data//compressed.bz2", std::ios_base::out | std::ios_base::binary | std::ios_base::app);

		io::filtering_ostream out_bzip2;
		out_bzip2.push(io::bzip2_compressor());
		out_bzip2.push(out_bzip2_file);

		std::string filename(".//data//decompressed_bzip2");
		std::ifstream input_text_file;
		input_text_file.open(filename.c_str(), std::ios::in | std::ios::binary);
		std::string s;
		while(input_text_file >> s) {
			// write to the compressed streams (here: file(s))
			out_bzip2 << s;
		}
		input_text_file.close();
	}
	catch( std::ios_base::failure ex )	{
		std::cout << ex.what();
	}
	catch( std::runtime_error re )	{
		std::cout << re.what();
	}
}



int main(int argc, char** argv) {
	try {

		boost::mutex gzip_compr_mutex_;
		boost::mutex bzip2_compr_mutex_;
		boost::condition_variable condition_go_gzip_compr_;
		boost::condition_variable condition_go_bzip2_compr_;

		int thread_num = 64;
		if(argc > 1)
			thread_num=boost::lexical_cast<int>(argv[1]);

		boost::thread_group thr_grp;

		boost::thread* gzip_decompr_thread = new boost::thread(
			&test_gzip_decompression,
			boost::ref<boost::condition_variable>(condition_go_gzip_compr_),
			boost::ref<boost::mutex>(gzip_compr_mutex_) );

		boost::thread* bzip2_decompr_thread = new boost::thread(
			&test_bzip2_decompression,
			boost::ref<boost::condition_variable>(condition_go_bzip2_compr_),
			boost::ref<boost::mutex>(bzip2_compr_mutex_) );


		boost::thread* gzip_compr_thread = new boost::thread(
			&test_gzip_compression,
			boost::ref<boost::condition_variable>(condition_go_gzip_compr_),
			boost::ref<boost::mutex>(gzip_compr_mutex_) );

		boost::thread* bzip2_compr_thread = new boost::thread(
			&test_bzip2_compression,
			boost::ref<boost::condition_variable>(condition_go_bzip2_compr_),
			boost::ref<boost::mutex>(bzip2_compr_mutex_) );

		thr_grp.add_thread( gzip_decompr_thread );
		thr_grp.add_thread( bzip2_decompr_thread );

		thr_grp.add_thread( gzip_compr_thread );
		thr_grp.add_thread( bzip2_compr_thread );
		
		thr_grp.join_all();

	}
	catch( std::exception& e ) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
