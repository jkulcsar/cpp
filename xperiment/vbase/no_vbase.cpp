class Storable {
public:
	Storable( const string s) : store( s ) { 
		string message( "Storable::Storable(const string)" );
		message += s;
		cout << message << endl;
	};

	virtual void read() = 0;
	virtual void write() = 0;
	virtual ~Storable()	{
		string message( "Storable::~Storable()" );
		cout << message << endl;
	};
private:
	const string	store;

	Storable( const Storable& );
	Storable& operator=( const Storable& );
};

class Transmitter : public Storable {
public:
	Transmitter( const string filename ) : Storable( filename ) { };
	void read()	{
		string	message( "Transmitter::read()" );
		cout << message << endl;
	};
	void write()	{
		string message( "Transmitter::write()" );
		cout << message << endl;
	};
};

class Receiver : public Storable {
public:
	Receiver( const string filename ) : Storable( filename ) { };
	void read()	{
		string	message( "Receiver::read()" );
		cout << message << endl;
	};
	void write()	{
		string message( "Receiver::write()" );
		cout << message << endl;
	};
};

class Radio : public Transmitter, public Receiver {
public:
	Radio( const string filename ) : Transmitter( filename ), Receiver( filename ) { };
	void read()	{
		Transmitter::read();
		Receiver::read();
		string	message( "Radio::read()" );
		cout << message << endl;
	};
	void write()	{
		Transmitter::write();
		Receiver::write();
		string message( "Radio::write()" );
		cout << message << endl;
	};
};
