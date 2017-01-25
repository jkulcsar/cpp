

//
//	Functions defining meanings for the following operators (§6.2) can be declared:
//	+	-	*	/	%	^	&
//	|	~	!	=	<	>	+=
//	=	*=	/=	%=	^=	&=	|=
//	<<	>>	>>=	<<=	==	!=	<=
//	>=	&&	||	++	>*	,	
//	->	[]	()	new	new[]	delete	delete[]
//
//	The following operators CANNOT be defined by a user:
//	:: (scope resolution; §4.9.4, §10.2.4),
//	. (member selection; §5.7), and
//	.* (member selection through pointer to function; §15.5).
//


enum Day { sun, mon, tue, wed, thu, fri, sat };

Day& operator++(Day& d)
{
	return d = (sat == d) ? sun : Day(1+d);
}



int main(int argc, char ** argv)
{
	Day today = fri;
	today++;


	return 0;
}
