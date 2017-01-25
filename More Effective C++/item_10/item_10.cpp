
//
// Item 10: Prevent memory leaks in constructors.
//
// It all adds up to this: if you replace pointer class members with their 
// corresponding auto_ptr objects, you fortify your constructors against 
// resource leaks in the presence of exceptions, you eliminate the need to 
// manually deallocate resources in destructors, and you allow const member 
// pointers to be handled in the same graceful fashion as non-const pointers. 
//
// Dealing with the possibility of exceptions during construction can be tricky, 
// but auto_ptr (and auto_ptr-like classes) can eliminate most of the drudgery. 
// Their use leaves behind code that's not only easy to understand, it's robust 
// in the face of exceptions, too. 
//

//
// does this syntax work? The book says clearly that exceptions thrown by the 
// initialization can not be caught! This shows otherwise:
//
//Initialization Lists and Exceptions
//Since constructors can throw exceptions, it's possible that you might want to be 
//able to handle exceptions that are thrown by constructors invoked as part of the 
//initialization list. 
//
//First, you should know that even if you catch the exception, it will get rethrown 
//because it cannot be guaranteed that your object is in a valid state because one 
//of its fields (or parts of its parent class) couldn't be initialized. That said, 
//one reason you'd want to catch an exception here is that there's some kind of 
//translation of error messages that needs to be done. 
//
//The syntax for catching an exception in an initialization list is somewhat awkward: 
//the 'try' goes right before the colon, and the catch goes after the body of the function: 
//
//class Foo
//{
//        Foo() try : _str( "text of string" ) 
//        { 
//        } 
//        catch ( ... ) 
//        { 
//                std::cerr << "Couldn't create _str";
//                // now, the exception is rethrown as if we'd written
//                // "throw;" here
//        }
//};
//


#include <iostream>
#include <string>
#include <list>

using namespace std;

class Image {                        // for image data
	string filename;
public:
	Image(const string& imageDataFileName) : filename(imageDataFileName) {
	}
  //...
};

class AudioClip {                    // for audio data
	string filename;
public:
	AudioClip(const string& audioDataFileName) : filename(audioDataFileName) {
	}
};

class PhoneNumber {					// for holding phone numbers
	//...
};


class BookEntry {                    // for each entry in the
public:                              // address book

  BookEntry(const string& name,
            const string& address = "",
            const string& imageFileName = "",
            const string& audioClipFileName = "");
  ~BookEntry();

  // phone numbers are added via this function
  void addPhoneNumber(const PhoneNumber& number);
  //...

private:
  string theName;                 // person's name
  string theAddress;              // their address
  list<PhoneNumber> thePhones;    // their phone numbers
  //Image *theImage;                // their image
  //AudioClip *theAudioClip;        // an audio clip from them
  const auto_ptr<Image> theImage;			// dynamically allocated pointers should be wrapped
  const auto_ptr<AudioClip> theAudioClip;	// in auto_ptr to avoid leaks if exception is thrown
											// in a constructor
};

BookEntry::BookEntry(const string& name,
                     const string& address,
                     const string& imageFileName,
                     const string& audioClipFileName)
					 try : theName(name), theAddress(address),
//  theImage(0), theAudioClip(0)
theImage(imageFileName != "" ? new Image(imageFileName) : 0),
theAudioClip(audioClipFileName != "" ? new AudioClip(audioClipFileName) : 0)

{
	//
	// initialize dynamically allocated objects
	// also in the member initialization list

	//if (imageFileName != "") {
	//  theImage = new Image(imageFileName);
	//}

	//if (audioClipFileName != "") {
	//  theAudioClip = new AudioClip(audioClipFileName);
	//}
}
catch(...)
{
	//
	// not much to do here now, all resources should be deallocated
	// properly since all ptrs are now auto_ptr
	// but here is a good place to log or notify something of the ex.
}

BookEntry::~BookEntry()
{
	//
	// nothing to do since the dynamically allocated objects
	// are now managed by auto_ptr
	
	//delete theImage;
	//delete theAudioClip;
}

int main(int argc, char** argv) {

	BookEntry be("The Simpsons", 
		"742 Evergreen Terrace", 
		"Homer_mugshot.jpg", 
		"Homer_says_Boring.mp3");

	return 0;

}