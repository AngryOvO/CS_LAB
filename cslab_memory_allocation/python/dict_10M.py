import time
import os
import psutil

def check_cpu_memory():

    pid = os.getpid()
    py = psutil.Process(pid)

    memory_usage = round(py.memory_info()[0] / 2.**30, 2)
    print("memory usage :", memory_usage, "%")


print("Python_memory_allocation")
print("data type: Dictionary")
print("data size: 10000000")

starttime = time.time()

y = {}
for i in range(10000000):
    y[f"{i}"] = i

endtime = time.time()
print("process time :", endtime - starttime)

check_cpu_memory()
