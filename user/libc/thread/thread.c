#include <thread.h>
#include <stdio.h>

/* 
 * \brief Creates a new thread.   
 *
 * \param[out] thread   The handle to the newly created thread.  
 * \param[in]  func	The function that the new thread shall execute.
 * \param[in]  arg	The argumet that is passed to the function when is executed.
 *
 * \return 		0 if successful, otherwise an error code:
 *			ERR_INSUFFICIENT_RESOURCES if there are not enough resources
 *						    available to create the thread.
 *			ERR_INVALID_ARGUMENTS      if any of the arguments passed are not valid.		
 */
int thread_create(thread_t *thread, void *(*func)(void*), void *arg)
{
   long error = __syscall2(SYSCALL_THREAD_CREATE, (long) thread, (long) (*func)(void*), (long) arg);
   return error;
}

/* 
 * \brief Exits the currently running thread.
 * 
 * \param[in] result	The return value that is passed to any thread that is 
 *                       trying to join on this thread.
 */
void thread_exit(void* result) {
    long error = __syscall1(SYSCALL_THREAD_EXIT, (long) result);
    return error;
} 

/*
 * \brief Joins a running thread. The calling thread will be suspended 
 *  	   until the target thread has terminated. If the target thread has already
 *	   terminated or the thread handle is invalid, the function returns
 *	   an error code.
 *
 * \param[in]  thread	The handle to the target thread.
 * \param[out] result	Address of the variable to receive the thread's
 * 			exit value.		
 * 
 * \return 		0 if successful, otherwise an error code:
 *			ERR_INVALID_THREAD if the thread handle does not map to a valid thread.
 *			ERR_THREAD_TERMINATED if the thread has already terminated.
 *			 The exit value must still be returned correctly.
 */
int thread_join(thread_t thread, void **result)
{
    long error = __syscall2(SYSCALL_THREAD_JOIN, (long) &thread, (long) *result);
    return error;
}

/*
 * \brief Get the identifier of a thread.
 *
 * \param[in] thread    The handle to the thread.
 * 
 * \return		a unique identifier (larger than 1) if successful, otherwise an error code:
 *                      ERR_INVALID_THREAD if the thread handle does not map to a valid thread.
 *                      ERR_THREAD_TERMINATED if the thread has already terminated.
 */
int thread_get_id(thread_t thread) 
{
    long error = __syscall1(SYSCALL_THREAD_GET_ID, (long) &thread);
    return error;
}

/*
 * \brief Get the thread handle for the currently running thread.
 *
 * \return 		The thread handle of the currently running thread.
 */
thread_t thread_self(void)
{
    long error = __syscall1(SYSCALL_THREAD_SELF);
    return error;
}
