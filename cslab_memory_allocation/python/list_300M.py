import time
import os
import psutil


def check_cpu_memory():

    pid = os.getpid()
    py = psutil.Process(pid)

    memory_usage = round(py.memory_info()[0]*10 / 2.**30, 2)
    print("memory usage :", memory_usage, "%")

def malloc_300M():

    print("PYTHON_MEMORY_ALLOCATION")
    print("data type: list")
    print("data size: 300000000")

    y = []
    for i in range(300000000):
     y.append(i)

    check_cpu_memory()

if __name__ == '__main__':
    
    starttime = time.time()

    malloc_300M()

    endtime = time.time()

    print("process time :", endtime - starttime)
