import time
import os
import psutil

def check_cpu_memory():

    pid = os.getpid()
    py = psutil.Process(pid)

    memory_usage = round(py.memory_info()[0] / 2.**30, 2)
    print("memory usage :", memory_usage, "%")

def malloc_300M():

    print("Python_memory_allocation")
    print("data type: list")
    print("data size: 100000000")

    y = []
    for i in range(100000000):
     y.append(i)

    check_cpu_memory()

if __name__ == '__main__':
    import multiprocessing
    
    starttime = time.time()

    processes = []

    for i in range(3):
        p = multiprocessing.Process(target=malloc_300M)
        p.start()
        processes.append(p)

    for process in processes:
        process.join()

    endtime = time.time()
    print("process time :", endtime - starttime)
    
