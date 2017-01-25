/*
    UnJumble, a brute-force anagram solver.
    Copyright (C) 2001 A.Sankaranarayanan.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software Foundation,
    Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

    Last modified 16/06/2001 09:12 pm

    UnJumble is a brute-force anagram solver. It takes a (presumably)
    jumbled word as its input and compares various permutations against
    a pre-stored word base (UNJUMBLE.DAT).

    The word base is a simple text file containing one word per line.
    You can easily edit the word base using any text editor. The word
    base should be in alphabetical (sorted) order and in lowercase, or
    UnJumble will not work correctly. You can use the SORT filter
    available in the OS to sort the word base. You may enter words in
    the word base in any order and follow it up with the command

      type unjumble.dat | sort > unjumble.dat (MS-DOS)
      cat unjumble.dat | sort > unjumble.dat  (UNIX & variants)

    The capacity of the word base is 2 billion and odd words (or
    whatever is the limit imposed by long integers on your system).
    The length of any single word is limited to 255 characters, far
    more than you'd ever need (considering it would probably
    take a few years to unjumble anything that long).

    Unjumble assumes that enough memory is available to it for the
    operation and does not perform any run-time checks in this
    regard -- it could malfunction if sufficient memory is not
    available to it.

    UnJumble is highly CPU intensive and may take a very long time
    to unscramble longer words -- so if it appears inert for long
    periods of time, don't reach out for Ctrl+Alt+Del, it probably
    hasn't hung (yet!). I found a lot of difference, though, in the
    performance of the program when compiled by different compilers.
    The GCC compiled version was almost 40-50% faster than the one
    compiled with BCC32.

    UnJumble is highly portable and will compile on most platforms
    without modifications (perhaps the #include <alloc.h> will have
    to be changed to #include <malloc.h> on UNIX platforms).

    Please make sure you include the word base UNJUMBLE.DAT when you
    distribute UnJumble.

    Do take the time to tell me how you like UnJumble. I know there
    is room for a lot of improvement (speed and otherwise), so if you
    improve it anyway, please send me a copy of the modified program.

    My e-mail address is: total_nerd@hotmail.com
*/

#include <stdio.h>                        /* general I/O */
#include <string.h>                       /* strcmp () */
#include <ctype.h>                        /* tolower () */
#include <malloc.h>                       /* malloc () & free () */
#include <stdlib.h>                       /* exit () */
#include <time.h>                         /* time () */

#define TRUE  0xff                        /* int'ized booleans */
#define FALSE 0x00

#define NORMAL_SHUTDOWN   0x0000          /* a few exit codes */
#define TOO_FEW_ARGUMENTS 0x0001          /* can be checked using */
#define INVALID_WORDBASE  0x0002          /* DOS ERRORLEVEL */
#define WORD_TOO_LONG     0x0003

#define MAX_WORD_LEN 255                  /* maximum word length */
#define WORDBASE_NAME "unjumble.dat"      /* modify with impunity! */

typedef unsigned char flag;               /* call unsigned char a flag */

typedef struct LetterTag {                /* letter node contains */
    char LetterData;                      /* character stored */
    flag Visited;                         /* visited/not visited flag */
    struct LetterTag **Link;              /* links to other nodes */
} Letter;

FILE *WordBase;                           /* pointer to word base stream */

/*----------------------------------------------------------------------------
 WordBaseLookup () takes a string as parameter and searches the file spec by
 the WordBase pointer. If the string is found in the file, the index position
 is returned, otherwise -1 is returned.
----------------------------------------------------------------------------*/
long WordBaseLookup (char *Word) {
    int Result = 1;                       /* result of string comp. */
    long Index = 0;                       /* index of word in file */
    char TempWord[MAX_WORD_LEN + 1];      /* temporary read buffer */

    rewind (WordBase);                    /* start at beginning of file */
                                          /* search till EOF/found/past */
    while ((fscanf (WordBase, "%s", TempWord) != EOF) && (Result > 0)) {
        Result = strcmp (Word, TempWord);
        ++Index;
    }

    return ((Result == 0) ? Index:-1);    /* if found, return Index */
}

/*----------------------------------------------------------------------------
 ProcessWord () takes a word as input and - you guessed it - processes it.
 It looks up in the word in the word base and prints it out. ProcessWord ()
 uses static local buffers to keep track of the words already found, so to
 deallocate these buffers, Word can be set to NULL. ProcessWord () normally
 returns 0, but if Word is NULL, it returns MatchCount.
----------------------------------------------------------------------------*/
int ProcessWord (char *Word) {
    static int MatchCount = 0;            /* to keep track of matches */
    static char **MatchList = NULL;       /* so as to avoid duplicates */
    long Result;                          /* result of word base lookup */
    int i;

    if (Word == NULL) {                   /* is it termination time? */
        if (MatchList != NULL) {
            for (i = 0; i < MatchCount; ++i) {
                free (MatchList[i]);      /* yes, deallocate everything */
            }
            free (MatchList);
        }
        return (MatchCount);              /* return no. of matches */
    }

    for (i = 0; i < MatchCount; ++i) {    /* search match list */
        if (strcmp (Word, MatchList[i]) == 0) {   /* if already generated */
            return (0);                   /* scram! */
        }
    }

    Result = WordBaseLookup (Word);       /* look it up */

    if (Result >= 0) {                    /* eureka! */
                                          /* add to match list */
        MatchList = (char **) realloc ((void *) MatchList,
                                 (MatchCount + 1) * sizeof (char *));
        MatchList[MatchCount] = (char *) malloc (strlen (Word) + 1);
        strcpy (MatchList[MatchCount++], Word);
        printf ("%010ld: %s\n", Result, Word);
    }

    return (0);                           /* dummy ignored by caller */
}

/*----------------------------------------------------------------------------
 RideLetterList () is a recursive function that scans the interconnected
 Letter nodes, taking a different path each time to come up with a new
 permutation. When one permutation is found, it calls a function to process
 the word.
----------------------------------------------------------------------------*/
void RideLetterList (Letter *LP, char *Ans, int Pos, int WdLen) {
    int i, j;

    Ans[Pos] = LP->LetterData;            /* store char. at current posn. */
    LP->Visited = TRUE;                   /* mark current node */

    for (i = j = 0; i < (WdLen - 1); ++i) {    /* for all links in node */
        if (LP->Link[i]->Visited == FALSE) {   /* if link not visited */
            RideLetterList (LP->Link[i],
                    Ans, Pos + 1, WdLen);      /* ride new link */
        }
        else {
            ++j;                          /* j holds no. of visited links */
        }
    }

    if (j == i) {                         /* if all links visited */
        ProcessWord (Ans);                /* process the word */
    }

    LP->Visited = FALSE;                  /* clear mark when we retrace */
}

/*----------------------------------------------------------------------------
 main () sets up the buffers, gets the word from the command line and calls
 the RideLetterList () function for each of the Letter nodes to generate all
 permutations of characters in the word.
----------------------------------------------------------------------------*/
int main (int argc, char *argv[]) {
    Letter *LetterList;                   /* pointer to first node */
    char Solution[MAX_WORD_LEN + 1];      /* holds permutations */
    int WordLength;                       /* length of user-spec word */
    int NMatches;                         /* no. of matches */
    time_t Begin, End;                    /* timer statistics */
    int i, j, k;

    printf ("UnJumble, Copyright (C) 2001 A.Sankaranarayanan.\n");
    printf ("UnJumble is distributed under the GNU GPL.\n\n");

    if (argc < 2) {                       /* not enough arguments */
        printf ("unjumble <jumbled-word>\n");
        exit (TOO_FEW_ARGUMENTS);
    }
                                          /* open dictionary */
    if ((WordBase = fopen (WORDBASE_NAME, "rt")) == NULL) {
        printf ("Unable to access word base <%s>.\n", WORDBASE_NAME);
        exit (INVALID_WORDBASE);
    }
                                          /* get word length */
    if ((WordLength = strlen (argv[1])) > MAX_WORD_LEN) {
        printf ("Jumbled word is too long.\n");
        exit (WORD_TOO_LONG);
    }

    printf ("Thinking, please wait...\n\n");
    Begin = time (NULL);                  /* record time at start */

    LetterList = (Letter *) malloc (WordLength * sizeof (Letter));
    Solution[WordLength] = '\0';          /* null terminate in advance */

    for (i = 0; i < WordLength; ++i) {    /* initialize Letter nodes */
        LetterList[i].LetterData = tolower (argv[1][i]);
        LetterList[i].Visited = FALSE;
        LetterList[i].Link =
                (Letter **) malloc ((WordLength - 1) * sizeof (Letter *));
        for (j = k = 0; j < WordLength; ++j) {
            if (i != j) {
                LetterList[i].Link[k++] = &LetterList[j];
            }
        }
    }

    for (i = 0; i < WordLength; ++i) {    /* for each Letter node */
        RideLetterList (&LetterList[i],   /* follow links recursively */
                    Solution, 0, WordLength);
    }

    NMatches = ProcessWord (NULL);
    End = time (NULL);                    /* record time of termination */

    if (NMatches > 0) {                   /* matches found? */
        printf ("\n%d match(es) in %ld second(s).\n",
                NMatches, (End - Begin)); /* yes, show details */
    }
    else {                                /* sorry, no matches */
        printf ("No matches in word base!\n");
    }

    for (i = 0; i < (WordLength - 1); ++i) {
        free (LetterList[i].Link);
    }

    free (LetterList);                    /* deallocate buffers */
    fclose (WordBase);                    /* shut word base */
    return (NORMAL_SHUTDOWN);             /* everything OK */
}
