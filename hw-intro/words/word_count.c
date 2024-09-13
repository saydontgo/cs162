/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utilities */

char *new_string(char *str) {
  char *new_str = (char *) malloc(strlen(str) + 1);
  if (new_str == NULL) {
    return NULL;
  }
  return strcpy(new_str, str);
}

int init_words(WordCount **wclist) {
  /*
     Initialize word count.
     Returns 0 if no errors are encountered
     in the body of this function; 1 otherwise.
  */
  *wclist = NULL;
  return 0;
}

size_t len_words(WordCount *wchead) {
  /* Return -1 if any errors are
     encountered in the body of
     this function.
  */
    size_t len = 1;
    if(wchead==NULL)
    return 0;
    WordCount* travel=wchead;
    while(travel->next!=NULL)
    {
      len++;
      travel=travel->next;
    }
    return len;
}

WordCount *find_word(WordCount *wchead, char *word) {
  /* Return count for word, if it exists */
  WordCount *wc = NULL;
  WordCount* travel=wchead;
  while(travel!=NULL)
  {
     if(strcmp(travel->word,word)==0)
     {
      wc=travel;
      break;
     }
     travel=travel->next;
  }
  return wc;
}

int add_word(WordCount **wclist, char *word) {
  /* If word is present in word_counts list, increment the count.
     Otherwise insert with count 1.
     Returns 0 if no errors are encountered in the body of this function; 1 otherwise.
  */
 int word_count=len_words(*wclist);
 if(word_count==0)
 {
   *wclist=(WordCount*)malloc(sizeof(char*)+sizeof(int)+sizeof(WordCount*));
   if(*wclist==NULL)
   return 1;
   (*wclist)->count=1;
   (*wclist)->word=new_string(word);
   (*wclist)->next=NULL;
   return 0;
 }
 WordCount* travel=*wclist;
 WordCount* prev_travel;
 while(travel!=NULL)
 {
    if(strcmp(travel->word,word)==0)
     {
      break;
     }
     prev_travel=travel;
     travel=travel->next;
 }
 if(travel==NULL)
 {
   prev_travel->next=(WordCount*)malloc(sizeof(char*)+sizeof(int)+sizeof(WordCount*));
   if(prev_travel->next==NULL)
   return 1;
   (prev_travel->next)->count=1;
   (prev_travel->next)->word=new_string(word);
   (prev_travel->next)->next=NULL;
 }
 else travel->count++;
 return 0;
}

void fprint_words(WordCount *wchead, FILE *ofile) {
  /* print word counts to a file */
  WordCount *wc;
  for (wc = wchead; wc; wc = wc->next) {
    fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
  }
}


