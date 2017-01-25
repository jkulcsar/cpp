
/*
    ASSUMPTIONS:
        All characters are case insensitive
    ENHANCEMENTS:
        Auto correction of word
        Display all words in postorder
 
    SAMPLE DATA: - ALGO, ALL, ALSO, ASSOC, TREE, TRIE
 
                                +--> [G] ---+--> [O]
                                |
                    +--> [L] ---+--> [L]
                    |           |
        +--> [A] ---+           +--> [S] ---+--> [O]
        |           |
        |           +--> [S] ---+--> [S] ---+--> [O] ---+--> [C]
[\0] ---+
        |                       +--> [E] ---+--> [E]
        |                       |
        +--> [T] ---+--> [R] ---+
                                |
                                +--> [I] ---+--> [E]
 
*/

#include "trie.hpp"

int main( int argc, char** argv )
{
    trie mytrie;
    char *s[] = {"tree","trie","algo","assoc","all","also","ass"};
    for(int i=0;i<sizeof(s)/sizeof(*s);i++)
    {
        mytrie.insert_word(s[i]);
    }
 
    mytrie.display();
 
    if(mytrie.search_word("all") == true) cout << "all exist" << endl;
    else cout << "all do not exist" << endl;
 
    mytrie.delete_word("all");
 
    if(mytrie.search_word("all") == true) cout << "all exist" << endl;
    else cout << "all do not exist" << endl;
 
    mytrie.display();

	return 0;
}
