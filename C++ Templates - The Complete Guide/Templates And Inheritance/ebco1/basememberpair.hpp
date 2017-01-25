#ifndef BASE_MEMBER_PAIR_HPP 
#define BASE_MEMBER_PAIR_HPP 

template <typename Base, typename Member> 
class BaseMemberPair : private Base { 
  private: 
    Member member; 
  public: 
    // constructor 
    BaseMemberPair (Base const & b, Member const & m) 
     : Base(b), member(m) { 
    } 

    // access base class data via first() 
    Base const& first() const { 
        return (Base const&)*this; 
    } 
    Base& first() { 
        return (Base&)*this; 
    } 

    // access member data via second() 
    Member const& second() const { 
        return this->member; 
    } 
    Member& second() { 
        return this->member; 
    } 
}; 

#endif // BASE_MEMBER_PAIR_HPP 