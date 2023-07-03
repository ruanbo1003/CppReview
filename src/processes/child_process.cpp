//
// Created by 阮波 on 2023/6/30.
//

#include <unistd.h>     // fork(), sleep()
#include <sys/wait.h>   // wait()
#include <errno.h>      // EAGAIN
#include <iostream>

using std::cout, std::endl;


namespace processes {

/*
 * one child process: wait, waitpid
 * https://man7.org/linux/man-pages/man2/wait.2.html
 */
void one_child_process() {
    pid_t pid = fork();
    if(pid == 0) {
        // child process
        pid_t self_id = getpid();  // get self process-id
        pid_t parent_id = getppid();  // get parent's process-id
        cout << "(child) self pid:" << self_id << ", " << "parent pid:" << parent_id << endl;

        sleep(3);
    } else {
        // parent process

        pid_t self_id = getpid();  // get self process-id
        pid_t parent_id = getppid();  // get parent's process-id
        cout << "(parent) self pid:" << self_id << ", " << "parent pid:" << parent_id << endl;

        // wait
        if(false)
        {
            int wstatus;

            /*
             * `wait` is blocking. Suspends the current thread until one of its children terminates.
             *  when child process exit, the wait_pid is the child process-id.
             *
             *  return value of wait():
             *      success : the process-id of the terminated child
             *      failure : -1
             */
            pid_t wait_pid = wait(&wstatus);   // equals to waitpid(-1, &wstatus, 0);
            cout << "child terminate pid:" << wait_pid << "(" << wstatus << ")" << endl;
        }

        // waitpid
        if(false)
        {
            //
            int wstatus;
            /*
             * function: pid_t waitpid(pid_t pid, int * wstatus, int options);
             * the parameter pid is -1, means wait for any child process
             */
            pid_t wait_pid = waitpid(-1, &wstatus, 0);
            cout << "child terminate pid:" << wait_pid << "(" << wstatus << ")" << endl;
        }

        // waitpid with options
        if(true)
        {
            int wstatus;

            while (true) {
                cout << "parent ..." << endl;

                /*
                 * waitpid() on success value: the process-id of the child whose state has changed.
                 *
                 * waitpid() return value with WNOHANG option:
                 *   0 : children process specified by pid have not changed
                 *  -1 : failure
                 */
                pid_t wait_pid = waitpid(-1, &wstatus, WNOHANG);
                cout << wait_pid << ", " << wstatus << endl;

                sleep(1);
            }

        }

    }
}


void child_process() {

    one_child_process();


}


}  // end of namespace
