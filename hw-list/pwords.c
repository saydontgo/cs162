/*
 * Word count application with one thread per input file.
 *
 * You may modify this file in any way you like, and are expected to modify it.
 * Your solution must read each input file from a separate thread. We encourage
 * you to make as few changes as necessary.
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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>

#include "word_count.h"
#include "word_helpers.h"
#define MAX_THREAD 64
typedef struct pa{
  word_count_list_t*word_counts;
  char*filename;
  int tid;//用于调试
}passing_argv;

void* threadfun(void*arg)
{
  passing_argv *p=arg;
  FILE *f;
  f = fopen(p->filename,"r");
  if(!f)
  {
        printf("%s文件无法打开\n",p->filename);
        exit(-1);
  }
  pthread_mutex_lock(&p->word_counts->lock);
  count_words(p->word_counts,f);
  pthread_mutex_unlock(&p->word_counts->lock);
  fclose(f);
  pthread_exit(NULL);
}


/*
 * main - handle command line, spawning one thread per file.
 */
int main(int argc, char* argv[]) {
  /* Create the empty data structure. */
  word_count_list_t *word_counts=malloc(sizeof(word_count_list_t));
  init_words(word_counts);
  pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
  word_counts->lock=lock;

  if (argc <= 1) {
    /* Process stdin in a single thread. */
    count_words(word_counts, stdin);
  } else {
    /* TODO */
    pthread_t threads[MAX_THREAD];
    passing_argv*tmp[MAX_THREAD];
    for(int i=1;i<argc;i++)
    {
      
      tmp[i]=malloc(sizeof(passing_argv));
      tmp[i]->filename=argv[i];
      tmp[i]->word_counts=word_counts;

      //调试信息
      tmp[i]->tid=i;

      int rc = pthread_create(&threads[i], NULL, threadfun, (void*)tmp[i]);
      if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
      }
    }

    for(int i=1;i<argc;i++)
    {        
      pthread_join(threads[i],NULL);
      free(tmp[i]);
    }
  }

  /* Output final result of all threads' work. */
  wordcount_sort(word_counts, less_count);
  fprint_words(word_counts, stdout);
  free(word_counts);
  return 0;
}
