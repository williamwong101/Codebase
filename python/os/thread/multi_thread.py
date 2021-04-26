from threading import Thread
import time


def func(name, iteration, sleep_sec):
    for i in range(iteration):
        print(name)
        time.sleep(sleep_sec)


def main():
    base_iteration = 100
    thread_pool = []
    for i in [1,2,4]:
        thread = Thread(target=func, args=('func_' + str(i), base_iteration // i, i, ))
        thread_pool.append(thread)
        thread.start()
    print("[main thread], started in thread pool:")
    print('[main thread], joining other thread')
    for thread in thread_pool:
        thread.join()
    print("[main thread], other thread join, all exit")


if __name__ == '__main__':
    main()