#include<stdio.h>
#include<pthread.h>

int read_count = 0;
int data = 1;

void *writer(void*);
void *reader(void*);

pthread_mutex_t m_reader, m_writer;

int main() {
int nReader, nWriter, i;

pthread_mutex_init(&m_reader, NULL);
pthread_mutex_init(&m_writer, NULL);

printf("\nEnter total number of reader: ");
scanf("%d", &nReader);

printf("\nEnter total number of writer: ");
scanf("%d", &nWriter);

pthread_t nReaderThread[nReader], nWriterThread[nWriter];

for(i=0; i < nReader; i++)
pthread_create(&nReaderThread[i], NULL, reader, (void *)i);

for(i=0; i < nWriter; i++)
pthread_create(&nWriterThread[i], NULL, writer, (void *)i);

for(i=0; i < nReader; i++)
pthread_join(nReaderThread[i], NULL);

for(i=0; i < nWriter; i++)
pthread_join(nWriterThread[i], NULL);

}

void *reader(void *a) {
int p = (int)a + 1;
printf("\nReader %d is trying to read", p);
pthread_mutex_lock(&m_reader);
read_count++;
if(read_count == 1) {
	pthread_mutex_lock(&m_writer);
	//printf("\n\nReader %d is reading data and data value is:\t\t%d\n", p, data);
	printf("\n\nThe value read by reader %d is \t\t%d\n", p, data);
	//printf("Total number of reader reading is %d", read_count);
}
pthread_mutex_unlock(&m_reader);

printf("\nNumber of reader present is: %d", read_count);

//pthread_mutex_lock(&m_reader);
read_count--;
if(read_count == 0) {
	printf("\nReader %d completed his work", p);
	pthread_mutex_unlock(&m_writer);
}

pthread_mutex_unlock(&m_reader);
}

void *writer(void *a) {
int p = (int)a + 1;
printf("\nWriter %d is trying to update data", p);
pthread_mutex_lock(&m_writer);
printf("\nWriter %d is updating data", p);
data++;
printf("\nWriter %d updated the data to:\t\t%d", p, data);

pthread_mutex_unlock(&m_writer);
}
