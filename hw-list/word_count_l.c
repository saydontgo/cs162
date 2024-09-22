/*
 * Implementation of the word_count interface using Pintos lists.
 *
 * You may modify this file, and are expected to modify it.
 */

/*
 * Copyright © 2021 University of California, Berkeley
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef PINTOS_LIST
#error "PINTOS_LIST must be #define'd when compiling word_count_l.c"
#endif

#include "word_count.h"


void init_words(word_count_list_t* wclist) { /* TODO */
  list_init(wclist);
}

size_t len_words(word_count_list_t* wclist) {
  /* TODO */
  return list_size(wclist);
}

word_count_t* find_word(word_count_list_t* wclist, char* word) {
  /* TODO */
  struct list_elem *e;

  for(e=list_begin(wclist);e!=list_tail(wclist);e=list_next(e))
  {
    word_count_t* tmp=list_entry(e,word_count_t,elem);
    if(strcmp(tmp->word,word)==0)
    return list_entry(e,word_count_t,elem);
  }
  return NULL;
}

word_count_t* add_word(word_count_list_t* wclist, char* word) {
  /* TODO */
  struct list_elem *e;

  for(e=list_begin(wclist);e!=list_tail(wclist);e=list_next(e))
  {
    word_count_t* tmp=list_entry(e,word_count_t,elem);
    if(strcmp(tmp->word,word)==0)
    {
      tmp->count++;
      break;
    }
  }
  if(e!=list_tail(wclist))return list_entry(e,word_count_t,elem);

  word_count_t *new_entry=(word_count_t*)malloc(sizeof(word_count_t));
  new_entry->word=word;
  new_entry->count=1;
  list_push_back(wclist,&(new_entry->elem));
  
  return new_entry;
}

void fprint_words(word_count_list_t* wclist, FILE* outfile) { /* TODO */
  if(!outfile)
  {
    printf("文件尚未打开\n");
    return;
  }
  if(wclist==NULL)
  {
    printf("list为空\n");
    return;
  }
  struct list_elem*e;
  for(e=list_begin(wclist);e!=list_end(wclist);e=list_next(e))
  {
    word_count_t* tmp=list_entry(e,word_count_t,elem);
    fprintf(outfile,"%8d\t%s\n",tmp->count,tmp->word);
  }
}

static bool less_list(const struct list_elem* ewc1, const struct list_elem* ewc2, void* aux) {
  /* TODO */ 
  word_count_t*e1=list_entry(ewc1,word_count_t,elem);
  word_count_t*e2=list_entry(ewc2,word_count_t,elem);
  if(e1->count!=e2->count)return e1->count<e2->count;
  if(strcmp(e1->word,e2->word)>0)return false;
  return true;
}


void wordcount_sort(word_count_list_t* wclist,
                    bool less(const word_count_t*, const word_count_t*)) {
  list_sort(wclist, less_list, less);
}



