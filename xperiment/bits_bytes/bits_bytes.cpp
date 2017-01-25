
#include <bitset>
#include <iostream>
#include <fstream>
#include <vector>

#include "boost/cast.hpp"

size_t bitcount (long n) {
	   size_t count = 0;
	   while (n) {
		  //count += n & 0x1;
		   count++;
		  n >>= 1;
	   }
	   return count;
	}

class value_and_count_info {
	unsigned int value_;
	size_t bit_count_;
public:
	value_and_count_info(unsigned int v, size_t c) : value_(v), bit_count_(c) {
	}
	unsigned int get_value() const {
		return value_;
	}
	size_t get_bit_count() const {
		return bit_count_;
	}
	void set_value(unsigned int v) {
		value_ = v;
	}
};

std::bitset<10> calculate_bitset( const std::vector<value_and_count_info>& vci, size_t total_bit_count) {

	std::bitset<10> record(0);
	size_t shift = total_bit_count;

	std::vector<value_and_count_info>::const_iterator it;
	for(it = vci.begin(); it != vci.end(); ++it) {
		{
			std::bitset<10> mask((*it).get_value());
			shift = shift - (*it).get_bit_count();
			mask <<= shift;
			record |= mask;
		}
	}
	return record;

}

void decode_bitset(const std::bitset<10>& record, const std::vector<size_t>& bit_counts) {

	size_t total_bit_count = 0;
	std::vector<size_t>::const_iterator it;
	for(it = bit_counts.begin(); it != bit_counts.end(); ++it) {
		total_bit_count += *it;
	}

	size_t shift = total_bit_count;
	for(it = bit_counts.begin(); it != bit_counts.end(); ++it) {
		shift = shift - (*it);
		std::bitset<10> mask(0);
		for(size_t idx = 0; idx < (*it); ++idx)
			mask.set(idx);
		mask <<= shift;
		std::bitset<10> target(0);
		target = record & mask;
		target >>= shift;
		unsigned int value = target.to_ulong();
		std::cout << "value: " << value << std::endl;
	}
}

void decode_bitset(const std::bitset<10>& record, std::vector<value_and_count_info>& vci) {

	size_t total_bit_count = 0;
	std::vector<value_and_count_info>::iterator it;

	for(it = vci.begin(); it != vci.end(); ++it) {
		total_bit_count += (*it).get_bit_count();
	}

	size_t shift = total_bit_count;
	for(it = vci.begin(); it != vci.end(); ++it) {
		shift = shift - (*it).get_bit_count();
		std::bitset<10> mask(0);
		for(size_t idx = 0; idx < (*it).get_bit_count(); ++idx)
			mask.set(idx);
		mask <<= shift;
		std::bitset<10> target(0);
		target = record & mask;
		target >>= shift;
		(*it).set_value(target.to_ulong());

	}
}

void reset_value_count_info(std::vector<value_and_count_info>& vci) {
	std::vector<value_and_count_info>::iterator it;

	for(it = vci.begin(); it != vci.end(); ++it) {
		(*it).set_value(0);
	}
}

void show_value_count_info(std::vector<value_and_count_info>& vci) {
	std::vector<value_and_count_info>::iterator it;

	for(it = vci.begin(); it != vci.end(); ++it) {
		std::cout << "value: " << (*it).get_value() << std::endl;
	}
}

void write_to_compressed_file(std::ostream& outfile_binary, const std::bitset<30>& record) {
	std::bitset<30> mask(0xFF);
	std::bitset<30> rec = record;
//	size_t total = total_bitcount_;
	size_t total = 30;

	std::cout << "writing: " << std::endl << record.to_string() << std::endl << std::endl;

	int i = total % 8;
	while(total > i) {
		std::bitset<30> result = rec & mask;
		unsigned long ulong = result.to_ulong();
		unsigned char byte = ulong;
		rec >>= 8;
		total -= 8;
		outfile_binary << byte;

		//try {
		//	short byte = boost::numeric_cast<short>(ulong);
		//	rec >>= 8;
		//	total -= 8;
		//	outfile_binary.write((&byte,1);
		//}
		//catch(boost::bad_numeric_cast& e) {
		//	std::cout << e.what() << std::endl;
		//}
	}

	// there are remainder bits in rec
	if(i) {
		unsigned char byte = (unsigned char) rec.to_ulong();
		outfile_binary << byte;
	}
}

bool read_from_compressed_file(std::istream& infile_binary, std::bitset<30>& record) {
//	std::bitset<30> mask(0xFF);
//	std::bitset<30> rec = record;
//	size_t total = total_bitcount_;
	while(!infile_binary.eof()) {

		size_t total = 30;

		// make sure we reset the output (target) bitset
		record.reset();

		int i = total % 8;
		size_t complete_bytes = total / 8;
		if(i != 0)
			complete_bytes++;

		//char* bytes = new char[complete_bytes];
		//infile_binary.read(bytes, complete_bytes);

		for(unsigned int idx = 0; idx < complete_bytes; idx++) {
			unsigned char byte;
			infile_binary >> byte;
			//char byte = bytes[idx];
			std::bitset<30> mask(byte);
			mask <<= 8 * idx;
			record |= mask;
		}

		return true;
	}
	return false;


	//if(bytes)
	//	delete[] bytes;

	//while(total > i) {
	//	std::bitset<30> result = rec & mask;
	//	char byte = result.to_ulong();
	//	rec >>= 8;
	//	total -= 8;
	//	outfile_binary << byte;
	//}

	// there are remainder bits in rec
	//if(i) {
	//	char byte = rec.to_ulong();
	//	outfile_binary << byte;
	//}
}

int main(int argc, char** argv) {
	size_t number = 838;

	int counter = 0;
	do {
		number = number ^ 0;
		if(number != 0) {
			counter++;
			number = number >> 8;
		}
	}
	while(number);

	number = 838;
	counter = 0;
	while(number ^ 0) {
		counter++;
		number >>= 8;
	}

	long event_size = 10312;
	size_t event_size_bitcount = bitcount(event_size);

	std::vector<value_and_count_info> vci;


	size_t total_bit_count = 10;
	size_t bit_count_1 = 3;
	size_t bit_count_2 = 4;
	size_t bit_count_3 = 3;

	size_t shift = total_bit_count;

	value_and_count_info vci1(2, bit_count_1);
	value_and_count_info vci2(4, bit_count_2);
	value_and_count_info vci3(5, bit_count_3);
	vci.push_back(vci1);
	vci.push_back(vci2);
	vci.push_back(vci3);
	
	std::bitset<10> record(0);
	
	{
		std::bitset<10> mask(2);
		shift = shift - bit_count_1;
		mask <<= shift;
		record |= mask;
	}
	
	{
		std::bitset<10> mask(4);
		shift = shift - bit_count_2;
		mask <<= shift;
		record |= mask;
	}

	{
		std::bitset<10> mask(5);
		shift = shift - bit_count_3;
		mask <<= shift;
		record |= mask;
	}

	std::bitset<10> another_record = calculate_bitset(vci, total_bit_count);

//	std::cout << mask << std::endl;
	std::cout << record << std::endl;
	std::cout << another_record << std::endl;
	std::cout << std::hex << another_record.to_ulong() << std::endl;

	// now try to decode the record just created based on the meta-info only;
	// only has bitcount info!

	std::vector<size_t> bit_counts_;
	bit_counts_.push_back(bit_count_1);
	bit_counts_.push_back(bit_count_2);
	bit_counts_.push_back(bit_count_3);


	decode_bitset(another_record, bit_counts_);

	show_value_count_info(vci);
	reset_value_count_info(vci);
	show_value_count_info(vci);
	decode_bitset(another_record, vci);
	show_value_count_info(vci);



	std::ifstream infile;
	std::ofstream outfile;
	

	// 27 bits held in a bitset<30>
	// in binary: 110000111000100000101001111
	std::bitset<30> bigger_bitset(102515023);

	std::bitset<30> incoming_record;
	incoming_record.reset();

	outfile.open("file", std::ios::out, std::ios::binary);
	write_to_compressed_file(outfile, bigger_bitset);
	outfile.close();

	infile.open("file", std::ios::in, std::ios::binary);
	while(read_from_compressed_file(infile, incoming_record))
		std::cout << "read back: " <<std::endl << incoming_record.to_string() << std::endl << std::endl;
	infile.close();


	return 0;
}