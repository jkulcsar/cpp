
#ifndef _IDENTIF_H
#define _IDENTIF_H
#include<iostream>
#include<string>
#include <cctype>

class Identifier {
public:
	const std::string& toString() const
	{
		return _theIdentifier;
	}

	//friend std::istream& operator>>(std::istream&, Identifier&);
	std::istream& read( std::istream& is )
	{
		std::istream::sentry s(is);
		if( !s )
			return is;
		std::string IDString;
		// find beginning of word
		char c = '\0';
		while( is && !('_' == c))
			is.get(c);
		IDString += c;

		// collect the rest
		while( is && (isalnum(c) || '_' == c))
		{
			is.get(c);
			if( isalnum(c) || '_' == c)
				IDString += c;
		}
		// The last character read does not belong to the identifier. The iostream library offers
		// the possibility of returning an unused character to the input so that it is available
		// to a subsequent program.
		is.putback(c); // back into the input stream

		_theIdentifier = IDString;
		return is;
	}

	// the "output" function must ALWAYS be const 
	std::ostream& write( std::ostream& os ) const
	{
		std::ostream::sentry s(os);
		if(s)
			os << _theIdentifier;
		return os;
	}

private:
	std::string _theIdentifier;
};

std::istream& operator>>(std::istream& is, Identifier& identif)
{
	return identif.read(is);
}

// the output operator must ALWAYS take a const ref !
std::ostream& operator<<( std::ostream& os, const Identifier& identif)
{
	return identif.write(os);
}

#endif
