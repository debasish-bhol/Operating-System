#include<stdio.h>
#include<pthread.h>

void writer();
void reader();

pthread_mutex_t m_reader, m_writer;

int maain() {
pthread_mutex_init(&m_reader, NULL);
pthread_mutex_init(&m_writer, NULL);


}

void reader() {
pthread_mutex_lock(&m_reader);



pthread_mutex_unlock(&m_reader);
}

void writer() {
pthread_mutex_lock(&m_writer);


pthread_mutex_unlock(&m_writer);
}