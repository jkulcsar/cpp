#ifndef CONTAINER_UTILITY_HPP
#define CONTAINER_UTILITY_HPP

template< typename Container >
void show( const Container& cont, const char* separator = "|", std::ostream& s = std::cout )
{
	s << cont.size() << std::endl;

	typename Container::const_iterator cit;
	cit = cont.begin();
	while( cit != cont.end() )
		s << *cit++ << separator;
	s << std::endl;
}

#endif
