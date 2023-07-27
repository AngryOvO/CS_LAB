import time
import os
import psutil

def check_cpu_memory():

    pid = os.getpid()
    py = psutil.Process(pid)

    memory_usage = round(py.memory_info()[0] / 2.**30, 2)
    print("memory usage :", memory_usage, "%")


print("Python_memory_allocation")
print("data type: list")
print("data size: 1000000")

starttime = time.time()

y = []
for i in range(1000000):
    y.append(i)

endtime = time.time()
print("process time :", endtime - starttime)

check_cpu_memory()
